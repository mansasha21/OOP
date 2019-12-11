#include "gtest/gtest.h"
#include "gtest/gtest-memleak.h"
#include <fstream>
#include <ctime>
#include "TicketSystem.hpp"
#include <sstream>

TEST(simulate, thread2) {
	config conf = { 2,10,200,500,2000,2500,0 };
	TicketSystem ts(conf);
	ts.simulate();
}
TEST(simulate, thread4) {
	config conf = { 4,10,200,500,2000,2500,0};
	TicketSystem ts(conf);
	ts.simulate();
}

TEST(simulate, thread8) {
	config conf = { 8,10,200,500,2000,2500,0 };
	TicketSystem ts(conf);
	ts.simulate();
}

TEST(simulate, thread16) {
	config conf = { 16,10,200,500,2000,2500,0 };
	TicketSystem ts(conf);
	ts.simulate();
}

TEST(ticketMachine, tickets)
{
	TicketMachine m;
	
	for(int i = 1; i<10;i++)
	{
		EXPECT_EQ(m.getNext(), i);
	}
}

TEST(customer,getTicket)
{
	Customer c(100, 100, 10);
	c.solve();
	EXPECT_EQ(c.getTicket(), 10);
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