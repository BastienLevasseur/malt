/********************  HEADERS  *********************/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <common/GTestHelper.hpp>

#include <python-integration/PythonAllocatorHooking.hpp>
#include <python-integration/PythonInterpreterStarter.hpp>

#include <common/Debug.hpp>

using namespace MALT;
using namespace testing;

PythonLocationTranslater* gblLocationTranslater = nullptr;

int main(int argc, char** argv){
    gblLocationTranslater = new PythonLocationTranslater();
    DummyStatistics* dummyStats = new DummyStatistics();
    PythonHandler* pythonHandler = new PythonHandler(dummyStats, gblLocationTranslater);
    PythonAllocatorHooking* allocatorHook = new PythonAllocatorHooking(pythonHandler);

    char* args[2] =  {"TestBacktraceStackPython", "/home/bastienlevasseur/malt/src/lib/python-integration/tests/PythonFile.py"};

    allocatorHook->enable();
    PythonInterpreterStarter::startPythonInterpreter(1, args);

    ::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(TestBacktraceStack, TestMain){
    std::cout << *gblLocationTranslater << std::endl;
    getchar();
    PythonLocation mainLoc = PythonLocation("/home/bastienlevasseur/malt/src/lib/python-integration/tests/PythonFile.py", "<module>", 10);

    EXPECT_TRUE(gblLocationTranslater->containsLocation(mainLoc));
}

TEST(TestBacktraceStack, TestFoo){
    PythonLocation fooLoc = PythonLocation("/home/bastienlevasseur/malt/src/lib/python-integration/tests/PythonFile.py", "foo", 7);

    EXPECT_TRUE(gblLocationTranslater->containsLocation(fooLoc));
}

TEST(TestBacktraceStack, TestBar){
    PythonLocation barLoc = PythonLocation("/home/bastienlevasseur/malt/src/lib/python-integration/tests/PythonFile.py", "bar", 2);

    EXPECT_TRUE(gblLocationTranslater->containsLocation(barLoc));
}

TEST(TestBacktraceStack, TestFalse){
    PythonLocation barLoc = PythonLocation("/home/bastienlevasseur/malt/src/lib/python-integration/tests/PythonFile.py", "fdbksudfkbjldfsbjkdfsbjkdfbjksdksjqf", 2);

    EXPECT_FALSE(gblLocationTranslater->containsLocation(barLoc));
}