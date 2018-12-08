#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "thread.h"
#include "addclient.h"
#include "removeclient.h"
#include "getmax.h"
#include "tcp_listen.h"

//this is server C source file
#define MAXLINE  511
#define MAX_SOCK 1024 // 솔라리스의 경우 64
#define MAX_ROOM 10
#define MAX_PERSON 5

char *EXIT_STRING = "exit";	// 클라이언트의 종료요청 문자열
char *START_STRING = "Connected to chat_server \n";
char *ROOM_STRING = "There is no room, create room plz \n";
char *ROOM_IN = "goin";
char *ROOM_OUT = "goout";
char *ROOM_NO = "There is no such room\n";
char *ROOM_LIST = "___ROOM LIST___\n";
char *OUT = "!out";

// 클라이언트 환영 메시지
int maxfdp1;				// 최대 소켓번호 +1
int num_user = 0;			// 채팅 참가자 수
int num_chat = 0;			// 지금까지 오간 대화의 수
int clisock_list[MAX_SOCK];		// 채팅에 참가자 소켓번호 목록
char ip_list[MAX_SOCK][20];		//접속한 ip목록
int listen_sock;			// 서버의 리슨 소켓

int room[MAX_ROOM][MAX_PERSON]={0,};
int roomcnt = 0;
int personcnt[MAX_ROOM] ={0,};
char *room_N[MAX_ROOM]={NULL,};
char bufall[MAXLINE];
							// 새로운 채팅 참가자 처리
void addClient(int s, struct sockaddr_in *newcliaddr);
int getmax();				// 최대 소켓 번호 찾기
void removeClient(int s);	// 채팅 탈퇴 처리 함수
int tcp_listen(int host, int port, int backlog); // 소켓 생성 및 listen
void errquit(char *mesg) { perror(mesg); exit(1); }

time_t ct;
struct tm tm;

