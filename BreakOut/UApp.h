#pragma once
#include <windows.h>
#include <d3dcompiler.h>
#include <d3d11.h>
#include <wrl/client.h> 
#include "UMesh.h"
#include "UVector.h"

class IGameState;

using Microsoft::WRL::ComPtr;



class UApp
{
private:
	UMesh* cubeMesh;
	UMesh* sphereMesh;


	ComPtr<ID3D11Device> m_device;
	ComPtr<ID3D11DeviceContext> m_deviceContext;
	ComPtr<IDXGISwapChain> m_swapChain;
	D3D11_VIEWPORT ViewportInfo;
	ComPtr<ID3D11Texture2D> m_frameBuffer;
	ComPtr<ID3D11RenderTargetView> m_frameBufferRTV;

	ComPtr<ID3D11PixelShader> m_pixelShader;
	ComPtr<ID3D11VertexShader> m_vertexShader;
	ComPtr<ID3D11InputLayout> simpleInputLayout;

	ComPtr<ID3D11RasterizerState> m_rasterizerState;

	ComPtr<ID3D11Buffer> TransformCBuffer;


public:
	static UApp* Ins;
	HWND m_mainWindow;

	IGameState* m_currentState = nullptr;

	IGameState* nextState = nullptr;



	void Init(HINSTANCE hwnd);
	void InitD3D(HINSTANCE hwnd);
	void InitWindow();
	void InitImgui();
	void Loading();
	void CreateDeviceAndSwapChain();
	void CreateFrameBuffer();
	void CreateShaders();
	void CreateRasterizerState();

	void ChangeState(IGameState* newState);

	IGameState* GetCurrentState() {return m_currentState;}

	void mainLoop();
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext() const { return m_deviceContext.Get(); }

	void Update();
	void Render();
	float ClearColor[4] = { 0, 0, 0, 1 };



	UMesh* GetCubeMesh() const { return cubeMesh; }	
	UMesh* SphereMesh() const { return sphereMesh; }


	ID3D11VertexShader* GetDefaultVS() const { return m_vertexShader.Get(); }
	ID3D11PixelShader* GetDefaultPS() const { return m_pixelShader.Get(); }
	ID3D11InputLayout* GetDefaultInputLayout() const{ return simpleInputLayout.Get(); }

	ID3D11Buffer* GetTransformCBuffer() const { return TransformCBuffer.Get(); }

};
