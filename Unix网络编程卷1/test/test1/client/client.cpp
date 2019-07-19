//client
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

using namespace std;

#define MAXLINE 100

int main(int argc, char** argv){
	int sockfd;
	int n;
	char recvline[MAXLINE+1];
	struct sockaddr_in servaddr;
	
	if( argc != 2 ){
		cout<<"usage:./client <ipaddress>"<<endl;
		exit(0);
	}
	if( (sockfd = socket(AF_INET,SOCK_STREAM, 0)) < 0 ){
		cout<<"socket error"<<endl;
		exit(0);
	} 
	
	memset(&servaddr, 0 , sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(1314);

	cout<< argv[1]<<endl;	
	if( (inet_pton(AF_INET, argv[1], &servaddr.sin_addr)) != 1 ){
		cout<<"connet error"<<endl;
		exit(0);
	}

	if( connect(sockfd, (struct sockaddr*)&servaddr,sizeof(servaddr)) < 0 ){
		cout <<"error connect"<< endl;
		exit(0);
	}
		
	while( (n = read(sockfd,recvline, MAXLINE)) > 0 ){
		recvline[n] = 0;
		cout<<"time:";
		cout <<recvline<<endl;
	}
	if( n < 0 ){
		cout<<"read error"<<endl;
	}
	return 0;
}
