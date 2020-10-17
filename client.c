#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>

char * buffer = NULL;
int sock;
int client;

void close_gracefully(int sig);

void read_stdin();
void * read_thread(void * args);

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		printf("No hostname provided; exiting\n");
		exit(1);
	}

	signal(SIGINT, close_gracefully);
	struct sockaddr_in server;
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == -1)
	{
		perror("socket:");
		exit(1);
	}
	
	struct hostent * host = gethostbyname(argv[1]);
	server.sin_family = AF_INET;
	server.sin_port = htons(9999);
	memcpy(&server.sin_addr, host->h_addr, host->h_length);

	if (connect(sock, (const struct sockaddr*)& server, sizeof(struct sockaddr_in)) == -1)
	{
		perror("connect:");
		close(sock);
		exit(1);
	}
	pthread_t th;
	pthread_create(&th, NULL, read_thread, NULL);
	read_stdin();

	/*char data[256];
	*/
	return 0;

}
void read_stdin()
{
	size_t n;
	while(1)
	{
		getline(&buffer, &n, stdin);
		buffer[strlen(buffer)-1] = 0;
		write(sock, buffer, strlen(buffer) + 1);
	}
}

void close_gracefully(int sig)
{
	close(sock);
	free(buffer);
	exit(0);
}

void * read_thread(void * args)
{
	char data[256];
	while (1)
	{
		read(sock, data, 256);
		printf(">> %s\n", data);
	}
}

