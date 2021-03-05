#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	char x[50];
	int i;
	for(i=0;i<50;i++){
		x[i] = i+1;
	}

	strncpy(x+20,x,20);
	strncpy(x+20,x,21);
	return 0;
}