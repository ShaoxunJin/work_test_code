#ifndef _PID_H_
#define _PID_H_

int m_calculate_PID(double kp, double ki, double kd, int length,
					double sample_time, double pid_in[],double out_data_increment[], double out_data_absolute[]);


#endif