#ifndef CHAR_TEST_H
#define CHAR_TEST_H

#include "head_file.h"

void char_test(char out_char[]);

void quote(int& input);

int quote_test(int quote_input, int& quote_output);

//如果函数采用返回引用的情况下 返回的数值必须是全局变量
int& quote_test_return_function();

//传递到常量字符串
void transfer_char_to_const_char();

void char_extern_static();

#endif
