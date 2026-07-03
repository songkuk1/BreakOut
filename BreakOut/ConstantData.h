#pragma once

#include <SimpleMath.h>

using DirectX::SimpleMath::Matrix;

struct VertexConstantData
{
	Matrix model;
	Matrix view;
	Matrix proj;

};