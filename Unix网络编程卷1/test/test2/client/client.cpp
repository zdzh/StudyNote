#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <iostream>
using namespace std;

#define MAXLINE 100

void str_cli(FILE* fp, int sockfd){
	char buf[MAXLINE],rec[MAXLINE];
	while( fgets(buf, MAXLINE, fp) != NULL ){
		cout <<"send "<<buf;
		write(sockfd, buf, strlen(buf));
		if( bcmp(buf, "close",sizeof("close")-1) == 0  ){
			break;
		}
		int n;
		if((n = read(sockfd, rec, MAXLINE))  > 0  ){
			rec[n] = '\0';
			cout<<"get "<<rec<< n<<endl;
		}
		cout<<"test ok"<<endl;
	}
}




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
	servaddr.sin_port = htons(23333);

	cout<< argv[1]<<endl;	
	if( (inet_pton(AF_INET, argv[1], &servaddr.sin_addr)) != 1 ){
		cout<<"connet error"<<endl;
		exit(0);
	}

	if( connect(sockfd, (struct sockaddr*)&servaddr,sizeof(servaddr)) < 0 ){
		cout <<"error connect"<< endl;
		exit(0);
	}

	str_cli(stdin, sockfd);
	
	return 0;
}
