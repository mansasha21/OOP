#pragma once
#include "Command.h"

class CopyCommand final: public Command
{
	int idx1_, idx2_;
	std::string prevBuf_;
public:
	CopyCommand(std::string& line_, std::string& clipboard, int idx1, int idx2);
	void undo() override;
	void redo() override;
};
