#프로그램을 시작하기전에 라이브러리 경로(PATH)를 지정해야 합니다.

'''
  bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/Your/PATH/2018_ESW_Project/server/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/Your/PATH/2018_ESW_Project/client/lib
'''

#source code설명

##저희가 만든 프로그램은 '하나의 server가 관리하는 client들의 그룹채팅 프로그램'입니다.
##server와 client가 확실하게 나누어져 있기 때문에 한 사람은 server source를 다른 한 사람은 client source를 맡아서 처리했습니다.

#구조는 이렇습니다.
##server로 동작할 PC는 한 대만 있으면 가능하고 server와 관련된 파일들만 있으면 되기때문에 server폴더와 client폴더를 따로 생성 했습니다.
##이렇게 만들면 client동작을 할 PC들도 client와 관련된 파일들만 다운받아 사용할 수 있기 때문입니다.

#그리고 각 폴더의 구성은

![makefile](C:/Users/일구칠/Desktop/makefile.png)

##이런식으로 lib, include, player 폴더를 각각 만들어서 lib에는 헤더파일로 만들 함수들의 소스코드와 Makefile, include에는 헤더파일들, player에는 main문과 Makefile을 넣었습니다.

#서버부분 Library 이름과 동작 기능

#서버부분 main source 동작 기능

#클라이언트 부분 Library 이름과 동작 기능

#클라이언트 부분 main source 동작 기능

#결과
