#include "head_file.h"

//�ⲿȫ�ֱ�������
extern int g_int;

void endian_test();

void endian_test_1(void);
//test operation system is using big endian or little endian
//big endian = high byte is stored in low address
//little endian = high byte is stored in high address
//little endian is identical to our common thought.

typedef union
{
	char a;
	int b;
}UNOIN_TEST;


