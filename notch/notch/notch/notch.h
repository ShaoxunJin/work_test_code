#ifndef _NOTCH_H_
#define _NOTCH_H_
#define PI 3.1415926535897932385
#define freq_zero 40
#define freq_pole 40
#define beta_zero 0.25
#define beta_pole 0.85
#define sample_time 0.0001

int m_calculation(double Freq_zero, double Freq_pole, double Beta_zero, double Beta_pole,
				  double Sample_time, int length, double input_data[], double output_data[]);
#endif