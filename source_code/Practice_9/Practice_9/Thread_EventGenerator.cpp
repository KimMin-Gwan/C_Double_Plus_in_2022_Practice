#include <Windows.h>
#include "Multi_Thread.h" 
#include "HeapPrioQ.h" 
#include "Event.h" 
#include "SimParam.h" 
using namespace std;
using std::this_thread::sleep_for;

void EventGen(ThreadParam_Event* pParam)
{
	//get paramater-----------------------------------------------
	HeapPrioQueue<int, Event>* pPriQ_Event = pParam->pPriQ_Event; //event pointer
	int myRole = pParam->role;
	int myAddr = pParam->myAddr;
	int maxRound = pParam->maxRound;
	int targetEventGen = pParam->targetEventGen;
	LARGE_INTEGER QP_freq = pParam->QP_freq; //time freq
	ThreadStatusMonitor* pThrdMon = pParam->pThrdMon; //monitering
	//------------------------------------------------------------
	T_Entry<int, Event>* pEntry, entry_event;
	Event event, * pEvent;
	int event_no = 0;
	int event_priority = 0;
	int event_gen_count = 0;
	int event_handler_addr;
	LARGE_INTEGER t_gen;
	//int temp = -1; //for debugging
	for (int round = 0; round < maxRound; round++)
	{
		if (event_gen_count >= targetEventGen) //if reach the target
		{
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE) //status became TERMINATE
				break; //and break the loop
			else  //or wait 500miliseconds and continue
			{
				sleep_for(std::chrono::milliseconds(500));
				continue;
			}
		}
		// temp = pPriQ_Event->size(); //for debugging
		event_no = event_gen_count + NUM_EVENTS_PER_GEN * myAddr;  //generate event number
		event_priority = targetEventGen - event_gen_count - 1; //reverse order of event_no
		event.setEventNo(event_no);
		event.setEventPri(event_priority);
		event.setEventGenAddr(myAddr); //no use in this solution
		event.setEventHandlerAddr(-1); //no use in this solution

		QueryPerformanceCounter(&t_gen); //time freq
		event.setEventGenTime(t_gen); //check teh generated point

		event.setEventStatus(GENERATED); //status became GENERATED
		entry_event.setKey(event.getEventPri());
		entry_event.setValue(event);

		//temp = pPriQ_Event->size(); //for debbuging
		while (pPriQ_Event->insert(entry_event) == NULL) //inserting in the Queue
		{	//if Queue is max size
			pParam->pCS_main->lock();
			cout << "PriQ_Event is Full, waiting ..." << endl;
			pParam->pCS_main->unlock();
			Sleep(100); //wait little
			//sleep_for(std::chrono::milliseconds(100));
		}
		//temp = pPriQ_Event->size();  //for debbuging
		pParam->pCS_main->lock(); 
		cout << "Successfully inserted into PriQ_Event " << endl;
		pParam->pCS_main->unlock();

		//temp = pPriQ_Event->size(); //for debbuging
		pParam->pCS_thrd_mon->lock();
		pThrdMon->eventGenerated[pThrdMon->totalEventGenerated] = event; //save the generated event in this round
		//temp = pPriQ_Event->size(); //for debbuging
		pThrdMon->numEventGenerated++;
		pThrdMon->totalEventGenerated++;
		pParam->pCS_thrd_mon->unlock();
		event_gen_count++;
		//temp = pPriQ_Event->size(); //for debbuging
		sleep_for(std::chrono::milliseconds(10));
	}
}