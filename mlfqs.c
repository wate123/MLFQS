//Jun Lin

#include <stdio.h>
#include <stdlib.h>
#include "prioque.h"

typedef struct {
    int Time;// time process is created and placed in queue
    int Pid; // unique process identifier
    int Run; // current amount of run time from tempQ
    int IO;  // current amount of I/O time from tempQ
    int Rep; // current repetitions from tempQ
    int runCount;
    int ioCount;
    int dCount;
    int q;   // quantum
    int b;  // demotion counter
    int g;  // promotion counter
    Queue tempQ;
    int Units;
    int finish;
    int count;
} ProcessData;

typedef struct {
    int RUN;
    int IO;
    int REP;
} temInput;


int main() {
  Queue hq; //highest priority
  Queue mq; //medium priority
  Queue lq; //lowest priority
  Queue proceReady;
  Queue io;  //io queue
  Queue newQ; //finish queue

  ProcessData data;
  ProcessData *enter;
  ProcessData *runQ = NULL;
  ProcessData *ioOp;
  ProcessData temp_ready;
  ProcessData *tempCurr;

  temInput dupe;

  init_queue(&hq, sizeof(ProcessData), TRUE, NULL, TRUE);
  init_queue(&mq, sizeof(ProcessData), TRUE, NULL, TRUE);
  init_queue(&lq, sizeof(ProcessData), TRUE, NULL, TRUE);
  init_queue(&proceReady, sizeof(ProcessData), TRUE, NULL, TRUE);
  init_queue(&io, sizeof(ProcessData), TRUE, NULL, TRUE);
  init_queue(&newQ, sizeof(ProcessData), TRUE, NULL, TRUE);


  int temp_time, temp_pid, temp_run, temp_io, temp_rep;

  int prev_pid=0;

  int null_process = 0;
  int processNum=0;

//input
  while(scanf("%d", &temp_time) != EOF) {
    scanf("%d",&temp_pid);
    if(prev_pid == temp_pid){
      scanf("%d %d %d", &temp_run, &temp_io, &temp_rep);
      dupe.RUN = temp_run;
      dupe.IO = temp_io;
      dupe.REP = temp_rep;
      while (end_of_queue(&proceReady)!=1) {
        tempCurr = pointer_to_current(&proceReady);
        next_element(&proceReady);
        if(tempCurr->Pid == temp_pid) {
          add_to_queue(&tempCurr->tempQ, &dupe, 1);
        }
      }
    }
    else {
      scanf("%d %d %d", &temp_run, &temp_io, &temp_rep);
      init_queue(&data.tempQ,sizeof(temInput), TRUE, NULL, TRUE);
      dupe.RUN = temp_run;
      dupe.IO = temp_io;
      dupe.REP = temp_rep;
      data.Time = temp_time;
      data.Pid = temp_pid;
      data.Run = temp_run;
      data.IO = temp_io;
      data.Rep = temp_rep;
      data.dCount = 0;
      data.count = 0;
      data.Units = 0;
      data.finish = 0;
      data.runCount = data.Run;
      data.ioCount = data.IO;
      add_to_queue(&proceReady, &data, 1);
      prev_pid = temp_pid;
      processNum++;
      destroy_queue(&data.tempQ);
    }
    rewind_queue(&proceReady);
  }
  
  
  int clock = 0;
  while(queue_length(&newQ) != processNum) {
    if(!empty_queue(&proceReady)) {
      enter = pointer_to_current(&proceReady);
      enter->q = 10;
      enter->b = 1;
      enter->g = 200000; //large g
    }
    if (!empty_queue(&proceReady) && clock == enter->Time) {
      remove_from_front(&proceReady, &temp_ready);
      add_to_queue(&hq, &temp_ready, 1);
      printf("CREATE: Process %d entered the ready queue at time %d.\n",temp_ready.Pid, clock);
    }
    if (!empty_queue(&io)) {
      ioOp = pointer_to_current(&io);
      for(int i=1;i<=queue_length(&io);i++) {
        ioOp->ioCount--;
        if(ioOp->ioCount == 0) {
          if(ioOp->q == 10) {
            if(ioOp->Rep != 1) {
              ioOp->runCount=ioOp->Run;
              ioOp->ioCount=ioOp->IO;
              ioOp->Rep--;
            }
            else if (!empty_queue(&ioOp->tempQ)) {
              remove_from_front(&ioOp->tempQ, &dupe);
              ioOp->runCount= dupe.RUN;
              ioOp->ioCount= dupe.IO;
              ioOp->IO = dupe.IO;
              ioOp->Rep = dupe.REP;
              ioOp->Run = dupe.RUN;
            }
            else {
              ioOp->finish = 1;
              ioOp->runCount = ioOp->Run;
            }
            printf("QUEUED: Process %d queued at level 1 at time %d\n",ioOp->Pid, clock);
            ioOp->count=0;
            remove_from_front(&io, &temp_ready);
            add_to_queue(&hq, &temp_ready,1);
          }
          else if(ioOp->q == 30) {
            if(ioOp->Rep != 1) {
              ioOp->Rep--;
              ioOp->runCount=ioOp->Run;
              ioOp->ioCount=ioOp->IO;
            }
            else if (!empty_queue(&ioOp->tempQ)) {
              remove_from_front(&ioOp->tempQ, &dupe);
              ioOp->runCount= dupe.RUN;
              ioOp->ioCount= dupe.IO;
              ioOp->IO = dupe.IO;
              ioOp->Rep = dupe.REP;
              ioOp->Run = dupe.RUN;
            }
            else {
              ioOp->finish = 1;
              ioOp->runCount = ioOp->Run;
            }

            if(ioOp->count != ioOp->q) {
              printf("QUEUED: Process %d queued at level 1 at time %d\n",ioOp->Pid, clock);
              ioOp->q = 10;
              ioOp->b = 1;
              ioOp->g = -1;
              ioOp->count=0;
              remove_from_front(&io, &temp_ready);
              add_to_queue(&hq, &temp_ready,1);
            }
            else {
              printf("QUEUED: Process %d queued at level 2 at time %d\n",ioOp->Pid, clock);
              ioOp->count=0;
              remove_from_front(&io, &temp_ready);
              add_to_queue(&mq, &temp_ready,1);
            }
          }else if(ioOp->q == 100) {
            if(ioOp->Rep != 1) {

              ioOp->runCount=ioOp->Run;
              ioOp->ioCount=ioOp->IO;
              ioOp->Rep--;
            }
            else if (!empty_queue(&ioOp->tempQ)) {
              remove_from_front(&ioOp->tempQ, &dupe);
              ioOp->Rep = dupe.REP;
              ioOp->ioCount= dupe.IO;
              ioOp->runCount= dupe.RUN;
              ioOp->Run = dupe.RUN;
              ioOp->IO = dupe.IO;
            }
            else {
              ioOp->finish = 1;
              ioOp->runCount = ioOp->Run;
            }
            if(ioOp->count != ioOp->q) {
              printf("QUEUED: Process %d queued at level 2 at time %d\n",ioOp->Pid, clock);
              ioOp->q = 30;
              ioOp->b = 2;
              ioOp->g = 2;
              ioOp->count=0;
              remove_from_front(&io, &temp_ready);
              add_to_queue(&mq, &temp_ready,1);
            }
            else {
              printf("QUEUED: Process %d queued at level 3 at time %d\n",ioOp->Pid, clock);
              ioOp->count=0;
              remove_from_front(&io, &temp_ready);
              add_to_queue(&lq, &temp_ready,1);
            }
          }
        }
        if(empty_queue(&io)) {break;}
        remove_from_front(&io, &temp_ready);
        add_to_queue(&io, &temp_ready,1);
        ioOp = pointer_to_current(&io);
      }
    }
      if (!empty_queue(&hq)) {
        runQ = pointer_to_current(&hq);
        if (runQ->runCount == runQ->Run) {
          printf("RUN: Process %d started execution at time %d, wants to execute for %d ticks.\n",runQ->Pid, clock, runQ->runCount);
        }
        runQ->runCount--;
        runQ->Units++;
        runQ->count++;
      }
      else if (!empty_queue(&mq)) {
        runQ = pointer_to_current(&mq);
        if (runQ->runCount == runQ->Run) {
          printf("RUN: Process %d started execution at time %d, wants to execute for %d ticks.\n",runQ->Pid, clock, runQ->runCount);
        }
        runQ->runCount--;
        runQ->Units++;
        runQ->count++;
      }
      else if (!empty_queue(&lq)) {
        runQ = pointer_to_current(&lq);
        if (runQ->runCount == runQ->Run) {
          printf("RUN: Process %d started execution at time %d, wants to execute for %d ticks.\n",runQ->Pid, clock, runQ->runCount);
        }
        runQ->runCount--;
        runQ->Units++;
        runQ->count++;
      }
      else {
        null_process++;
      }
      if(runQ!=NULL && runQ->finish == 1 && runQ->runCount==0) {
        if(runQ->q == 10) {
          printf("FINISHED: Process %d finished at time %d\n", runQ->Pid, clock);
          remove_from_front(&hq, &temp_ready);
          add_to_queue(&newQ, &temp_ready, 1);
          runQ = NULL;
        }
        else if(runQ->q == 30) {
          printf("FINISHED: Process %d finished at time %d\n", runQ->Pid, clock);
          remove_from_front(&mq, &temp_ready);
          add_to_queue(&newQ, &temp_ready, 1);
          runQ = NULL;
        }
        else if(runQ->q == 100) {
          printf("FINISHED: Process %d finished at time %d\n", runQ->Pid, clock);
          remove_from_front(&lq, &temp_ready);
          add_to_queue(&newQ, &temp_ready, 1);
          runQ = NULL;
        }
      }
      if (runQ!= NULL && runQ->count == runQ->q && runQ->runCount!=0) {
        runQ->dCount ++; //add 1 to its demotion counter
        runQ->count = 0;
        if(runQ->dCount == runQ->b) { //if demotion counter = demotion limit
          if(runQ->q == 10) {
            remove_from_front(&hq, &temp_ready);
            temp_ready.dCount = 0;
            temp_ready.q = 30;
            temp_ready.b = 2;
            temp_ready.g = 2;
            add_to_queue(&mq, &temp_ready, 1);
            printf("QUEUED: Process %d queued at level 2 at time %d\n",temp_ready.Pid, clock);
            runQ = NULL;
          }
          else if(runQ->q == 30) {
            remove_from_front(&mq, &temp_ready);
            temp_ready.dCount = 0;
            temp_ready.q = 100;
            temp_ready.b = -1;
            temp_ready.g = 1;
            add_to_queue(&lq, &temp_ready, 1);
            printf("QUEUED: Process %d queued at level 3 at time %d\n",temp_ready.Pid, clock);
            runQ=NULL;
          }
        }
      }
      else if (runQ!=NULL && runQ->runCount ==0 && runQ->ioCount!=0 && runQ->finish ==0) {
        if(runQ->q == 10) {
          printf("QUEUED: Process %d queued at IO at time %d\n",runQ->Pid, clock);
          remove_from_front(&hq, &temp_ready);
          add_to_queue(&io, &temp_ready, 1);
          runQ = NULL;
        }
        else if(runQ->q == 30) {
          printf("QUEUED: Process %d queued at IO at time %d\n",runQ->Pid, clock);
          remove_from_front(&mq, &temp_ready);
          add_to_queue(&io, &temp_ready, 1);
          runQ = NULL;
        }
        else if(runQ->q == 100) {
          printf("QUEUED: Process %d queued at IO at time %d\n",runQ->Pid, clock);
          remove_from_front(&lq, &temp_ready);
          add_to_queue(&io, &temp_ready, 1);
          runQ = NULL;
        }
      }
      else if(runQ!=NULL && runQ->count == runQ->q) {
        runQ->count =0;
        if(runQ->q == 30) {
          printf("QUEUED: Process %d queued at level 2 at time %d\n",runQ->Pid, clock);
          remove_from_front(&mq, &temp_ready);
          add_to_queue(&mq, &temp_ready, 1);
          runQ = NULL;
        }
        else if(runQ->q == 100) {
          printf("QUEUED: Process %d queued at level 3 at time %d\n",runQ->Pid, clock);
          remove_from_front(&lq, &temp_ready);
          add_to_queue(&lq, &temp_ready, 1);
          runQ = NULL;
        }
      }
      clock++;
    }
    printf("\nScheduler shutdown at time %d\n",clock);
    printf("\nTotal CPU usage for all processes scheduled:\n");
    printf("\nProcess <<null>>:   %5d time units.\n",null_process);
    while(end_of_queue(&newQ)!=1) {
      tempCurr = pointer_to_current(&newQ);
      printf("Process  %d       %5d time units.\n",tempCurr->Pid,tempCurr->Units);
      next_element(&newQ);
    }
    destroy_queue(&proceReady);
    destroy_queue(&io);
    destroy_queue(&newQ);
    destroy_queue(&hq);
    destroy_queue(&mq);
    destroy_queue(&lq);

    return 0;
  }

