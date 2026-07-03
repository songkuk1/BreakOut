#pragma once
#include "UObject.h"
#include "UVector.h"
#include <SimpleMath.h>
#include "InputManager.h"


using DirectX::SimpleMath::Vector3;

class UObjectFactory
{



private:
	static UObjectFactory* Ins;

	UVector<UObject*> objectList;


public:

	static UObjectFactory* GetInstance()
	{
		if (Ins == nullptr)
			Ins = new UObjectFactory();
		return Ins;
	}

	UObject* CreateBall(Vector3 location, Vector3 scale);
	UObject* CreateBlock(Vector3 location, Vector3 scale = {0.1f,0.1f,0.1f});
	UObject* CreatePlayer(Vector3 location, Vector3 scale);
	void Render();
	void Update(double deltaTime);
	void ReleaseAll();
	~UObjectFactory();
private:
	void AddObjectList(UObject* obj);
	

};