/*****************************************************************************************
*    A program that creates "n" threads(based on how many of them you want)              *
*    with the <pthread> API of UNIX systems, witch each of them rows a dice once         *
*    and generates a different value each time the program runs.                         *                                                                   *
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void print_dice(int value)
{
    
    switch(value)
    {
        case 1: printf(     " _____________\n"
                            "|             |\n"
                            "|             |\n"
                            "|     ()      |\n"
                            "|             |\n"
                            "|_____________|\n");
                break;
        
        case 2: printf(     " _____________\n"
                            "|          () |\n"
                            "|             |\n"
                            "|             |\n"
                            "| ()          |\n"
                            "|_____________|\n");
                break;
        
        case 3: printf(     " _____________\n"
                            "|          () |\n"
                            "|             |\n"
                            "|      ()     |\n"
                            "|             |\n"
                            "|  ()         |\n"
                            "|_____________|\n");
                break;

        case 4: printf(     " _____________\n"
                            "| ()       () |\n"
                            "|             |\n"
                            "|             |\n"
                            "|             |\n"
                            "| ()       () |\n"
                            "|_____________|\n");
                break;

        case 5: printf(     " _____________\n"
                            "| ()       () |\n"
                            "|             |\n"
                            "|      ()     |\n"
                            "|             |\n"
                            "| ()       () |\n"
                            "|_____________|\n");
                break;

        case 6: printf(     " _____________\n"
                            "| ()       () |\n"
                            "|             |\n"
                            "| ()       () |\n"
                            "|             |\n"
                            "| ()       () |\n"
                            "|_____________|\n");
                break;
        
    }

    printf("\n");
}

void* row_dice(void* arg)
{
    int num;
    
    pthread_mutex_lock(&lock);

    printf("%s:\n", (char*) arg);

    num = (rand() % 6) + 1;

    print_dice(num);

    pthread_mutex_unlock(&lock);
    
    return NULL;
}

int main()
{
    pthread_t *th;
    char buffer[80];
    int numThreads;

    srand(time(NULL));

    printf("-----main Begin-----\n");

    int isNum = 0;
    do
    {
        isNum = 1;
        printf("Number of threads that will row the dice once: ");
        fgets(buffer, 80, stdin);

        for(int i=0; buffer[i]; i++)
        {
            if(buffer[0] == '\n')
            {
                printf("At least one thread must be created!\n");
                isNum = 0;
                break;
            }
            else if(!(buffer[i] >= '0' && buffer[i] <= '9') && !(buffer[i] == '\n'))
            {
                printf("Only numbers are acepted in this field!\n");
                isNum = 0;
                break;
            }
            
        }
    }while(!isNum);

    numThreads = atoi(buffer);
    th = malloc(numThreads*sizeof(pthread_t));
    char threadArgs[numThreads][10];
    
    for(int i=0; i<numThreads; i++)
    {
        snprintf(threadArgs[i], 10, "Thread %d", i+1);
        int rt = pthread_create(&th[i], NULL, row_dice, (void*)threadArgs[i]);
        if(rt != 0)
        {
            fprintf(stderr, "Error: <thread %d> creation has failed.\n", i+1);
            exit(EXIT_FAILURE);
        }
    }
    for(int i=0; i<numThreads; i++)
    {
        int rw = pthread_join(th[i], NULL);
        if(rw != 0)
        {
            fprintf(stderr, "Error: Main thread has failed to wait for <Thread %d>.\n", i+1);
            exit(EXIT_FAILURE);
        }

    }

    free(th);

    return 0;
}
