#ifndef CHAR_TEST_H
#define CHAR_TEST_H

#include "head_file.h"

void char_test(char out_char[]);

void quote(int& input);

int quote_test(int quote_input, int& quote_output);

//����������÷������õ������ ���ص���ֵ������ȫ�ֱ���
int& quote_test_return_function();

//���ݵ������ַ���
void transfer_char_to_const_char();

void char_extern_static();

#endif
