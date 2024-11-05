/*
    Deiby Santiago Munoz Patino 1844360
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int max;
int num_threads;

void *mythread(void *arg) {
  int i; // stack (private per thread)
  int counter = 0; // local counter for each thread
  printf("Thread %d: begin [addr of i: %p]\n", *(int *)arg, &i);
  for (i = 0; i < max; i++) {
    counter = counter + 1;
  }
  printf("Thread %d: done [counter: %d]\n", *(int *)arg, counter);
  return (void *)(size_t)counter; // return counter as the thread result
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "usage: main-second <loopcount> <num_threads>\n");
    exit(1);
  }
  max = atoi(argv[1]);
  num_threads = atoi(argv[2]);

  pthread_t *threads = malloc(sizeof(pthread_t) * num_threads);
  int *thread_ids = malloc(sizeof(int) * num_threads);
  int total_counter = 0;
  void **thread_results = malloc(sizeof(void *) * num_threads);

  printf("main: begin\n");

  for (int i = 0; i < num_threads; i++) {
    thread_ids[i] = i;
    pthread_create(&threads[i], NULL, mythread, &thread_ids[i]);
  }

  for (int i = 0; i < num_threads; i++) {
    pthread_join(threads[i], &thread_results[i]);
    total_counter += (int)(size_t)thread_results[i];
  }

  printf("main: done\n [counter: %d]\n [should: %d]\n",
         total_counter, max * num_threads);

  free(threads);
  free(thread_ids);
  free(thread_results);

  return 0;
}
