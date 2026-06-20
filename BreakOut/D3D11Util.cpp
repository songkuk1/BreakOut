#pragma once
#include "D3D11Util.h"
#include "UApp.h"
#include <cassert>
void D3D11Util::CreateVSAndInputlayout(const LPCWSTR& fileName, ComPtr<ID3D11VertexShader>& vertexShader, ComPtr<ID3D11InputLayout>& inputLayout)
{
	ID3DBlob* vertexshaderCSO = nullptr;

	//¹öÅØ½º ½¦ÀÌ´õ »ý¼º
	HRESULT hr = D3DCompileFromFile(fileName, nullptr, nullptr, "mainVS", "vs_5_0", 0, 0, &vertexshaderCSO,nullptr);

	 UApp::Ins->GetDevice()->CreateVertexShader(vertexshaderCSO->GetBufferPointer(), vertexshaderCSO->GetBufferSize(), nullptr, vertexShader.GetAddressOf());

	 D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	 {
		 { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		 { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	 };

	 hr = UApp::Ins->GetDevice()->CreateInputLayout(inputElementDesc,
		 ARRAYSIZE(inputElementDesc),
		 vertexshaderCSO->GetBufferPointer(),
		 vertexshaderCSO->GetBufferSize(),
		 inputLayout.GetAddressOf());

	vertexshaderCSO->Release();


}

void D3D11Util::CreatePS(const LPCWSTR& fileName, ComPtr<ID3D11PixelShader>& pixelShader)
{
	ID3DBlob* pixelshaderCSO = nullptr;

	HRESULT hr = D3DCompileFromFile(fileName, nullptr, nullptr, "mainPS", "Ps_5_0", 0, 0, &pixelshaderCSO, nullptr);

	//ÇÈ¼¿½¦ÀÌ´õ »ý¼º
	hr = D3DCompileFromFile(L"Shaders/defaultPS.hlsl", nullptr, nullptr, "mainPS", "ps_5_0", 0, 0, &pixelshaderCSO, nullptr);

	assert(SUCCEEDED(hr));

	UApp::Ins->GetDevice()->CreatePixelShader(pixelshaderCSO->GetBufferPointer(), pixelshaderCSO->GetBufferSize(), nullptr, pixelShader.GetAddressOf());



	assert(SUCCEEDED(hr));
	pixelshaderCSO->Release();
}
