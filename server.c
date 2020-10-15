#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * buffer = NULL;

void read_stdin();

int main()
{
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
