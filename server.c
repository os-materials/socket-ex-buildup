#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>

char * buffer = NULL;
int sock;
int client;

void close_gracefully(int sig);

void read_stdin();
void * write_thread(void * args);

int main()
{
	signal(SIGINT, close_gracefully);
	struct sockaddr_in my_address;
	my_address.sin_family = AF_INET;
	my_address.sin_port = htons(9999);
	my_address.sin_addr.s_addr = INADDR_ANY;
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == -1)
	{
		perror("socket:");
		exit(1);
	}
	
	if (bind(sock, (struct sockaddr*) &my_address, sizeof(struct sockaddr_in)) == -1)
	{
		perror("bind:");
		close(sock);
		exit(1);
	}

	if (listen(sock, 10) == -1)
	{
		perror("listen:");
		close(sock);
		exit(1);
	}

	client = accept(sock, NULL, NULL);

	pthread_t th;
	pthread_create (&th, NULL, write_thread, NULL);

	char data[256];
	while (1)
	{
		read(client, data, 256);
		printf(">>%s\n", data);
	}

	return 0;

}
void read_stdin()
{
	size_t n;
	while(1)
	{
		getline(&buffer, &n, stdin);
		buffer[strlen(buffer)-1] = 0;
		write(client, buffer, strlen(buffer)+1);
	}
}

void * write_thread (void * args)
{
	read_stdin();
}

void close_gracefully(int sig)
{
	close(sock);
	free(buffer);
	exit(0);
}
