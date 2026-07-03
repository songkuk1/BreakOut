#pragma once
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#include "States/IGameState.h"
#include "States/MainMenuState.h"
#include "States/InGameState.h"

#include <iostream>
#include <cassert>
#include "UApp.h"
#include "FMeshData.h"
#include "D3D11Util.h"
#include "GeometryGenerator.h"
#include "ConstantData.h"


#include "SoundManager.h"
#include "Time.h"
#include "InputManager.h"



#include "../Third-party/ImGui/imgui.h"
#include "../Third-party/ImGui/imgui_internal.h"
#include "../Third-party/ImGui/imgui_impl_dx11.h"
#include "../Third-party/ImGui/imgui_impl_win32.h"


UApp* UApp::Ins = nullptr;
LPCWSTR defaultVSFileName = L"Shaders/defaultVS.hlsl";
LPCWSTR defaultPSFileName = L"Shaders/defaultPS.hlsl";

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT	CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, message, wParam, lParam))
	{
		return true;
	}
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}



void UApp::Init(HINSTANCE hInstance)
{
	Ins = this;

	InitWindow();
	InitD3D(hInstance);
	InitImgui();
	//필요한 데이터 불러오기
	Loading();

	//타이머 초기화
	Time::GetInstance()->Init();
	SoundManager::GetInstance()->Init();
	
	//게임 시작시 메인 메뉴부터
	ChangeState(new MainMenuState());
}

void UApp::InitD3D(HINSTANCE hInstance)
{
	CreateDeviceAndSwapChain();
	CreateFrameBuffer();
	CreateShaders();

	// Create Constant Buffer
	D3D11_BUFFER_DESC constantbufferdesc = {};
	constantbufferdesc.ByteWidth = sizeof(VertexConstantData);
	constantbufferdesc.Usage = D3D11_USAGE_DYNAMIC;
	constantbufferdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantbufferdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	m_device->CreateBuffer(&constantbufferdesc, nullptr, &TransformCBuffer);
	
}

void UApp::InitWindow()
{
	WCHAR WindowClass[] = L"Break_Out";

	WCHAR Title[] = L"Break Out";


	WNDCLASSW wndclass = { 0, WndProc, 0,0,0,0,0,0,0, WindowClass };

	RegisterClassW(&wndclass);


	m_mainWindow = CreateWindowExW(0, WindowClass, Title, WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1024, 1024,
		nullptr, nullptr, wndclass.hInstance, nullptr);

	if (m_mainWindow)
	{
		ShowWindow(m_mainWindow, SW_SHOW);
		UpdateWindow(m_mainWindow);
	}
}

void UApp::InitImgui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("Resources/NanumGothic-Bold.ttf", 24.0f, nullptr, io.Fonts->GetGlyphRangesKorean());

	// ImGui 백엔드 초기화
	ImGui_ImplWin32_Init((void*)m_mainWindow);
	ImGui_ImplDX11_Init(m_device.Get(), m_deviceContext.Get());



}

void UApp::Loading()
{
	FMeshData cubeData = GeometryGenerator::MakeCube();
	cubeMesh = new UMesh(cubeData);

	FMeshData sphereData = GeometryGenerator::MakeSphere(1.0f,20,20);
	sphereMesh = new UMesh(sphereData);

	
}

void UApp::CreateDeviceAndSwapChain()
{
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
	};

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

	swapChainDesc.BufferDesc.Width = 0;
	swapChainDesc.BufferDesc.Height = 0;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.OutputWindow = m_mainWindow;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	//device,device context, swap chain 생성
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		featureLevels,
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION, &swapChainDesc, m_swapChain.GetAddressOf(), m_device.GetAddressOf(), nullptr, m_deviceContext.GetAddressOf());


	assert(SUCCEEDED(hr));

	//생성후 스왑체인 정보 가져오기
	DXGI_SWAP_CHAIN_DESC actualDesc = {};
	m_swapChain->GetDesc(&actualDesc);

	ViewportInfo = { 0.0f, 0.0f,
		static_cast<float>(actualDesc.BufferDesc.Width),
		static_cast<float>(actualDesc.BufferDesc.Height),
		0.0f, 1.0f };


}

void UApp::CreateFrameBuffer()
{
	HRESULT hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(m_frameBuffer.GetAddressOf()));

	assert(SUCCEEDED(hr));

	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	hr = m_device->CreateRenderTargetView(m_frameBuffer.Get(), &rtvDesc, m_frameBufferRTV.GetAddressOf());


}

void UApp::CreateShaders()
{
	D3D11Util::CreateVSAndInputlayout(defaultVSFileName, m_vertexShader, simpleInputLayout);
	D3D11Util::CreatePS(defaultPSFileName, m_pixelShader);

}

void UApp::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;

	HRESULT hr = m_device->CreateRasterizerState(&rasterizerDesc, m_rasterizerState.GetAddressOf());

	assert(SUCCEEDED(hr));


}

void UApp::ChangeState(IGameState* newState)
{
	nextState = newState;
}

void UApp::mainLoop()
{
	Update();
	Render();



}

ID3D11Device* UApp::GetDevice()
{
	return m_device.Get();
}

void UApp::Update()
{
	Time::GetInstance()->Update();
	InputManager::GetInstance()->Update();

	double deltaTime = Time::GetInstance()->GetDeltaTime();

	if(nextState != nullptr)
	{

		if(m_currentState != nullptr)
		{
			m_currentState->Exit();
			delete m_currentState;
		}

		m_currentState = nextState;
		m_currentState->Enter();
		nextState = nullptr;
	}


	if(m_currentState != nullptr)
	{

		m_currentState->Update(deltaTime);

	}
}

void UApp::Render()
{
	m_deviceContext->ClearRenderTargetView(m_frameBufferRTV.Get(), ClearColor);

	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceContext->IASetInputLayout(simpleInputLayout.Get());
	
	m_deviceContext->RSSetViewports(1, &ViewportInfo);
	m_deviceContext->RSSetState(m_rasterizerState.Get());

	m_deviceContext->OMSetRenderTargets(1, m_frameBufferRTV.GetAddressOf(), nullptr);

	m_deviceContext->VSSetConstantBuffers(0, 1, TransformCBuffer.GetAddressOf());

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if(m_currentState != nullptr)
	{
		m_currentState->Render();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	m_swapChain->Present(1, 0);


}
