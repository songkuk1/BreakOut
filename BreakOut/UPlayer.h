#pragma once
#include "UObject.h"
#include "InputManager.h"
#include "UApp.h"
#include "PhysicsComponent.h"


class UPlayer : public UObject
{
public:
	UPlayer(std::unique_ptr<UMeshRenderer> meshRenderer, Vector3 location, Vector3 scale);

	~UPlayer() override;

	void CheckInput();
	PhysicsComponent* physicsComponent;

	bool moveLeft = false;
	bool moveRight = false;

	FObjectType GetType() const override { return FObjectType::Player; }
	PhysicsComponent* GetPhysicsComponent() const override { return physicsComponent; }
	void Update(double deltaTime) override;
	float horizontalInput = 0.0f;
	float moveSpeed = 1.0f;

};