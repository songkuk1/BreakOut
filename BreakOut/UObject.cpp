#include "UObject.h"

void UObject::Draw()
{
	if(m_meshRenderer)
	{
		VertexConstantData VSCData;

		VSCData.model = GetModelMatrix().Transpose();
		VSCData.view = Matrix();
		VSCData.proj = Matrix();
		m_meshRenderer->DrawMesh(VSCData);
	}

}

Matrix& UObject::GetModelMatrix()
{
	if(dirty)
	{
		model = Matrix::CreateScale(scale) * Matrix::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z) * Matrix::CreateTranslation(location);


		dirty = false;
	}

	return model;
}

void UObject::SetLocation(Vector3 InLocation) 
{ 
	location = InLocation; 
	dirty = true;
}
void UObject::SetRotation(Vector3 InRotation) 
{
	rotation = InRotation;
	dirty = true;
}
void UObject::SetScale(Vector3 InScale) 
{ 
	scale = InScale;
	dirty = true;
}