#pragma once

class TicketMachine final
{
	int current;
public:
	explicit TicketMachine(int current = 0);
	int getNext();
};
