#include "pch.h"

#include <Singleton.h>
#include <easylogging++.h>

INITIALIZE_EASYLOGGINGPP

using namespace std;
using namespace el;


TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);

  Configurations conf("E:/GitHub/QtTest/Common/LogConfiguration.conf");
  Loggers::reconfigureAllLoggers(conf);

  LOG(INFO) << "²âÊÔ³É¹¦£¡";
  LOG(ERROR) << "²âÊÔÊ§°Ü£¡";
}

TEST(derive, Singleton)
{
	class A : public Singleton<A>
	{
	public:
		A() {}

	public:
		void print() { cout << "address: " << this << endl; }
	};

	A& a = A::getInstance();
	a.print();
	A& b = A::getInstance();
	b.print();
	EXPECT_TRUE(true);
}