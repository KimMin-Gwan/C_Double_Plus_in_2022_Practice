//#include <stdio.h>
//#include <stdlib.h>
#include <Windows.h>
#include <thread>
#include <mutex>
#include "Multi_Thread.h" 
#include "HeapPrioQ.h" 
#include "Event.h" 
#include "ConsoleDisplay.h" 
#include "SimParam.h" 
#include <time.h>
#include <conio.h>
using namespace std;

void main()
{
	ofstream fout;
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "ERROR: Fail to open output.txt file" << endl;
		exit;
	}
	HeapPrioQueue<int, Event> heapPriQ_Event(50, string("HeapPriorityQueue_Event"));
	double elapsed_time, min_elapsed_time, max_elapsed_time;
	double avg_elapsed_time, total_elapsed_time;
	Event* pEvent, *pEvProc, *pEv_min_elasped_time = NULL, * pEv_max_elapsed_time = NULL;
	HANDLE consHndlr;
	LARGE_INTEGER freq;
	ThreadStatusMonitor thrdMon;
	THREAD_FLAG eventThreadFlag = RUN;
	int numEventGenerated, numEventProcessed, count, event_in_priQ = 0;
	mutex cs_main;
	mutex cs_thrd_mon;
	ThreadParam_Event thrdParam_EventGen, thrdParam_EventHndlr;
	Event eventProcessed[TOTAL_NUM_EVENTS];
	srand(time(NULL));
	//initialize =====================================================================
	consHndlr = initConsoleHandler(); //init console handler
	thrdMon.pFlagThreadTerminate = &eventThreadFlag;
	thrdMon.totalEventGenerated = 0;
	thrdMon.totalEventProcessed = 0;


	for (int i = 0; i < TOTAL_NUM_EVENTS; i++)
	{
		thrdMon.eventProcessed[i].setEventNo(-1);
		thrdMon.eventProcessed[i].setEventPri(-1);
	}
	QueryPerformanceFrequency(&freq);
	//event handler ===================================================================
	thrdMon.numEventProcessed = 0; //init number of event processed
	thrdParam_EventHndlr.role = EVENT_HANDLER; //thread as event handler
	thrdParam_EventHndlr.myAddr = 1; //initalize the address
	thrdParam_EventHndlr.pCS_main = &cs_main; //main mutex
	thrdParam_EventHndlr.pCS_thrd_mon = &cs_thrd_mon;  //thread mutex
	thrdParam_EventHndlr.pPriQ_Event = &heapPriQ_Event; //generated event address
	thrdParam_EventHndlr.maxRound = MAX_ROUND;
	thrdParam_EventHndlr.targetEventGen = NUM_EVENTS_PER_GEN;
	thrdParam_EventHndlr.pThrdMon = &thrdMon;
	thrdParam_EventHndlr.QP_freq = freq;
	thread thrd_EvProc(EventProc, &thrdParam_EventHndlr);

	cs_main.lock(); //lock for console output in main function
	cout << "Thread_EventProc is created and activated ..." << endl;
	cs_main.unlock();

	//event generator ==================================================================
	thrdMon.numEventGenerated = 0; //init number of event processed
	thrdParam_EventGen.role = EVENT_GENERATOR; //thread as event handler
	thrdParam_EventGen.myAddr = 0; //initalize the address
	thrdParam_EventGen.pCS_main = &cs_main; //main mutex
	thrdParam_EventGen.pCS_thrd_mon = &cs_thrd_mon;  //thread mutex
	thrdParam_EventGen.pPriQ_Event = &heapPriQ_Event; //generated event address
	thrdParam_EventGen.targetEventGen = NUM_EVENTS_PER_GEN;
	thrdParam_EventGen.maxRound = MAX_ROUND;
	thrdParam_EventGen.pThrdMon = &thrdMon;
	thrdParam_EventHndlr.QP_freq = freq;
	thread thrd_EvGen(EventGen, &thrdParam_EventGen);

	cs_main.lock();
	cout << "Thread_EventGen is created and activated .., " << endl;
	cs_main.unlock();
	//int temp = -1; //for dubbuging
	/* periodic monitoring in main() */
	for (int round = 0; round < MAX_ROUND; round++)
	{
		cs_main.lock();
		cls(consHndlr);
		gotoxy(consHndlr, 0, 0);
		cout << "Thread monitoring by main() ::" << endl;
		cout << " round : " << round << "current total_event_gen : " << thrdMon.totalEventGenerated
			<< "total_event_proc : " << thrdMon.totalEventProcessed << endl;

		cout << endl <<  "*****************************" << endl;
		numEventGenerated = thrdMon.numEventGenerated;
		cout << "Events generated (current total = " << numEventGenerated << endl;
		heapPriQ_Event.fprint(fout);
		for (int i = 0; i < numEventGenerated; i++)
		{
			pEvent = &thrdMon.eventGenerated[i];
			if (pEvent != NULL)
			{
				pEvent->printEvent();
				if (((i + 1) % EVENT_PER_LINE) == 0)
					cout << endl;
			}
		}

		cout << endl << "*****************************" << endl;
		event_in_priQ = heapPriQ_Event.size();
		cout << "currently in Priority_Queue : " << event_in_priQ << endl;
		heapPriQ_Event.printQue();
		heapPriQ_Event.fprint(fout);

		//temp = heapPriQ_Event.size(); //for debbugging

		cout << endl << endl << "*****************************" << endl;
		numEventProcessed = thrdMon.totalEventProcessed;
		cout << "Events processed current total = :  " << numEventProcessed << endl;

		count = 0;
		total_elapsed_time = 0.0;
		for (int ev = 0; ev < numEventProcessed; ev++)
		{
			pEvent = &thrdMon.eventProcessed[ev];
			if (pEvent != NULL)
			{ pEvent->printEvent();
				if (((ev + 1) % EVENT_PER_LINE) == 0)
					printf("\n ");
			}
			if (ev == 0)
			{
				min_elapsed_time = max_elapsed_time = total_elapsed_time
					= pEvent->getEventElapsedTime(); // in milli-second
				pEv_min_elasped_time = pEv_max_elapsed_time = pEvent;
			}
			else
			{
				if (min_elapsed_time > pEvent->getEventElapsedTime())
				{
					min_elapsed_time = pEvent->getEventElapsedTime(); // in milli-second
					pEv_min_elasped_time = pEvent;
				}
				if (max_elapsed_time < pEvent->getEventElapsedTime())
				{
					max_elapsed_time = pEvent->getEventElapsedTime(); // in milli-second
					pEv_max_elapsed_time = pEvent;
				}
				total_elapsed_time += pEvent->getEventElapsedTime();
			}
		} //end for showing eventProcessed
		cout << endl;
		if (numEventProcessed > 0)
		{
			avg_elapsed_time = total_elapsed_time / numEventProcessed;
			cout << "numEventProcessed = " << numEventProcessed << endl;
			cout << "min_elapsed_time = " <<  min_elapsed_time << endl;
			cout << *pEv_min_elasped_time << endl;
			cout << "max_elapsed_time = " << max_elapsed_time << endl;
			cout << *pEv_max_elapsed_time << endl;
			cout << "avg_elapsed_time = " << avg_elapsed_time << endl;
		}

		if (numEventProcessed >= TOTAL_NUM_EVENTS)
		{
			eventThreadFlag = TERMINATE; //terminate threads
			cs_main.unlock();
			break;
		}
		cs_main.unlock();
		Sleep(100);
	}
	thrd_EvProc.join();
	thrd_EvGen.join();

	fout.close(); //close

	cout << "Hit any key to terminate : " << endl;
	_getch();
}