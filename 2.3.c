#include <stdio.h>
#include <stdlib.h>

int fibR(int n);
int fibI(int n);

int main(){
	
	int num;

	while( (scanf("%d", &num)) != EOF){
		printf("%d\n", fibI(num));
		printf("%d\n", fibR(num));
	}
	
	return 0; 

}

int fibR(int n){
	if (n == 0 || n == 1)
		return n;
	else 
		return (fibR(n-1) + fibR(n-2));
}

int fibI(int n){
	
	int first = 1, second = 1, i, res;
 
	for (i = 0; i < n; i++){
		if (i <= 1)
			res = 1;
		else {
			res = first + second;
			first = second;
			second = res;
		}
	}
	return res;
}
