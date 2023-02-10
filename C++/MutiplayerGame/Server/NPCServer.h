//#ifndef NPC_SERVER_H
//#define NPC_SERVER_H
//
//#include "NPC.h"
//#include "NetworkManagerServer.h"
//
//enum ENPCControlType
//{
//	//ESCT_Human,
//	ESCT_AI
//};
//
//class NPCServer : public NPC
//{
//public:
//	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn( new NPCServer() ); }
//	virtual void HandleDying() override;
//
//	virtual void Update() override;
//
//	void SetNPCControlType( ENPCControlType inNPCControlType ) { mNPCControlType = inNPCControlType; }
//
//	void TakeDamage( int inDamagingNPCId );
//	bool HandleCollisionWithNPC(NPC* inNPC);
//protected:
//	NPCServer();
//
//private:
//
//	//void HandleShooting();
//
//	ENPCControlType	mNPCControlType;
//
//
//	//float		mTimeOfNextShot;
//	//float		mTimeBetweenShots;
//
//};
//
//#endif // NPC_SERVER_H
