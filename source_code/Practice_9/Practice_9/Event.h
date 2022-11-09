#ifndef EVENT_H
#define EVENT_H
#include <iostream>
#include <fstream>
#include <thread>
#include <process.h>
#include <Windows.h>
#include <string>
#include <iomanip> for setw
using namespace std;

#define MAX_EVENT_PRIORITY 100
#define NUM_EVENT_GENERATORS 1
enum EventStatus {GENERATED, ENQUEUED, PROCESSED, UNDEFINED};

class Event
{
	friend ostream& operator << (ostream& ostr, const Event& e);
public:
	Event(); //default constructor
	Event(int event_id, int event_pri, string title, int gen_addr); //constructor
	//Inline_function------------------------------------------------------
	void setEventHandlerAddr(int evtHndlerAddr) { event_handler_addr = evtHndlerAddr; } //set handler Address
	void setEventGenAddr(int genAddr) { event_gen_addr = genAddr; } //set generate Address
	void setEventNo(int evtNo) { event_no = evtNo; } //set event number
	void setEventPri(int pri) { event_pri = pri; } //set event priarity
	void setEventStatus(EventStatus evtStatus) { eventStatus = evtStatus; } //set event status
	void setEventGenTime(LARGE_INTEGER t_gen) { t_event_gen = t_gen; } //check the genarating time
	void setEventProcTime(LARGE_INTEGER t_proc) { t_event_proc = t_proc; } //check the processing time
	void setEventElapsedTime(double t_elapsed_ms) { t_elapsed_time_ms = t_elapsed_ms; } //check elapsed time from process started
	LARGE_INTEGER getEventGenTime() { return t_event_gen; } //get genarating time
	LARGE_INTEGER getEventProcTime() { return t_event_proc; } //get processeing time
	double getEventElapsedTime() { return t_elapsed_time_ms; } //get elapsed time
	int getEventPri() { return event_pri; } //get priarity
	int getEventNo() { return event_no; } //get event number
	bool operator >(Event& e) { return (event_pri > e.event_pri); } //compare operater overloading 
	bool operator <(Event& e) { return (event_pri > e.event_pri); } //compare operater overloading
	//print function--------------------------------------------------------
	void printEvent(ostream& ostr); //print Event as ostream
	void printEvent(); //print Event as ostream
private:
	int event_no;
	int event_gen_addr;
	int event_handler_addr;
	int event_pri;
	string event_title;
	EventStatus eventStatus;
	//for check the time---------------------------------------------------
	LARGE_INTEGER t_event_gen;
	LARGE_INTEGER t_event_proc;
	double t_elapsed_time_ms;
};
Event* genRandEvent(int event_no); //make random event
string gensRandString(); //to make rand title
#endif