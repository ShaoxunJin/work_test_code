#ifndef _ONE_ORDER_LPF_H_
#define _ONE_ORDER_LPF_H_
#define PI 3.1415926535897932385
#define freq 15
#define damping 0.7
#define sample_time 0.01

int m_calculation(double Freq, double Damping, double Sample_time, int length, double input_data[], double output_data[]);
#endif