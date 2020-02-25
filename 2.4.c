// real numbers
#include <stdio.h>
int slength(char str[]);
double str2double(char str[]);

int main(){

	char str[999];
	while( scanf("%s", str) != EOF ){
		printf("%.10g\n", str2double(str));
	}
	return 0;
}

int slength(char *s){
	char *p = s;
	while (*p != '\0') p++;
	return p - s;
}

double str2double(char str[]){

	int len = slength(str); 

	enum node{prolog, i_p, d_p, e, e_plus, suf} Node;
	Node = prolog;
	double number;
	double mult = 10;
	int exp = 0;
	int expb = 0;
	double expM = 1;
	int eSign = 0;
	int edigit = 0;
	int digit = 0;

	for( int i = 0; i < len; i++){
		char symbol = str[i];
		switch(Node){
			case(prolog):
				if(symbol >= '0' && symbol <= '9'){
					number = (int)symbol - 48;
					digit = 1;
					Node = i_p;
					break;	
				} else if(symbol == '.'){
					number = 0;
					Node = d_p;
					break;
				}

			case(i_p):
				if(symbol >= '0' && symbol <= '9'){
					number = number * mult + ((int)symbol - 48);
					Node = i_p;
				} else if(symbol == '.'){
					Node = d_p;
				} else if(symbol == 'e' || symbol == 'E'){
					expb = 1;
					Node = e;
				} else if(symbol == 'f' || symbol == 'F'){
					Node = suf;
				}
				break;

			case(d_p):
				if(symbol >= '0' && symbol <= '9'){
					number = number + ((int)symbol - 48)/mult;
					mult = mult * 10;
					digit = 1;
					Node = d_p;	
				} else if(symbol == 'e' || symbol == 'E'){
					if(digit) {Node = e; expb = 1;} 
				} else if(symbol == 'f' || symbol == 'F'){
					if(digit) Node = suf; 
				}
				break;

			case(e):
				if(symbol >= '0' && symbol <= '9'){
					exp = (int)symbol - 48;
					edigit = 1;
					Node = e_plus;	
				} else if(symbol == '+'){
					Node = e_plus;
				} else if(symbol == '-'){
					Node = e_plus;
					eSign = 1;
				}
				break;

			case(e_plus):
				if(symbol >= '0' && symbol <= '9'){
					exp = exp * mult + ((int)symbol - 48);
					edigit = 1;
					Node = e_plus;	
				} else if(symbol == 'f' || symbol == 'F'){
					Node = suf;
				}
				break;
				
			case(suf):
				break;
			
		} 
	}	
	if(expb){
		for( int i = 0; i < exp; i++){
			expM = expM * 10;  
		}
		if(eSign){
			number = number / expM;
		} else {
			number = number * expM;
		}
	}
	return number;
}
