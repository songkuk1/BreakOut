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
 
## 구성 클래스
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

구 데이터의 경우, 회전을 이용하여 생성하는 방식이다.
1)원점을 기준으로 radius만큼 아래에 남극점을 찍는다.
<img width="862" height="698" alt="image" src="https://github.com/user-attachments/assets/0cdbd85e-fe46-46ab-b9d0-52cd166be8a3" />

2)원점을 기준으로 z축 회전을하여, 북극점까지의 자오선을 긋는다.
<img width="1200" height="718" alt="image" src="https://github.com/user-attachments/assets/88634d84-e8d6-4fe3-9530-f5c1bbda0da3" />

3)자오선에 있는 점을 y축 회전시키면 구가 만들어진다.
<img width="400" height="226" alt="SphereGenerate" src="https://github.com/user-attachments/assets/cac08455-58e5-44a3-939a-225d9271051f" />

점들을 많이 설정할수록 완벽한 구에 가까워진다.

6.IGameState
게임은 "state"로 구성되어있음 
1)MainMenuState : 게임 시작시 처음 등장하는 상태
<img width="995" height="958" alt="image" src="https://github.com/user-attachments/assets/7722aa45-2fd0-4b39-a4cc-1d067ab08272" />



2)InGameState : 벽돌깨기 게임이 진행되고있는 상태
<img width="982" height="964" alt="image" src="https://github.com/user-attachments/assets/680aa3f6-3758-4f7f-9afa-04753703f00e" />



3)ResultState : 게임 종료 후 결과를 알려주는 상태
<img width="990" height="960" alt="image" src="https://github.com/user-attachments/assets/18745039-f642-413a-8b50-947e20846894" />

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


