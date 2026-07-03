#pragma once

class IGameState
{
public:
	virtual ~IGameState() = default;

	//해당 스테이트로 진입할때 호출
	virtual void Enter() = 0;

	//매 프레임마다 업데이트하거나 체크해야 하는로직이있으면 작성
	virtual void Update(double deltaTime) = 0;
	
	virtual void Render() = 0;
	//스테이트에서 나갈때 호출
	virtual void Exit() = 0;
};