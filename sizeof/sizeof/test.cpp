#include <stdio.h>
#include <string.h>
int main()
{
	printf("test...");
	char a;
	char *ptr_a = &a;
	strncpy(ptr_a, "abcd");

	printf("result = %s\n",ptr_a);
	printf("a = %c", a);

}
