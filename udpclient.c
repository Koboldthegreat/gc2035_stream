#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>


#define SERVER "192.168.3.100"
#define BUFLEN 23040
#define PORT 8888

struct timeval timeout={2,0};

void die(char *s)
{
	perror(s);
	exit(1);
}

void sendshake(int s)
{
	char buf = '\1';
	if (send(s, &buf, 1, 0) == -1)
	{
		die("send");
	}
}


int main(void)
{
	struct sockaddr_in si_other;
	int s, i, slen=sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];

	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
		die("socket");
	}
	setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char)&timeout, sizeof(struct timeval));

	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);

	if (inet_aton(SERVER, &si_other.sin_addr) == 0)
	{
		fprintf(stderr, "inet_aton() failed \n");
		exit(1);
	}
	int count = 0;
	int frame = 0;
	printf("3: %d", (char)'\3');
	if (connect(s, (struct sockaddr *) &si_other, (socklen_t) slen)<0)
	{
		die("conn");
	}
	sendshake(s);
	sendshake(s);
	while (1)
	{
		sendshake(s);
		memset(buf, '\0', BUFLEN);
		if (recv(s, buf, BUFLEN, 0) < 0)
		{
			die("recv");
		}
		count += 1;
		if (buf[0] == 3 && buf[69] == 3 && buf[128] == 3){
			//printf("frameshake found");
			count = 0;
			sendshake(s);
			frame += 1;
		} else {
			fwrite(buf, BUFLEN, 1, stdout);
			fflush(stdout);
		}

	}
	printf("frames captured: %d\n", frame);
	close(s);
	return 0;
}


