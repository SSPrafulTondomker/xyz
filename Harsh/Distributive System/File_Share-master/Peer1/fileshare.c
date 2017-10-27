/***************************************************************************
 *Author:  Charan
 *Date:  22 April 2015
 *Filename: fileshare.c
 *Description: main program for file share protocol

 ****************************************************************************/
#include"headers.h"
#include"server.h"
#include"client.h"
int main(int argc,int *argv[]){
	int server_port;
	printf("Enter the port no. to which you want to bind\n");
	scanf("%d",&server_port);
	int pid;
	pid = fork();
	if(pid == 0){
		printf("Please enter the port to which to want to connect\n");
		int client_port;
		scanf("%d",&client_port);
		char c;
		scanf("%c",&c); // This character eliminates \n after taking input //
		printf("This part is client\n");
		tcp_client(client_port);
	}
	else{
		tcp_server(server_port);
	}
	return 0;
}
