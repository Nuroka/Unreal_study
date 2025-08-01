# Unreal Study

## 개요
이 저장소는 **Unreal Engine 5.4** 기반으로 언리얼 엔진을 학습하기 위해 만든 여러 실습용 프로젝트들을 모아둔 공간입니다. GameDev.tv의 Unreal Engine C++ 개발 강의에서 다루는 튜토리얼 예제들을 직접 만들어보고 확장하면서 엔진 구조, C++/블루프린트 연동, 게임플레이 구현, 입력 시스템, UI, 물리, 퍼즐 설계 등을 익히는 것이 목적입니다.  

## 포함된 프로젝트 및 간단한 설명
각 서브 프로젝트는 언리얼 엔진을 실습하며 배우기 좋은 프로토타입 형태의 게임입니다.

- **ToonTanks**  
  탱크를 조종하며 적의 타워와 교전하는 3D 슈터형 프로토타입입니다. 플레이어 탱크와 적 타워의 커스텀 Pawn 구현, 향상된 입력 시스템(Enhanced Input), 발사체 생성, 체력/데미지 로직, 이펙트(연기/폭발), HUD 메시지, 카메라 쉐이크 등 기본적인 게임플레이 구성 요소를 학습할 수 있습니다. :contentReference[oaicite:1]{index=1}

- **Shoot**  
  기본적인 슈팅 메커닉을 연습하는 간단한 샘플 게임입니다. 플레이어 입력을 받아 발사체를 생성하고 목표물과 충돌 처리, 점수/피드백 등을 통해 실시간 반응형 게임플레이의 기초를 다집니다. (Course 스타일과 구조를 공유하는 예제) :contentReference[oaicite:2]{index=2}

- **ObstacleAssault**  
  장애물 코스 형태의 실습 프로젝트로, 캐릭터 이동, 플랫폼 트래버설, 물리적 제어, 애니메이션/이동 시스템 등을 통한 환경 내 탐색과 난이도 있는 경로 수행을 연습합니다. 언리얼 엔진의 입력, 이동, 게임 흐름 제어를 자연스럽게 결합하는 연습에 적합합니다. :contentReference[oaicite:3]{index=3}

- **CryptRaider**  
  3D 퍼즐 기반의 탐색형 게임으로, 플레이어가 객체를 잡아 움직이고, 트리거를 활성화하여 문이나 벽을 열어 금상(gold statue)을 찾는 구조입니다. 라이트닝(Lumen), 모듈러 레벨 디자인, 라인 트레이싱, C++와 블루프린트 연동, 간단한 HUD, 사운드 효과 등을 포함하여 보다 복합적인 게임 시스템을 경험할 수 있습니다. :contentReference[oaicite:4]{index=4}

## 주요 학습 요소 (Learning Goals)
- Unreal Engine 5.4 환경 구성 및 프로젝트 설정  
- C++ 기반 게임플레이 로직 구현  
- Enhanced Input 시스템 사용  
- Pawn/Actor/Component 구조 이해  
- 블루프린트와 C++ 간 데이터/함수 호출  
- HUD/UI 구성 및 실시간 피드백  
- 레벨 디자인과 모듈러 구성  
- 라인 트레이싱, 충돌, 물리 인터랙션  
- 사운드 및 이펙트 통합  
- 게임 상태 관리 (시작/종료/정답 처리 등)

## 기술 스택
- **엔진**: Unreal Engine 5.4  
- **언어**: C++ (및 일부 블루프린트 연동)  
- **플랫폼**: Windows (Visual Studio 기반 빌드)  
- **입력 시스템**: Enhanced Input  
- **렌더링**: Lumen (CryptRaider 등에서 사용)  

## 필수 사전 준비
1. **Unreal Engine 5.4** 설치 (Epic Games Launcher에서 5.4.x 버전 설치)  
2. **Visual Studio** (C++ 개발 워크로드 포함)  
   - Windows의 경우 "Desktop development with C++" 워크로드, Unreal용 추천 구성  
3. Git 클라이언트 (옵션)  

## 실행 방법 (세부)

1. 원하는 서브 프로젝트 폴더로 이동합니다. 예:  
   - `ToonTanks/`  
   - `Shoot/`  
   - `ObstacleAssault/ObstacleAssault/`  
   - `CryptRaider/`  

2. 해당 폴더 안의 `.uproject` 파일을 우클릭하여 **"Generate Visual Studio project files"** 를 실행합니다.  
3. 생성된 `.sln` 솔루션을 Visual Studio로 엽니다.  
4. Visual Studio에서 **Configuration**을 `Development Editor`로 설정한 뒤 빌드합니다.  
5. `.uproject` 파일을 더블클릭하여 Unreal Editor에서 엽니다.  
6. Editor 내에서 **Play** 버튼을 눌러 게임을 실행합니다.  

> 참고: 각 프로젝트는 언리얼의 기본 튜토리얼 구조를 따르므로, 추가적인 플러그인 활성화나 입력 매핑 설정이 필요할 수 있습니다. 에디터 내 메시지를 확인하고 요구되는 설정을 적용해주세요.

