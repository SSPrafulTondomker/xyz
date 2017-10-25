
/**************************************************************************

 *Author:  Charan
 *Date:  20 April 2015
 *Filename: client.h
 *Description: Client program for file share protocol

 ****************************************************************************/
#include"headers.h"
#define MAX 1024
void tcp_client(int client_port)
{
	int ClientSocket;
	struct sockaddr_in serv_addr;

	ClientSocket = socket(AF_INET,SOCK_STREAM,0);
	if(ClientSocket<0)
	{
		printf("ERROR WHILE CREATING A SOCKET\n");
		return;
	}
	else
		printf("[CLIENT] Socket created \n");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(client_port);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bzero(&(serv_addr.sin_zero),8);

	while (connect(ClientSocket, (struct sockaddr *)&serv_addr,sizeof(struct sockaddr)) < 0);

	printf("[CONNECTED]\n");

	while(1){

		char *got_data_1,*send_command_1,*received_data_1;
		char *token1;
		int bytes_received,bytes;
		char buffer[1024],send_command[1024],got_data[1024],received_data[1024];
		fgets(buffer,1023,stdin);
		strcpy(got_data,buffer);


		if (strcmp(got_data , "q") == 0 || strcmp(got_data , "Q") == 0)
		{
			send(ClientSocket, got_data,strlen(got_data), 0); 
			close(ClientSocket);
			break;
		}
		else{
			/* get the first token */
			token1 = strtok(got_data," ");
			if(token1 != NULL)
			{
				/*1*/
				/***************************Index Get Requests***************************/
				if(strcmp(token1,"IndexGet") == 0)
				{
					token1 = strtok(NULL," ");
					/*1(a)*/
					/***********Short List Request****************************/
					if(strcmp(token1,"ShortList\n") == 0){
						strcpy(send_command,"is");
						if( send(ClientSocket,send_command,strlen(send_command),0) < 0 ) 
							printf("error while sending\n");

						while(1)
						{
							bytes_received=recv(ClientSocket,received_data,1024,0);
							if(bytes_received < 0)
							{
								printf("ERROR while reading from the socket\n");
							}
							else
							{	   
								received_data[bytes_received] = '\0';
								if(strcmp(received_data,"End Of File") == 0)
									break;
								fwrite(received_data,1,bytes_received,stdout);
							}
						}
						continue;
					}
					/*1(b)*/
					/********************LongList Request************************/
					else if(strcmp(token1,"LongList\n") == 0){
						strcpy(send_command,"il");
						if( send(ClientSocket,send_command,strlen(send_command),0) < 0 ) 
							printf("error while sending\n");

						while(1)
						{
							bytes_received=recv(ClientSocket,received_data,1024,0);
							if(bytes_received < 0)
							{
								printf("ERROR while reading from the socket\n");
							}
							else
							{	   
								received_data[bytes_received] = '\0';
								if(strcmp(received_data,"End Of File") == 0)
									break;
								fwrite(received_data,1,bytes_received,stdout);
							}
						}
						continue;
					}
					/*1(c)*/
					/***********************RegEx Request**************************/
					else if(strcmp(token1,"RegEx") == 0){
						memset(send_command,0,1024);
						strcpy(send_command,"ir");
						token1 = strtok(NULL," ");
						if(token1 != NULL){
							strcat(send_command," ");
							strcat(send_command,token1);
							printf("%s\n",send_command );
							if(send(ClientSocket,send_command,strlen(send_command),0)<0)
								printf("ERROR while writing to the socket\n");

							while(1)
							{
								bytes_received=recv(ClientSocket,received_data,1024,0);
								received_data[bytes_received] = '\0';
								if(strcmp(received_data,"End Of File") == 0)break;
								fwrite(received_data,1,bytes_received,stdout);

							}
							printf("\ncommand succesfully completed now\n");
							continue;
						}
						else printf("Please Type \"IndexGet --regex <regex-argument>\"	\n");

					}

				}
				/*2*/
				/*******************File Hash Requests *******************************/
				else if(strcmp(token1,"FileHash") == 0)
				{

					token1 = strtok(NULL," ");
					if(token1 != NULL)
					{
						/*2(a)*/
						/***********************Verify Request***************/
						if(strcmp(token1,"Verify") == 0){
							strcpy(send_command,"fv");
							token1 = strtok (NULL, " ");
							if(token1!=NULL){
								strcat(send_command," ");
								strcat(send_command,token1);
								printf("%s\n",send_command );
								send(ClientSocket, send_command,strlen(send_command), 0);
								printf("Command sent\n");
								bytes_received=recv(ClientSocket,received_data,1024,0);
								received_data[bytes_received] = '\0';
								if(strcmp(received_data,"End Of File") == 0)break;
								fwrite(received_data,1,bytes_received,stdout);

								printf("\ncommand execution completed now\n");
								continue;
							}
							else printf("Please Type \"FileHash --verify <file-name>\"	\n");

						}
						/*2(b)*/
						/*****************Check All Request*************************/
						else if(strcmp(token1,"CheckAll") == 0 ){
							/**XXXXXXXXXXXXXXXXXXXX NOT WORKING XXXXXXXXXXXXXXXXXXXXXXX*/
							strcpy(send_command,"fc");
							send(ClientSocket,send_command,strlen(send_command),0);
							while(1){
								bytes_received = recv(ClientSocket,received_data,1024,0);
								received_data[bytes_received] = '\0';
								if(strcmp(received_data,"End Of File") == 0)break;
								fwrite(received_data,1,bytes_received,stdout);
							}
							printf("\ncommand execution done\n");
							continue;

						}
					}
					else printf("Please enter proper command \" FileHash --verify <file-name> or --checkall \" \n");

				}
				/*2(c)*/
				/*********************File Download Request***********************/
				else if(strcmp(token1,"FileDownload") == 0){
					token1 = strtok(NULL," ");
					if(token1 != NULL){
						memset(send_command,0,1024);
						strcpy(send_command,"D");
						strcat(send_command," ");
						strcat(send_command,token1);

						token1[strlen(token1)-1]='\0';

						if( send(ClientSocket, send_command,strlen(send_command), 0) < 0)
							printf("Error while passing command to server\n");
						printf(" %s ",token1 );
						//printf("Check");
						while(1){
							bytes = recv(ClientSocket,received_data,1024,0);
							received_data[bytes] = '\0';
							if(strcmp(received_data,"END")==0 ) break;
							printf("%s ", received_data);
						}
						printf("\n");
						FILE *fp = fopen(token1,"w");
						if(fp == NULL){
							//printf("*******\n");
							printf("Error opening the file\n");
						}
						while(1){
							bytes = recv(ClientSocket,received_data,1024,0);
							received_data[bytes] = '\0';
							if(strcmp(received_data,"END")==0 ) break;
							fprintf(fp, "%s", received_data);
						}
						fclose(fp);
						printf("File Downloaded succesfully\n");
						continue;
					}
				}
				/*2(d)*/
				/***************File Upload Request******************************/
				else if(strcmp(token1,"FileUpload") == 0){
					token1 = strtok(NULL," ");
					if(token1 != NULL){
						strcpy(send_command,"U");
						strcat(send_command," ");
						strcat(send_command,token1);
						send_command[strlen(send_command)-1]='\0';
						token1[strlen(token1)-1]='\0';

						printf("%s\n",send_command );
						if( send(ClientSocket, send_command,strlen(send_command), 0) < 0)
							printf("Error while passing command to server\n");

						//recv(ClientSocket,received_data,1024,0);
						//if( received_data[0]=='y' || received_data[0]=='Y'){
						FILE *fp = fopen(token1,"r");
						if(fp == NULL)
						{
							printf("wrong file\n");
							continue;
						}
						char send_data[1024];
						memset(send_data,0,1024);
						//printf("Check");
						int bytes_read,bytes_sent;
						while(!feof(fp))
						{ 	
							memset(send_data,0,1024);
							bytes_read = fread(send_data,1,1024,fp);
							send_data[bytes_read] = '\0';
							bytes_sent = write(ClientSocket,send_data,1024);

						}
						//printf("Check");
						char end[]="END";
						write(ClientSocket,end,1024);
						fclose(fp);

						//}
						//else
						//	continue;

						char tim[1024];char str[1024];
						struct stat st;
						stat(token1, &st);
						int size = st.st_size;
						sprintf(str, "%d", size);
						sprintf(tim,"%d",ctime(&st.st_mtime));
						//write(connectionSocket,str,1024);
						//write(connectionSocket,tim,1024);
						printf("------ %s %s %s",token1,str,tim );
						char md5[1024];
						strcpy(md5,"md5sum");
						strcat(md5," ");
						strcat(md5,token1);
						strcat(md5," | awk '{print $1}' > checksum " );
						system(md5);

						//printf("%s\n",md5 );
						FILE *checkfp = fopen("checksum","r");
						//printf("*******\n");
						while(!feof(checkfp)){
							int bytes = fread(send_data,1,1024,checkfp);
							send_data[bytes]='\0';
							//write(connectionSocket,send_data,1024);
							printf("%s-----\n",send_data );
						}
						printf("File Uploaded\n");	
						fclose(checkfp);

					}
				}
			}
		}

	}
}
