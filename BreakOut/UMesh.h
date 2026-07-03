#pragma once
#include <d3d11.h>
#include <memory>
#include <wrl/client.h> 
using Microsoft::WRL::ComPtr;


struct FMeshData;

class UMesh
{
	
	ComPtr<ID3D11Buffer> vertexBuffer;
	ComPtr<ID3D11Buffer> indexBuffer;
	ComPtr<ID3D11Buffer> vertexConstantBuffer;
	ComPtr<ID3D11Buffer> pixelConstantBuffer;


	int vertexCount = 0;
	int indexCount = 0;
	unsigned int stride = 0;

public:
	UMesh(FMeshData& meshData);
	~UMesh() = default;

	void Draw();

};