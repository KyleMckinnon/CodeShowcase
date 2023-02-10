#include "Bullet.h"
#include "Maths.h"
#include "Player.h"
//#include "NPC.h"
#include "Timing.h"
#include "InputState.h"
#include "InputMemoryBitStream.h"
#include "OutputMemoryBitStream.h"
using namespace std;

Bullet::Bullet() :
	mVelocity(Vector3::Zero),
	mMaxLinearSpeed(50.f),
	mMaxRotationSpeed(5.f),
	mWallRestitution(0.1f),
	mNPCRestitution(0.1f),
	mBulletId(0),
	mLastMoveTimestamp(0.0f),
	mThrustDir(0.f),
	mSpeed(6)


{
	SetScale(GetScale() * 0.5f);
	SetCollisionRadius( 0.5f );
}



void Bullet::Update()
{
	

	timeDelta = Timing::sInstance.GetDeltaTime();

	SetLocation(GetLocation() + mVelocity * timeDelta);

	ProcessCollisions();

	
}

void Bullet::InitFromShooter(Player *shooter)
{

	SetPlayerId(shooter->GetPlayerId());
	
	Vector3 forward = shooter->GetForwardVector();
	Vector3 location = shooter->GetLocation();

	forward *= 1.2f;

	location = forward + location;
	SetVelocity(forward * mSpeed);
	SetLocation(location);
	

	SetRotation(shooter->GetRotation());
	
	
}
bool Bullet::HandleCollisionWithPlayer(Player* inPlayer)
{
	(void)inPlayer;



	//hit cat



	return false;
}
void Bullet::ProcessCollisions()
{
	float sourceRadius = GetCollisionRadius();
	Vector3 sourceLocation = GetLocation();

	///now let's iterate through the world and see what we hit...
	///note: since there's a small number of objects in our game, this is fine.
	///but in a real game, brute-force checking collisions against every other object is not efficient.
	///it would be preferable to use a quad tree or some other structure to minimize the
	///number of collisions that need to be tested.
	for (auto goIt = World::sInstance->GetGameObjects().begin(), end = World::sInstance->GetGameObjects().end(); goIt != end; ++goIt)
	{
		GameObject* target = goIt->get();
		if (target != this && !target->DoesWantToDie())
		{
			//simple collision test for spheres- are the radii summed less than the distance?
			Vector3 targetLocation = target->GetLocation();
			float targetRadius = target->GetCollisionRadius();

			Vector3 delta = targetLocation - sourceLocation;
			float distSq = delta.LengthSq2D();
			float collisionDist = (sourceRadius + targetRadius);
			if (distSq < (collisionDist * collisionDist))
			{
				//first, tell the other guy there was a collision with a player, so it can do something...
				Player* player = dynamic_cast<Player*>(target);
				/*NPC* npc = dynamic_cast<NPC*>(target);*/

				if (!player)
				{
					this->SetDoesWantToDie(true);
				}
			
			}
		}
	}
}

void Bullet::ProcessCollisionsWithScreenWalls()
{
	Vector3 location = GetLocation();
	float x = location.mX;
	float y = location.mY;

	float vx = mVelocity.mX;
	float vy = mVelocity.mY;

	float radius = GetCollisionRadius();

	//if the cat collides against a wall, the quick solution is to push it off
	/*if( ( y + radius ) >= HALF_WORLD_HEIGHT && vy > 0 )
	{
		mVelocity.mY = -vy * mWallRestitution;
		location.mY = HALF_WORLD_HEIGHT - radius;
		SetLocation( location );
	}
	else if( y <= ( -HALF_WORLD_HEIGHT - radius ) && vy < 0 )
	{
		mVelocity.mY = -vy * mWallRestitution;
		location.mY = -HALF_WORLD_HEIGHT - radius;
		SetLocation( location );
	}

	if( ( x + radius ) >= HALF_WORLD_WIDTH && vx > 0 )
	{
		mVelocity.mX = -vx * mWallRestitution;
		location.mX = HALF_WORLD_WIDTH - radius;
		SetLocation( location );
	}
	else if(  x <= ( -HALF_WORLD_WIDTH - radius ) && vx < 0 )
	{
		mVelocity.mX = -vx * mWallRestitution;
		location.mX = -HALF_WORLD_WIDTH - radius;
		SetLocation( location );
	}*/
}

uint32_t Bullet::Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const
{
	uint32_t writtenState = 0;

	if( inDirtyState & ECRS_BulletId )
	{
		inOutputStream.Write( (bool)true );
		inOutputStream.Write( GetBulletId() );

		writtenState |= ECRS_BulletId;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}


	if( inDirtyState & ECRS_Pose )
	{
		inOutputStream.Write( (bool)true );

		Vector3 velocity = mVelocity;
		inOutputStream.Write( velocity.mX );
		inOutputStream.Write( velocity.mY );

		Vector3 location = GetLocation();
		inOutputStream.Write( location.mX );
		inOutputStream.Write( location.mY );

		inOutputStream.Write( GetRotation() );

		writtenState |= ECRS_Pose;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}

	//always write mThrustDir- it's just two bits
	if( mThrustDir != 0.f )
	{
		inOutputStream.Write( true );
		inOutputStream.Write( mThrustDir > 0.f );
	}
	else
	{
		inOutputStream.Write( false );
	}

	if( inDirtyState & ECRS_Color )
	{
		inOutputStream.Write( (bool)true );
		inOutputStream.Write( GetColor() );

		writtenState |= ECRS_Color;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}

	if( inDirtyState & ECRS_Health )
	{
		inOutputStream.Write( (bool)true );
		

		writtenState |= ECRS_Health;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}

	return writtenState;
}

bool Bullet::operator==(Bullet &other)
{
	// Game Object Part.
	//Call the == of the base, Bullet reference is
	//downcast explicitly.
	if(!GameObject::operator==(other)) return false;

	if(this->ECRS_AllState != other.ECRS_AllState) return false;

	if (!Maths::Is3DVectorEqual(this->mVelocity, other.mVelocity)) return false;
	if (!Maths::FP_EQUAL(this->mMaxLinearSpeed, other.mMaxLinearSpeed)) return false;
	if (!Maths::FP_EQUAL(this->mMaxRotationSpeed, other.mMaxRotationSpeed)) return false;
	if (!Maths::FP_EQUAL(this->mWallRestitution, other.mWallRestitution)) return false;
	if (!Maths::FP_EQUAL(this->mNPCRestitution, other.mNPCRestitution)) return false;
	if(this->mBulletId != other.mBulletId) return false;

	if (!Maths::FP_EQUAL(this->mLastMoveTimestamp, other.mLastMoveTimestamp)) return false;
	if (!Maths::FP_EQUAL(this->mThrustDir, other.mThrustDir)) return false;

	return true;
}
