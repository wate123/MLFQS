//
// Illustrates basic usage of some prioque.c functions.
// Written 9/2017 by Golden G. Richard III (@nolaforensix)
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prioque.h"

typedef struct Process_Data {
    int Num;
    int Pid;  //Process Id
    int A_time; //Process Arrival Time
    int B_time; //Process Bruest Time
    int Priority; //Process Priority
    int F_time; //Process Finish Time
    int R_time; //Process Remaining  Time During Execution
    int W_time; //Waiting Time
    int S_time; //Process start Time
    int Res_time;
} Process_Data;


// comparison function for queue of Process_Data elements
int some_type_compare(void *e1, void *e2) {
  Process_Data *s1=(Process_Data *)e1;
  Process_Data *s2=(Process_Data *)e2;
  if (s1->a == s2->a && s1->buf != s2->buf) {
    return 1;
  }
  else {
    return 0;
  }
}


int main(int argc, char *argv[]) {
  FILE* fptr;
  fptr = fopen("input.txt","r");
  Queue q;
  init_queue(&q, sizeof(Process_Data), TRUE, some_type_compare, FALSE);
  Process_Data time, pid, run, io, repeat;
  int clock = 0;
  time.a = 0;
  while(!empty_queue(&q)){
    for (int i = 1; i < repeat.a ; ++i) {

    }
  }
  fscanf(fptr,"%d", &time);


  add_to_queue(&q, &s1, s1.a+1);
  add_to_queue(&q, &s2, s2.a+1);
  add_to_queue(&q, &s3, s3.a+1);
  add_to_queue(&q, &s4, s4.a+1);
  rewind_queue(&q);
  printf("Queue contains:\n");
  int clock = 0;
  while (! end_of_queue(&q)) {
    printf("%d %s with priority %d\n",
           ((Process_Data *)pointer_to_current(&q))->a,
           ((Process_Data *)pointer_to_current(&q))->buf,
           current_priority(&q));
    next_element(&q);
  }
  remove_from_front(&q, &e);
  printf("Removed %d %s from queue.\n", e.a, e.buf);
  printf("Queue contains:\n");
  while (! end_of_queue(&q)) {
    printf("%d %s with priority %d\n",
           ((Process_Data *)pointer_to_current(&q))->a,
           ((Process_Data *)pointer_to_current(&q))->buf,
           current_priority(&q));
    next_element(&q);
  }
  printf("Destroying queue.\n");
  destroy_queue(&q);
  printf("Queue contains:\n");
  while (! end_of_queue(&q)) {
    printf("%d %s with priority %d\n",
           ((Process_Data *)pointer_to_current(&q))->a,
           ((Process_Data *)pointer_to_current(&q))->buf,
           current_priority(&q));
    next_element(&q);
  }
}