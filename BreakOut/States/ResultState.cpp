#pragma once
#include "ResultState.h"
#include "MainMenuState.h"
#include "../UApp.h"
#include "../Third-party/ImGui/imgui.h"
ResultState::ResultState(int maxScore, int playerScore) : scoreMessage(u8"점수 : " + std::to_string(playerScore) + u8" / " + std::to_string(maxScore))
{
	if(maxScore == playerScore)
	{
		resultMessage = u8"클리어 하셨습니다!";
	}
	else
	{
		resultMessage = u8"게임 오버!";
	}



}

void ResultState::Enter()
{
}

void ResultState::Update(double deltaTime)
{
}

void ResultState::Render()
{
    // 1. 화면 중앙 좌표 및 창 크기 설정
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

    // 2. 창 플래그 설정: 타이틀바, 크기조절, 이동 등 숨김
    ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse;

    // 3. ImGui 창 시작
    ImGui::Begin("ResultScreen", nullptr, window_flags);

    float windowWidth = ImGui::GetWindowSize().x;

    // 상단 여백
    ImGui::Dummy(ImVec2(0.0f, 30.0f));

    // --- 4. 결과 메시지 (클리어 / 게임 오버) ---
    ImGui::SetWindowFontScale(2.0f); // 폰트 크기 2배 확대
    float resultWidth = ImGui::CalcTextSize(resultMessage.c_str()).x;
    ImGui::SetCursorPosX((windowWidth - resultWidth) * 0.5f); // 가운데 정렬
    ImGui::Text("%s", resultMessage.c_str());
    ImGui::SetWindowFontScale(1.0f); // 폰트 크기 원상 복구

    ImGui::Dummy(ImVec2(0.0f, 20.0f)); // 줄바꿈 여백

    // --- 5. 점수 메시지 ---
    ImGui::SetWindowFontScale(1.5f); // 폰트 크기 1.5배 확대
    float scoreWidth = ImGui::CalcTextSize(scoreMessage.c_str()).x;
    ImGui::SetCursorPosX((windowWidth - scoreWidth) * 0.5f); // 가운데 정렬
    ImGui::Text("%s", scoreMessage.c_str());
    ImGui::SetWindowFontScale(1.0f);

    ImGui::Dummy(ImVec2(0.0f, 50.0f)); // 버튼 위 여백


    // --- 버튼 스타일 설정 ---
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 10));
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(255, 200, 100, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(255, 170, 70, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(255, 140, 50, 255));

    // --- 6. 하단 버튼 (메인 메뉴 / 종료) ---
    ImVec2 buttonSize(200.0f, 40.0f);
    float buttonPosX = (windowWidth - buttonSize.x) * 0.5f;

    ImGui::SetCursorPosX(buttonPosX);
    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.5f);
    if (ImGui::Button(u8"메인 메뉴로", buttonSize))
    {
        // 메인 메뉴 State로 전환
        UApp::Ins->ChangeState(new MainMenuState());
    }

    ImGui::Spacing();

    ImGui::SetCursorPosX(buttonPosX);
    if (ImGui::Button(u8"게임 종료", buttonSize))
    {
        // 엔진 종료 로직
        PostMessage(UApp::Ins->m_mainWindow, WM_QUIT, 0, 0);
    }
    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar(2);
    // 창 닫기
    ImGui::End();

}

void ResultState::Exit()
{



}
