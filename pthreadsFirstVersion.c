/*
    Deiby Santiago Munoz Patino 1844360
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int max;

void *mythread(void *arg) {
  char *letter = arg;
  int i; // stack (private per thread)
  int counter = 0; // local counter for each thread
  printf("%s: begin [addr of i: %p]\n", letter, &i);
  for (i = 0; i < max; i++) {
    counter = counter + 1;
  }
  printf("%s: done [counter: %d]\n", letter, counter);
  return (void *)(size_t)counter; // return counter as the thread result
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage: main-first <loopcount>\n");
    exit(1);
  }
  max = atoi(argv[1]);

  pthread_t p1, p2;
  int total_counter = 0;
  void *p1_result, *p2_result;

  printf("main: begin\n");

  pthread_create(&p1, NULL, mythread, "A");
  pthread_create(&p2, NULL, mythread, "B");

  pthread_join(p1, &p1_result);
  pthread_join(p2, &p2_result);

  total_counter = (int)(size_t)p1_result + (int)(size_t)p2_result;

  printf("main: done\n [counter: %d]\n [should: %d]\n",
         total_counter, max * 2);
  return 0;
}
