#pragma once
#include "UObjectFactory.h"
#include "UBall.h"
#include "UBlock.h"
#include "UPlayer.h"
#include "UApp.h"
#include "UMeshRenderer.h"



UObjectFactory* UObjectFactory::Ins = nullptr;

UObject* UObjectFactory::CreateBall(Vector3 location, Vector3 scale)
{
	UBall* newBall = new UBall(std::make_unique<UMeshRenderer>(UApp::Ins->SphereMesh(), UMeshRenderer::BallOrder),location,scale);
	AddObjectList(newBall);
	return newBall;
}

UObject* UObjectFactory::CreateBlock(Vector3 location, Vector3 scale)
{
	UBlock* newBlock = new UBlock(std::make_unique<UMeshRenderer>(UApp::Ins->GetCubeMesh(), UMeshRenderer::BlockOrder),location,scale);
	AddObjectList(newBlock);
	return newBlock;
}


UObject* UObjectFactory::CreatePlayer(Vector3 location, Vector3 scale)
{
	UPlayer* newPlayer = new UPlayer(std::make_unique<UMeshRenderer>(UApp::Ins->GetCubeMesh(), UMeshRenderer::PlayerOrder), location, scale);
	AddObjectList(newPlayer);
	return newPlayer;
}

void UObjectFactory::AddObjectList(UObject* obj)
{
	objectList.push_back(obj);

}

void UObjectFactory::Render()
{
	UINT objListSize = objectList.size();

	for(UINT i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->isActive == false)
			continue;


		if(objectList[i]->GetRenderer() != nullptr)
		{
			if (objectList[i]->isActive == false)
				continue;

			objectList[i]->Draw();
		}


	}



}

void UObjectFactory::Update(double deltaTime)
{

	for(UINT i = 0; i < objectList.size(); ++i)
	{
		objectList[i]->Update(deltaTime);
	}


	for (UINT i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->isActive == false)
			continue;

		for (UINT j = i + 1; j < objectList.size(); ++j)
		{
			if (objectList[j]->isActive == false)
				continue;

			UObject* objA = objectList[i];
			UObject* objB = objectList[j];

			PhysicsComponent* physicsA = objA->GetPhysicsComponent();
			PhysicsComponent* physicsB = objB->GetPhysicsComponent();

			if (physicsA && physicsB)
			{
				if (physicsA->CheckCollision(physicsB))
				{
					physicsA->OnCollision(physicsB);
					physicsB->OnCollision(physicsA);
				}
			}
		}
	}
}

void UObjectFactory::ReleaseAll()
{
	int objListCount = objectList.size();
	for (UINT i = 0; i < objListCount; ++i)
	{
		delete objectList[i];
	}
	objectList.Clear();
}

UObjectFactory::~UObjectFactory()
{

	ReleaseAll();
}
