#pragma once
#include <string>

const std::string EoF("EOF");
const std::string REDO("redo");
const std::string UNDO("undo");
const std::string DELETE("delete");
const std::string PASTE("paste");
const std::string COPY("copy");
const std::string WRONG("wrong");
const std::string INSERT("insert");

class ParsedCommand
{
	std::string type;
protected:
	ParsedCommand(const std::string& type);
public:
	virtual ~ParsedCommand() = default;
	ParsedCommand(const ParsedCommand& cmd) = default;
	ParsedCommand(ParsedCommand&& cmd) = default;
	ParsedCommand& operator=(const ParsedCommand& cmd) = default;
	ParsedCommand& operator=(ParsedCommand&& cmd) = default;
	static ParsedCommand getWrong();
	static ParsedCommand getEOF();
	static ParsedCommand getRedo();
	static ParsedCommand getUndo();
	std::string getType() const;
};

