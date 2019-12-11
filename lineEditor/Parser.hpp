#pragma once
#include <istream>
#include "ParsedCommand.hpp"
#include <memory>

class Parser final
{
	std::istream& is_;
public:
	Parser(std::istream& is);
	std::unique_ptr<ParsedCommand>parseCommand() const;
	~Parser() = default;
};