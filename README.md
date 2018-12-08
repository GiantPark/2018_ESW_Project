### 프로그램을 시작하기전에 라이브러리 경로(PATH)를 지정해야 합니다.

```
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/Your/PATH/2018_ESW_Project/server/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/Your/PATH/2018_ESW_Project/client/lib
```

### source code설명

저희가 만든 프로그램은 '하나의 server가 관리하는 client들의 그룹채팅 프로그램'입니다.
server와 client가 확실하게 나누어져 있기 때문에 한 사람은 server source를 다른 한 사람은 client source를 맡아서 처리했습니다.

구조는 이렇습니다.
server로 동작할 PC는 한 대만 있으면 가능하고 server와 관련된 파일들만 있으면 되기때문에 server폴더와 client폴더를 따로 생성 했습니다.
이렇게 만들면 client동작을 할 PC들도 client와 관련된 파일들만 다운받아 사용할 수 있기 때문입니다.

그리고 각 폴더의 구성은



이런식으로 lib, include, player 폴더를 각각 만들어서 lib에는 헤더파일로 만들 함수들의 소스코드와 Makefile, include에는 헤더파일들, player에는 main문과 Makefile을 넣었습니다.

### 서버부분 Library 이름과 동작 기능

1)addclient.c : 새로운 채팅 참가자 처리 -> 채팅 클라이언트 목록에 추가, 유저 수 증가

2)getmax.c : 최대 소켓번호 찾기

3)removeclient.c : 채팅 탈퇴 처리 -> 저장된 리스트 재배열, 유저 수 감소

4)tcp_listen.c : listen 소켓 생성 및 listen -> 클라이언트로부터 연결요청을 기다림

5)thread.c : 명령어를 처리할 스레드 -> 서버가 명령어를 쓰면 그 명령어에 맞는 출력을 해줌

### 서버부분 main source 동작 기능

### 서버 실행 명령어

```
./server 9999 //port 번호
```
### 서버 명령어


### 클라이언트 부분 Library 이름과 동작 기능

1)client_tcp_connect.c : 서버와의 tcp_connect 설정

### 클라이언트 부분 main source 동작 기능

1)서버로 메세지 전달

2)서버에서 받은 메세지 처리 (방 입장 여부에 따라 글자색을 바꿔줌)

3)각종 유저 명령어 출력

### 클라이언트 실행 명령어
```
./client (server IP) (port number) (nick name)
```
### 클라이언트 명령어
```
mk (room name)
in (room name)
rl
```
mk (방 이름) : 입력한 방 이름으로 방을 생성합니다.

in (방 이름) : 입력한 방으로 입장합니다.

rl : (room list) 방의 목록을 보여줍니다.

### 결과

![client](./img/client 1.PNG)
