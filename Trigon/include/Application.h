#ifndef APPLICATION_H
#define APPLICATION_H
#pragma once
#include <PxPhysicsAPI.h>
#include <PxFoundation.h>
#include <PxPhysics.h>
#include <PxSimulationEventCallback.h>
#include <PxScene.h>
#include <PxSceneDesc.h>
#include <PxSimulationEventCallback.h>
#include <PxShape.h>
#include "geometry/PxSphereGeometry.h"
#include "geometry/PxPlaneGeometry.h"
#include "geometry/PxGeometry.h"
#include "PxActor.h"

class CPhysicsError : public physx::PxDefaultErrorCallback
{
public:

	void reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line)
	{
		printf("\n%s", message);
	}
};

class CPhysicsAllocator : public physx::PxDefaultAllocator
{
public:
	~CPhysicsAllocator() 
	{

	}


};


class Application
{
private:

	bool appShouldQuit = false;
	CPhysicsAllocator*	m_pAllocator;
	CPhysicsError*		m_pError;


public:

	Application();

	void BaseSetup();

	virtual void OnInit();
	virtual void OnAwake();
	virtual void OnStart();
	virtual void OnEarlyUpdate();
	virtual void OnUpdate();
	virtual void OnLateUpdate();
	virtual void OnQuit();

	bool ShouldQuit();
};


#endif // !APPLICATION_H


