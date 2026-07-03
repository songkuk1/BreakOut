#pragma once
#include "UObject.h"
#include <SimpleMath.h>
#include "Rect.h"

using DirectX::SimpleMath::Vector3;

class PhysicsComponent
{
public:
	PhysicsComponent(UObject* InOwner,FRect Incollider, FRect Inboundary);

	~PhysicsComponent() = default;

	UObject* owner = nullptr;

	Vector3 velocity;
	FRect collider;
	FRect boundary;

	void SetVelocity(Vector3 newVelocity);
	Vector3 GetVelocity() const;

	void Update(double deltaTime);
	void UpdateLocation(double deltaTime);
	UObject* GetOwner() const { return owner; }	
	const FRect& GetColliderBounds() const { return collider; }
	Vector2 CalculateOverlap(const FRect& collider, const FRect& otherCollider, const Vector3& objectLocation, const Vector3& otherObjectLocation);
	bool CheckCollision(const PhysicsComponent* otherCollider);
	void OnCollision(const PhysicsComponent* otherCollider);
	void CheckBoundaryCollision();
	bool isGrouned(float groundEpsilon = 0.01f);
};
