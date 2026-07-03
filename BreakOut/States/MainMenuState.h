#pragma once
#include "IGameState.h"
#include "../UObject.h"
class MainMenuState : public IGameState
{
	
public:


	virtual void Enter() override;
	virtual void Update(double deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;

};