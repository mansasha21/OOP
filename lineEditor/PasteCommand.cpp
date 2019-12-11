#include "PasteCommand.h"

PasteCommand::PasteCommand(std::string& line_, std::string& clipboard):Command(line_,clipboard){}

void PasteCommand::redo()
{
	line_.append(clipboard);
}

void PasteCommand::undo()
{
	line_.erase(line_.length() - clipboard.length(), clipboard.length());
}

