/**************************************************************************

 *Author: Charan
 *Date:  20 April 2015
 *Filename: server.h
 *Description: Server program for file share protocol

 ****************************************************************************/

#include "headers.h"
#define MAX 1024
void tcp_server(int server_port)
{

        //printf("Yup It Entered Server");
	struct sockaddr_in server_addr,client_addr; 
	int connectionSocket,sock;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
		perror("Socket");
		exit(1);
	}

	server_addr.sin_family = AF_INET;         
	server_addr.sin_port = htons(server_port);     
	server_addr.sin_addr.s_addr = INADDR_ANY; 
	bzero(&(server_addr.sin_zero),8); 


	if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))== -1) 
	{
		perror("Unable to bind");
		exit(1);
	}

	// Listening to connections
	if (listen(sock, 5) == -1) //maximum connections listening to 5
	{
		perror("Listen");
		exit(1);
	}
	fflush(stdout);
	// Accepting connections
	while((connectionSocket=accept(sock , (struct sockaddr*)NULL,NULL))<0);
	// NULL will get filled in by the client's sockaddr once a connection is establised

	printf("[CONNECTED]>>>>>> server\n");

	while(1)
	{
		int bytes_received;
		char received_data[MAX],send_data[MAX];
		char *token1;

		bytes_received=recv(connectionSocket,received_data,MAX,0);
		received_data[bytes_received]='\0';
		/*1*/
		/********************IndexGet Requets*********************/
		/*1(a)*/
		/*****************Shartlist Request*********************/
		if(received_data[0]=='i' && received_data[1]=='s')
		{
			system("ls > outfile_long");//System Call
			//file to be sent here shortlist
			FILE *fp = fopen("outfile_long","r");
			if(fp == NULL)
			{
				//printf("Check");
				printf("wrong file\n");
				continue;
			}
			memset(send_data,0,MAX);
			int bytes_read,bytes_sent;
			while(!feof(fp))
			{
				bytes_read = fread(send_data,1,MAX,fp);
				send_data[bytes_read] = '\0';
				bytes_sent = write(connectionSocket,send_data,MAX);
				//printf("Check");
			}
			printf("End file\n");
			memset(send_data,0,MAX);
			char end[]= "End Of File";
			strcpy(send_data,end);
			write(connectionSocket,send_data,MAX);
			fclose(fp);
			continue;
		}
		/*1(b)*/
		/************LongList Request*****************/
		else if( received_data[0]=='i' && received_data[1]=='l')
		{     
			system("ls -l > outfile_long");//System Call
			//file to be sent here longlist
			FILE *fp = fopen("outfile_long","r");
			if(fp == NULL)
			{
				//printf("Check");
				printf("wrong file\n");
				continue;
			}
			memset(send_data,0,MAX);
			int bytes_read,bytes_sent;
			while(!feof(fp))
			{
				bytes_read = fread(send_data,1,MAX,fp);
				send_data[bytes_read] = '\0';
				bytes_sent = write(connectionSocket,send_data,MAX);
			}
			printf("End file\n");
			memset(send_data,0,MAX);
			char end[]= "End Of File";
			strcpy(send_data,end);
			write(connectionSocket,send_data,MAX);
			//printf("Check");
			fclose(fp);
			continue;
		}
		/*1(c)*/
		/*******************RegEx Request**************************/
		else if(received_data[0]=='i' && received_data[1]=='r')
		{

			token1 = strtok(received_data," ");
			token1 = strtok(NULL," ");
			char token2[MAX];
			strncpy(token2,token1,strlen(token1)-1);
			char proc_command[MAX];
			strcpy(proc_command,"find . -name ");
			strcat(proc_command,token2);
			strcat(proc_command," > out_regex");
			system(proc_command);

			FILE *fp = fopen("out_regex","r");
			if(fp == NULL)
			{
				printf("wrong file\n");
				continue;
			}
			memset(send_data,0,MAX);
			int bytes_read,bytes_sent;
			while(!feof(fp))
			{ 
				//printf("Check");
				bytes_read = fread(send_data,1,MAX,fp);
				send_data[bytes_read] = '\0';
				bytes_sent = write(connectionSocket,send_data,MAX);
			}
			printf("End file\n");
			memset(send_data,0,MAX);
			char end[]= "End Of File";
			strcpy(send_data,end);
			write(connectionSocket,send_data,MAX);
			fclose(fp);
			continue;
		}
		/*2*/
		/******************************FileHash Request*************************/
		/*2(a)*/
		/******************************Verify Request****************************/
		else if(received_data[0]=='f' && received_data[1]=='v')
		{

			printf("%s\n",received_data );
			token1 = strtok(received_data," ");
			token1 = strtok(NULL," ");

			//printf("Check");
			char commanded[MAX],command1[MAX];
			token1[strlen(token1)-1]='\0';

			strcpy(commanded,"md5sum ");
			strcat(commanded,token1);
			strcat(commanded," | awk '{print $1}' > out1");
			system(commanded);

			strcpy(command1,"stat");
			strcat(command1," ");
			strcat(command1,token1);
			strcat(command1," | grep Modify | awk '{print $3}' >> out1");
			system(command1);
			printf("%s\n",command1 );

			FILE *f=fopen("out1","r");
			char data[300];
			fread(data,1,300,f);
			fclose(f);
			data[strlen(data)-1]='\0';
			printf("%s\n",data );
			write(connectionSocket,data,300);


		}
		/*2(b)*/
		/**************************Check All Request*************************/
		else if(received_data[0]=='f' && received_data[1]=='c')
		{
			/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"NOT DONE"XXXXXXXXXXXXXXXXXXXXXXXXXXX*/


		}
		/*2(c)*/
		/***********************File Downloading Request***********************/
		else if(received_data[0] == 'D')
		{
			printf("%s\n",received_data );
			token1 = strtok(received_data," ");
			token1 = strtok(NULL," ");
			token1[strlen(token1)-1]='\0';

			memset(send_data,0,MAX);
			int bytes_read,bytes_sent;

			char tim[MAX];char str[MAX];
			struct stat st;
			stat(token1, &st);
			int size = st.st_size;
			sprintf(str, "%d", size);
			sprintf(tim,"%d",ctime(&st.st_mtime));
			write(connectionSocket,str,MAX);
			write(connectionSocket,tim,MAX);

			char md5[MAX];
			strcpy(md5,"md5sum");
			strcat(md5," ");
			strcat(md5,token1);
			strcat(md5," | awk '{print $1}' > checksum " );
			system(md5);

			printf("%s\n",md5 );
			FILE *checkfp = fopen("checksum","r");
			while(!feof(checkfp))
			{
				//printf("Check");
				int bytes = fread(send_data,1,MAX,checkfp);
				send_data[bytes]='\0';
				write(connectionSocket,send_data,MAX);
				printf("%s\n",send_data );
			}
			char end[]="END";
			write(connectionSocket,end,MAX);
			fclose(checkfp);
			FILE *fop = fopen(token1,"r");
			if(fop == NULL)
				printf("Error opening file\n");
			while(!feof(fop))
			{
				//printf("Check");
				bytes_read = fread(send_data,1,MAX,fop);
				send_data[bytes_read] = '\0';
				bytes_sent = write(connectionSocket,send_data,MAX);
			}
			strcpy(end,"END");
			write(connectionSocket,end,MAX);
			fclose(fop);
			printf("file sent\n");
			continue;
		}
		/*2(d)*/
		/********************File Uploading Request**************************/
		else if(received_data[0] == 'U'){
			token1 = strtok(received_data," ");
			token1 = strtok(NULL," ");
			char status[MAX];char token2[MAX];int bytes;
			int c;
			int temp=0;
			FILE *fp = fopen(token1,"w");
			if(fp == NULL){
				printf("Error opening the file\n");
			}
			//printf("*******\n");		}
			while(1){
				bytes = recv(connectionSocket,received_data,MAX,0);
				received_data[bytes] = '\0';
				if(strcmp(received_data,"END")==0 ){ 
					if(temp==0)
					{
						strcpy(token2,"rm");
						strcat(token2," ");
						strcat(token2,token1);
						system(token2);
					}
					break;
				}
				fprintf(fp, "%s", received_data);
				temp++;
			}
			fclose(fp);
			printf("File Uploaded succesfully\n");
			continue;
	}


}
close(connectionSocket);


}

