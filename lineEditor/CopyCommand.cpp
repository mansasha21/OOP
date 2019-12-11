#include "CopyCommand.h"
#include <algorithm>

CopyCommand::CopyCommand(std::string& line, std::string& clipboard,
															int idx1, int idx2) : Command(line, clipboard),
																						idx1_(idx1),
																						idx2_(idx2),
																						prevBuf_(clipboard){}

void CopyCommand::redo()
{
	clipboard = line_.substr(idx1_, idx2_ - idx1_);
}

void CopyCommand::undo()
{
	std::swap(prevBuf_, clipboard);
}

