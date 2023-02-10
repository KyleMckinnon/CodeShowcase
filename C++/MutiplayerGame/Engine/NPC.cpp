//#include "NPC.h"
//#include "Maths.h"
//#include "InputState.h"
//#include "InputMemoryBitStream.h"
//#include "OutputMemoryBitStream.h"
//
////zoom hardcoded at 100...if we want to lock NPCs on screen, this could be calculated from zoom
//const float HALF_WORLD_HEIGHT = 3.6f;
//const float HALF_WORLD_WIDTH = 6.4f;
//
//NPC::NPC() :
//	GameObject(),
//	mVelocity( Vector3::Zero ),
//	mMaxLinearSpeed( 50.f ),
//	mMaxRotationSpeed( 5.f ),
//	mWallRestitution( 0.1f ),
//	mNPCRestitution( 0.1f ),
//	mNPCId( 0 ),
//	mLastMoveTimestamp ( 0.0f ),
//	mThrustDir( 0.f ),
//	mHealth( 1 ),
//	mSpeed(5),
//	mIsShooting( false )
//
//{
//	SetCollisionRadius( 0.5f );
//}
//
//void NPC::AdjustVelocityByThrust( float inDeltaTime )
//{
//	//just set the velocity based on the thrust direction -- no thrust will lead to 0 velocity
//	//simulating acceleration makes the client prediction a bit more complex
//	Vector3 forwardVector = GetForwardVector();
//	mVelocity = forwardVector * ( mThrustDir * inDeltaTime * mMaxLinearSpeed );
//}
//
//void NPC::SimulateMovement( float inDeltaTime )
//{
//	//simulate us...
//	AdjustVelocityByThrust( inDeltaTime );
//
//	SetLocation( GetLocation() + mVelocity * inDeltaTime );
//
//	ProcessCollisions();
//}
//void NPC::Update()
//{
//	CheckForTarget();
//}
//void NPC::CheckForTarget()
//{
//	Vector3 forward = GetForwardVector();
//	Vector3 location = GetLocation();
//
//	forward *= 1.0f;
//
//	location = forward + location;
//	SetVelocity(forward * mSpeed);
//	//SetLocation(location);
//}
//void NPC::SetTarget(Player* target)
//{
//	m_target = target;
//}
//void NPC::ProcessCollisions()
//{
//	//right now just bounce off the sides..
//	ProcessCollisionsWithScreenWalls();
//
//	float sourceRadius = GetCollisionRadius();
//	Vector3 sourceLocation = GetLocation();
//
//	//now let's iterate through the world and see what we hit...
//	//note: since there's a small number of objects in our game, this is fine.
//	//but in a real game, brute-force checking collisions against every other object is not efficient.
//	//it would be preferable to use a quad tree or some other structure to minimize the
//	//number of collisions that need to be tested.
//	for( auto goIt = World::sInstance->GetGameObjects().begin(), end = World::sInstance->GetGameObjects().end(); goIt != end; ++goIt )
//	{
//		GameObject* target = goIt->get();
//		if( target != this && !target->DoesWantToDie() )
//		{
//			//simple collision test for spheres- are the radii summed less than the distance?
//			Vector3 targetLocation = target->GetLocation();
//			float targetRadius = target->GetCollisionRadius();
//
//			Vector3 delta = targetLocation - sourceLocation;
//			float distSq = delta.LengthSq2D();
//			float collisionDist = ( sourceRadius + targetRadius );
//			if( distSq < ( collisionDist * collisionDist ) )
//			{
//				//first, tell the other guy there was a collision with a NPC, so it can do something...
//
//				if( target->HandleCollisionWithNPC( this ) )
//				{
//					//okay, you hit something!
//					//so, project your location far enough that you're not colliding
//					Vector3 dirToTarget = delta;
//					dirToTarget.Normalize2D();
//					Vector3 acceptableDeltaFromSourceToTarget = dirToTarget * collisionDist;
//					//important note- we only move this cat. the other cat can take care of moving itself
//					SetLocation( targetLocation - acceptableDeltaFromSourceToTarget );
//
//
//					Vector3 relVel = mVelocity;
//
//					//if other object is another NPC, it might have velocity, so there might be relative velocity...
//					NPC* otherNPC = dynamic_cast<NPC*>(target);
//					if( otherNPC )
//					{
//						relVel -= otherNPC->mVelocity;
//					}
//
//					//got vel with dir between objects to figure out if they're moving towards each other
//					//and if so, the magnitude of the impulse ( since they're both just balls )
//					float relVelDotDir = Dot2D( relVel, dirToTarget );
//
//					if (relVelDotDir > 0.f)
//					{
//						Vector3 impulse = relVelDotDir * dirToTarget;
//
//						if( otherNPC )
//						{
//							mVelocity -= impulse;
//							mVelocity *= mNPCRestitution;
//						}
//						else
//						{
//							mVelocity -= impulse * 2.f;
//							mVelocity *= mWallRestitution;
//						}
//
//					}
//				}
//			}
//		}
//	}
//}
//
//void NPC::ProcessCollisionsWithScreenWalls()
//{
//	Vector3 location = GetLocation();
//	float x = location.mX;
//	float y = location.mY;
//
//	float vx = mVelocity.mX;
//	float vy = mVelocity.mY;
//
//	float radius = GetCollisionRadius();
//
//	//if the cat collides against a wall, the quick solution is to push it off
//	if( ( y + radius ) >= HALF_WORLD_HEIGHT && vy > 0 )
//	{
//		mVelocity.mY = -vy * mWallRestitution;
//		location.mY = HALF_WORLD_HEIGHT - radius;
//		SetLocation( location );
//	}
//	else if( y <= ( -HALF_WORLD_HEIGHT - radius ) && vy < 0 )
//	{
//		mVelocity.mY = -vy * mWallRestitution;
//		location.mY = -HALF_WORLD_HEIGHT - radius;
//		SetLocation( location );
//	}
//
//	if( ( x + radius ) >= HALF_WORLD_WIDTH && vx > 0 )
//	{
//		mVelocity.mX = -vx * mWallRestitution;
//		location.mX = HALF_WORLD_WIDTH - radius;
//		SetLocation( location );
//	}
//	else if(  x <= ( -HALF_WORLD_WIDTH - radius ) && vx < 0 )
//	{
//		mVelocity.mX = -vx * mWallRestitution;
//		location.mX = -HALF_WORLD_WIDTH - radius;
//		SetLocation( location );
//	}
//}
//
//uint32_t NPC::Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const
//{
//	uint32_t writtenState = 0;
//
//	if( inDirtyState & ECRS_NPCId )
//	{
//		inOutputStream.Write( (bool)true );
//		inOutputStream.Write( GetNPCId() );
//
//		writtenState |= ECRS_NPCId;
//	}
//	else
//	{
//		inOutputStream.Write( (bool)false );
//	}
//
//
//	if( inDirtyState & ECRS_Pose )
//	{
//		inOutputStream.Write( (bool)true );
//
//		Vector3 velocity = mVelocity;
//		inOutputStream.Write( velocity.mX );
//		inOutputStream.Write( velocity.mY );
//
//		Vector3 location = GetLocation();
//		inOutputStream.Write( location.mX );
//		inOutputStream.Write( location.mY );
//
//		inOutputStream.Write( GetRotation() );
//
//		writtenState |= ECRS_Pose;
//	}
//	else
//	{
//		inOutputStream.Write( (bool)false );
//	}
//
//	//always write mThrustDir- it's just two bits
//	if( mThrustDir != 0.f )
//	{
//		inOutputStream.Write( true );
//		inOutputStream.Write( mThrustDir > 0.f );
//	}
//	else
//	{
//		inOutputStream.Write( false );
//	}
//
//	if( inDirtyState & ECRS_Color )
//	{
//		inOutputStream.Write( (bool)true );
//		inOutputStream.Write( GetColor() );
//
//		writtenState |= ECRS_Color;
//	}
//	else
//	{
//		inOutputStream.Write( (bool)false );
//	}
//
//	if( inDirtyState & ECRS_Health )
//	{
//		inOutputStream.Write( (bool)true );
//		inOutputStream.Write( mHealth, 4 );
//
//		writtenState |= ECRS_Health;
//	}
//	else
//	{
//		inOutputStream.Write( (bool)false );
//	}
//
//	return writtenState;
//}
//
//bool NPC::operator==(NPC &other)
//{
//	// Game Object Part.
//	//Call the == of the base, NPC reference is
//	//downcast explicitly.
//	if(!GameObject::operator==(other)) return false;
//
//	if(this->ECRS_AllState != other.ECRS_AllState) return false;
//
//	if (!Maths::Is3DVectorEqual(this->mVelocity, other.mVelocity)) return false;
//	if (!Maths::FP_EQUAL(this->mMaxLinearSpeed, other.mMaxLinearSpeed)) return false;
//	if (!Maths::FP_EQUAL(this->mMaxRotationSpeed, other.mMaxRotationSpeed)) return false;
//	if (!Maths::FP_EQUAL(this->mWallRestitution, other.mWallRestitution)) return false;
//	if (!Maths::FP_EQUAL(this->mNPCRestitution, other.mNPCRestitution)) return false;
//	if(this->mNPCId != other.mNPCId) return false;
//
//	if (!Maths::FP_EQUAL(this->mLastMoveTimestamp, other.mLastMoveTimestamp)) return false;
//	if (!Maths::FP_EQUAL(this->mThrustDir, other.mThrustDir)) return false;
//	if(this->mHealth != other.mHealth) return false;
//	if(this->mIsShooting != other.mIsShooting) return false;
//
//	return true;
//}
