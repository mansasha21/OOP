#include "LineEditor.hpp"
#include "ParsedInsert.hpp"
#include "ParsedCopy.hpp"
#include "ParsedDelete.hpp"

LineEditor::LineEditor(Parser& parser) :parser_{ parser }, editor_{line_}, log_("log.txt") {}

void LineEditor::copy(int idx1, int idx2)
{
	
	if(areCorrectParamsCopy(idx1,idx2))
	{
		log_ << "Copy was skipped (incorrect index)" << std::endl;
		return;
	}
	editor_.addAndExecuteCommand(factory_.createCommand(commands::copy, line_, clipboard_, idx1, idx2));
}

void LineEditor::erase(int idx1, int idx2)
{
	if (areCorrectParamsErase(idx1,idx2))
	{
		log_ << "Erase was skipped (incorrect index)" << std::endl;
		return;
	}
	editor_.addAndExecuteCommand(factory_.createCommand(commands::del, line_, clipboard_, idx1, idx2));
}

void LineEditor::insert(const std::string& str, size_t idx)
{
	if (areCorrectParamsInsert(idx))
	{
		log_ << "Insert was skipped (incorrect index)" << std::endl;
		return;
	}
	editor_.addAndExecuteCommand(factory_.createCommand(commands::insert, line_, clipboard_, str, idx));
}

void LineEditor::parseAndExecute()
{
	auto cmd = parser_.parseCommand();
	auto type = (*cmd).getType();
	while(type != EoF)
	{
		if (type == WRONG)
		{
			log_ << "Unparsed line" << std::endl;
		}
		else if(type == REDO)
		{
			redo();
		}
		else if (type == UNDO)
		{
			undo();
		}
		else if(type == INSERT)
		{
			const auto insCmd = dynamic_cast<ParsedInsert*>(cmd.release());
			auto [insStr, idx] = insCmd->getFields();
			insert(insStr, idx);
			delete insCmd;
		}
		else if (type == COPY)
		{
			const auto copyCmd = dynamic_cast<ParsedCopy*>(cmd.release());
			auto [idx1, idx2] = copyCmd->getFields();
			copy(idx1, idx2);
			delete copyCmd;
		}
		else if (type == DELETE)
		{
			const auto deleteCmd = dynamic_cast<ParsedDelete*>(cmd.release());
			auto [idx1, idx2] = deleteCmd->getFields();
			erase(idx1, idx2);
			delete deleteCmd;
		}
		else if (type == PASTE)
		{
			paste();
		}
		cmd = parser_.parseCommand();
		type = (*cmd).getType();
	}
}

void LineEditor::paste()
{
	editor_.addAndExecuteCommand(factory_.createCommand(commands::paste, line_, clipboard_));
}

std::string LineEditor::showLine() const
{
	return line_;
}

bool LineEditor::areCorrectParamsErase(int idx1, int idx2) const
{
	return idx1 >= line_.size() || idx1 < 0 || idx2 < 0 || idx2 < idx1 || idx2>line_.size();
}

bool LineEditor::areCorrectParamsCopy(int idx1, int idx2) const
{
	return idx1 < 0 || idx2 < 0 || idx1 >= line_.size() || idx2 < idx1 || idx2 > line_.size();
}

bool LineEditor::areCorrectParamsInsert(int idx) const
{
	return idx > line_.size() || idx < 0;
}

void LineEditor::redo()
{
	editor_.redo();
}

void LineEditor::undo()
{
	editor_.undo();
}
