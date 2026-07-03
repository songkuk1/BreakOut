#pragma once
#include "UMesh.h"
#include "UVector.h"
#include <wrl/client.h> 
#include <memory>
using Microsoft::WRL::ComPtr;


struct VertexConstantData;

class UMeshRenderer
{
private:
	UMesh* m_meshes;
	ComPtr<ID3D11PixelShader> PS;
	ComPtr<ID3D11VertexShader> VS;
	ComPtr<ID3D11InputLayout> InputLayout;
	UINT DrawOrder = 0;


public:
	UMeshRenderer(UMesh* meshes, UINT InDrawOrder)
	{
		m_meshes = meshes;
		SetDrawOrder(InDrawOrder);


	}
	~UMeshRenderer() = default;
	


	const static UINT BlockOrder;
	const static UINT PlayerOrder;
	const static UINT BallOrder;

	void SetDrawOrder(UINT InDrawOrder) { DrawOrder = InDrawOrder; }
	UINT GetDrawOrder() const { return DrawOrder; };
	void SetShader(ID3D11InputLayout* inputLayout, ID3D11VertexShader* vs, ID3D11PixelShader* ps);
	void DrawMesh(VertexConstantData data);


};