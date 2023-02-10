#include "Building.h"
#include "Maths.h"

#include "InputMemoryBitStream.h"
#include "OutputMemoryBitStream.h"



Building::Building() :
	GameObject()

{
	//SetScale(GetScale() * 0.5f);
	SetCollisionRadius(0.5f);
}

void Building::Update()
{

}

uint32_t Building::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	uint32_t BuildingWrittenState = 0;

	Vector3 location = GetLocation();
	inOutputStream.Write(location.mX);
	inOutputStream.Write(location.mY);

	inOutputStream.Write(GetRotation());

	inOutputStream.Write(GetColor());




	// add Building structure later


	return BuildingWrittenState;
}

bool Building::operator==(Building& other)
{
	// Game Object Part.
	//Call the == of the base, Player reference is
	//downcast explicitly.
	if (!GameObject::operator==(other)) return false;


	return true;
}
