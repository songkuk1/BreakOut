#pragma once
#include "IGameState.h"
#include <string>


class ResultState : public IGameState
{

	public:
		ResultState(int maxScore, int playerScore);
		~ResultState() = default;
	virtual void Enter() override;
	virtual void Update(double deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;

	std::string resultMessage;
	std::string scoreMessage;


};