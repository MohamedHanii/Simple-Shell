#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

void sighandler(int signum) {
   FILE *fp;
   fp = fopen("logFile.txt", "a");
   fprintf(fp, "Process Terminated \n");
   fclose(fp);
   wait(NULL); //handle zombile state


}

int main()
{
    char input[50];
    const char dlimit[2] = " ";
    char *args[26];
    int sync = 0;
    pid_t child_pid;

    // Create a New LogFile and delete old one
    FILE *fp;
    fp = fopen("logFile.txt", "w");
    fclose(fp);

    while (1)
    {
        printf(" $> ");
        scanf("%[^\n]%*c", input);
        // Partition the String Input
        int i = 0;
        args[0] = strtok(input, dlimit);
        while (args[i] != NULL)
        {
            if (*args[i] == '&')
            {
                sync = 1;
                i--;
            }
            args[++i] = strtok(NULL, dlimit);
        }
        if (strcmp("exit", input) == 0)
        {
            exit(0);
        }
        else
        {
            child_pid = fork();

            if (child_pid > 0) // parent
            {
                signal(SIGCHLD, sighandler);
                if (sync == 0)
                {
                    wait(NULL);
                }
                else
                {
                    sync = 0;
                }
            }
            else if (child_pid == 0)// child
            {
                int created = execvp(args[0], args);

                if (created = -1)
                {
                    printf("%s Command Not Found \n", args[0]);
                }
                exit(1);
            }
            else
            {
                printf("This Error Creating this Process");
            }
        }


    }
    return (0);
}
