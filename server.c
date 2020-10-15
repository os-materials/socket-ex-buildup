#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char * buffer = NULL;
	size_t n;
	getline(&buffer, &n, stdin);
	printf("%s--%ld\n", buffer, strlen(buffer));
	buffer[strlen(buffer)-1] = 0;
	printf("%s--%ld\n", buffer, strlen(buffer));
	free(buffer);
	return 0;

}
