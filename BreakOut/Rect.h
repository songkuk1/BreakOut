#pragma once
#include <SimpleMath.h>	

using DirectX::SimpleMath::Vector2;


struct FRect
{
	
	Vector2 _min;
	Vector2 _max;

	FRect() : _min(Vector2(0.0f, 0.0f)), _max(Vector2(0.0f, 0.0f)) {}
	FRect(Vector2 min, Vector2 max) : _min(min), _max(max) {}

	float GetWidth() const { return _max.x - _min.x; }
	float GetHeight() const { return _max.y - _min.y; }

	//물체가 움직이면 그에 맞춰서 충돌박스도 옮겨줘야함
	void SetCenter(const Vector2& newCenter)
	{
		float halfWidth = GetWidth() / 2.0f;
		float halfHeight = GetHeight() / 2.0f;

		_min.x = newCenter.x - halfWidth;
		_min.y = newCenter.y - halfHeight;
		_max.x = newCenter.x + halfWidth;
		_max.y = newCenter.y + halfHeight;
	}

	bool Intersects(const FRect& other) const
	{
		return !(_min.x > other._max.x || _max.x < other._min.x ||
			_min.y > other._max.y || _max.y < other._min.y);
	}

};