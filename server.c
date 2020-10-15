#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

char * buffer = NULL;
int sock;
int client;

void read_stdin();

int main()
{
	struct sockaddr_in my_address;
	my_address.sin_family = AF_INET;
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
		edit(1);
	}

	client = accept(sock, NULL, NULL);

	char data[256];
	while (1)
	{
		read(client, data, 256);
		printf(">>%s\n"
	}

	return 0;

}
void read_stdin()
{
	size_t n;
	while(1)
	{
		getline(&buffer, &n, stdin);
	}
}
