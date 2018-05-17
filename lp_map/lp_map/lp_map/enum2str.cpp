#include "stdafx.h"
#include "enum2str.h"

const char *enum2str(WHLP_SLOT_INFO_ENUM t)
{
	const char *slot_str = 0;
	switch(t)
	{
	case 0:
		slot_str = "no wafer";
		break;
	case 1:
		slot_str = "normally wafer";
		break;
	case 2:
		slot_str = "cross wafer";
		break;
	case 3:
		slot_str = "double wafer";
		break;
	default:
		slot_str = "invalid slot info";
		break;
	}
	return slot_str;
}