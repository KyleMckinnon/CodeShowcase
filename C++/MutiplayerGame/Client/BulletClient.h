#ifndef BULLET_CLIENT_H
#define BULLET_CLIENT_H

#include "Bullet.h"
#include "SpriteComponent.h"

class BulletClient : public Bullet
{
public:
	static	GameObjectPtr	StaticCreate()		{ return GameObjectPtr( new BulletClient() ); }


	virtual void	Read( InputMemoryBitStream& inInputStream ) override;

protected:
	BulletClient();


private:
	float				mTimeLocationBecameOutOfSync;
	float				mTimeVelocityBecameOutOfSync;

	SpriteComponentPtr	mSpriteComponent;
};
typedef shared_ptr< BulletClient >	BulletClientPtr;
#endif //Bullet_CLIENT_H
