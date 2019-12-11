#include "gtest/gtest.h"
#include "gtest/gtest-memleak.h"
#include "Parser.hpp"
#include "CopyCommand.h"
#include "DeleteCommand.h"
#include "Editor.h"
#include "InsertCommand.h"
#include "PasteCommand.h"
#include "CommandFactoryr.hpp"
#include "LineEditor.hpp"

TEST(InsertCmd, insertBeginOne) {
	std::string buf, clipboard;
	Editor ed(buf);
	
	ed.addAndExecuteCommand(std::make_unique<InsertCommand>(InsertCommand(buf, clipboard, "Hello world!!!", 0)));
	EXPECT_EQ(ed.showLine(), "Hello world!!!");
}

TEST(DeleteCmd, insertDeleteOne) {
	std::string buf, clipboard;
	Editor ed(buf);
	ed.addAndExecuteCommand(std::make_unique<InsertCommand>(InsertCommand(buf, clipboard, "Hello world!!!", 0)));
	ed.addAndExecuteCommand(std::make_unique<DeleteCommand>(DeleteCommand(buf, clipboard, 0, buf.size())));
	EXPECT_EQ(ed.showLine(), "");
}

TEST(CopyPasteCmd, insertCopyDeletePasteOne) {
	std::string buf, clipboard;
	Editor ed(buf);
	ed.addAndExecuteCommand(std::make_unique<InsertCommand>(InsertCommand(buf, clipboard, "Hello world!!!", 0)));
	ed.addAndExecuteCommand(std::make_unique<CopyCommand>(CopyCommand(buf, clipboard,0,5)));
	ed.addAndExecuteCommand(std::make_unique<DeleteCommand>(DeleteCommand(buf, clipboard, 0, buf.size())));
	ed.addAndExecuteCommand(std::make_unique<PasteCommand>(PasteCommand(buf, clipboard)));
	EXPECT_EQ(ed.showLine(), "Hello");
}

TEST(InsertCmd, insertUndoOne) {
	std::string buf, clipboard;
	Editor ed(buf);
	ed.addAndExecuteCommand(std::make_unique<InsertCommand>(InsertCommand(buf, clipboard, "Hello world!!!", 0)));
	ed.undo();
	EXPECT_EQ(ed.showLine(), "");
}

TEST(InsertCmd, insertUndoRedoOne) {
	std::string buf, clipboard;
	Editor ed(buf);
	ed.addAndExecuteCommand(std::make_unique<InsertCommand>(InsertCommand(buf, clipboard, "Hello world!!!", 0)));
	ed.undo();
	ed.redo();
	EXPECT_EQ(ed.showLine(), "Hello world!!!");
}

TEST(InsertCmd, insertUndoRedoRedoOne) {
	std::string buf, clipboard;
	Editor ed(buf);
	ed.addAndExecuteCommand(std::make_unique<InsertCommand>(InsertCommand(buf, clipboard, "Hello world!!!", 0)));
	ed.undo();
	ed.redo();
	ed.redo();
	EXPECT_EQ(ed.showLine(), "Hello world!!!");
}

TEST(InsertCmd, insertUndoRedoUndoRedoOne) {
	std::string buf, clipboard;
	Editor ed(buf);
	ed.addAndExecuteCommand(std::make_unique<InsertCommand>(InsertCommand(buf, clipboard, "Hello world!!!", 0)));
	ed.undo();
	ed.redo();
	ed.undo();
	ed.redo();
	EXPECT_EQ(ed.showLine(), "Hello world!!!");
}

TEST(InsertCmd, insertUndoRedoUndoOne) {
	std::string buf, clipboard;
	Editor ed(buf);
	ed.addAndExecuteCommand(std::make_unique<InsertCommand>(InsertCommand(buf, clipboard, "Hello world!!!", 0)));
	ed.undo();
	ed.redo();
	ed.undo();
	EXPECT_EQ(ed.showLine(), "");
}

TEST(InsertCmd, insertMiddleOne) {
	std::string buf, clipboard;
	Editor ed(buf);
	ed.addAndExecuteCommand(std::make_unique<InsertCommand>(InsertCommand(buf, clipboard, "Hello world!!!", 0)));
	ed.addAndExecuteCommand(std::make_unique<InsertCommand>(InsertCommand(buf, clipboard, "dark ", 6)));
	EXPECT_EQ(ed.showLine(), "Hello dark world!!!");
}

