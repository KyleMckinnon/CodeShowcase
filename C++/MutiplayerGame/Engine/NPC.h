//#ifndef NPC_H_
//#define NPC_H_
//
//#include "GameObject.h"
//#include "World.h"
//#include "Player.h"
//#include <iostream>
//
//
//class InputState;
//class Player;
//
///* We'll later create client and server versions of this class */
//
//class NPC : public GameObject
//{
//public:
//	CLASS_IDENTIFICATION( 'NPCC', GameObject )
//
//	enum ENPCReplicationState
//	{
//		ECRS_Pose = 1 << 0,
//		ECRS_Color = 1 << 1,
//		ECRS_NPCId = 1 << 2,
//		ECRS_Health = 1 << 3,
//
//		ECRS_AllState = ECRS_Pose | ECRS_Color | ECRS_NPCId | ECRS_Health
//	};
//
//
//	static	GameObject*	StaticCreate()			{ return new NPC(); }
//
//
//	//Note - the code in the book doesn't provide this until the client.
//	//This however limits testing.
//	static	GameObjectPtr	StaticCreatePtr()			{ return GameObjectPtr(new NPC()); }
//
//
//	virtual uint32_t GetAllStateMask()	const override	{ return ECRS_AllState; }
//
//	virtual void Update() override;
//
//	void SimulateMovement( float inDeltaTime );
//
//	void ProcessCollisions();
//	void ProcessCollisionsWithScreenWalls();
//
//	/*void SpawnNPC();*/
//
//	void		SetPlayerId( uint32_t inPlayerId )			{ mPlayerId = inPlayerId; }
//	uint32_t	GetPlayerId()						const 	{ return mPlayerId; }
//
//	void		SetNPCId(uint32_t inNPCId) { mNPCId = inNPCId; }
//	uint32_t	GetNPCId()						const { return mNPCId; }
//
//	void			SetVelocity( const Vector3& inVelocity )	{ mVelocity = inVelocity; }
//	const Vector3&	GetVelocity()						const	{ return mVelocity; }
//
//
////	virtual void	Read( InputMemoryBitStream& inInputStream ) override;
//
//	uint32_t Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const override;
//	// For testing
//
//	float GetMaxLinearSpeed() { return mMaxLinearSpeed; }
//	float GetMaxRotationSpeed() { return mMaxRotationSpeed; }
//	float GetWallRestitution() { return mWallRestitution; }
//	float GetNPCRestitution() { return mNPCRestitution; }
//	float GetLastMoveTimestamp() { return mLastMoveTimestamp; }
//	float GetThrustDir() { return mThrustDir; }
//	int GetHealth() { return mHealth; }
//	bool IsShooting() { return mIsShooting; }
//
//	bool operator==(NPC &other);
//
//	void SetTarget(Player* target);
//	void SetPlayerName(std::string newName) { mName = newName; }
//
//	
//protected:
//	NPC();
//
//private:
//
//	void CheckForTarget();
//	void	AdjustVelocityByThrust( float inDeltaTime );
//
//	Vector3				mVelocity;
//	Player* m_target;
//	Vector3 directionToPlayer;
//	
//	float				mMaxLinearSpeed;
//	float				mMaxRotationSpeed;
//
//	//bounce fraction when hitting various things
//	float				mWallRestitution;
//	float				mNPCRestitution;
//
//
//	uint32_t			mPlayerId;
//	uint32_t			mNPCId;
//protected:
//
//	///move down here for padding reasons...
//
//	float				mLastMoveTimestamp;
//
//	float				mThrustDir;
//	int					mHealth;
//
//	bool				mIsShooting;
//	float		mSpeed;
//	std::string         mName;
//};
//
//
//typedef shared_ptr< NPC >	NPCPtr;
//
//#endif // PLAYER_H_
