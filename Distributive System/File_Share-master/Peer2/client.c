#include "headers.h"
#include "var.h"

int main(){
	printf("[Client]: Please enter the server port number:\n");
	scanf("%d",&port);
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	/*---- Configure settings of the server address struct ----*/
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	addr_size = sizeof serverAddr;
	int Errno = connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
	if( Errno == 0){
		printf("[Client]: Connection with server established.\n");
		printf("[Client]: Please enter a message to server.\n");
	}
	else{
		printf("[Client]: Failed to connect with server and Error number is %d\n", Errno);
	}
	/*---- Read the message from the server into the buffer ----*/
	iret1 = pthread_create( &thread1, NULL, Recv_From_Server, NULL);
	if(iret1)
	{
		printf("Thread creation failed: %d\n", iret1);

	}

	iret2 = pthread_create( &thread2, NULL, Send_To_Server, NULL);
	if(iret2)
	{
		printf("Thread creation failed: %d\n", iret2);

	}

	printf("pthread_create() for thread 1 returns: %d\n",iret1);
	printf("pthread_create() for thread 2 returns: %d\n",iret2);

	/* Wait till threads are complete before main continues. Unless we  */
	/* wait we run the risk of executing an exit which will terminate   */
	/* the process and all threads before the threads have completed.   */

	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL); 


	return 0;
}
