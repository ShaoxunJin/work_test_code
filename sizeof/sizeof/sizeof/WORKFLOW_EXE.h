#ifndef WORKFLOW_EXE_H
#define WORKFLOW_EXE_H

#include "head_file.h"

#include "WRMC_WORKFLOW_tc.h"


#define _WORKFLOW_WR_

#ifdef _WORKFLOW_WR_
#include "STATION_INTERFACE.h"
#include "STATION_MODEL_ABSTRACT_INTERFACE.h"
#include "MACHINE_CONSTANT_CLASS.h"
#include "STATION_CONTROLLER_CLASS.h"
#include "WG_STATION_MODEL_CLASS.h"
#include "EXCEPTION_CLASS.h"
using namespace WRH;
#endif

void WORKFLOW_EXE();


#endif