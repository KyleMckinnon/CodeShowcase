//#include "NPCClient.h"
//
//#include "TextureManager.h"
//#include "GameObjectRegistry.h"
//
//#include "InputMemoryBitStream.h"
//#include "OutputMemoryBitStream.h"
//#include "NetworkManagerClient.h"
//
//#include "StringUtils.h"
//
//NPCClient::NPCClient() :
//	mTimeLocationBecameOutOfSync( 0.f ),
//	mTimeVelocityBecameOutOfSync( 0.f )
//{
//	mSpriteComponent.reset( new SpriteComponent( this ) );
//	mSpriteComponent->SetTexture( TextureManager::sInstance->GetTexture( "player" ) );
//}
//
//void NPCClient::HandleDying()
//{
//	NPC::HandleDying();
//
//}
//
//
//void NPCClient::Update()
//{
//	//for now, we don't simulate any movement on the client side
//	//we only move when the server tells us to move
//	
//	
//}
//
//void NPCClient::Read( InputMemoryBitStream& inInputStream )
//{
//	bool stateBit;
//
//	uint32_t readState = 0;
//
//	inInputStream.Read( stateBit );
//	if( stateBit )
//	{
//		uint32_t NPCId;
//		inInputStream.Read( NPCId );
//		SetNPCId( NPCId );
//		readState |= ECRS_NPCId;
//	}
//
//	float oldRotation = GetRotation();
//	Vector3 oldLocation = GetLocation();
//	Vector3 oldVelocity = GetVelocity();
//
//	float replicatedRotation;
//	Vector3 replicatedLocation;
//	Vector3 replicatedVelocity;
//
//	inInputStream.Read( stateBit );
//	if( stateBit )
//	{
//		inInputStream.Read( replicatedVelocity.mX );
//		inInputStream.Read( replicatedVelocity.mY );
//
//		SetVelocity( replicatedVelocity );
//
//		inInputStream.Read( replicatedLocation.mX );
//		inInputStream.Read( replicatedLocation.mY );
//
//		SetLocation( replicatedLocation );
//
//		inInputStream.Read( replicatedRotation );
//		SetRotation( replicatedRotation );
//
//		readState |= ECRS_Pose;
//	}
//
//	inInputStream.Read( stateBit );
//	if( stateBit )
//	{
//		inInputStream.Read( stateBit );
//		mThrustDir = stateBit ? 1.f : -1.f;
//	}
//	else
//	{
//		mThrustDir = 0.f;
//	}
//
//	inInputStream.Read( stateBit );
//	if( stateBit )
//	{
//		Vector3 color;
//		inInputStream.Read( color );
//		SetColor( color );
//		readState |= ECRS_Color;
//	}
//
//	inInputStream.Read( stateBit );
//	if( stateBit )
//	{
//		mHealth = 0;
//		inInputStream.Read( mHealth, 4 );
//		readState |= ECRS_Health;
//	}
//
//	if( GetNPCId() == NetworkManagerClient::sInstance->GetNPCId() )
//	{
//		//did we get health? if so, tell the hud!
//		if( ( readState & ECRS_Health ) != 0 )
//		{
//		//	HUD::sInstance->SetNPCHealth( mHealth );
//		}
//	}
//}
