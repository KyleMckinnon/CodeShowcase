//#include "NPCServer.h"
//#include "ClientProxy.h"
//#include "Timing.h"
//#include "MoveList.h"
//#include "Maths.h"
//#include "Bullet.h"
//#include "GameObjectRegistry.h"
//#include "PlayerServer.h"
//
//NPCServer::NPCServer() :
//	mNPCControlType( ESCT_AI )
//	//mTimeOfNextShot( 0.f ),
//	//mTimeBetweenShots( 0.2f )
//{
//}
//
//void NPCServer::HandleDying()
//{
//	NetworkManagerServer::sInstance->UnregisterGameObject( this );
//}
//
//void NPCServer::Update()
//{
//	NPC::Update();
//
//
//	Vector3 oldLocation = GetLocation();
//	Vector3 oldVelocity = GetVelocity();
//	float oldRotation = GetRotation();
//
//	ClientProxyPtr client = NetworkManagerServer::sInstance->GetClientProxy( GetNPCId() );
//	if( client )
//	{
//		MoveList& moveList = client->GetUnprocessedMoveList();
//		for( const Move& unprocessedMove : moveList )
//		{
//			const InputState& currentState = unprocessedMove.GetInputState();
//			float deltaTime = unprocessedMove.GetDeltaTime();
//			
//			SimulateMovement( deltaTime );
//		}
//
//		moveList.Clear();
//	}
//
//	/*HandleShooting();*/
//
//	if( !Maths::Is2DVectorEqual( oldLocation, GetLocation() ) ||
//		!Maths::Is2DVectorEqual( oldVelocity, GetVelocity() ) ||
//		oldRotation != GetRotation() )
//	{
//		NetworkManagerServer::sInstance->SetStateDirty( GetNetworkId(), ECRS_Pose );
//	}
//}
//
////void NPCServer::HandleShooting()
////{
////	float time = Timing::sInstance.GetFrameStartTime();
////	if( mIsShooting && Timing::sInstance.GetFrameStartTime() > mTimeOfNextShot )
////	{
////		//not exact, but okay
////		mTimeOfNextShot = time + mTimeBetweenShots;
////
////		//fire!
////		/*BulletPtr bullet = std::static_pointer_cast< Bullet >( GameObjectRegistry::sInstance->CreateGameObject( 'YARN' ) );
////		bullet->InitFromShooter( this );*/
////	}
////}
//bool NPCServer::HandleCollisionWithNPC(NPC* inNPC)
//{
//	int myNPCID = GetNPCId();
//	int otherNPCID = inNPC->GetNPCId();
//
//	if (myNPCID == 0)
//	{
//		TakeDamage(otherNPCID);
//	}
//
//	else
//	{
//		TakeDamage(otherNPCID);
//	}
//
//	return true;
//}
//void NPCServer::TakeDamage( int inDamagingNPCId )
//{
//	mHealth--;
//	if( mHealth <= 0.f )
//	{
//		//score one for damaging player...
//		//ScoreBoardManager::sInstance->IncScore( inDamagingPlayerId, 1 );
//
//		//and you want to die
//		SetDoesWantToDie( true );
//
//		//tell the client proxy to make you a new cat
//	/*	ClientProxyPtr clientProxy = NetworkManagerServer::sInstance->GetClientProxy( GetPlayerId() );
//		if( clientProxy )
//		{
//			clientProxy->HandleNPCDied();
//		}*/
//	}
//
//	//tell the world our health dropped
//	NetworkManagerServer::sInstance->SetStateDirty( GetNetworkId(), ECRS_Health );
//}
