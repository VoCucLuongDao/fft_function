#include "stdio.h"
#include "stdint.h"
#include "math.h"

#define N_bits    10
#define N         (int) pow(2,N_bits)
#define pi        3.141592
/***************************************************************************************/
struct complex_number
{
	float Re;
	float Im;
};
typedef complex_number complex;
 
complex Wkn(int kn,int Ns)
{
	complex W;
	W.Re =   cos(2*pi*kn/Ns);
	W.Im =  -sin(2*pi*kn/Ns);
	return  W;
}
/********************************************************************************/
complex add_complex(complex x1, complex x2)
{
	complex y;
	y.Re = x1.Re + x2.Re;
	y.Im = x1.Im + x2.Im;
	return y;
}

complex sub_complex(complex x1, complex x2)
{
	complex y;
	y.Re = x1.Re - x2.Re;
	y.Im = x1.Im - x2.Im;
	return y;
}

complex mul_complex(complex x1, complex x2)
{
	complex y;
	y.Re = x1.Re*x2.Re - x1.Im*x2.Im;
	y.Im = x1.Im*x2.Re + x1.Re*x2.Im;
	return y;
}
/*******************************************************************************/
uint16_t invert_bits(uint16_t value)
{  
    uint8_t  sbit = N_bits >> 1;
    uint16_t temp_value = 0;
    
	if( N_bits & 0x01)
	{
	    temp_value |= (value & (0x01 << sbit));
	}
   
    for( uint16_t i = 0; i < sbit ; i += 1)
    {
    	temp_value |= ((value >> (N_bits - 1 - 2*i)) & (0x01 << i));
    	temp_value |= ((value & (0x01 << i)) << (N_bits - 1 - 2*i)); 	
	}
	
	return temp_value;
}

void fft(float *x)
{
	//dao bit input data
      complex temp_x[N];
    for(uint16_t i = 0; i < N; i++)
   {
      	temp_x[i].Re = x[invert_bits(i)];
      	temp_x[i].Im = 0;
   }
	//fft
	 complex temp_x_1[N];
	 complex temp_value;
	 
	for(uint16_t t_N = 2; t_N <= N; t_N *= 2)
    {
	    for(uint16_t k = 0; k < N/t_N;  k += 1)   
	   {
			for(uint16_t n = 0; n < t_N/2; n += 1)
		    {      
		        temp_value                  = mul_complex(temp_x[t_N*k + n + t_N/2], Wkn(n, t_N));
		        temp_x_1[t_N*k + n]         = add_complex(temp_x[t_N*k + n], temp_value); 
		        temp_x_1[t_N*k + n + t_N/2] = sub_complex(temp_x[t_N*k + n], temp_value);
		    }
	    }
    
    	for(uint16_t i = 0; i < N; i += 1 )
	    {
		   	temp_x[i] = temp_x_1[i];
		} 
   	}
	
	// output data
	uint32_t result[N/2]; 
	for(uint16_t t = 0; t < N/2; t += 1)
	{
		result[t] = (uint32_t)(sqrt(temp_x_1[t].Re*temp_x_1[t].Re + temp_x_1[t].Im*temp_x_1[t].Im) + 0.5);
		printf(" %d \n",result[t]);
	}
}


