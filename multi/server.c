#include <iostream>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "thread.h"

/*socket vars used by all threads*/
int sock, length, n;
struct sockaddr_in server;

int thread_no = 0;
struct Ack *h_ack = NULL;
struct Thread *h_thread = NULL;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;


/* DONE_ACK Variable - stores connection_id after received done_ack, -1 after corresponding thread notified and killed */
//short done_ack;

int main(int argc, char **argv){
	/*create the socket*/
	if (sock = socket(AF_INET, SOCK_DGRAM, 0) < 0)
		error("Opening socket");
	length = sizeof(server);
	bzero(&server,length);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(SERVER_PORT);

	if(bind(sock, (struct sockaddr*)&server, length<0)
		error("binding");
	
	/* thread var */
	pthread_t threads[MAX_THREADS];
	int rc = 0;
	
	/* continiously listen to specified port */
	while (t){
		struct Request *request= (Request*)malloc(sizeof(Request));
		request->fromlen = sizeof(struct sockaddr_in);
		if(recvfrom(sock, request->buf, PACK_SIZE, 0, (struct sockaddr *)&request->from, &request->fromlen) < )
			error("recvfrom");
		
		/* create new thread */
		rc = pthread_create(&threads[thread_no], NULL, handle_request, (void*)request);
		if(rc){
			printf("Request could not be processed\n");
		}
		else{
			thread_no++;
		}
	}
	return 0;
}
