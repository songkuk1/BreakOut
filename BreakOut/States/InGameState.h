#pragma once


#include "IGameState.h"
#include "../UObject.h"
#include <SimpleMath.h>
#include "../UVector.h"


using DirectX::SimpleMath::Vector3;

class InGameState : public IGameState
{



private:

	enum class EInGameState 
	{
		Ready,
		InPlay,
	};

	EInGameState gameplayState;

	UObject* player = nullptr;
	UObject* ball = nullptr;
	UVector<UObject*> blocks;

	float blockpadding;

	Vector3 blockScale = { 0.1f,0.05f,0.05f };

	int rowBlockNum = 15;
	int colBlockNum = 5;

	float stateTimer = 0.0f;

	int playScore;
public:
	virtual void Enter() override;
	virtual void Update(double deltaTime) override;
	virtual void Render() override;
	virtual void Exit() override;
	void AddScore(int score) { playScore += score; }
	

};