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
    int Time;
    int Pid;  //Process Id
    int Run; //Process Bruest Time
    int IO;  // I/O time
    int Rep; // repeat
    int q; //quantum
    int g; //promotion counter
    int b; //demotion counter
    int fin; //finished bit
    int pro_c;
    int total_cpu;
    int count; // counter to count ticks ran
    int r_c; // decremental counter for run
    int io_c;// decremental counter for io
    int dem_c;//demotion counter(times over quantum)

    Queue tempQ;
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
  Queue proceReady;
  Queue newQ;
  Queue io;


  //initialize queue
  init_queue(&hq, sizeof(Process_Data), TRUE, NULL, TRUE);
  init_queue(&mq, sizeof(Process_Data), TRUE, NULL, TRUE);
  init_queue(&lq, sizeof(Process_Data), TRUE, NULL, TRUE);
  init_queue(&proceReady, sizeof(Process_Data), TRUE, NULL, TRUE);
  init_queue(&newQ, sizeof(Process_Data), TRUE, NULL, TRUE);
  init_queue(&io, sizeof(Process_Data), TRUE, NULL, TRUE);

  Process_Data data;
  Process_Data *tempCurr;
  Process_Data temp_ready;
  Process_Data *doing_io;
  Process_Data *enter;
  Process_Data *last_ran = NULL;
  temInput dupe;



  int temTime, temPid, temRun, temIo, temRep;
  int prevPid;
  int processNum;
  int null_process = 0;

  while (scanf("%d", &temTime) != EOF){
    scanf("%d", &temPid);
    if(prevPid == temPid){
      scanf("%d %d %d", &temRun, &temIo, &temRep);
      while (end_of_queue(&proceReady) != TRUE){
        tempCurr = pointer_to_current(&proceReady);
        next_element(&proceReady);
        if(tempCurr->Pid == temPid){
          add_to_queue(&tempCurr->tempQ, &dupe, 1);
        }
      }
      dupe.run = temRun;
      dupe.io = temIo;
      dupe.rep = temRep;
    } else{
      scanf("%d %d %d", &temRun, &temIo, &temRep);
      init_queue(&data.tempQ, sizeof(temInput), TRUE, NULL, TRUE);
      data.Time = temTime;
      data.Pid = temPid;
      data.Run = temRun;
      data.IO = temIo;
      data.Rep = temRep;
      add_to_queue(&proceReady,&data, 1);
      prevPid = temPid;
      processNum++;
      destroy_queue(&data.tempQ);
    }
    rewind_queue(&proceReady);
  }

  //scheduler
  int clock = 0;
  while(queue_length(&newQ) != processNum){
    if(!empty_queue(&proceReady)){
      enter = pointer_to_current(&proceReady);
      enter->q = 10;
      enter->b = 1;
      enter->g = -1;
    }

    //high priority
    if (!empty_queue(&proceReady) && clock == enter->Time) {
      remove_from_front(&proceReady, &temp_ready);
      add_to_queue(&hq, &temp_ready, 1);
      printf("CREATE: Process %d entered the ready queue at time %d.\n",data.Pid, clock);
    }

    if (!empty_queue(&io)) {
      doing_io = pointer_to_current(&io);
      for(int i=1;i<=queue_length(&io);i++) {
        doing_io->io_c--;
        if(doing_io->io_c == 0) {
          if(doing_io->q == 100) {
            if(doing_io->Rep != 1) {
              doing_io->Rep--;
              doing_io->r_c=doing_io->Run;
              doing_io->io_c=doing_io->IO;
            }
            else if (!empty_queue(&doing_io->tempQ)) {
              remove_from_front(&doing_io->tempQ, &dupe);
              doing_io->Run = dupe.run;
              doing_io->r_c= dupe.run;
              doing_io->io_c= dupe.io;
              doing_io->IO = dupe.io;
            }
            else {
              doing_io->fin = 1;
              doing_io->r_c = doing_io->Run;
            }
            if(doing_io->count != doing_io->q) {
              printf("QUEUED: Process %d queued at level 2 at time %d\n",doing_io->Pid, clock);
              doing_io->q = 30;
              doing_io->b = 2;
              doing_io->g = 2;
              doing_io->count=0;
              remove_from_front(&io, &temp_ready);
              add_to_queue(&mq, &temp_ready,1);
            }
            else {
              printf("QUEUED: Process %d queued at level 3 at time %d\n",doing_io->Pid, clock);
              doing_io->count=0;
              remove_from_front(&io, &temp_ready);
              add_to_queue(&lq, &temp_ready,1);
            }
          }
          else if(doing_io->q == 30) {
            if(doing_io->Rep != 1) {
              doing_io->Rep--;
              doing_io->r_c=doing_io->Run;
              doing_io->io_c=doing_io->IO;
            }
            else if (!empty_queue(&doing_io->tempQ)) {
              remove_from_front(&doing_io->tempQ, &dupe);
              doing_io->Rep = dupe.rep;
              doing_io->Run = dupe.run;
              doing_io->r_c= dupe.run;
              doing_io->io_c= dupe.io;
              doing_io->IO = dupe.io;
            }
            else {
              doing_io->fin = 1;
              doing_io->r_c = doing_io->Run;
            }

            if(doing_io->count != doing_io->q) {
              printf("QUEUED: Process %d queued at level 1 at time %d\n",doing_io->Pid, clock);
              doing_io->q = 10;
              doing_io->b = 1;
              doing_io->g = -1;
              doing_io->count=0;
              remove_from_front(&io, &temp_ready);
              add_to_queue(&hq, &temp_ready,1);
            }
            else {
              printf("QUEUED: Process %d queued at level 2 at time %d\n",doing_io->Pid, clock);
              doing_io->count=0;
              remove_from_front(&io, &temp_ready);
              add_to_queue(&mq, &temp_ready,1);
            }
          }
          else if(doing_io->q == 10) {
            if(doing_io->Rep != 1) {
              doing_io->Rep--;
              doing_io->r_c=doing_io->Run;
              doing_io->io_c=doing_io->IO;
            }
            else if (!empty_queue(&doing_io->tempQ)) {
              remove_from_front(&doing_io->tempQ, &dupe);
              doing_io->Rep = dupe.rep;
              doing_io->Run = dupe.run;
              doing_io->r_c= dupe.run;
              doing_io->io_c= dupe.io;
              doing_io->IO = dupe.io;
            }
            else {
              doing_io->fin = 1;
              doing_io->r_c = doing_io->Run;
            }
            printf("QUEUED: Process %d queued at level 1 at time %d\n",doing_io->Pid, clock);
            doing_io->count=0;
            remove_from_front(&io, &temp_ready);
            add_to_queue(&hq, &temp_ready,1);
          }
        }
        if(empty_queue(&io)) {break;}
        remove_from_front(&io, &temp_ready);
        add_to_queue(&io, &temp_ready,1);
        doing_io = pointer_to_current(&io);
      }
    }

    if (!empty_queue(&hq)) {
      last_ran = pointer_to_current(&hq);
      if (last_ran->r_c == last_ran->Run) {
        printf("RUN: Process %d started execution at time %d, wants to execute for %d ticks.\n",last_ran->Pid, clock, last_ran->r_c);
      }
      last_ran->r_c--;
      last_ran->total_cpu++;
      last_ran->count++;
    }else if (!empty_queue(&mq)) {
      last_ran = pointer_to_current(&mq);
      if (last_ran->r_c == last_ran->Run) {
        printf("RUN: Process %d started execution at time %d, wants to execute for %d ticks.\n",last_ran->Pid, clock, last_ran->r_c);
      }
      last_ran->r_c--;
      last_ran->total_cpu++;
      last_ran->count++;
    }else if (!empty_queue(&lq)) {
      last_ran = pointer_to_current(&lq);
      if (last_ran->r_c == last_ran->Run) {
        printf("RUN: Process %d started execution at time %d, wants to execute for %d ticks.\n",last_ran->Pid, clock, last_ran->r_c);
      }
      last_ran->r_c--;
      last_ran->total_cpu++;
      last_ran->count++;
    }
    else {
      null_process++;
    }
    //if all stages and cpu and io are done then add an extra RUN and set fin bit
    //check if last_ran is completely done. if all 0 and fin bit == 0 then add a run cycle and set fin bit to 1 after finished
    if(last_ran!=NULL && last_ran->fin == 1 && last_ran->r_c==0) {
      if(last_ran->q == 10) {
        printf("FINISHED: Process %d finished at time %d\n", last_ran->Pid, clock);
        remove_from_front(&hq, &temp_ready);
        add_to_queue(&newQ, &temp_ready, 1);
        last_ran = NULL;
      }
      else if(last_ran->q == 30) {
        printf("FINISHED: Process %d finished at time %d\n", last_ran->Pid, clock);
        remove_from_front(&mq, &temp_ready);
        add_to_queue(&newQ, &temp_ready, 1);
        last_ran = NULL;
      }
      else if(last_ran->q == 100) {
        printf("FINISHED: Process %d finished at time %d\n", last_ran->Pid, clock);
        remove_from_front(&lq, &temp_ready);
        add_to_queue(&newQ, &temp_ready, 1);
        last_ran = NULL;
      }
    }
    //demotion
    if (last_ran!= NULL && last_ran->count == last_ran->q && last_ran->r_c!=0) {
      last_ran->dem_c ++; //add 1 to its demotion counter
      last_ran->count = 0;
      if(last_ran->dem_c == last_ran->b) { //if demotion counter = demotion limit
        if(last_ran->q == 10) {
          remove_from_front(&hq, &temp_ready);
          temp_ready.dem_c = 0;
          temp_ready.q = 30;
          temp_ready.b = 2;
          temp_ready.g = 2;
          add_to_queue(&mq, &temp_ready, 1);
          printf("QUEUED: Process %d queued at level 2 at time %d\n",temp_ready.Pid, clock);
          last_ran = NULL;
        }
        else if(last_ran->q == 30) {
          remove_from_front(&mq, &temp_ready);
          temp_ready.dem_c = 0;
          temp_ready.q = 100;
          temp_ready.b = -1;
          temp_ready.g = 1;
          add_to_queue(&lq, &temp_ready, 1);
          printf("QUEUED: Process %d queued at level 3 at time %d\n",temp_ready.Pid, clock);
          last_ran=NULL;
        }
      }
    }
      //add to io queue if conditions are met
    else if (last_ran!=NULL && last_ran->r_c ==0 && last_ran->io_c!=0 && last_ran->fin ==0) {
      if(last_ran->q == 10) {
        printf("QUEUED: Process %d queued at IO at time %d\n",last_ran->Pid, clock);
        remove_from_front(&hq, &temp_ready);
        add_to_queue(&io, &temp_ready, 1);
        last_ran = NULL;
      }
      else if(last_ran->q == 30) {
        printf("QUEUED: Process %d queued at IO at time %d\n",last_ran->Pid, clock);
        remove_from_front(&mq, &temp_ready);
        add_to_queue(&io, &temp_ready, 1);
        last_ran = NULL;
      }
      else if(last_ran->q == 100) {
        printf("QUEUED: Process %d queued at IO at time %d\n",last_ran->Pid, clock);
        remove_from_front(&lq, &temp_ready);
        add_to_queue(&io, &temp_ready, 1);
        last_ran = NULL;
      }
    }
      //round robin
    else if(last_ran!=NULL && last_ran->count == last_ran->q) {
      last_ran->count =0;
      if(last_ran->q == 30) {
        printf("QUEUED: Process %d queued at level 2 at time %d\n",last_ran->Pid, clock);
        remove_from_front(&mq, &temp_ready);
        add_to_queue(&mq, &temp_ready, 1);
        last_ran = NULL;
      }
      else if(last_ran->q == 100) {
        printf("QUEUED: Process %d queued at level 3 at time %d\n",last_ran->Pid, clock);
        remove_from_front(&lq, &temp_ready);
        add_to_queue(&lq, &temp_ready, 1);
        last_ran = NULL;
      }
    }
    clock++;
  }
  printf("\nScheduler shutdown at time %d\n",clock);
  printf("\nTotal CPU usage for all processes scheduled:\n\n");
  printf("\nProcess <<null>>:  %6d time units.\n",null_process);
  while(end_of_queue(&newQ)!=1) {
    tempCurr = pointer_to_current(&newQ);
    printf("Process  %d      %6d time units.\n",tempCurr->Pid,tempCurr->total_cpu);
    next_element(&newQ);
  }
  destroy_queue(&proceReady);
  destroy_queue(&hq);
  destroy_queue(&mq);
  destroy_queue(&lq);
  destroy_queue(&io);
  destroy_queue(&newQ);
  return 0;
  }