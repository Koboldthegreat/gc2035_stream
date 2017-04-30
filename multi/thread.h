#include <iostream>
#include <sys/types>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>
#include "packet.h"

#define MAX_THREADS 20
#define REQ_SIZE 16

struct Request{
	socklen_t fromlen;
	struct sockaddr_in from;
	char buf[REQ_SIZE];
};

struct Thread{
	int connection_id;
	struct Thread *next_thread;
};

void* handle_request(void*);
short insert_thread();
void remove_thread(short);
