#ifndef ENUM2STR_H
#define ENUM2STR_H

typedef enum
{
	WHLP_SLOT_INFO_MIN = -1,
	WHLP_NO_WAFER,               // 槽内无硅片
	WHLP_NORMALLY_INSERT,        // 正确插入
	WHLP_CROSS_SLOT,             // 跨槽
	WHLP_DOUBLE_SLOT,            // 叠片
	WHLP_SLOT_INFO_MAX
} WHLP_SLOT_INFO_ENUM;

const char *enum2str(WHLP_SLOT_INFO_ENUM t);

#endif