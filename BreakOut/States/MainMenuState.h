#pragma once
#include "IGameState.h"
class MainMenuState : public IGameState
{
public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Exit() override;

};