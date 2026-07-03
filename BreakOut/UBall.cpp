#include "UBall.h"

UBall::UBall(std::unique_ptr<UMeshRenderer> meshRenderer,Vector3 location, Vector3 scale) : UObject(std::move(meshRenderer))
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
	boundary = FRect(Vector2(-1.0f, -1.0f), Vector2(1.0f, 1.0f));
	physicsComponent = new PhysicsComponent(this, colliderBox, boundary);
	physicsComponent->SetVelocity(Vector3(0.0f, 0.3f, 0.0f));
}

UBall::~UBall()
{
	delete physicsComponent;
	physicsComponent = nullptr;

}

void UBall::Update(double deltaTime)
{

	physicsComponent->Update(deltaTime);
}
