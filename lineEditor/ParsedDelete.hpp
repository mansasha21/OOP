#pragma once
#include "ParsedCommand.hpp"
#include <utility>

class ParsedDelete final: public ParsedCommand
{
	int idx1;
	int idx2;
public:
	ParsedDelete(int idx1, int idx2);
	~ParsedDelete() override = default;
	ParsedDelete(const ParsedDelete& cmd) = default;
	ParsedDelete(ParsedDelete&& cmd) = default;
	ParsedDelete& operator=(const ParsedDelete& cmd) = default;
	ParsedDelete& operator=(ParsedDelete&& cmd) = default;

	std::pair<int, int> getFields() const;
};

