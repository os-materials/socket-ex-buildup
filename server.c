#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

char * buffer = NULL;
int sock;

void read_stdin();

int main()
{
	struct sockaddr_in my_address;
	my_address.sin_family = AF_INET;
	my_address.sin_addr.s_addr = INADDR_ANY;
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == -1)
	{
		perror("Error creating socket:");
		exit(1);
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
