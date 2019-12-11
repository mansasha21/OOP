#include "DeleteCommand.h"

DeleteCommand::DeleteCommand(std::string& line_, std::string& clipboard,
																	  int idx1, int idx2) : Command(line_, clipboard),
																							idx1_(idx1),
																							idx2_(idx2),
																							deletedPart({}){}

void DeleteCommand::redo()
{
	deletedPart = line_.substr(idx1_, idx2_ - idx1_);
	line_ = line_.substr(0, idx1_) + line_.substr(idx2_);
}

void DeleteCommand::undo()
{
	line_.insert(idx1_, deletedPart);
	deletedPart = "";
}



