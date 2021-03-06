#ifndef WR4T_WORKFLOW_TC_H
#define WR4T_WORKFLOW_TC_H

typedef enum
{
	WR4T_STATION_MIN = 0,
	WR4T_STATION_MODEL_WT,
	WR4T_STATION_MODEL_WU1,
	WR4T_STATION_MODEL_WU2,
	WR4T_STATION_MODEL_OC,
	WR4T_STATION_MODEL_IC,
	WR4T_STATION_MODEL_WG,
	WR4T_STATION_MODEL_WC1,
	WR4T_STATION_MODEL_WC2,
	WR4T_STATION_MODEL_WC3,
	WR4T_STATION_MAX
}WR4T_STATION_MODEL_ENUM;


typedef enum
{
	WR4T_EXCHANGE_TYPE_MIN = 0,
	WR4T_EXCHANGE_TYPE_PUT,
	WR4T_EXCHANGE_TYPE_GET,
	WR4T_EXCHANGE_TYPE_MOVE_TO_EXCHANGE,
	WR4T_EXCHANGE_TYPE_MOVE_TO_RETRACT,
	WR4T_EXCHANGE_TYPE_MOVE_TO_APPROACH,
	WR4T_EXCHANGE_TYPE_MOVE_TO_DEFINE_LOW,
	WR4T_EXCHANGE_TYPE_MOVE_TO_DEFINE_EXCHANGE,
	WR4T_EXCHANGE_TYPE_MOVE_TO_DEFINE_HIGH,
	WR4T_EXCHANGE_TYPE_SWAP_PUT_GET,
	WR4T_EXCHANGE_TYPE_SWAP_PICKUP,
	WR4T_EXCHANGE_TYPE_MAX
}WR4T_EXCHANGE_TYPE_ENUM;

typedef enum
{
	WZ4A_SIZE_MIN = 0,
	WZ4A_2_INCH,     
	WZ4A_3_INCH,         
	WZ4A_4_INCH,		  
	WZ4A_5_INCH,     
	WZ4A_6_INCH,         
	WZ4A_8_INCH,	
	WZ4A_12_INCH,
	WZ4A_18_INCH,
	WZ4A_PLATE_9_INCH,
	WZ4A_PLATE_13_INCH,
	WZ4A_UNKOWN_INCH,
	WZ4A_SIZE_MAX
} WZ4A_WAFER_SIZE_ENUM;

typedef enum
{
	WR4T_ARM_STATION_MIM = 0,
	WR4T_ARM_STATION_A = 0x41,
	WR4T_ARM_STATION_B,
	WR4T_ARM_STATION_C,
	WR4T_ARM_STATION_D,
	WR4T_ARM_STATION_E,
	WR4T_ARM_STATION_F,
	WR4T_ARM_STATION_G,
	WR4T_ARM_STATION_H,
	WR4T_ARM_STATION_I,
	WR4T_ARM_STATION_J,
	WR4T_ARM_STATION_K,
	WR4T_ARM_STATION_L,
	WR4T_ARM_STATION_M,
	WR4T_ARM_STATION_N,
	WR4T_ARM_STATION_O,
	WR4T_ARM_STATION_P,
	WR4T_ARM_STATION_Q,
	WR4T_ARM_STATION_R,
	WR4T_ARM_STATION_S,
	WR4T_ARM_STATION_T,
	WR4T_ARM_STATION_U,
	WR4T_ARM_STATION_V,
	WR4T_ARM_STATION_W,
	WR4T_ARM_STATION_X,
	WR4T_ARM_STATION_Y,
	WR4T_ARM_STATION_Z,

	WR4T_ARM_STATION_a = 0x61,
	WR4T_ARM_STATION_b,
	WR4T_ARM_STATION_c,
	WR4T_ARM_STATION_d,
	WR4T_ARM_STATION_e,
	WR4T_ARM_STATION_f,
	WR4T_ARM_STATION_g,
	WR4T_ARM_STATION_h,
	WR4T_ARM_STATION_i,
	WR4T_ARM_STATION_j,
	WR4T_ARM_STATION_k,
	WR4T_ARM_STATION_l,
	WR4T_ARM_STATION_m,
	WR4T_ARM_STATION_n,
	WR4T_ARM_STATION_o,
	WR4T_ARM_STATION_p,
	WR4T_ARM_STATION_q,
	WR4T_ARM_STATION_r,
	WR4T_ARM_STATION_s,
	WR4T_ARM_STATION_t,
	WR4T_ARM_STATION_u,
	WR4T_ARM_STATION_v,
	WR4T_ARM_STATION_w,
	WR4T_ARM_STATION_x,
	WR4T_ARM_STATION_y,
	WR4T_ARM_STATION_z,
	WR4T_ARM_STATION_MAX
}WR4T_ARM_STATION_ENUM;

typedef enum
{
	WR4T_ARM_MIM = 0,
	WR4T_UPPER_ARM,
	WR4T_LOWER_ARM,
	WR4T_ARM_MAX
}WR4T_ARM_ID_ENUM;

#endif