int main(int argc, char *argv[]) {

	for (int a = 0; a < MAX_ROOM; a++)
	{
		room_N[a] = malloc(sizeof(char) * 10);
	}

	struct sockaddr_in cliaddr;
	char buf[MAXLINE + 1]; //클라이언트에서 받은 메시지
	int i, j, room_in_f = 0,nbyte, accp_sock, addrlen = sizeof(struct
		sockaddr_in);
	fd_set read_fds;	//읽기를 감지할 fd_set 구조체
	pthread_t a_thread;

	if (argc != 2) {
		printf("사용법 :%s port\n", argv[0]);
		exit(0);
	}
	listen_sock = tcp_listen(INADDR_ANY, atoi(argv[1]), 5);
	//스레드 생성
	pthread_create(&a_thread, NULL, thread_function, (void *)NULL);
	while (1) {
		FD_ZERO(&read_fds);
		FD_SET(listen_sock, &read_fds);
		for (i = 0; i < num_user; i++)
			FD_SET(clisock_list[i], &read_fds);

		maxfdp1 = getmax() + 1;	// maxfdp1 재 계산
		if (select(maxfdp1, &read_fds, NULL, NULL, NULL) < 0)
			errquit("select fail");

		if (FD_ISSET(listen_sock, &read_fds)) {
			accp_sock = accept(listen_sock,
				(struct sockaddr*)&cliaddr, &addrlen);
			if (accp_sock == -1) errquit("accept fail");
			addClient(accp_sock, &cliaddr);

			send(accp_sock, START_STRING, strlen(START_STRING), 0);

			if(roomcnt == 0){
                        	send(accp_sock, ROOM_STRING ,strlen(ROOM_STRING), 0);
                        }
			else{
				send(accp_sock, ROOM_LIST, strlen(ROOM_LIST), 0);
				for(int r=0;r<roomcnt;r++){
					//printf("room_N[%d]is = %s\n",r,room_N[r]);
					send(accp_sock, room_N[r], strlen(room_N[r]), 0);
				}
			}
			ct = time(NULL);			//현재 시간을 받아옴
			tm = *localtime(&ct);
			write(1, "\033[0G", 4);		//커서의 X좌표를 0으로 이동
			printf("[%02d:%02d:%02d]", tm.tm_hour, tm.tm_min, tm.tm_sec);
			fprintf(stderr, "\033[33m");//글자색을 노란색으로 변경
			printf("사용자 1명 추가. 현재 참가자 수 = %d\n", num_user);
			fprintf(stderr, "\033[32m");//글자색을 녹색으로 변경
			fprintf(stderr, "\n");
			fprintf(stderr, "server>"); //커서 출력
		}

		// 클라이언트가 보낸 메시지를 모든 클라이언트에게 방송
		for (i = 0; i < num_user; i++) {
			if (FD_ISSET(clisock_list[i], &read_fds)) {
				num_chat++;//총 대화 수 증가
				nbyte = recv(clisock_list[i], buf, MAXLINE, 0);

				if (nbyte <= 0) {
					removeClient(i);	// 클라이언트의 종료
					continue;
				}
				buf[nbyte] = 0;
				// 종료문자 처리
				if (strstr(buf, EXIT_STRING) != NULL) {
					removeClient(i);	// 클라이언트의 종료
					continue;
				}
				if(strstr(buf,"mk ")==buf){
                                        room[roomcnt][personcnt[roomcnt]] = clisock_list[i];
					char *temp = strtok(buf," ");
                                        temp = strtok(NULL," ");
					strcpy(room_N[roomcnt],temp);
                                        personcnt[roomcnt]++;
                                        roomcnt++;
					send(clisock_list[i], ROOM_IN,strlen(ROOM_IN), 0);
					temp = NULL;
					continue;
                                }
				else if(strstr(buf,"in ")==buf){
					char *temp = strtok(buf," ");
					temp = strtok(NULL," ");
					for (int z =0 ; z < roomcnt ; z++)
					{
						if(strcmp(room_N[z],temp)==0)
						{
                                        		room[z][personcnt[z]] = clisock_list[i];
                                        		personcnt[z]++;
							send(clisock_list[i], ROOM_IN,strlen(ROOM_IN), 0);
							room_in_f = 1;
							break;
						}
					}
					if (!room_in_f){
						send(clisock_list[i], ROOM_NO,strlen(ROOM_NO), 0);
						room_in_f = 0;
					}
					continue;
                                }
				else if(strstr(buf,"rl")!=NULL){
					if(roomcnt == 0){
                        			send(clisock_list[i], ROOM_STRING ,strlen(ROOM_STRING), 0);
                        		}
					else{
						send(clisock_list[i], ROOM_LIST, strlen(ROOM_LIST), 0);
						for(int r=0;r<roomcnt;r++){
							printf("room_N[%d]is = %s\n",r,room_N[r]);
							send(clisock_list[i], room_N[r], strlen(room_N[r]), 0);
						}
					}
					continue;
				}
				else if(strstr(buf,OUT)!=NULL){
					for(int z = 0 ; z < roomcnt ; z++){
						for(int y=0; y<personcnt[z]; y++){
							if(room[z][y] == clisock_list[i]){
								for(int e=y; e<personcnt[z]; e++){
									room[z][e] = room[z][e+1];
								}
								personcnt[z]--;
								send(clisock_list[i], ROOM_OUT,strlen(ROOM_OUT), 0);
							}
						}
					}
					continue;
				}

				else{
					for(int a = 0; a < roomcnt ; a++){
						for(int b = 0; b < personcnt[a]; b++){
							if(room[a][b] == clisock_list[i]){
							// 모든 group채팅 참가자에게 메시지 방송
                                       				for (int c = 0; c < personcnt[a]; c++)
                                     					send(room[a][c], buf, nbyte, 0);
									// 모든 채팅 참가자에게 메시지 방송
                                        			printf("\033[0G");              //커서의 X좌표를 0으로 이동
                                        			fprintf(stderr, "\033[97m");//글자색을 흰색으로 변경
                                        			printf("%s", buf);                      //메시지 출력
                                        			fprintf(stderr, "\033[32m");//글자색을 녹색으로 변경
                                        			fprintf(stderr, "\n");
                                        			fprintf(stderr, "server>"); //커서 출력	

							}
						}
					}
				}
			}
		}

	}  // end of while
	for (int a = 0; a < MAX_ROOM; a++)
	{
		free(room_N[a]);
	}
	return 0;
}
