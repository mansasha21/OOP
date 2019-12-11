#pragma once
#include "Command.h"
class DeleteCommand final : public Command
{
	int idx1_, idx2_;
	std::string deletedPart;
public:
	DeleteCommand(std::string& line_, std::string& clipboard, int idx1, int idx2);
	void undo() override;
	void redo() override;
};
