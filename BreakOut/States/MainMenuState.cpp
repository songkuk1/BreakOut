#pragma once
#include "MainMenuState.h"
#include "../UObjectFactory.h"
#include "../Third-party/ImGui/imgui.h"
#include "../UApp.h"
#include "InGameState.h"
void MainMenuState::Enter()
{


}

void MainMenuState::Update(double deltaTime)
{
	



}

void MainMenuState::Render()
{

    // 화면 중앙 좌표 계산
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    // 창 크기 고정
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

    // 창 플래그 설정: 타이틀바 숨김, 크기 조절 불가, 이동 불가, 접기 불가
    ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse;

    // 창 시작
    ImGui::Begin("MainMenu", nullptr, window_flags);

    float windowWidth = ImGui::GetWindowSize().x;

    // --- 1. 게임 제목 ---
    ImGui::SetWindowFontScale(2.5f); // 폰트 크기 임시 확대
    const char* titleText = "Break Out!";
    float titleWidth = ImGui::CalcTextSize(titleText).x;
    ImGui::SetCursorPosX((windowWidth - titleWidth) * 0.5f); // 가운데 정렬
    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.2f);
    ImGui::Text(titleText);
    ImGui::SetWindowFontScale(1.0f); // 폰트 크기 원상 복구

    // 여백
    ImGui::Dummy(ImVec2(0.0f, 30.0f));

    // 버튼 크기 설정
    ImVec2 buttonSize(200.0f, 40.0f);
    float buttonPosX = (windowWidth - buttonSize.x) * 0.5f;

    // --- 버튼 스타일 설정 ---
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 10));
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(255, 200, 100, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(255, 170, 70, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(255, 140, 50, 255));

    // --- 2. 게임 시작 버튼 ---
    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 200) * 0.5f);
    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.5f);
    if (ImGui::Button(u8"게임 시작", buttonSize))
    {

        UApp::Ins->ChangeState(new InGameState());
    }

    // 여백
    ImGui::Spacing();

    // --- 3. 게임 종료 버튼 ---
    ImGui::SetCursorPosX(buttonPosX);
    if (ImGui::Button(u8"게임 종료", buttonSize))
    {

        PostMessage(UApp::Ins->m_mainWindow, WM_QUIT, 0, 0);
    }

    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar(2);
    // 창 종료
    ImGui::End();
}

void MainMenuState::Exit()
{

}
