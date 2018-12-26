
#include <stdio.h>
#include <fcntl.h>      //For stat()
#include <sys/types.h>   
#include <sys/stat.h>
#include <sys/wait.h>   //for waitpid()
#include <unistd.h>     //for fork(), wait()
#include <string.h>     //for string comparison etc
#include <stdlib.h>     //for malloc()

int main()
{

    char *userInput = (char*)(malloc(120));
    char *parts[6];
    char *command;
    //read user input
    printf("YWIMC > ");
 	fgets(userInput, 120, stdin);
	strtok(userInput, "\n");
	int *result = (int *)malloc(sizeof(int));
	int cPid[120];
	int n = 0;
    while ( strcmp(userInput, "quit") != 0 ){
	int i = 1;
	command = strtok(userInput, " ");
	parts[i] = strtok(NULL, " ");
	
	while(parts[i] != NULL){
		i++;
		parts[i] = strtok(NULL, " ");
	}
	parts[0] = command;
	struct stat fileStat;
	int x = 0;	
		if(strcmp(command, "wait") == 0){
			int q = atoi(parts[1]);
			for(int h = 0; h < n; h++){
				if(q == cPid[h]){
					cPid[h] = 0;
				}
			}
			if(waitpid(q, result, 0) == -1){
				printf("%i not a valid child pid\n", q);
			}
		}else if(strcmp(command, "result") == 0){
			
			printf("%i\n", WEXITSTATUS(*result));
		}else if(strcmp(command, "printchild") == 0){
			printf("Unwaited Child Processes\n");
			for(int g = 0; g < n; g++){
				if(cPid[g] != 0){
					printf("%i\n", cPid[g]);
				}
			}
		}else{
        	 x = stat(command, &fileStat); //Separate and create path variable should be first step
        	if(x < 0){
                	printf("%s not found\n", command);
        	}else{
        		int z = fork();
        		if(z == 0){	
				execv(command, parts);
                		return 0;
        		}else{
				cPid[n] = z;
				n++;
			}

       if(strcmp(parts[i - 1], "&") != 0){
	int aCPid = cPid[n-1];
	cPid[n-1] = 0;
	 waitpid(aCPid, result, 0);
	}else{
	 printf("Child %d in background\n", cPid[n - 1]);
	}
        	}
	}
        printf("YWIMC > ");
 	fgets(userInput, 120, stdin);
	strtok(userInput, "\n");
    }
    
    printf("Goodbye!\n");
    return 0;

}

