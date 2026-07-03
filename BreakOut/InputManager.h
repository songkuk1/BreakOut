#pragma once

constexpr int MAX_KEYS = 256;

class InputManager
{
public:
		 
	InputManager();
	~InputManager();

	static InputManager* GetInstance();


	// 매 프레임마다 키보드 상태 갱신

	void Update();

	bool CurrentKeyStates[MAX_KEYS] = { 0 };
	bool PreviousKeyStates[MAX_KEYS] = { 0 };


	bool IsKeyDown(int key);
	bool IsPrevKeyDown(int key);
	bool IsKeyPressed(int key);
	bool IsKeyReleased(int key);




	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;




};
