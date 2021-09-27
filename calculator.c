#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLEN 1000

int fds[100][2];
char operators[100];
int numberOperators=0;

//child operation
int child(int children, char operation){
	close(0);
	if (children == 1){
		dup(fds[0][0]);
	} else{
		dup(fds[numberOperators+children-1][0]);
	}

	close(3);
	dup(fds[children][0]);
	close(1);
	dup(fds[numberOperators+children][1]);

	if (operation == '+')
		execl("./add", "add", "-v", NULL);
	if (operation == '-')
                execl("./subtract", "subtract", "-v", NULL);
	if (operation == '*')
                execl("./multiply", "multiply", "-v", NULL);
	if (operation == '/')
                execl("./divide", "divide", "-v", NULL);
}

int main(int argc, char *argv[]) {
	char line[MAXLEN], *temp;

	FILE *dataFile = fopen(argv[1], "r");
	//read the first line - it contains the configuration
	fgets(line, MAXLEN, dataFile); 

	// sample content for line: a + b - c
	strtok(line, " \n"); //skip the symbol representing variable/parameter
	int numberOperators=0;
	while (temp = strtok(NULL, " \n")) {
		operators[numberOperators] = temp[0];
		printf("operator: %c\n", operators[numberOperators]);
		numberOperators++;
		strtok(NULL, " \n"); //skip the symbol representing variable/parameter
	}

	//creates pipe for operation
	for (int i = 0; i < 2*numberOperators+1; i++)
		pipe(fds[i]);

	//counts number of children	
	for (int i = 1; i <= numberOperators; i++){
		if (fork() == 0)
			child(i, operators[i-1]);
	}
	//setup the configuration with necessary # of children
	//continue to read the data from the file
	//you can use fscanf() to read the remaining data!
	//Here is some code to get started!
	int valuen;
	//int total;
	/*
	int num = 0;
	while(fscanf(dataFile, "%d", &valuen) == 1){
                write(fds[num][1], &valuen, sizeof(int));
		num++;
		printf("%d", total);
	}
	*/
	
	//continues until break
	while (1){
		for (int i = 0; i <= numberOperators; i++){
			//gets data	
			if (fscanf(dataFile, "%d", &valuen) == 1)
				write(fds[i][1], &valuen, sizeof(int));
			else
				exit(0);
		}
	}
	
}

