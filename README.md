# 벽돌 깨기

## 미리보기
[유튜브 링크](https://youtu.be/_GReAcy3QZg)

## 목차
1.[프로젝트 소개](#프로젝트-소개)



## 프로젝트 소개
DirectX11을 이용해서 벽돌깨기 게임을 만드는 프로젝트입니다.

개발 기간: 2026-06-04 ~ 2026-07-03

+ Languages:	C++, HLSL
+ Graphics API:	DirectX 11
+  Tools :	ImGui
+  + Environment:	Visual Studio 2022, Git
 
## 구성 요소
1.App
win32,Directx11 등을 초기화하고 메인 루프가 돌아가는 곳

2.InputManager
플레이어가 준 입력을 처리하는 클래스

3.SoundManager
사운드를 관리하는 클래스

4.Time
게임의 프레임을 조정하고 시간을 측정하는 클래스

5.GeometryGenerator
도형의 메시데이터를 생성하는 클래스, 정육면체와 구 데이터를 생성할 수 있음

6.IGameState
게임은 "state"로 구성되어있음 
1)MainMenuState : 게임 시작시 처음 등장하는 상태

2)InGameState : 벽돌깨기 게임이 진행되고있는 상태

3)ResultState : 게임 종료 후 결과를 알려주는 상태

7.ObjectFactory
각 State마다 존재해야하는 오브젝트를 생성해주는 클래스
State가 바뀌면 현재 State에있는 오브젝트를 모두 정리하고 다음 State에 존재해야하는 오브젝트를 생성한다.

8.Object
게임내에 존재하는 오브젝트를 나타내는 클래스
1)Ball : 벽돌깨기에서의 공

2)Block : 벽돌

3)Player : 플레이어

Object에 속하는 클래스

8-1.PhysicsComponent 
각종 물리 처리를 담당하는 클래스

8-2.MeshRenderer
메시 렌더링을 담당하는 클래스


