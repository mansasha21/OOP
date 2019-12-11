#pragma once
#include "ParsedCommand.hpp"

class ParsedPaste final : public ParsedCommand
{
public:
	ParsedPaste();
	~ParsedPaste() override = default;
	ParsedPaste(const ParsedPaste& cmd) = default;
	ParsedPaste(ParsedPaste&& cmd) = default;
	ParsedPaste& operator=(const ParsedPaste& cmd) = default;
	ParsedPaste& operator=(ParsedPaste&& cmd) = default;
};

