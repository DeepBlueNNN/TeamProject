# D3D 팀플 테스트 프로젝트파일입니다.  
  
## 주요 변동사항  
+ 코드표기법 : 클래스 멤버변수 : m_variable / 함수 : Function(int param) / 구조체 멤버변수 : variable / 열거형 멤버변수 : ALL_CAP
+ framework.h 구성 및 순서변경
+ RenderUI() 함수 -> GUIRender()로 함수명 변경
+ GameObject2 -> GameObject 단일화
+ Transform : 디렉토리 Environment로 이동
+ Utility -> StringPath 클래스명 변경
+ Models -> Assets 애셋 디렉토리명 변경
+ 등등..

## 체크필요
+ Basid Object의 Light 쉐이더파일 호환 오류
+ 창크기 변경 시 MAIN->ResizeScreen() 오류
+ bool 자료형 변수 앞에 is로 시작 건의
+ struct Ray 위치 건의
+ 프로젝트명 추천 : OneButtonRun / D3D_Team / 등등..
