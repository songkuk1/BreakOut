#pragma once
#include "UObject.h"
#include "UApp.h"
#include "PhysicsComponent.h"


class UBall : public UObject
{
public:
	UBall(std::unique_ptr<UMeshRenderer> meshRenderer,Vector3 location, Vector3 scale);
	~UBall() override;

	PhysicsComponent* physicsComponent;
	FObjectType GetType() const override { return FObjectType::Ball; }
	PhysicsComponent* GetPhysicsComponent() const override { return physicsComponent; }
	void Update(double deltaTime) override;

};