#include "ParsedDelete.hpp"

ParsedDelete::ParsedDelete(int idx1, int idx2):ParsedCommand(DELETE), idx1(idx1), idx2(idx2){}

std::pair<int, int> ParsedDelete::getFields() const
{
	return { idx1, idx2 };
}


