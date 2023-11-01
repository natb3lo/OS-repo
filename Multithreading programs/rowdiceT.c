/*****************************************************************************************
*    A program that creates "n" threads(based on how many of them you want and at your   *
*    own risk) with the <pthread> API of UNIX systems, witch each of them rows a dice    *
*    as many times as you decide and generates the frequency that each die face          *
*    showed up by each thread.                                                           *
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int numRolls = 0;

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
    int num, sum;
    int freq[6] = {0};
    int count = 0;
    char st[3] = "st";
    char nd[3] = "nd";
    char rd[3] = "rd";
    char th[3] = "th";

    pthread_mutex_lock(&lock);

    for(int i=0; i<strlen((char*)arg)+7; i++)
    {
        printf("-");
    }

    printf("\n");

    for(int i=0, b=strlen((char*)arg)+7; ; i++)
    {
        printf(" ");
        if(i == (b/4)-1)
        {
            printf("%s\n", (char*)arg);
            break;
        }
    } 
    //printf("%s\n", (char*)arg);

    for(int i=0; i<strlen((char*)arg)+7; i++)
    {
        printf("-");
    }
    printf("\n");

    do
    {
        num = (rand() % 6) + 1;
        freq[num-1] += 1;
        sum += num;

        printf("%5d%s Roll: %d\n", count+1, ((count+1) == 1) ? st : ((count+1) == 2) ? nd : ((count+1) == 3) ? rd : th, num);
        
        count++;

    }while(count < numRolls);

    printf("\nFrequency:\n\n");

    for(int i=0; i<6; i++)
    {
        printf("(%d) ", i+1);
        printf("%.2f%%\n", ((float)freq[i] / numRolls) * 100.0);
        print_dice(i+1);
        
    }

    pthread_mutex_unlock(&lock);
    
    return NULL;
}

int main()
{
    pthread_t *th;
    char buffer[80];
    int numThreads;

    srand(time(NULL));

    printf("-----Main Begin-----\n");

    int isNum = 0;
    do
    {
        isNum = 1;
        printf("Number of threads: ");
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

    isNum = 0;
    do
    {
        isNum = 1;
        printf("Number of Rollings for each Thread: ");
        fgets(buffer, 80, stdin);

        for(int i=0; buffer[i]; i++)
        {
            if(buffer[0] == '\n' || buffer[0] == '0')
            {
                printf("The dice must be rolled at least 1 time!\n");
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

    numRolls = atoi(buffer);

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
