#include "ParsedInsert.hpp"

ParsedInsert::ParsedInsert(int idx, const std::string& insStr):ParsedCommand(INSERT),idx(idx), insStr(insStr){}

std::pair<std::string, int> ParsedInsert::getFields() const
{
	return { insStr, idx };
}
