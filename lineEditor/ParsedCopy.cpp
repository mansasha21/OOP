#include "ParsedCopy.hpp"
ParsedCopy::ParsedCopy(int idx1, int idx2):ParsedCommand(COPY), idx1(idx1), idx2(idx2){}

std::pair<int, int> ParsedCopy::getFields() const
{
	return { idx1, idx2 };
}
