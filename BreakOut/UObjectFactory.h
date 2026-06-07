#pragma once
#include "UObject.h"
#include "UVector.h"

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

	UObject* CreateBall();
	UObject* CreatePlayerPaddle();

private:
	void AddObjectList(UObject* obj);


};