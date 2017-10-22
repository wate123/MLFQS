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

Process_Data *printProcess;
void printPro(Queue *que){
  printProcess = (Process_Data *)pointer_to_current(que);
  printf("%d\n", printProcess->Pid);
}

int main() {
  Queue hq;     //highest priority
  Queue mq;     //medium priority
  Queue lq;     //lowest priority

  //initialize queue
  init_queue(&hq, sizeof(Process_Data), TRUE, NULL, TRUE);
  init_queue(&mq, sizeof(Process_Data), TRUE, NULL, TRUE);
  init_queue(&lq, sizeof(Process_Data), TRUE, NULL, TRUE);

  Process_Data temp;
  Process_Data


  int temp_time, temp_pid, temp_run, temp_io, temp_rep;

  while (scanf("%d", &temp_time) != EOF){
    scanf("%d", &temp_pid);

  }
}