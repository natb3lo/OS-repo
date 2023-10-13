/****************************************************************************************
 *   A program that creates three threads with the <pthread> API of UNIX systems,       *
 *  witch each of them rows a dice once and generates a different value each time       *
 *  the program runs.                                                                   *
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
    pthread_t t1, t2, t3;
    srand(time(NULL));

    printf("-----main Begin-----\n");

    if((pthread_create(&t1, NULL, row_dice, "Thread 1")) != 0)
    {
        fprintf(stderr, "Error: <thread 1> creation has failed.\n");
        exit(EXIT_FAILURE);
    }
    if((pthread_create(&t2, NULL, row_dice, "Thread 2")) != 0)
    {
        fprintf(stderr, "Error: <thread 2> creation has failed.\n");
        exit(EXIT_FAILURE);
    }
    if((pthread_create(&t3, NULL, row_dice, "Thread 3")) != 0)
    {
        fprintf(stderr, "Error: <thread 3> creation has failed.\n");
        exit(EXIT_FAILURE);
    }

    if((pthread_join(t1, NULL)) != 0)
    {
        fprintf(stderr, "Error: Main thread has failed to wait for <Thread 1>.");
        exit(EXIT_FAILURE);
    }
    if((pthread_join(t2, NULL)) != 0)
    {
        fprintf(stderr, "Error: Main thread has failed to wait for <Thread 2>.");
        exit(EXIT_FAILURE);
    }
    if((pthread_join(t3, NULL)) != 0)
    {
        fprintf(stderr, "Error: Main thread has failed to wait for <Thread 3>.");
        exit(EXIT_FAILURE);
    }
   

    return 0;
}
