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
	servaddr.sin_port = htons(1314);
	
	if( bind(listenfd, (SA*)&servaddr, sizeof(servaddr)) < 0 ){
		cout<<"error bind"<<endl;
		exit(0);
	}
	
	if( listen(listenfd, 5) < 0 ){
		cout<<"listen error"<<endl;
		exit(0);
	}

	socklen_t len;	
	getsockname(listenfd,  (SA*)&servaddr, &len);
	cout<<servaddr.sin_addr.s_addr<<endl;
	cout<<servaddr.sin_port<<endl;
	cout<<ntohl(servaddr.sin_port)<<endl;

	while(1){
		cout<<"runing"<<endl;	
		connfd = accept(listenfd,(SA*)NULL,NULL);
		cout<<"client connect!!!"<<endl;
		ticks = time(NULL);
		snprintf(buf,sizeof(buf),"%.24s\n",ctime(&ticks));
		write(connfd, buf,strlen(buf));
		close(connfd);
	}
	cout<< "close sever" <<endl;
	
}
	
