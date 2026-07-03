#pragma once

#include "UPlayer.h"
#include <SimpleMath.h>
#include "Rect.h"

using DirectX::SimpleMath::Vector2;
using DirectX::SimpleMath::Vector3;


UPlayer::UPlayer(std::unique_ptr<UMeshRenderer> meshRenderer, Vector3 location, Vector3 scale) : UObject(std::move(meshRenderer))
{
	GetRenderer()->SetShader(UApp::Ins->GetDefaultInputLayout(), UApp::Ins->GetDefaultVS(), UApp::Ins->GetDefaultPS());
	SetLocation(location);
	SetScale(scale);

	Vector3 size = GetScale();
	Vector2 _min(-size.x, -size.y);
	Vector2 _max(size.x, size.y);
	//충돌 박스
	FRect colliderBox(_min, _max);
	//이동 범위 설정
	FRect boundary;
	boundary = FRect(Vector2(-1.0f,-1.0f), Vector2(1.0f, 1.0f));
	physicsComponent = new PhysicsComponent(this, colliderBox, boundary);
}

UPlayer::~UPlayer()
{
	delete physicsComponent;
	physicsComponent = nullptr;

}

void UPlayer::CheckInput()
{
	//방향키 설정
	moveLeft = InputManager::GetInstance()->IsKeyDown(VK_LEFT);
	moveRight = InputManager::GetInstance()->IsKeyDown(VK_RIGHT);

}

void UPlayer::Update(double deltaTime)
{
	CheckInput();

	if(moveLeft)
		{
		horizontalInput = -1.0f;
	}
	else if(moveRight)
	{
		horizontalInput = 1.0f;
	}
	else
	{
		horizontalInput = 0.0f;
	}

	Vector3 currentVelocity = physicsComponent->GetVelocity();
	currentVelocity.x = horizontalInput * moveSpeed;

	physicsComponent->SetVelocity(currentVelocity);
	physicsComponent->Update(deltaTime);


}
