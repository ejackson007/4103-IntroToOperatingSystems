//
//  main.cpp
//  MiniProject3
//
//  Created by Evan Jackson on 10/22/19.
//  Copyright © 2019 Evan Jackson. All rights reserved.
//  This code was written to find the summation of an array
//  of size 6000 filled with the values 1-6000 using pthreads.
//  with and without a semaphore
//

#include <iostream>
#include <pthread.h>

#define ARRAY_SIZE 6000
#define THREAD_COUNT 4

using namespace std;

int pid = 0; //Used to define which part of the array the thread is working on
//initialize array to store individual thread sums
int sum[THREAD_COUNT] = {0};
int a[ARRAY_SIZE];
pthread_mutex_t the_mutex;

//function to create a sum for the thread partition
void* partial_sum(void* arg) {
    int thread_pid = pid++;
    for (int i = thread_pid * (ARRAY_SIZE / THREAD_COUNT);
         i < (thread_pid + 1) * (ARRAY_SIZE / THREAD_COUNT);
         i++){
        //lock so that there is no interference
        pthread_mutex_lock(&the_mutex);
        sum[thread_pid] += a[i];
        //unlock
        pthread_mutex_unlock(&the_mutex);
    }
    return sum;
}

int main(int argc, const char * argv[]) {
    int total = 0;
    //initialize threads
    pthread_t threads[THREAD_COUNT];
    //Fill array with values
    for(int i = 0; i < ARRAY_SIZE; i++)
        a[i] = i + 1;
    
    //send each thread to the sum function to get partial sum
    for(int i = 0; i < THREAD_COUNT; i++)
        pthread_create(&threads[i], NULL, partial_sum, (void*)NULL);
    
    //join threads
    for(int i = 0; i < THREAD_COUNT; i++)
        pthread_join(threads[i], NULL);
    
    for(int i = 0; i < THREAD_COUNT; i++)
        total += sum[i];
    
    printf("The summation of the array is: %d\n", total);
    return 0;
}
