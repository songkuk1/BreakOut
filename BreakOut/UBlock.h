#pragma once

#include "UObject.h"
#include "UApp.h"
#include <memory>
#include "PhysicsComponent.h"


class UBlock : public UObject
{
public:
	UBlock(std::unique_ptr<UMeshRenderer> meshRenderer, Vector3 location, Vector3 scale);
	~UBlock() override;
	FObjectType GetType() const override { return FObjectType::Block; }
	PhysicsComponent* physicsComponent;
	PhysicsComponent* GetPhysicsComponent() const override { return physicsComponent; }
	void Update(double deltaTime) override
	{
		//블록은 움직이지 않으므로 업데이트 필요 없음
	}


};