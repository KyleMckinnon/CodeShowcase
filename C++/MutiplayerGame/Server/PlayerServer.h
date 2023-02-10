#ifndef PLAYER_SERVER_H
#define PLAYER_SERVER_H

#include "Player.h"
#include "NetworkManagerServer.h"

enum EPlayerControlType
{
	ESCT_Human,
	ESCT_AI
};

class PlayerServer : public Player
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn( new PlayerServer() ); }
	virtual void HandleDying() override;

	virtual void Update() override;

	void SetPlayerControlType( EPlayerControlType inPlayerControlType ) { mPlayerControlType = inPlayerControlType; }

	void TakeDamage( int inDamagingPlayerId );

	bool HandleCollisionWithPlayer(Player* inPlayer);


protected:
	PlayerServer();

private:


	void NPCUpdate();
	void HandleShooting();
	void PlayerMovementUpdate();
	EPlayerControlType	mPlayerControlType;
	

	float		mTimeOfNextShot;
	float		mTimeBetweenShots;

};
typedef shared_ptr< PlayerServer >	PlayerServerPtr;
#endif // PLAYER_SERVER_H
