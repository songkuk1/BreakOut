#pragma once
#include "GeometryGenerator.h"
#include "FVertex.h"
#include "UVector.h"

using DirectX::SimpleMath::Vector3;

FMeshData GeometryGenerator::MakeCube()
{
	UVector<Vector3> positions;

	//¾Õ¸é
	positions.push_back({ Vector3(1.0f, -1.0f, -1.0f) });
	positions.push_back({ Vector3(-1.0f, -1.0f, -1.0f) });
	positions.push_back({ Vector3(-1.0f, 1.0f, -1.0f) });
	positions.push_back({ Vector3(1.0f, 1.0f, -1.0f) });

	//¿ÞÂÊ¸é
	positions.push_back({ Vector3(-1.0f, -1.0f, -1.0f) });
	positions.push_back({ Vector3(-1.0f, -1.0f, 1.0f) });
	positions.push_back({ Vector3(-1.0f, 1.0f, 1.0f) });
	positions.push_back({ Vector3(-1.0f, 1.0f, -1.0f) });


	//¿À¸¥ÂÊ¸é
	positions.push_back({ Vector3(1.0f, -1.0f, -1.0f) });
	positions.push_back({ Vector3(1.0f, 1.0f, -1.0f) });
	positions.push_back({ Vector3(1.0f, 1.0f, 1.0f) });
	positions.push_back({ Vector3(1.0f, -1.0f, 1.0f) });

	//µÞ¸é
	positions.push_back({ Vector3(1.0f, -1.0f, 1.0f) });
	positions.push_back({ Vector3(-1.0f, -1.0f, 1.0f) });
	positions.push_back({ Vector3(-1.0f, 1.0f, 1.0f) });
	positions.push_back({ Vector3(1.0f, 1.0f, 1.0f) });

	//À­¸é
	positions.push_back({ Vector3(1.0f, 1.0f, -1.0f) });
	positions.push_back({ Vector3(-1.0f, 1.0f, -1.0f) });
	positions.push_back({ Vector3(-1.0f, 1.0f, 1.0f) });
	positions.push_back({ Vector3(1.0f, 1.0f, 1.0f) });

	//¾Æ·§¸é
	positions.push_back({ Vector3(1.0f, -1.0f, -1.0f) });
	positions.push_back({ Vector3(1.0f, -1.0f, -1.0f) });
	positions.push_back({ Vector3(-1.0f, -1.0f, 1.0f) });
	positions.push_back({ Vector3(1.0f, -1.0f, 1.0f) });
	FMeshData meshData;
	

	for(size_t i =0; i < positions.size(); ++i)
	{
		FVertex v;
		v.position = positions[i];
		v.normal = v.position;
		v.normal.Normalize();
		meshData.vertices.push_back(v);
	}

	meshData.indices = {
	0,  1,  2,  0,  2,  3,  // ¾Õ¸é
	4,  5,  6,  4,  6,  7,  // ¿ÞÂÊ¸é
	8,  9,  10, 8,  10, 11, // ¿À¸¥ÂÊ
	12, 13, 14, 12, 14, 15, // µÞ¸é
	16, 17, 18, 16, 18, 19, // À­¸é
	20, 21, 22, 20, 22, 23  // ¾Æ·§¸é
	};

	return meshData;
}

FMeshData GeometryGenerator::MakeSphere(float radius,int sliceCount,int stackCount)
{
	FMeshData meshData;

    const float dTheta = DirectX::XM_2PI / float(sliceCount);

    const float dPhi = -DirectX::XM_PI / float(stackCount);

	UVector<FVertex>& vertices = meshData.vertices;
	UVector<uint32_t>& indices = meshData.indices;

	for(int i = 0; i <= stackCount; ++i)
	{
		Vector3 startPoint = Vector3::Transform(Vector3(0.0f, -radius,0.0f ), DirectX::SimpleMath::Matrix::CreateRotationZ(dPhi * i));

		for(int j =0; j <= sliceCount; ++j)
		{
			FVertex v;
			v.position = Vector3::Transform(startPoint, DirectX::SimpleMath::Matrix::CreateRotationY(dTheta * j));
			v.normal = v.position;
			v.normal.Normalize();

			vertices.push_back(v);
		}

	}

	for(int i =0; i < stackCount; ++i)
	{
		int offset = i * (sliceCount + 1);

		for(int j = 0; j < sliceCount; ++j)
		{
			indices.push_back(j + offset);
			indices.push_back(j + offset + sliceCount + 1);
			indices.push_back(j + offset + sliceCount + 2);

			indices.push_back(j + offset);
			indices.push_back(j + offset + sliceCount + 2);
			indices.push_back(j + offset + 1);
		}
	}


	return meshData;
}
