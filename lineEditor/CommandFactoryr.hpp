#pragma once
#include "Command.h"
#include <memory>
#include "CopyCommand.h"
#include "DeleteCommand.h"
#include "InsertCommand.h"
#include "PasteCommand.h"
#include "stdexcept"

enum class commands
{
	copy, del, insert, paste
};

class CommandFactory final
{
public:
	template <typename ... Args>
	std::unique_ptr<Command> createCommand(commands cmd, Args&&... args)
	{
		switch (cmd)
		{
		case commands::copy:
			return construct<CopyCommand>(std::forward<Args>(args)...);
		case commands::del:
			return  construct<DeleteCommand>(std::forward<Args>(args)...);
		case commands::insert:
			return  construct<InsertCommand>(std::forward<Args>(args)...);
		case commands::paste:
			return  construct<PasteCommand>(std::forward<Args>(args)...);
		default:
			throw std::invalid_argument("Command is not supported");
		}
	}
private:
	template <typename Concrete, typename... Args>
	std::enable_if_t<std::is_constructible_v<Concrete, Args...>,std::unique_ptr<Concrete>>
	construct(Args&&... params)
	{
		return std::make_unique<Concrete>(std::forward<Args>(params)...);
	}
	
	template <typename Concrete, typename... Ts>
	std::unique_ptr<Concrete> construct(...)
	{
		return nullptr;
	}
};