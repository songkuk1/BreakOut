#pragma once

#include "Time.h"
#include <windows.h>


void Time::Init()
{
    //초당 틱 수를 얻어옴
    QueryPerformanceFrequency(&frequency);

    //초기 시간 기록
    QueryPerformanceCounter(&prevTime);
}

void Time::Update()
{
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);

    double actualDeltaTime = static_cast<double>(currentTime.QuadPart - prevTime.QuadPart) / frequency.QuadPart;
    targetFrameTime = 1.0 / targetFPS;

	//목표 프레임 시간보다 실제 경과 시간이 짧으면 남은 시간을 Sleep으로 대기
    if (actualDeltaTime < targetFrameTime)
    {
        double remainingTime = targetFrameTime - actualDeltaTime;

        Sleep(static_cast<DWORD>(remainingTime * 1000));

        QueryPerformanceCounter(&currentTime);
        deltaTime = static_cast<double>(currentTime.QuadPart - prevTime.QuadPart) / frequency.QuadPart;
    }
    else
    {
        deltaTime = actualDeltaTime;
    }

	//모종의 이유로 델타 타임이 1/30초보다 길어지면 1/30초로 제한해서 프레임 드랍이 심하게 일어나지 않도록 함
    if (deltaTime > 1 / 30.0f)
    {
        deltaTime = 1 / 30.0f;
    }

    prevTime = currentTime;
}