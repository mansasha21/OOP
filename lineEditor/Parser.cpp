#include "Parser.hpp"
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include "ParsedDelete.hpp"
#include "ParsedCopy.hpp"
#include "ParsedInsert.hpp"
#include "ParsedPaste.hpp"

Parser::Parser(std::istream& is):is_(is){}

std::unique_ptr<ParsedCommand> Parser::parseCommand() const 
{
	std::string str;
	if(!std::getline(is_, str))
	{
		return std::make_unique<ParsedCommand>(ParsedCommand::getEOF());
	}
	std::stringstream ss(str);
	std::string type;
	if(!(ss>>type))
	{
		return std::make_unique<ParsedCommand>(ParsedCommand::getWrong());
	}
	std::transform(type.begin(), type.end(),type.begin(), [](unsigned char c) {return std::tolower(c); });
	if(type == INSERT)
	{
		std::string insStr;
		int idx;
		if(!(ss >>insStr>>idx))
		{
			return std::make_unique<ParsedCommand>(ParsedCommand::getWrong());
		}
		return std::make_unique<ParsedInsert>(ParsedInsert(idx,insStr));
	}
	if(type == COPY || type == DELETE)
	{
		int idx1, idx2;
		if (!(ss >> idx1 >> idx2))
		{
			return std::make_unique<ParsedCommand>(ParsedCommand::getWrong());
		}
		if(type == COPY)
			return std::make_unique<ParsedCopy>(ParsedCopy(idx1,idx2));
		return std::make_unique<ParsedDelete>(ParsedDelete(idx1, idx2));
	}
	if(type == PASTE)
	{
		return std::make_unique<ParsedPaste>(ParsedPaste());;
	}
	if(type == REDO)
	{
		return  std::make_unique<ParsedCommand>(ParsedCommand::getRedo());
	}
	if (type == UNDO)
	{
		return  std::make_unique<ParsedCommand>(ParsedCommand::getUndo());
	}
	return std::make_unique<ParsedCommand>(ParsedCommand::getWrong());
}


