#include "TicketMachine.h"

TicketMachine::TicketMachine(int current):current(current){}

int TicketMachine::getNext()
{
	return ++current;
}