/***********************************************************************************************************/
int main()
{
	//ket qua thu duoc la do thi tan so nhung bi co Fs/N lan...
	// van de 1: phai lap day cac phan tu bi thieu cua x[N] bang 0 truoc khi FFT
	// van de 2: cat mang lien tuc mot doan N tu tin hieu thu duoc
	// van de 3: Chan !!!! khi nao ranh lam tiep
    float x[1024]   = {0 , 244 , 485 , 719 , 943 , 1153 , 1347 , 1521 , 1674 , 1803 , 1905 , 1981 , 2028 , 2047 , 2036 , 1996 , 1927 , 1831 , 1708 , 1562 , 1392 , 1203 , 997 , 776 , 545 , 305 , 61 , -183 , -426 , -662 , -888 , -1102 , -1300 , -1480 , -1638 , -1773 , -1882 , -1965 , -2019 , -2045 , -2041 , -2008 , -1947 , -1857 , -1741 , -1600 , -1437 , -1252 , -1050 , -833 , -603 , -366 , -122 , 122 , 366 , 603 , 833 , 1050 , 1252 , 1437 , 1600 , 1741 , 1857 , 1947 , 2008 , 2041 , 2045 , 2019 , 1965 , 1882 , 1773 , 1638 , 1480 , 1300 , 1102 , 888 , 662 , 426 , 183 , -61 , -305 , -545 , -776 , -997 , -1203 , -1392 , -1562 , -1708 , -1831 , -1927 , -1996 , -2036 , -2047 , -2028 , -1981 , -1905 , -1803 , -1674 , -1521 , -1347 , -1153 , -943 , -719 , -485 , -244 , 0 , 244 , 485 , 719 , 943 , 1153 , 1347 , 1521 , 1674 , 1803 , 1905 , 1981 , 2028 , 2047 , 2036 , 1996 , 1927 , 1831 , 1708 , 1562 , 1392 , 1203 , 997 , 776 , 545 , 305 , 61 , -183 , -426 , -662 , -888 , -1102 , -1300 , -1480 , -1638 , -1773 , -1882 , -1965 , -2019 , -2045 , -2041 , -2008 , -1947 , -1857 , -1741 , -1600 , -1437 , -1252 , -1050 , -833 , -603 , -366 , -122 , 122 , 366 , 603 , 833 , 1050 , 1252 , 1437 , 1600 , 1741 , 1857 , 1947 , 2008 , 2041 , 2045 , 2019 , 1965 , 1882 , 1773 , 1638 , 1480 , 1300 , 1102 , 888 , 662 , 426 , 183 , -61 , -305 , -545 , -776 , -997 , -1203 , -1392 , -1562 , -1708 , -1831 , -1927 , -1996 , -2036 , -2047 , -2028 , -1981 , -1905 , -1803 , -1674 , -1521 , -1347 , -1153 , -943 , -719 , -485 , -244 , 0 , 244 , 485 , 719 , 943 , 1153 , 1347 , 1521 , 1674 , 1803 , 1905 , 1981 , 2028 , 2047 , 2036 , 1996 , 1927 , 1831 , 1708 , 1562 , 1392 , 1203 , 997 , 776 , 545 , 305 , 61 , -183 , -426 , -662 , -888 , -1102 , -1300 , -1480 , -1638 , -1773 , -1882 , -1965 , -2019 , -2045 , -2041 , -2008 , -1947 , -1857 , -1741 , -1600 , -1437 , -1252 , -1050 , -833 , -603 , -366 , -122 , 122 , 366 , 603 , 833 , 1050 , 1252 , 1437 , 1600 , 1741 , 1857 , 1947 , 2008 , 2041 , 2045 , 2019 , 1965 , 1882 , 1773 , 1638 , 1480 , 1300 , 1102 , 888 , 662 , 426 , 183 , -61 , -305 , -545 , -776 , -997 , -1203 , -1392 , -1562 , -1708 , -1831 , -1927 , -1996 , -2036 , -2047 , -2028 , -1981 , -1905 , -1803 , -1674 , -1521 , -1347 , -1153 , -943 , -719 , -485 , -244 , 0 , 244 , 485 , 719 , 943 , 1153 , 1347 , 1521 , 1674 , 1803 , 1905 , 1981 , 2028 , 2047 , 2036 , 1996 , 1927 , 1831 , 1708 , 1562 , 1392 , 1203 , 997 , 776 , 545 , 305 , 61 , -183 , -426 , -662 , -888 , -1102 , -1300 , -1480 , -1638 , -1773 , -1882 , -1965 , -2019 , -2045 , -2041 , -2008 , -1947 , -1857 , -1741 , -1600 , -1437 , -1252 , -1050 , -833 , -603 , -366 , -122 , 122 , 366 , 603 , 833 , 1050 , 1252 , 1437 , 1600 , 1741 , 1857 , 1947 , 2008 , 2041 , 2045 , 2019 , 1965 , 1882 , 1773 , 1638 , 1480 , 1300 , 1102 , 888 , 662 , 426 , 183 , -61 , -305 , -545 , -776 , -997 , -1203 , -1392 , -1562 , -1708 , -1831 , -1927 , -1996 , -2036 , -2047 , -2028 , -1981 , -1905 , -1803 , -1674 , -1521 , -1347 , -1153 , -943 , -719 , -485 , -244 , 0 , 244 , 485 , 719 , 943 , 1153 , 1347 , 1521 , 1674 , 1803 , 1905 , 1981 , 2028 , 2047 , 2036 , 1996 , 1927 , 1831 , 1708 , 1562 , 1392 , 1203 , 997 , 776 , 545 , 305 , 61 , -183 , -426 , -662 , -888 , -1102 , -1300 , -1480 , -1638 , -1773 , -1882 , -1965 , -2019 , -2045 , -2041 , -2008 , -1947 , -1857 , -1741 , -1600 , -1437 , -1252 , -1050 , -833 , -603 , -366 , -122 , 122 , 366 , 603 , 833 , 1050 , 1252 , 1437 , 1600 , 1741 , 1857 , 1947 , 2008 , 2041 , 2045 , 2019 , 1965 , 1882 , 1773 , 1638 , 1480 , 1300 , 1102 , 888 , 662 , 426 , 183 , -61 , -305 , -545 , -776 , -997 , -1203 , -1392 , -1562 , -1708 , -1831 , -1927 , -1996 , -2036 , -2047 , -2028 , -1981 , -1905 , -1803 , -1674 , -1521 , -1347 , -1153 , -943 , -719 , -485 , -244 , 0 , 244 , 485 , 719 , 943 , 1153 , 1347 , 1521 , 1674 , 1803 , 1905 , 1981 , 2028 , 2047 , 2036 , 1996 , 1927 , 1831 , 1708 , 1562 , 1392 , 1203 , 997 , 776 , 545 , 305 , 61 , -183 , -426 , -662 , -888 , -1102 , -1300 , -1480 , -1638 , -1773 , -1882 , -1965 , -2019 , -2045 , -2041 , -2008 , -1947 , -1857 , -1741 , -1600 , -1437 , -1252 , -1050 , -833 , -603 , -366 , -122 , 122 , 366 , 603 , 833 , 1050 , 1252 , 1437 , 1600 , 1741 , 1857 , 1947 , 2008 , 2041 , 2045 , 2019 , 1965 , 1882 , 1773 , 1638 , 1480 , 1300 , 1102 , 888 , 662 , 426 , 183 , -61 , -305 , -545 , -776 , -997 , -1203 , -1392 , -1562 , -1708 , -1831 , -1927 , -1996 , -2036 , -2047 , -2028 , -1981 , -1905 , -1803 , -1674 , -1521 , -1347 , -1153 , -943 , -719 , -485 , -244 , 0 , 244 , 485 , 719 , 943 , 1153 , 1347 , 1521 , 1674 , 1803 , 1905 , 1981 , 2028 , 2047 , 2036 , 1996 , 1927 , 1831 , 1708 , 1562 , 1392 , 1203 , 997 , 776 , 545 , 305 , 61 , -183 , -426 , -662 , -888 , -1102 , -1300 , -1480 , -1638 , -1773 , -1882 , -1965 , -2019 , -2045 , -2041 , -2008 , -1947 , -1857 , -1741 , -1600 , -1437 , -1252 , -1050 , -833 , -603 , -366 , -122 , 122 , 366 , 603 , 833 , 1050 , 1252 , 1437 , 1600 , 1741 , 1857 , 1947 , 2008 , 2041 , 2045 , 2019 , 1965 , 1882 , 1773 , 1638 , 1480 , 1300 , 1102 , 888 , 662 , 426 , 183 , -61 , -305 , -545 , -776 , -997 , -1203 , -1392 , -1562 , -1708 , -1831 , -1927 , -1996 , -2036 , -2047 , -2028 , -1981 , -1905 , -1803 , -1674 , -1521 , -1347 , -1153 , -943 , -719 , -485 , -244 , 0 , 244 , 485 , 719 , 943 , 1153 , 1347 , 1521 , 1674 , 1803 , 1905 , 1981 , 2028 , 2047 , 2036 , 1996 , 1927 , 1831 , 1708 , 1562 , 1392 , 1203 , 997 , 776 , 545 , 305 , 61 , -183 , -426 , -662 , -888 , -1102 , -1300 , -1480 , -1638 , -1773 , -1882 , -1965 , -2019 , -2045 , -2041 , -2008 , -1947 , -1857 , -1741 , -1600 , -1437 , -1252 , -1050 , -833 , -603 , -366 , -122 , 122 , 366 , 603 , 833 , 1050 , 1252 , 1437 , 1600 , 1741 , 1857 , 1947 , 2008 , 2041 , 2045 , 2019 , 1965 , 1882 , 1773 , 1638 , 1480 , 1300 , 1102 , 888 , 662 , 426 , 183 , -61 , -305 , -545 , -776 , -997 , -1203 , -1392 , -1562 , -1708 , -1831 , -1927 , -1996 , -2036 , -2047 , -2028 , -1981 , -1905 , -1803 , -1674 , -1521 , -1347 , -1153 , -943 , -719 , -485 , -244 , 0 , 244 , 485 , 719 , 943 , 1153 , 1347 , 1521 , 1674 , 1803 , 1905 , 1981 , 2028 , 2047 , 2036 , 1996 , 1927 , 1831 , 1708 , 1562 , 1392 , 1203 , 997 , 776 , 545 , 305 , 61 , -183 , -426 , -662 , -888 , -1102 , -1300 , -1480 , -1638 , -1773 , -1882 , -1965 , -2019 , -2045 , -2041 , -2008 , -1947 , -1857 , -1741 , -1600 , -1437 , -1252 , -1050 , -833 , -603 , -366 , -122 , 122 , 366 , 603 , 833 , 1050 , 1252 , 1437 , 1600 , 1741 , 1857 , 1947 , 2008 , 2041 , 2045 , 2019 , 1965 , 1882 , 1773 , 1638 , 1480 , 1300 , 1102 , 888 , 662 , 426 , 183 , -61 , -305 , -545 , -776 , -997 , -1203 , -1392 , -1562 , -1708 , -1831 , -1927 , -1996 , -2036 , -2047 , -2028 , -1981 , -1905 , -1803 , -1674 , -1521 , -1347 , -1153 , -943 , -719 , -485 , -244 , 0 , 244 , 485 , 719 , 943 , 1153 , 1347 , 1521 , 1674 , 1803 , 1905 , 1981 , 2028 , 2047 , 2036 , 1996 , 1927 , 1831 , 1708 , 1562 , 1392 , 1203 , 997 , 776 , 545 , 305 , 61 , -183 , -426 , -662 , -888 , -1102 , -1300 , -1480 , -1638 , -1773 , -1882 , -1965 , -2019 , -2045 , -2041 , -2008 , -1947 , -1857 , -1741 , -1600 , -1437 , -1252 , -1050 , -833 , -603 , -366 , -122 , 122 , 366 , 603 , 833 , 1050 , 1252 , 1437 , 1600 , 1741 , 1857 , 1947 , 2008 , 2041 , 2045 , 2019 , 1965 , 1882 , 1773 , 1638 , 1480 , 1300 , 1102 , 888 , 662 , 426 , 183};
	fft(x);
	return 0;
}
