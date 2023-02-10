#ifndef Building_CLIENT_H
#define Building_CLIENT_H

#include "Building.h"
#include "SpriteComponent.h"

class BuildingClient : public Building
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new BuildingClient()); }

	virtual void Update();


	virtual void	Read(InputMemoryBitStream& inInputStream) override;

protected:
	BuildingClient();


private:
	float				mTimeLocationBecameOutOfSync;
	float				mTimeVelocityBecameOutOfSync;

	SpriteComponentPtr	mSpriteComponent;
};
typedef shared_ptr< BuildingClient >	BuildingClientPtr;
#endif //PLAYER_CLIENT_H
