#pragma once
#include <string>
#include <memory>


class Command
{
protected:
	std::string& line_;
	std::string& clipboard;
public:
	Command(std::string& line_,  std::string& clipboard);
	virtual void undo() = 0;
	virtual void redo() = 0;
	virtual ~Command() = default;
};
