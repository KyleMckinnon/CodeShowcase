#ifndef BUILDING_SERVER_H
#define BUILDING_SERVER_H

#include "Building.h"
#include "NetworkManagerServer.h"



class BuildingServer : public Building
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new BuildingServer()); }


	virtual void Update() override;



protected:
	BuildingServer();

private:



};

#endif 