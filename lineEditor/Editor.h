#pragma once
#include "Command.h"
#include <memory>
#include <vector>

class Editor final
{
	std::vector<std::unique_ptr<Command>> commands_;
	std::vector <std::unique_ptr<Command>> canceledCommands;
	std::string& line;
public:
	Editor(std::string& line);
	void addAndExecuteCommand(std::unique_ptr<Command> cmd);
	void undo();
	void redo();
	std::string showLine() const;
};
