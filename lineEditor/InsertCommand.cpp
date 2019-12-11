#include "InsertCommand.h"

InsertCommand::InsertCommand(std::string& line_, std::string& clipboard, const std::string& str, size_t idx)
							:Command(line_,clipboard),
							 str(str),
						     idx(idx){}

void InsertCommand::redo()
{
	line_.insert(idx, str);
}
void InsertCommand::undo()
{
	line_.erase(idx, str.length());
}
