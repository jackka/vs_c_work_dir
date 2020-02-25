#include <stdio.h>
#include <stdlib.h>


int main(){
	
	double number;
	double x;
	double res;
	double altRes;
	int state = 0;

	while( (scanf("%lf", &number)) != EOF){	

		/* computation */
		if(state == 0){
			x = number;
			state += 1;
		} else if(state == 1){
			altRes = number;
			res = x * number;
			state += 1;
		} else if(state == 2){
			res = res + number;
			state += 1;
		} else res = res * x + number;
	}
	
	if(state == 2) printf("%.10g\n", altRes);
	else if (state > 2) printf("%.10g\n", res);
	return 0; 

}
