#pragma once
#include "GeometryGenerator.h"


using DirectX::SimpleMath::Vector3;

FMeshData GeometryGenerator::MakeRectangle()
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
	

	for(size_t i =0; i < i < positions.size(); ++i)
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
