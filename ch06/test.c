#include <stdio.h>
#include <string.h>

int main()
{
	char s[100];
	while(1)
	{
		fgets(s,100,stdin);
		printf("%s",s);
	}
	return 0;
}
