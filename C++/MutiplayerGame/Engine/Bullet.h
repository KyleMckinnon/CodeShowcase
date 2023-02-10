#ifndef BULLET_H_
#define BULLET_H_

#include "GameObject.h"
#include "World.h"


class InputState;
class Player;
//class NPC;
/* We'll later create client and server versions of this class */

class Bullet : public GameObject
{
public:
	CLASS_IDENTIFICATION( 'YARN', GameObject )

	enum EBulletReplicationState
	{
		ECRS_Pose = 1 << 0,
		ECRS_Color = 1 << 1,
		ECRS_BulletId = 1 << 2,
		ECRS_Health = 1 << 3,

		ECRS_AllState = ECRS_Pose | ECRS_Color | ECRS_BulletId | ECRS_Health
	};


	static	GameObject*	StaticCreate()			{ return new Bullet(); }

	//Note - the code in the book doesn't provide this until the client.
	//This however limits testing.
	static	GameObjectPtr	StaticCreatePtr()			{ return GameObjectPtr(new Bullet()); }
	
	float timeDelta;

	virtual uint32_t GetAllStateMask()	const override	{ return ECRS_AllState; }

	virtual void Update() override;

	void SimulateMovement( float inDeltaTime );

	void ProcessCollisions();
	void ProcessCollisionsWithScreenWalls();
	void InitFromShooter(Player *shooter);

	void		SetBulletId( uint32_t inBulletId )			{ mBulletId = inBulletId; }
	uint32_t	GetBulletId()						const 	{ return mBulletId; }

	void		SetNPCId(uint32_t inNPCId) { mNPCId = inNPCId; }
	uint32_t	GetNPCId()						const { return mNPCId; }

	void		SetPlayerId(uint32_t inPlayerId) { mPlayerId = inPlayerId; }
	uint32_t	GetPlayerId()						const { return mPlayerId; }
	void			SetVelocity( const Vector3& inVelocity )	{ mVelocity = inVelocity; }
	const Vector3&	GetVelocity()						const	{ return mVelocity; }


 	//virtual void	Read( InputMemoryBitStream& inInputStream ) override;

	uint32_t Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const override;
	// For testing


	float GetMaxLinearSpeed() { return mMaxLinearSpeed; }
	float GetMaxRotationSpeed() { return mMaxRotationSpeed; }
	float GetWallRestitution() { return mWallRestitution; }
	float GetNPCRestitution() { return mNPCRestitution; }
	float GetLastMoveTimestamp() { return mLastMoveTimestamp; }
	float GetThrustDir() { return mThrustDir; }
	float GetSpeed() const { return mSpeed; }
	
	virtual bool HandleCollisionWithPlayer(Player* inCat) override;
	//virtual bool HandleCollisionWithNPC(NPC* inCat) override;
	bool operator==(Bullet &other);
protected:
	Bullet();

	float		mSpeed;

private:
	uint32_t			mPlayerId;
	uint32_t			mNPCId;
	Vector3				mVelocity;


	float				mMaxLinearSpeed;
	float				mMaxRotationSpeed;

	//bounce fraction when hitting various things
	float				mWallRestitution;
	float				mNPCRestitution;


	uint32_t			mBulletId;

protected:

	///move down here for padding reasons...

	float				mLastMoveTimestamp;

	float				mThrustDir;



};

typedef shared_ptr< Bullet >	BulletPtr;

#endif // Bullet_H_
