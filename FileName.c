#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define ERROR_OF -1
#define BUFFER_SIZE 1024

int broji(char* filename){
	
	FILE* fp = NULL;
	char buffer[BUFFER_SIZE];
	int count = 0;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Eroor");
		return ERROR_OF;
	}
	
	while (!feof(fp)) {
		fgets(buffer, BUFFER_SIZE, fp);
		++count;
	}

	fclose(fp);


}



int main() {
	

	return 0;
}