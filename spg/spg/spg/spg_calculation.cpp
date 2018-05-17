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

	/*����ʱ��ʱ�䲻���˶��켣��ʱ��*/
	if (mv_gen_data[axis_id].cur_time <= mv_loc_params.switch_time[7])
	{
		/*ȷ����ǰ�ļ��ٶ�*/
		k = mv_gen_data[axis_id].cur_time;
		ntab = mv_loc_params.switch_time[1];
		nacc = mv_loc_params.switch_time[2];
		nvel = mv_loc_params.switch_time[4];

		if (k > 0)//xj070713
		{
			/*���ٶ�1*/
			if (k <= ntab)
			{
				/*���ٶȵ��������ֵ*/
				mv_gen_data[axis_id].cur_acc = mv_loc_table.acc_tab[k - 1];		//����Ϊ��k-1����Ϊ��һ�����Ǵ��㿪ʼ���������ƣ�
			}
			else
			{
				/*��ʱ������������ٶ��˶�*/
				mv_gen_data[axis_id].cur_acc =
					mv_loc_table.acc_tab[mv_loc_table.acc_tab_len - 1];
			}

			if (k > nacc)
			{
				/*���ٶ�2*/
				if (k <= (nacc + ntab))
				{
					/*���ٶȵݼ���0*/
					mv_gen_data[axis_id].cur_acc -= mv_loc_table.acc_tab[k - nacc - 1];
				}
				else
				{
					/*���ٶȺ㶨��0����ʱ�����������ٶ������˶�*/
					mv_gen_data[axis_id].cur_acc -=
						mv_loc_table.acc_tab[mv_loc_table.acc_tab_len - 1];
				}

				if (k > nvel)
				{
					/*���ٶ�3(ʵ����Ϊ����)*/
					if (k <= (nvel + ntab))
					{
						/*���ٶȵݼ����������ֵ*/
						mv_gen_data[axis_id].cur_acc -= mv_loc_table.acc_tab[k - nvel - 1];
					}
					else
					{
						/*��ʱ������Ը��������ٶ��˶�*/
						mv_gen_data[axis_id].cur_acc -=
							mv_loc_table.acc_tab[mv_loc_table.acc_tab_len - 1];
					}

					if (k > (nvel + nacc))
					{
						/*���ٶ�4(ʵ����Ϊ����)*/
						if (k <= (nvel + nacc + ntab))
						{
							/*���ٶȵ�����0*/
							mv_gen_data[axis_id].cur_acc += mv_loc_table.acc_tab[k - nvel - nacc - 1];
						}
						else
						{
							/*���ٶȺ㶨��0��ͬʱ�ٶ�Ҳ����0���˶�����*/
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

		/*���ǲ�������*/
		//mv_gen_data[axis_id].cur_acc = mv_loc_params.pos_factor * mv_gen_data[axis_id].cur_acc;

		/*�����˶������Ӱ��*/
		mv_gen_data[axis_id].cur_acc =
			mv_loc_params.acc_sign * mv_gen_data[axis_id].cur_acc;

		/*�˶��켣�Ŀ�ʼ*/
		if (mv_gen_data[axis_id].cur_time == 0)
		{
			/*���õ�������δ����(æ)*/
			*spg_ready_ptr = SMEE_FALSE;

			/*��ʾ��ʼ����*/
			*step_event_ptr = RLSGMV_STEP_START_ACCELERATION;
		}
		else if (mv_gen_data[axis_id].cur_time == mv_loc_params.switch_time[3])//xj071113
		{
			/*���õ��������Ե���δ����(æ)*/
			*spg_ready_ptr = SMEE_FALSE; //xj070712

			/*��ʾ�������ٶ�*/
			*step_event_ptr = RLSGMV_STEP_START_CONSTANT_MOVE;
		}
		else if(mv_gen_data[axis_id].cur_time == mv_loc_params.switch_time[7])/*�˶��켣���յ�*/
		{
			/*���õ��������Ե���δ����(æ)*/
			*spg_ready_ptr = SMEE_FALSE; //xj070712

			/*��ʾֹͣ����*/
			*step_event_ptr = RLSGMV_STEP_END_DECELERATION;
		}
		else
		{
			/*���õ�������δ����(æ)*/
			*spg_ready_ptr = SMEE_FALSE;

			/*��ʾû���µ��¼�����*/
			*step_event_ptr = RLSGMV_STEP_NO_EVENT;
		}

		/*����ʱ��������ļ���ֵ*/
		mv_gen_data[axis_id].cur_time++;
	}
	else
	{
		/*���õ�ǰ���ٶ�Ϊ0*/
		mv_gen_data[axis_id].cur_acc = 0;

		/*���õ��������Ѿ���(����)*/
		*spg_ready_ptr = SMEE_TRUE;

		/*��ʾû���µ��¼�����*/
		*step_event_ptr = RLSGMV_STEP_NO_EVENT;
	}

	/*�Լ��ٶ�ǰ��������ٶ�*/
	mv_gen_data[axis_id].prev_vel = mv_gen_data[axis_id].cur_vel;
	mv_gen_data[axis_id].cur_vel += mv_gen_data[axis_id].cur_acc;

	/*���ٶȺ�����������λ��*/
	mv_gen_data[axis_id].cur_pos_rel += mv_gen_data[axis_id].prev_vel;

	/*�����Թ��ʵ�λ�Ʊ�ʾ��ʵ��λ�ơ��ٶȡ����ٶ�*/
	spg_data_ptr->position =
		mv_loc_params.pos_factor * mv_gen_data[axis_id].cur_pos_rel * RL_POS_UNIT;
	spg_data_ptr->position += mv_loc_params.start_pos;
	spg_data_ptr->velocity =
		mv_loc_params.pos_factor * mv_gen_data[axis_id].cur_vel *
			mv_loc_params.vel_unit;
	spg_data_ptr->acceleration =
		mv_loc_params.pos_factor * mv_gen_data[axis_id].cur_acc *
			mv_loc_params.acc_unit;

	/*��ǰ���ٶȹ�0*/
	mv_gen_data[axis_id].cur_acc = 0;
	
	system("pause");
	return ret_val;
}