TEST(InsertCmd, insertEndOne) {
	std::string buf, clipboard;
	Editor ed(buf);
	ed.addAndExecuteCommand(std::make_unique<InsertCommand>(InsertCommand(buf, clipboard, "Hello world!!!", 0)));
	ed.addAndExecuteCommand(std::make_unique<InsertCommand>(InsertCommand(buf, clipboard, " to be continued ", std::string("Hello world!!!").size())));
	EXPECT_EQ(ed.showLine(), "Hello world!!! to be continued ");
}

TEST(InsertCmd, insertEndUndoOne) {
	std::string buf, clipboard;
	Editor ed(buf);
	ed.addAndExecuteCommand(std::make_unique<InsertCommand>(InsertCommand(buf, clipboard, "Hello world!!!", 0)));
	ed.addAndExecuteCommand(std::make_unique<InsertCommand>(InsertCommand(buf, clipboard, " to be continued ", std::string("Hello world!!!").size())));
	ed.undo();
	EXPECT_EQ(ed.showLine(), "Hello world!!!");
}

TEST(DeleteCmd, insertDeleteEnd) {
	std::string buf, clipboard;
	Editor ed(buf);
	ed.addAndExecuteCommand(std::make_unique<InsertCommand>(InsertCommand(buf, clipboard, "Hello world!!!", 0)));
	ed.addAndExecuteCommand(std::make_unique<DeleteCommand>(DeleteCommand(buf, clipboard, buf.size() - 2, buf.size())));
	EXPECT_EQ(ed.showLine(), "Hello world!");
}

TEST(DeleteCmd, insertDeleteEndUndo) {
	std::string buf, clipboard;
	Editor ed(buf);
	ed.addAndExecuteCommand(std::make_unique<InsertCommand>(InsertCommand(buf, clipboard, "Hello world!!!", 0)));
	ed.addAndExecuteCommand(std::make_unique<DeleteCommand>(DeleteCommand(buf, clipboard, buf.size() - 2, buf.size())));
	ed.undo();
	EXPECT_EQ(ed.showLine(), "Hello world!!!");
}

TEST(DeleteCmd, insertDeleteMiddleUndo) {
	std::string buf, clipboard;
	Editor ed(buf);
	ed.addAndExecuteCommand(std::make_unique<InsertCommand>(InsertCommand(buf, clipboard, "Hello world!!!", 0)));
	ed.addAndExecuteCommand(std::make_unique<DeleteCommand>(DeleteCommand(buf, clipboard, 6, 11)));
	ed.undo();
	EXPECT_EQ(ed.showLine(), "Hello world!!!");
}

TEST(DeleteCmd, insertDeleteMiddle) {
	std::string buf, clipboard;
	Editor ed(buf);
	ed.addAndExecuteCommand(std::make_unique<InsertCommand>(InsertCommand(buf, clipboard, "Hello world!!!", 0)));
	ed.addAndExecuteCommand(std::make_unique<DeleteCommand>(DeleteCommand(buf, clipboard, 5, 11)));
	EXPECT_EQ(ed.showLine(), "Hello!!!");
}

TEST(CopyPasteCmd, insertCopyCopyPasteOne) {
	std::string buf, clipboard;
	Editor ed(buf);
	ed.addAndExecuteCommand(std::make_unique<InsertCommand>(InsertCommand(buf, clipboard, "Hello world!!!", 0)));
	ed.addAndExecuteCommand(std::make_unique<CopyCommand>(CopyCommand(buf, clipboard, 0, 5)));
	ed.addAndExecuteCommand(std::make_unique<CopyCommand>(CopyCommand(buf, clipboard, 6, 11)));
	ed.addAndExecuteCommand(std::make_unique<PasteCommand>(PasteCommand(buf, clipboard)));
	EXPECT_EQ(ed.showLine(), "Hello world!!!world");
}

TEST(factory, insertCopyCopyPasteOne) {
	std::string buf, clipboard;
	Editor ed(buf);
	CommandFactory factory;
	ed.addAndExecuteCommand(factory.createCommand(commands::insert,buf, clipboard, "Hello world!!!", 0));
	ed.addAndExecuteCommand(factory.createCommand(commands::copy, buf, clipboard, 0, 5));
	ed.addAndExecuteCommand(factory.createCommand(commands::copy, buf, clipboard, 6, 11));
	ed.addAndExecuteCommand(factory.createCommand(commands::paste, buf, clipboard));
	EXPECT_EQ(ed.showLine(), "Hello world!!!world");
}

