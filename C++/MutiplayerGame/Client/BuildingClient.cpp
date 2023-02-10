#include "BuildingClient.h"

#include "TextureManager.h"
#include "GameObjectRegistry.h"

#include "InputMemoryBitStream.h"
#include "OutputMemoryBitStream.h"
#include "NetworkManagerClient.h"

#include "StringUtils.h"

BuildingClient::BuildingClient() :
	mTimeLocationBecameOutOfSync(0.f),
	mTimeVelocityBecameOutOfSync(0.f)
{
	mSpriteComponent.reset(new SpriteComponent(this));
	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("buld"));
}




void BuildingClient::Update()
{
	//for now, we don't simulate any movement on the client side
	//we only move when the server tells us to move
}

void BuildingClient::Read(InputMemoryBitStream& inInputStream)
{

	float oldRotation = GetRotation();
	Vector3 oldLocation = GetLocation();

	float replicatedRotation;
	Vector3 replicatedLocation;


	inInputStream.Read(replicatedLocation.mX);
	inInputStream.Read(replicatedLocation.mY);

	SetLocation(replicatedLocation);

	inInputStream.Read(replicatedRotation);
	SetRotation(replicatedRotation);

	Vector3 color;
	inInputStream.Read(color);
	SetColor(color);

}
