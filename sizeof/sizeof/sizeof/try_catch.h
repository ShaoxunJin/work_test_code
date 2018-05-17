#ifndef TRY_CATCH_H
#define TRY_CATCH_H

#include "head_file.h"


void try_catch(void);

void throw_int(int) throw(int);

void throw_none() throw();

void throw_all() throw(...);


#endif