TEST(lineEditor, insert)
{
	std::istringstream ss("insert hello 0");
	Parser parser(ss);
	LineEditor ld(parser);
	ld.parseAndExecute();
	EXPECT_EQ(ld.showLine(), "hello");
}
TEST(lineEditor, insertCopyPaste)
{
	std::istringstream ss("insert hello 0\ncopy 0 5\npaste ");
	Parser parser(ss);
	LineEditor ld(parser);
	ld.parseAndExecute();
	EXPECT_EQ(ld.showLine(), "hellohello");
}
TEST(lineEditor, insertCopyPasteUndo)
{
	std::istringstream ss("insert hello 0\ncopy 0 5\npaste\nundo ");
	Parser parser(ss);
	LineEditor ld(parser);
	ld.parseAndExecute();
	EXPECT_EQ(ld.showLine(), "hello");
}
TEST(lineEditor, insertCopyPasteUndoRedo)
{
	std::istringstream ss("Insert hello 0\ncopy 0 5\npaste\nundo\nredo ");
	Parser parser(ss);
	LineEditor ld(parser);
	ld.parseAndExecute();
	EXPECT_EQ(ld.showLine(), "hellohello");
}
TEST(lineEditor, insertCopyPasteUndoUndoUndo)
{
	std::istringstream ss("Insert hello 0\ncopy 0 5\npaste\nundo\nundo\nundo ");
	Parser parser(ss);
	LineEditor ld(parser);
	ld.parseAndExecute();
	EXPECT_EQ(ld.showLine(), "");
}
TEST(lineEditor, insertCopyPasteUndoX3RedoX3)
{
	std::istringstream ss("Insert hello 0\ncopy 0 5\npaste\nundo\nundo\nundo\nredo\nredo\nredo ");
	Parser parser(ss);
	LineEditor ld(parser);
	ld.parseAndExecute();
	EXPECT_EQ(ld.showLine(), "hellohello");
}
TEST(lineEditor, insertWrongCopyPaste)
{
	std::istringstream ss("Insert hello 0\ncopy 6 10\npaste ");
	Parser parser(ss);
	LineEditor ld(parser);
	ld.parseAndExecute();
	EXPECT_EQ(ld.showLine(), "hello");
}
TEST(lineEditor, insertCopyPasteDeleteBegin)
{
	std::istringstream ss("insert hello 0\ncopy 0 5\npaste\ndelete 0 5 ");
	Parser parser(ss);
	LineEditor ld(parser);
	ld.parseAndExecute();
	EXPECT_EQ(ld.showLine(), "hello");
}
TEST(lineEditor, insertCopyPasteDeleteEnd)
{
	std::istringstream ss("insert hello 0\ncopy 0 5\npaste\ndelete 5 10 ");
	Parser parser(ss);
	LineEditor ld(parser);
	ld.parseAndExecute();
	EXPECT_EQ(ld.showLine(), "hello");
}
TEST(lineEditor, insertCopyPasteWrongDelete)
{
	std::istringstream ss("insert hello 0\ncopy 0 5\npaste\ndelete 5 11 ");
	Parser parser(ss);
	LineEditor ld(parser);
	ld.parseAndExecute();
	EXPECT_EQ(ld.showLine(), "hellohello");
}

TEST(lineEditor, WronginsertCopyPaste)
{
	std::istringstream ss("insert hello 2\n ");
	Parser parser(ss);
	LineEditor ld(parser);
	ld.parseAndExecute();
	EXPECT_EQ(ld.showLine(), "");
}


GTEST_API_ int main(int argc, char* argv[])
{
	if (argc > 0)
	{
		testing::internal::FilePath arg(argv[0]);
		const auto name = arg.RemoveDirectoryName().RemoveExtension("exe").string();
		testing::GTEST_FLAG(output) = std::string("xml:") + name + ".xml";
	}
	testing::InitGoogleTest(&argc, argv);
#if defined(_MSC_VER)
	testing::UnitTest::GetInstance()->listeners().Append(new testing::MSVCMemoryLeakListener());
#endif // defined(_MSC_VER)
	return RUN_ALL_TESTS();
}