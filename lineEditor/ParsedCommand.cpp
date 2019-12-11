#include "ParsedCommand.hpp"

ParsedCommand::ParsedCommand(const std::string& type):type(type){}


std::string ParsedCommand::getType() const
{
	return type;
}
ParsedCommand ParsedCommand::getEOF()
{
	return  EoF ;
}
ParsedCommand ParsedCommand::getWrong()
{
	return WRONG;
}
ParsedCommand ParsedCommand::getRedo()
{
	return REDO;
}
ParsedCommand ParsedCommand::getUndo()
{
	return UNDO;
}




