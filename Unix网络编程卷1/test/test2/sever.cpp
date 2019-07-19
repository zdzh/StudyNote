#include <time.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define MAXLINE 100
#define SA struct sockaddr
//#define bzero(a,b)     memset(a,0,b)

void str_echo(int sockfd){
	ssize_t n;
	char buf[MAXLINE];
	while(1){
		if( (n = read(sockfd, buf, MAXLINE)) > 0 ){
			if( bcmp(buf, "close",sizeof("close")-1) == 0 ){
				cout<<"close read"<<endl;
				return;
			}
			else{
				write(sockfd, buf, n);
				buf[n] = '\0';
				cout<<"get: "<<buf<<endl; 
			}
		}
		if( n < 0 && errno != EINTR ){
			cout<<"error read"<<endl;
			break;
		}
	}
	cout<<"finish"<<endl;
}

int main(int argc,char **argv){
	int listenfd;
	int connfd;
	struct sockaddr_in servaddr;
	char buf[MAXLINE];
	time_t ticks;
	
	if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
		cout<<"error: socket"<<endl;
		exit(0);
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(23333);
	
	if( bind(listenfd, (SA*)&servaddr, sizeof(servaddr)) < 0 ){
		cout<<"error bind"<<endl;
		exit(0);
	}
	
	if( listen(listenfd, 5) < 0 ){
		cout<<"listen error"<<endl;
		exit(0);
	}

	socklen_t clilen;
	struct sockaddr_in cliaddr;
	while(1){
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd,(SA*)&cliaddr,&clilen);
		cout<<"client connect!!!"<<endl;
		if( fork() == 0 ){ 
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		close(connfd);
	}
	cout<< "close sever" <<endl;
	
}
	
