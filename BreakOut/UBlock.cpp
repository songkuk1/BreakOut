#include "UBlock.h"

UBlock::UBlock(std::unique_ptr<UMeshRenderer> meshRenderer, Vector3 location, Vector3 scale) : UObject(std::move(meshRenderer))
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
	boundary = FRect(Vector2(-1.0f, 1.0f), Vector2(1.0f, 1.0f));
	physicsComponent = new PhysicsComponent(this, colliderBox, boundary);
}

UBlock::~UBlock()
{
	delete physicsComponent;
	physicsComponent = nullptr;


}

