#include <Windows.h>
#include "InputManager.h"


InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

InputManager* InputManager::GetInstance()
{
	static InputManager instance;

	return &instance;
}

void InputManager::Update()
{
	//매 프레임마다 현재 키상태 내용을 이전 키상태 내용으로 복사하고 현재 키상태를 갱신
	memcpy(PreviousKeyStates, CurrentKeyStates, sizeof(bool) * MAX_KEYS);

	for (int i = 0; i < MAX_KEYS; i++)
	{
		CurrentKeyStates[i] = GetAsyncKeyState(i) & 0x8000; //현재 눌려있는지 여부
	}
}

bool InputManager::IsKeyDown(int key)
{
	return CurrentKeyStates[key];
}

bool InputManager::IsPrevKeyDown(int key)
{
	return PreviousKeyStates[key];
}

//눌리기 시작
bool InputManager::IsKeyPressed(int key)
{
	return IsKeyDown(key) && !IsPrevKeyDown(key);
}

//키 떼짐
bool InputManager::IsKeyReleased(int key)
{
	return !IsKeyDown(key) && IsPrevKeyDown(key);

}

