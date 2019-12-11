#pragma once
#include "Parser.hpp"
#include "CommandFactoryr.hpp"
#include "Editor.h"
#include <fstream>

class LineEditor final
{
	Parser& parser_;
	std::string line_, clipboard_;
	CommandFactory factory_;
	Editor editor_;
	std::ofstream log_;

	bool areCorrectParamsErase(int idx1, int idx2) const;
	bool areCorrectParamsInsert(int idx) const;
	bool areCorrectParamsCopy(int idx1, int idx2) const;
public:
	LineEditor(Parser& parser);

	void parseAndExecute();

	void insert(const std::string& str, size_t idx);
	void copy(int idx1, int idx2);
	void erase(int idx1, int idx2);
	void paste();

	void redo();
	void undo();

	std::string showLine() const;
};

