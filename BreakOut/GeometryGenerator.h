#pragma once
#include "FMeshData.h"
#include "UVector.h"

class MeshData;


class GeometryGenerator
{
public:
	static FMeshData MakeCube();
	static FMeshData MakeSphere(float radius, int sliceCount, int stackCount);
	










};