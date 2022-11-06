#ifndef MULTI_THREAD_H
#define MULTI_THREAD_H
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <process.h>
#include <string>
#include "HeapPrioQ.h"
#include "Event.h"
#include "SimParam.h"
using namespace std;
enum ROLE { EVENT_GENERATOR, EVENT_HANDLER };
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };

typedef struct ThreadStatusMonitor
{
 int numEventGenerated;
 int numEventProcessed;
 int totalEventGenerated;
 int totalEventProcessed;
 Event eventGenerated[TOTAL_NUM_EVENTS];  //saved generated  event
 Event eventProcessed[TOTAL_NUM_EVENTS]; //saved processed event
 THREAD_FLAG *pFlagThreadTerminate; //terminate flag
}ThreadStatusMonitor;

typedef struct ThreadParam
{
 mutex *pCS_main; //main mutex
 mutex *pCS_thrd_mon; //thread mutex
 HeapPrioQueue<int, Event> *pPriQ_Event; //event pointer
 FILE *fout; //file pointer
 ROLE role; //check role
 int myAddr; 
 int maxRound; 
 int targetEventGen;
 LARGE_INTEGER QP_freq; //freq for time check
 ThreadStatusMonitor *pThrdMon; //thrd moniter pointer
}ThreadParam_Event;

void EventProc(ThreadParam_Event* pParam); //event handler
void EventGen(ThreadParam_Event* pParam); //event generator

#endif