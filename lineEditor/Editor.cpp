#include "Editor.h"

Editor::Editor(std::string& line):line(line){}

void Editor::addAndExecuteCommand(std::unique_ptr<Command> cmd)
{
	(*cmd).redo();
	commands_.push_back(std::move(cmd));
}
void Editor::undo()
{
	if (commands_.empty())
		return;
	canceledCommands.push_back(std::move(commands_.back()));
	commands_.pop_back();
	(*canceledCommands.back()).undo();
}

void Editor::redo()
{
	if (canceledCommands.empty())
		return;
	(*canceledCommands.back()).redo();
	commands_.push_back(std::move(canceledCommands.back()));
	canceledCommands.pop_back();
}

std::string Editor::showLine() const
{
	return line;
}

