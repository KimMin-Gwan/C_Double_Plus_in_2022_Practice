#include "Event.h"

ostream& operator << (ostream& ostr, const Event& e)
{
	ostr << "Event(pri : " << setw(3) << e.event_pri << ", gen:" << setw(3) << e.event_gen_addr;
	ostr << ", no : " << setw(3) << e.event_no << ")";
	return ostr;
}

Event::Event()
	:event_no(0), event_gen_addr(0), event_handler_addr(-1), event_pri(0), eventStatus(UNDEFINED), event_title("Default")
{
	cout << "default event was constructed" << endl;
}

Event::Event(int event_id, int event_pri, string title, int gen_addr)
	:event_no(event_id), event_gen_addr(gen_addr), event_pri(event_pri), event_title(title)
{
	setEventStatus(GENERATED); //status
	setEventHandlerAddr(-1); //no use
	cout << this->event_title << " was constructed" << endl;
}

void Event::printEvent(ostream& ostr)
{
	ostr << "Event(pri : " << setw(3) << this->event_pri << ", gen:" << setw(3) << this->event_gen_addr;
	ostr << ", no : " << setw(3) << this->event_no << ")";
}

Event* genRandEvent(int event_no)
{
	Event* pEv;
	int eventPri;
	int eventGenID;
	string eventTitle;

	eventPri = rand() % MAX_EVENT_PRIORITY; //rand priority
	eventGenID = rand() % NUM_EVENT_GENERATORS; //rand gen Address
	eventTitle = gensRandString(); //rand title
	pEv = (Event*)new Event(event_no, eventPri, eventTitle, eventGenID); //allocate Event
	return pEv;
}

string gensRandString()
{
	string temp; //temp
	char charArray[2] = {}; //temp character array
	int length;
	length = rand() % 4 + 4; // 4 ~ 7 
	for (int i = 0; i < length; i++)
	{
		charArray[0] = rand() % 26 + 'a';
		charArray[1] = '\0';
		temp.append(charArray); //append char array to string
	}
	return temp; 
}
