#pragma once
#include "UMesh.h"
#include "UVector.h"
#include <wrl/client.h> 
#include <memory>
using Microsoft::WRL::ComPtr;

class UMeshRenderer
{
	UVector<std::unique_ptr<UMesh>> m_meshes;
	ComPtr<ID3D11PixelShader> PS;
	ComPtr<ID3D11VertexShader> VS;



};