#pragma once
#include "ParsedCommand.hpp"
#include <utility>
class ParsedInsert final : public ParsedCommand
{
	int idx;
	std::string insStr;
public:
	ParsedInsert(int idx, const std::string& insStr);
	~ParsedInsert() override = default;
	ParsedInsert(const ParsedInsert& cmd) = default;
	ParsedInsert(ParsedInsert&& cmd) = default;
	ParsedInsert& operator=(const ParsedInsert& cmd) = default;
	ParsedInsert& operator=(ParsedInsert&& cmd) = default;
	std::pair<std::string, int> getFields() const;
	
};

