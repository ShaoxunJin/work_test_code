#ifndef _MAP_H_
#define _MAP_H_
#include "enum2str.h"
#define OK 0
#define ERROR 1
#define WH4A_MAX_SLOT_NBR 25
#define MAX_DATA_LENGTH 2048

int m_resolve_slot_state(int sample_nbr, double *pos_data, double *sn_data, WHLP_SLOT_INFO_ENUM slot[WH4A_MAX_SLOT_NBR]);

#endif