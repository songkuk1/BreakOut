#pragma once
#include "UMeshRenderer.h"
#include <memory>
#include "ConstantData.h"
#include <SimpleMath.h>


enum FObjectType
{
	Player,
	Ball,
	Block
};

using DirectX::SimpleMath::Matrix;
using DirectX::SimpleMath::Vector3;
class UObject
{
	//위치,회전,크기 정보를 담고있는 model 행렬
	Matrix model = Matrix();
	Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 location = Vector3(0.0f, 0.0f, 0.0f);

	std::unique_ptr<UMeshRenderer> m_meshRenderer;
public:

	UObject(std::unique_ptr<UMeshRenderer> meshRenderer) : m_meshRenderer(std::move(meshRenderer)){}
	virtual ~UObject() = default;
	virtual void Update(double deltaTime) = 0;
	virtual class PhysicsComponent* GetPhysicsComponent() const = 0;
	UMeshRenderer* GetRenderer() const { return m_meshRenderer.get(); }
	void Draw();

	virtual	FObjectType GetType() const = 0;

	Matrix& GetModelMatrix();
	void SetLocation(Vector3 InLocation);
	void SetRotation(Vector3 InRotation);
	void SetScale(Vector3 InScale);

	Vector3 GetLocation() const { return location; }
	Vector3 GetScale() const { return scale; }



	//물체의 transform이 변경되었는지 체크
	bool dirty = false;

	//물체를 활성화할지 체크
	bool isActive = true;



};