#include "UMesh.h"
#include "FMeshData.h"
#include "UApp.h"
#include <iostream>




UMesh::UMesh(FMeshData& meshData)
{
	vertexCount = meshData.vertices.size();
	indexCount = meshData.indices.size();
	stride = sizeof(FVertex);

	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.ByteWidth = sizeof(FVertex) * vertexCount;
	vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexBufferSRD = { meshData.vertices.data() };

	HRESULT hResult = UApp::Ins->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexBufferSRD, vertexBuffer.GetAddressOf());

	if (FAILED(hResult))
	{
		std::cout << "Create VertexBuffer in MeshCreate Failed" << std::endl;
		return;
	}

	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.ByteWidth = sizeof(uint32_t) * indexCount;
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA indexBufferSRD = { meshData.indices.data() };
	hResult = UApp::Ins->GetDevice()->CreateBuffer(&indexBufferDesc, &indexBufferSRD, indexBuffer.GetAddressOf());
	if (FAILED(hResult))
	{
		std::cout << "Create IndexBuffer in MeshCreate Failed" << std::endl;
		return;
	}
}

void UMesh::Draw()
{
	UINT offset = 0;
	UApp::Ins->GetContext()->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	UApp::Ins->GetContext()->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, offset);
	UApp::Ins->GetContext()->DrawIndexed(indexCount, 0, 0);


}
