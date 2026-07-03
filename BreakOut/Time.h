#pragma once
#include <windows.h>

class Time
{
	Time() = default;
	~Time() = default;

public:
	static Time* GetInstance()
	{
		static Time instance;
		return &instance;
	}

	void Init();
	void Update();

	double GetDeltaTime() const { return deltaTime * timeScale; }


	LARGE_INTEGER frequency;
	LARGE_INTEGER prevTime;

	double timeScale = 1.0f;
	double deltaTime;

	//목표 프레임 시간
	double targetFrameTime;
	//목표 FPS
	int targetFPS = 60;
};
