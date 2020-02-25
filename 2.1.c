#include <stdio.h>
#include <stdlib.h>


int main(){
	
	double number;
	double e;
	double x;
	double x_i = 1;
	double x_ip1;
	double x_d;
	int state = 0;

	while( (scanf("%lf", &number)) != EOF){	

		/* computation */
		if(state == 0){
			e = number;
			state += 1;
		} else {
			x = number;
			while(1){
				x_ip1 = 0.5 * (x_i + x/x_i);
				x_d = x_i - x_ip1;
				if(x_d < 0) x_d *= -1;
				x_i = x_ip1;
				if(x_d < e) break; 
			}
			printf("\n%.10g", x_ip1);
			x_i = 1;
			x_ip1 = 0;
			x_d = 0;
		}		
	}
	
	return 0; 
}
