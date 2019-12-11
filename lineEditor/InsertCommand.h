#pragma once
#include "Command.h"


class InsertCommand final : public Command
{
	std::string str;
	size_t idx;
public:
	InsertCommand(std::string& line_, std::string& clipboard, const std::string& str, size_t idx);
	void undo() override;
	void redo() override;
	~InsertCommand() override = default;
};

