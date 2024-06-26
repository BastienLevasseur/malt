/********************  HEADERS  *********************/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <common/GTestHelper.hpp>

#include <python-integration/PythonAllocatorHooking.hpp>
#include <python-integration/PythonInterpreterStarter.hpp>

#include <common/Debug.hpp>

using namespace MALT;
using namespace testing;

int main(int argc, char** argv){
    PythonLocationTranslater* locationTranslater = new PythonLocationTranslater();
    DummyStatistics* dummyStats = new DummyStatistics();
    PythonHandler* pythonHandler = new PythonHandler(dummyStats, locationTranslater);
    PythonAllocatorHooking* allocatorHook = new PythonAllocatorHooking(pythonHandler);

    allocatorHook->enable();
}

TEST(tmpTest, test){
    char* args[2] =  {"", "TestBacktracePython.py"};
    PythonInterpreterStarter::startPythonInterpreter(1, args);

    EXPECT_EQ(0, 1);
}

