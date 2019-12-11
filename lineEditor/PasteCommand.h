#pragma once
#include "Command.h"

class PasteCommand final: public Command
{
public:
	PasteCommand(std::string& line_, std::string& clipboard);
	void undo() override;
	void redo() override;
	~PasteCommand() override = default;
};
