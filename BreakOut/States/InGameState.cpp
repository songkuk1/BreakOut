#pragma once

#include "InGameState.h"
#include "../UObjectFactory.h"
#include "../PhysicsComponent.h" 
#include "../Third-party/ImGui/imgui.h"
#include "../UApp.h"
#include "ResultState.h"
void InGameState::Enter()
{
	
	player = UObjectFactory::GetInstance()->CreatePlayer({ 0.0f,-0.9f ,0.0f},{0.05f,0.025f ,0.05f});
    int countX = rowBlockNum;
    int countY = colBlockNum;
    float edgeMargin = 0.05f; // 마진을 좀 더 넉넉하게 잡는다.
    float fixedPadding = 0.01f; // 고정된 간격

    // 사용 가능한 총 너비
    float usableWidth = 2.0f - (edgeMargin * 2.0f);

    // 패딩이 차지하는 총 너비
    float totalPaddingWidth = fixedPadding * (countX - 1);

    // 블록 1개당 할당될 '실제 가로 길이' 계산
    float actualWidth = (usableWidth - totalPaddingWidth) / countX;
	float actualHeight = blockScale.y * 2.0f; // 블록의 실제 높이는 스케일값을 기반으로 계산
    // 역산한 실제 길이를 바탕으로 스케일(Scale) 재조정
    // actualWidth = blockScale.x * 2.0f 가정
    blockScale.x = actualWidth / 2.0f;

    // 시작점 (스케일값=실제크기 절반)
    float startX = -1.0f + edgeMargin + blockScale.x;
    float startY = 1.0f - edgeMargin - blockScale.y; // Y축 상단 여백도 edgeMargin과 동일하게 준다고 가정

    // 블록 간의 이동 간격 (반드시 '실제 크기 + 패딩' 이어야 함)
    float stepX = actualWidth + fixedPadding;
    float stepY = actualHeight + fixedPadding; // Y축 패딩을 X축과 동일하게 맞춘다고 가정

    for (int i = 0; i < countX; ++i)
    {
        float x = startX + (stepX * i);

        for (int j = 0; j < countY; ++j)
        {
            float y = startY - (stepY * j);

            blocks.push_back(UObjectFactory::GetInstance()->CreateBlock({ x, y, 0.0f }, blockScale));
        }
    }

    //공 생성
	ball = UObjectFactory::GetInstance()->CreateBall({ 0.0f,0.0f ,0.0f }, { 0.025f,0.025f ,0.025f });


    //게임 상태 초기화
	gameplayState = EInGameState::Ready;
    stateTimer = 3.0f;
    playScore = 0;
}

void InGameState::Update(double deltaTime)
{

    switch(gameplayState)
    {
        case EInGameState::Ready:
            stateTimer -= static_cast<float>(deltaTime);
            if(stateTimer <= 0.0f)
            {
                gameplayState = EInGameState::InPlay;
            }
            break;
        case EInGameState::InPlay:
            // 게임 진행 중 로직
            UObjectFactory::GetInstance()->Update(deltaTime);
			int maxScore = rowBlockNum * colBlockNum;
            if(ball->GetPhysicsComponent()->isGrouned() || maxScore == playScore)
            {
				UApp::Ins->ChangeState(new ResultState(rowBlockNum * colBlockNum, playScore));
            }
            break;

	}


	
}

void InGameState::Render()
{
	UObjectFactory::GetInstance()->Render();


    if (gameplayState == EInGameState::Ready)
    {
        // --- 1. 무조건 화면 한가운데를 찾는 절대 좌표 공식 ---
        ImVec2 screenSize = ImGui::GetIO().DisplaySize; // 현재 게임 창의 해상도
        ImVec2 screenCenter = ImVec2(screenSize.x * 0.5f, screenSize.y * 0.5f); // 정중앙 좌표

        // 창의 중심점(Pivot: 0.5, 0.5)을 화면 정중앙에 딱 맞춤
        ImGui::SetNextWindowPos(screenCenter, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        // 배경 투명화 및 UI 창 플래그
        ImGui::SetNextWindowBgAlpha(0.0f);
        ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoInputs |
            ImGuiWindowFlags_NoBackground;

        ImGui::Begin("CountdownUI", nullptr, window_flags);

        std::string countText;
        if (stateTimer > 0.0f)
        {
            countText = std::to_string(static_cast<int>(std::ceil(stateTimer)));
        }
        else
        {
            countText = u8"시작!";
        }

        ImGui::SetWindowFontScale(5.0f); // 폰트 크기 5배

        // --- 2. 텍스트 자체를 창 안에서 완벽하게 중앙 정렬 ---
                  
        ImVec2 textSize = ImGui::CalcTextSize(countText.c_str()); // 출력될 글자의 실제 가로세로 길이
        ImVec2 windowSize = ImGui::GetWindowSize(); // 현재 투명한 ImGui 창의 크기

        // 가로(X) 정중앙 배치
        ImGui::SetCursorPosX((windowSize.x - textSize.x) * 0.5f);
        // 세로(Y) 정중앙 배치 (글자 위아래 쏠림 방지)    
        ImGui::SetCursorPosY((windowSize.y - textSize.y) * 0.5f);

        // 출력
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "%s", countText.c_str());
        ImGui::SetWindowFontScale(1.0f);

        ImGui::End();
    }

}

void InGameState::Exit()
{
	UObjectFactory::GetInstance()->ReleaseAll();


    player = nullptr;

    
    ball = nullptr;

    for(int i =0; i < blocks.size(); ++i)
    {
        
		blocks[i] = nullptr;
	}

	blocks.Clear();
}
