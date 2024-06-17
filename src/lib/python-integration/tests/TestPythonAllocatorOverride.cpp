/********************  HEADERS  *********************/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <common/GTestHelper.hpp>
#include <python-integration/MaltPythonAllocator.hpp>
#include <python-integration/PythonInterpreterStarter.hpp>

//TODO: Replace the assert by MALT_FATAL_ARG, if we can include Debug.hpp in CMake

using namespace MALT;
using namespace testing;

DummyStatistics* gblDummyStats = nullptr;
MaltPythonAllocator_t* gblMaltPythonAllocator = nullptr;

PythonAllocator_t* gblOldPythonAllocator;
PythonAllocator_t* gblNewPythonAllocator;


TEST(TestPythonAllocatorOverride, TestMaltPythonAllocator){
    EXPECT_NOT_NULL(gblMaltPythonAllocator);
    EXPECT_NOT_NULL(gblMaltPythonAllocator->originalAllocator);
    EXPECT_NOT_NULL(gblMaltPythonAllocator->customAllocator);
    EXPECT_NOT_NULL(gblMaltPythonAllocator->maltPythonHandler);

    EXPECT_FALSE(gblMaltPythonAllocator->recursiveGuard);
    EXPECT_TRUE(gblMaltPythonAllocator->enabledFlag);
}

/*
For each test :

- Check that the old unmodified Python allocator function is different from the new modified one
    i.e: Check that the allocator has been changed

- Check that the new Python allocator function is the MALT Python allocator function
    i.e: Check that the allocator has been changed to the MALT Python allocator

Tests are on all domains on all functions
*/

TEST(TestPythonAllocatorOverride, TestOverrideRawDomainMalloc){ 
    EXPECT_NE(gblOldPythonAllocator->allocatorRaw->malloc, gblNewPythonAllocator->allocatorRaw->malloc);
    EXPECT_EQ(gblNewPythonAllocator->allocatorRaw->malloc, gblMaltPythonAllocator->customAllocator->allocatorRaw->malloc);
}

TEST(TestPythonAllocatorOverride, TestOverrideRawDomainFree){
    EXPECT_NE(gblOldPythonAllocator->allocatorRaw->free, gblNewPythonAllocator->allocatorRaw->free);
    EXPECT_EQ(gblNewPythonAllocator->allocatorRaw->free, gblMaltPythonAllocator->customAllocator->allocatorRaw->free);
}

TEST(TestPythonAllocatorOverride, TestOverrideRawDomainCalloc){
    EXPECT_NE(gblOldPythonAllocator->allocatorRaw->calloc, gblNewPythonAllocator->allocatorRaw->calloc);
    EXPECT_EQ(gblNewPythonAllocator->allocatorRaw->calloc, gblMaltPythonAllocator->customAllocator->allocatorRaw->calloc);
}

TEST(TestPythonAllocatorOverride, TestOverrideRawDomainRealloc){
    EXPECT_NE(gblOldPythonAllocator->allocatorRaw->realloc, gblNewPythonAllocator->allocatorRaw->realloc);
    EXPECT_EQ(gblNewPythonAllocator->allocatorRaw->realloc, gblMaltPythonAllocator->customAllocator->allocatorRaw->realloc);
}



TEST(TestPythonAllocatorOverride, TestOverrideMemDomainMalloc){
    EXPECT_NE(gblOldPythonAllocator->allocatorMem->malloc, gblNewPythonAllocator->allocatorMem->malloc);
    EXPECT_EQ(gblNewPythonAllocator->allocatorMem->malloc, gblMaltPythonAllocator->customAllocator->allocatorMem->malloc);
}

TEST(TestPythonAllocatorOverride, TestOverrideMemDomainFree){
    EXPECT_NE(gblOldPythonAllocator->allocatorMem->free, gblNewPythonAllocator->allocatorMem->free);
    EXPECT_EQ(gblNewPythonAllocator->allocatorMem->free, gblMaltPythonAllocator->customAllocator->allocatorMem->free);
}

TEST(TestPythonAllocatorOverride, TestOverrideMemDomainCalloc){
    EXPECT_NE(gblOldPythonAllocator->allocatorMem->calloc, gblNewPythonAllocator->allocatorMem->calloc);
    EXPECT_EQ(gblNewPythonAllocator->allocatorMem->calloc, gblMaltPythonAllocator->customAllocator->allocatorMem->calloc);
}

TEST(TestPythonAllocatorOverride, TestOverrideMemDomainRealloc){
    EXPECT_NE(gblOldPythonAllocator->allocatorMem->realloc, gblNewPythonAllocator->allocatorMem->realloc);
    EXPECT_EQ(gblNewPythonAllocator->allocatorMem->realloc, gblMaltPythonAllocator->customAllocator->allocatorMem->realloc);
}



TEST(TestPythonAllocatorOverride, TestOverrideObjDomainMalloc){
    EXPECT_NE(gblOldPythonAllocator->allocatorObj->malloc, gblNewPythonAllocator->allocatorObj->malloc);
    EXPECT_EQ(gblNewPythonAllocator->allocatorObj->malloc, gblMaltPythonAllocator->customAllocator->allocatorObj->malloc);
}

TEST(TestPythonAllocatorOverride, TestOverrideObjDomainFree){
    EXPECT_NE(gblOldPythonAllocator->allocatorMem->free, gblNewPythonAllocator->allocatorMem->free);
    EXPECT_EQ(gblNewPythonAllocator->allocatorObj->free, gblMaltPythonAllocator->customAllocator->allocatorObj->free);
}

TEST(TestPythonAllocatorOverride, TestOverrideObjDomainCalloc){
    EXPECT_NE(gblOldPythonAllocator->allocatorMem->calloc, gblNewPythonAllocator->allocatorMem->calloc);
    EXPECT_EQ(gblNewPythonAllocator->allocatorObj->calloc, gblMaltPythonAllocator->customAllocator->allocatorObj->calloc);
}

TEST(TestPythonAllocatorOverride, TestOverrideObjDomainRealloc){
    EXPECT_NE(gblOldPythonAllocator->allocatorMem->realloc, gblNewPythonAllocator->allocatorMem->realloc);
    EXPECT_EQ(gblNewPythonAllocator->allocatorObj->realloc, gblMaltPythonAllocator->customAllocator->allocatorObj->realloc);
}


int main(int argc, char** argv){
    gblDummyStats = new DummyStatistics();
	PythonHandler* pythonHandler = new PythonHandler(gblDummyStats);

	PythonInterpreterStarter::startPythonInterpreter(0, nullptr);

    gblOldPythonAllocator = initialisePythonAllocator();
    
    getPythonAllocatorFunctions(gblOldPythonAllocator);

	initialiseMaltPythonAllocator(pythonHandler);
    gblMaltPythonAllocator = getGlobalMaltPythonAllocator();
    
    enableMaltPythonAllocator(gblMaltPythonAllocator);
    
    gblNewPythonAllocator = initialisePythonAllocator();
    
    getPythonAllocatorFunctions(gblNewPythonAllocator);
    
    ::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
