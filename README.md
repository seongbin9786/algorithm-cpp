## C++ Algorithm Practices on WSL

기준 환경:

- Windows 10 Home
- WSL 2
- Ubuntu 20.04
- VSCode
- C/C++ Extensions Pack (VSCode Extension)

### How to Set-up

1. Clone Repository

2. Copy templates/include to /include

3. Depdendency 설치

4. 빌드/실행/디버그는 아래 명령어 참고

### 지금 불편한 점

1. debug mode와 release mode의 전환이 매우 불편함

    - `make win` 스크립트 만들기: `trigger.hpp` 파일 수정 + `make clean` + `make all OS=win`

2. Test Case Runner 필요 (main.cpp 실행 X)

    - (ex) `make test 16`
    - 16번 TC 수행 (16.cpp) => `void test_16();` 실행

3. 문제 넘버를 입력하면 해당 문제만 빌드하도록. 

    - 문제가 점점 쌓이고 있고 빌드 타임이 길어지는 중. src/ 다 빌드하기 때문.
    - 가능하면 main.cpp가 없으면 더 좋을듯. 이게 어려우면 어쩔 수 없이 main.cpp에서 불러오고, 최소한만 빌드에 포함
    - `make build 16` => `main.cpp` 재작성 + `make win` 수행

4. Generate 로 문제 넘버랑 문제 이름 받아서 폴더를 자동 생성

    - (ex) `make new 016_Anagram`
    - 자동으로 파일명 problem_16.cpp, .hpp 생성 후 내용까지 작성함.

5. `int problem_()` => `void problem_()` 으로 통일

### Formatting

VSCode에서 C/C++ format 하는 방법 (기본값 세팅으로 안 됨)

Format Document (Shift Alt F) 눌러도 무반응인데, 우클릭 해서 Format Document With를 클릭하고 > Configure Default Formatter > C/C++ 누르면 그 때 부터 잘 됨.

### Dependency

#### 1. Linux의 C/C++ 컴파일 환경 설치(디버거 포함)

gdb가 디버거이다. VSCode에서도 활용하니 설치 필요.

`sudo apt-get install build essential gdb`

#### 2. VSCode 확장팩 설치 (언어 + a)

`Ctrl+Shift+X`(확장 탭) > C/C++ Extensions Pack (VS Code Extension)

### Template generated by

C/C++ Project Generator (확장팩에 미포함. 따로 설치해야.)

### Reference

[WSL 2에 C++ 개발환경 셋업하기](https://evanss.tistory.com/entry/WSL-2-VS-Code%EB%A1%9C-C-%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8-%EA%B5%AC%EC%84%B1%ED%95%98%EA%B8%B0?category=941001)

### Build

`Ctrl+Shift+B` 혹은 `make all`

#### Build Windows Binary

make all OS=win

#### Build Linux Binary

make all

### Run Linux Binary

make run

### Debug

F5 - choose g++

### 주의 사항

1. 파일 읽는 경로(CWD) 기준: 
    - 명령어를 입력하는 폴더 (YES)
    - executable이 있는 폴더 (NO) - 대체 왜 이러는지 모르겠음.. Makefile 때문일수도.

2. 전처리문 수정 시 `make clean` 필요
    - `make all` 해도 무시되는 듯

### Reference

[CMake 설치 및 이해](https://evanss.tistory.com/entry/WSL-2%EC%99%80-VS-Code%EC%97%90%EC%84%9C-CMake%EB%A1%9C-C-%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8-%EA%B5%AC%EC%84%B1%ED%95%98%EA%B8%B0?category=941001)
