#pragma once
#include <wrl/client.h> 
#include <d3dcompiler.h>
#include <d3d11.h>
#include "UVector.h"

using Microsoft::WRL::ComPtr;

class D3D11Util
{
public:
    static void CreateVSAndInputlayout(
        const LPCWSTR& fileName,
        ComPtr<ID3D11VertexShader>& vertexShader,
        ComPtr<ID3D11InputLayout>& inputLayout);

    static void CreatePS(const LPCWSTR& fileName, ComPtr<ID3D11PixelShader>& pixelShader);

	template<typename T>
	static void UpdateConstantBuffer(ID3D11DeviceContext* context, ID3D11Buffer* cBuffer, T& cBufferData)
	{
		D3D11_MAPPED_SUBRESOURCE constantbufferMSR;
		context->Map(cBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &constantbufferMSR);
		memcpy(constantbufferMSR.pData, &cBufferData, sizeof(T));

		context->Unmap(cBuffer, 0);
	}




};