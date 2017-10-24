//
// Illustrates basic usage of some prioque.c functions.
// Written 9/2017 by Golden G. Richard III (@nolaforensix)
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prioque.h"

typedef struct  {
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

typedef struct {
    int run;
    int io;
    int rep;
}temInput;

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


  int temTime, temPid, temRun, temIo, temRep;
  int prevPid = 0;

  while (scanf("%d", &temTime) != EOF){
    scanf("%d", &temPid);
    if(prevPid == temPid){
      scanf("%d %d %d", &temRun, &temIo, &temRep);

    }

  }
}