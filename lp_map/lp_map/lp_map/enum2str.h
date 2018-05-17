#ifndef ENUM2STR_H
#define ENUM2STR_H

typedef enum
{
	WHLP_SLOT_INFO_MIN = -1,
	WHLP_NO_WAFER,               // �����޹�Ƭ
	WHLP_NORMALLY_INSERT,        // ��ȷ����
	WHLP_CROSS_SLOT,             // ���
	WHLP_DOUBLE_SLOT,            // ��Ƭ
	WHLP_SLOT_INFO_MAX
} WHLP_SLOT_INFO_ENUM;

const char *enum2str(WHLP_SLOT_INFO_ENUM t);

#endif