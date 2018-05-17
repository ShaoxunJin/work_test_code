#include "headfile.h"
int RLSGMV_p_generate(
						RLSGMV_spg_data_struct *spg_data_ptr,
						SMEE_BOOL *spg_ready_ptr,
						RLSGMV_step_event_enum *step_event_ptr
						)

{
	int ret_val = OK;
	int k = 0;
	int ntab = 0;
	int nacc = 0;
	int nvel = 0;

	/*若计时器时间不到运动轨迹总时间*/
	if (mv_gen_data[axis_id].cur_time <= mv_loc_params.switch_time[7])
	{
		/*确定当前的加速度*/
		k = mv_gen_data[axis_id].cur_time;
		ntab = mv_loc_params.switch_time[1];
		nacc = mv_loc_params.switch_time[2];
		nvel = mv_loc_params.switch_time[4];

		if (k > 0)//xj070713
		{
			/*加速段1*/
			if (k <= ntab)
			{
				/*加速度递增至最大值*/
				mv_gen_data[axis_id].cur_acc = mv_loc_table.acc_tab[k - 1];		//这里为何k-1？因为第一个点是从零开始，后续类似；
			}
			else
			{
				/*该时间段内以最大加速度运动*/
				mv_gen_data[axis_id].cur_acc =
					mv_loc_table.acc_tab[mv_loc_table.acc_tab_len - 1];
			}

			if (k > nacc)
			{
				/*加速段2*/
				if (k <= (nacc + ntab))
				{
					/*加速度递减至0*/
					mv_gen_data[axis_id].cur_acc -= mv_loc_table.acc_tab[k - nacc - 1];
				}
				else
				{
					/*加速度恒定在0，该时间段内以最大速度匀速运动*/
					mv_gen_data[axis_id].cur_acc -=
						mv_loc_table.acc_tab[mv_loc_table.acc_tab_len - 1];
				}

				if (k > nvel)
				{
					/*加速段3(实际上为减速)*/
					if (k <= (nvel + ntab))
					{
						/*加速度递减至负的最大值*/
						mv_gen_data[axis_id].cur_acc -= mv_loc_table.acc_tab[k - nvel - 1];
					}
					else
					{
						/*该时间段内以负的最大加速度运动*/
						mv_gen_data[axis_id].cur_acc -=
							mv_loc_table.acc_tab[mv_loc_table.acc_tab_len - 1];
					}

					if (k > (nvel + nacc))
					{
						/*加速段4(实际上为减速)*/
						if (k <= (nvel + nacc + ntab))
						{
							/*加速度递增至0*/
							mv_gen_data[axis_id].cur_acc += mv_loc_table.acc_tab[k - nvel - nacc - 1];
						}
						else
						{
							/*加速度恒定在0，同时速度也降至0，运动结束*/
							mv_gen_data[axis_id].cur_acc +=
								mv_loc_table.acc_tab[mv_loc_table.acc_tab_len - 1];
						}
					}
					else
					{
						;
					}
				}
				else
				{
					;
				}
			}
			else
			{
				;
			}
		}
		else
		{
			;
		}

		/*考虑补偿因子*/
		//mv_gen_data[axis_id].cur_acc = mv_loc_params.pos_factor * mv_gen_data[axis_id].cur_acc;

		/*考虑运动方向的影响*/
		mv_gen_data[axis_id].cur_acc =
			mv_loc_params.acc_sign * mv_gen_data[axis_id].cur_acc;

		/*运动轨迹的开始*/
		if (mv_gen_data[axis_id].cur_time == 0)
		{
			/*设置点生成器未就绪(忙)*/
			*spg_ready_ptr = SMEE_FALSE;

			/*表示开始加速*/
			*step_event_ptr = RLSGMV_STEP_START_ACCELERATION;
		}
		else if (mv_gen_data[axis_id].cur_time == mv_loc_params.switch_time[3])//xj071113
		{
			/*设置点生成器仍当作未就绪(忙)*/
			*spg_ready_ptr = SMEE_FALSE; //xj070712

			/*表示进入匀速段*/
			*step_event_ptr = RLSGMV_STEP_START_CONSTANT_MOVE;
		}
		else if(mv_gen_data[axis_id].cur_time == mv_loc_params.switch_time[7])/*运动轨迹的终点*/
		{
			/*设置点生成器仍当作未就绪(忙)*/
			*spg_ready_ptr = SMEE_FALSE; //xj070712

			/*表示停止加速*/
			*step_event_ptr = RLSGMV_STEP_END_DECELERATION;
		}
		else
		{
			/*设置点生成器未就绪(忙)*/
			*spg_ready_ptr = SMEE_FALSE;

			/*表示没有新的事件发生*/
			*step_event_ptr = RLSGMV_STEP_NO_EVENT;
		}

		/*增加时间计数器的计数值*/
		mv_gen_data[axis_id].cur_time++;
	}
	else
	{
		/*设置当前加速度为0*/
		mv_gen_data[axis_id].cur_acc = 0;

		/*设置点生成器已就绪(空闲)*/
		*spg_ready_ptr = SMEE_TRUE;

		/*表示没有新的事件发生*/
		*step_event_ptr = RLSGMV_STEP_NO_EVENT;
	}

	/*对加速度前向积分求速度*/
	mv_gen_data[axis_id].prev_vel = mv_gen_data[axis_id].cur_vel;
	mv_gen_data[axis_id].cur_vel += mv_gen_data[axis_id].cur_acc;

	/*对速度后向积分求相对位移*/
	mv_gen_data[axis_id].cur_pos_rel += mv_gen_data[axis_id].prev_vel;

	/*计算以国际单位制表示的实际位移、速度、加速度*/
	spg_data_ptr->position =
		mv_loc_params.pos_factor * mv_gen_data[axis_id].cur_pos_rel * RL_POS_UNIT;
	spg_data_ptr->position += mv_loc_params.start_pos;
	spg_data_ptr->velocity =
		mv_loc_params.pos_factor * mv_gen_data[axis_id].cur_vel *
			mv_loc_params.vel_unit;
	spg_data_ptr->acceleration =
		mv_loc_params.pos_factor * mv_gen_data[axis_id].cur_acc *
			mv_loc_params.acc_unit;

	/*当前加速度归0*/
	mv_gen_data[axis_id].cur_acc = 0;
	
	system("pause");
	return ret_val;
}