#pragma once
#include <d3d11.h>


class UMesh
{
	std::unique_ptr<ID3D11Buffer> vertexBuffer;
	std::unique_ptr<ID3D11Buffer> indexBuffer;


};