#pragma once
#include "ParsedCommand.hpp"
#include "utility"


class ParsedCopy final : public ParsedCommand
{
	int idx1;
	int idx2;
public:
	ParsedCopy(int idx1, int idx2);
	~ParsedCopy() override = default;
	ParsedCopy(const ParsedCopy& cmd) = default;
	ParsedCopy(ParsedCopy&& cmd) = default;
	ParsedCopy& operator=(const ParsedCopy& cmd) = default;
	ParsedCopy& operator=(ParsedCopy&& cmd) = default;
	
	std::pair<int, int> getFields() const;
};

