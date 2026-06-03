#pragma once
#include <windows.h>
#include <d3dcompiler.h>
#include <d3d11.h>
#include <wrl/client.h> 

class IGameState;

using Microsoft::WRL::ComPtr;


class UApp
{
public:
	static UApp* Ins;
	HWND m_mainWindow;

	IGameState* m_currentState = nullptr;

	IGameState* nextState = nullptr;

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

	void Init(HINSTANCE hwnd);
	void InitD3D(HINSTANCE hwnd);
	void InitWindow();
	void CreateDeviceAndSwapChain();
	void CreateFrameBuffer();
	void CreateShaders();
	void CreateRasterizerState();

	void ChangeState(IGameState* newState);

	void mainLoop();

	void Update();
	void Render();
	float ClearColor[4] = { 0, 0, 0, 1 };
};
