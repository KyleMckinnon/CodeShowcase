#ifndef BUILDING_H_
#define BUILDING_H_

#include "GameObject.h"
#include "World.h"




/* We'll later create client and server versions of this class */

class Building : public GameObject
{
public:
	CLASS_IDENTIFICATION('BULD', GameObject)

		static	GameObject* StaticCreate() { return new Building(); }

	enum EBuildingReplicationState
	{
		ECRS_Pose = 1 << 0,
		ECRS_Color = 1 << 1,
		ECRS_BuildingId = 1 << 2,
		ECRS_Health = 1 << 3,

		ECRS_AllState = ECRS_Pose | ECRS_Color | ECRS_BuildingId | ECRS_Health
	};


	//Note - the code in the book doesn't provide this until the client.
	//This however limits testing.
	static	GameObjectPtr	StaticCreatePtr() { return GameObjectPtr(new Building()); }
	virtual uint32_t GetAllStateMask()	const override { return ECRS_AllState; }

	virtual void Update() override;



	//	virtual void	Read( InputMemoryBitStream& inInputStream ) override;

	uint32_t Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;

	// For testing

	bool operator==(Building& other);
protected:
	Building();

private:


protected:

	///move down here for padding reasons...

};

typedef shared_ptr< Building >	BuildingPtr;

#endif // Building_H_
