#include "UMeshRenderer.h"
#include "UApp.h"
#include "D3D11Util.h"
#include "ConstantData.h"

const UINT UMeshRenderer::BlockOrder = 100;
const UINT UMeshRenderer::BallOrder = 50;
const UINT UMeshRenderer::PlayerOrder = 999;


void UMeshRenderer::SetShader(ID3D11InputLayout* inputLayout, ID3D11VertexShader* vs, ID3D11PixelShader* ps)
{
	PS = ps;
	VS = vs;
	InputLayout = inputLayout;
}

void UMeshRenderer::DrawMesh(VertexConstantData data)
{
	static ID3D11VertexShader* lastVS = nullptr;
	static ID3D11PixelShader* lastPS = nullptr;
	static ID3D11InputLayout* lastInputLayout = nullptr;

	if(m_meshes)
	{
		if(lastVS == nullptr)
		{
			UApp::Ins->GetContext()->IASetInputLayout(InputLayout.Get());
			UApp::Ins->GetContext()->VSSetShader(VS.Get(), 0, 0);
			UApp::Ins->GetContext()->PSSetShader(PS.Get(), 0, 0);
		}
		else
		{
			if (lastVS != VS.Get())
				UApp::Ins->GetContext()->VSSetShader(VS.Get(), 0, 0);
			if (lastPS != PS.Get())
				UApp::Ins->GetContext()->PSSetShader(PS.Get(), 0, 0);
			if (lastInputLayout != InputLayout.Get())
				UApp::Ins->GetContext()->IASetInputLayout(InputLayout.Get());

		}


		D3D11Util::UpdateConstantBuffer(UApp::Ins->GetContext(), UApp::Ins->GetTransformCBuffer(), data);
		m_meshes->Draw();
	}



}
