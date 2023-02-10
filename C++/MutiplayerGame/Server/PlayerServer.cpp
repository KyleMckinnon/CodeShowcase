#include "PlayerServer.h"
#include "ClientProxy.h"
#include "Timing.h"
#include "MoveList.h"
#include "Maths.h"
#include "Bullet.h"
#include "Server.h"
#include "GameObjectRegistry.h"
using namespace std;
PlayerServer::PlayerServer() :
	mPlayerControlType( ESCT_Human ),
	mTimeOfNextShot( 0.f ),
	mTimeBetweenShots( 0.2f )
{}

void PlayerServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject( this );
	cout << "Player Died" << endl;
}

void PlayerServer::Update()
{
	Player::Update();

	Vector3 position = GetLocation();

	if (mPlayerControlType == EPlayerControlType::ESCT_Human) 
	{
		PlayerMovementUpdate();
	}
	else
	{
		if (mPlayerControlType == EPlayerControlType::ESCT_AI)
		{
			NPCUpdate();
		}
	}
}

void PlayerServer::NPCUpdate()
{
	Vector3 oldLocation = GetLocation();
	Vector3 oldVelocity = GetVelocity();
	float oldRotation = GetRotation();

	Vector3 newVelocity;
	newVelocity = Vector3::Zero;

	PlayerPtr player = nullptr;
	player = static_cast<Server*> (Engine::sInstance.get())->FollowPlayer(GetLocation(), this->GetPlayerId());
	float deltaTime = Timing::sInstance.GetDeltaTime();

	if (player != NULL)
	{
		
		Vector3 DistanceToPlayer = player->GetLocation() - GetLocation();
		Vector3 ahead = GetForwardVector();
		DistanceToPlayer.Normalize2D();
		ahead.Normalize2D();


		float angleOfNPC = std::acos(Dot2D(ahead, DistanceToPlayer));

		float newRotation = GetRotation() + (angleOfNPC * this->GetMaxRotationSpeed() * deltaTime);
		SetRotation(newRotation);


		float inputForwardDelta = 1.0f;
		mThrustDir = inputForwardDelta;

		SetVelocity(DistanceToPlayer);

		SimulateMovement(deltaTime);

		if (!Maths::Is2DVectorEqual(oldLocation, GetLocation()) || !Maths::Is2DVectorEqual(oldVelocity, GetVelocity()) || oldRotation != GetRotation())
		{
			NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ECRS_Pose);
		}
	}
}
void PlayerServer::PlayerMovementUpdate()
{

	Vector3 oldPlayerLocation = GetLocation();
	Vector3 oldPlayerVelocity = GetVelocity();
	float oldPlayerRotation = GetRotation();

	ClientProxyPtr client = NetworkManagerServer::sInstance->GetClientProxy(GetPlayerId());
	if (client)
	{
		MoveList& moveList = client->GetUnprocessedMoveList();
		for (const Move& unprocessedMove : moveList)
		{
			const InputState& currentState = unprocessedMove.GetInputState();
			float deltaTime = unprocessedMove.GetDeltaTime();
			ProcessInput(deltaTime, currentState);
			SimulateMovement(deltaTime);
		}

		moveList.Clear();
	}

	HandleShooting();

	if (!Maths::Is2DVectorEqual(oldPlayerLocation, GetLocation()) ||
		!Maths::Is2DVectorEqual(oldPlayerVelocity, GetVelocity()) ||
		oldPlayerRotation != GetRotation())
	{
		NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ECRS_Pose);
	}
}
bool PlayerServer::HandleCollisionWithPlayer(Player* inPlayer)
{
	int myPlayerID = GetPlayerId();
	int otherPlayerID = inPlayer->GetPlayerId();

	if (myPlayerID == 0)
	{
		//TakeDamage(otherPlayerID);
	}
	else
	{
		TakeDamage(otherPlayerID);
		cout << "Taking Damage" << endl;
	}

	return true;
}
void PlayerServer::HandleShooting()
{
	float time = Timing::sInstance.GetFrameStartTime();
	if( mIsShooting && Timing::sInstance.GetFrameStartTime() > mTimeOfNextShot )
	{
		//not exact, but okay
		mTimeOfNextShot = time + mTimeBetweenShots;

		//fire!
		BulletPtr bullet = std::static_pointer_cast< Bullet >( GameObjectRegistry::sInstance->CreateGameObject( 'YARN' ) );
		bullet->InitFromShooter( this );
	}
}

void PlayerServer::TakeDamage( int inDamagingPlayerId )
{
	mHealth--;
	if( mHealth <= 0.f )
	{
		//score one for damaging player...
		//ScoreBoardManager::sInstance->IncScore( inDamagingPlayerId, 1 );

		//and you want to die
		SetDoesWantToDie( true );

		//tell the client proxy to make you a new cat
		ClientProxyPtr clientProxy = NetworkManagerServer::sInstance->GetClientProxy( GetPlayerId() );
		if( clientProxy )
		{
			clientProxy->HandlePlayerDied();
			
		}

		cout << "Player Died" << endl;


	}

	//tell the world our health dropped
	NetworkManagerServer::sInstance->SetStateDirty( GetNetworkId(), ECRS_Health );
	cout << "hp dropped" << endl;
}
