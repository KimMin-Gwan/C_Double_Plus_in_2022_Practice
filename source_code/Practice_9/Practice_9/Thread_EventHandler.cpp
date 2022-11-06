#include <Windows.h>
#include "Multi_Thread.h" 
#include "HeapPrioQ.h" 
#include "Event.h" 
using namespace std;

using std::this_thread::sleep_for;
void EventProc(ThreadParam_Event* pParam)
{
	//get paramater-----------------------------------------------
	HeapPrioQueue<int, Event>* pPriQ_Event = pParam->pPriQ_Event; //event pointer
	int myRole = pParam->role;
	int myAddr = pParam->myAddr;
	int maxRound = pParam->maxRound;
	int targetEventGen = pParam->targetEventGen;
	LARGE_INTEGER QP_freq = pParam->QP_freq; //time freq 
	ThreadStatusMonitor* pThrdMon = pParam->pThrdMon; //moniter
	//-------------------------------------------------------------
	T_Entry<int, Event>* pEntry;
	Event event;

	LARGE_INTEGER t_gen, t_proc;
	LONGLONG t_diff;
	double elapsed_time;

	//Event* pEvent, * pEventProc;
	//int event_no = 0;
	//int eventPriority = 0;
	//int event_gen_count = 0;
	//int num_Ev_processed = 0;
	//int temp = 0; //to the size
	//Sleep(100);
	for (int round = 0; round < maxRound; round++)
	{
		//temp = pPriQ_Event->size(); //for debbuging
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
			break;
		if (pPriQ_Event->size() != 0)
		{
			//temp = pPriQ_Event->size(); //for debbuging
			pEntry = pPriQ_Event->removeHeapMin(); //remove highest element
			event = pEntry->getValue();
			pParam->pCS_thrd_mon->lock(); //thread lock
			event.setEventHandlerAddr(myAddr); //get handler address
			//time check part--------------------------------------------
			QueryPerformanceCounter(&t_proc); //check the time
			event.setEventProcTime(t_proc); //get the processing time
			t_gen = event.getEventGenTime(); //get the generated time
			//temp = pPriQ_Event->size(); //for debbuging
			t_diff = t_proc.QuadPart - t_gen.QuadPart; //calculationg operating time
			elapsed_time = ((double)t_diff / QP_freq.QuadPart); //in second
			event.setEventElapsedTime(elapsed_time * 1000); //in milli-second
			//------------------------------------------------------------
			pThrdMon->eventProcessed[pThrdMon->totalEventProcessed] = event; //save the processed event in this round
			pThrdMon->numEventProcessed++; 
			pThrdMon->totalEventProcessed++;
			pParam->pCS_thrd_mon->unlock(); //thread unlock
			//temp = pPriQ_Event->size(); //for debbuging
		} 
		sleep_for(std::chrono::milliseconds(100 + rand() % 100));
	}
}