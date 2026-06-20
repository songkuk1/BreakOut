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






};