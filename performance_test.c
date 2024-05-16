#include <stdio.h>

int main(int argc, char ** argc){
	setuid(atoi(argv[1])); // set uid
	
	int i = 0;
	while(1){
		i = (i+1) % 1000;
	}
}