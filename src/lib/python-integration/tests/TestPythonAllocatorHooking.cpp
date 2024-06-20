/********************  HEADERS  *********************/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <common/GTestHelper.hpp>

#include <python-integration/PythonAllocatorHooking.hpp>
#include <python-integration/PythonInterpreterStarter.hpp>

using namespace MALT;
using namespace testing;


class MockPythonHandler : public PythonHandler {
	public:
		MockPythonHandler(DummyStatistics* dummyStats) : PythonHandler(dummyStats){};
		MOCK_METHOD(void, onMalloc, (const PythonAllocatorDomainType& pyMallocDomain, size_t size), (override));
		MOCK_METHOD(void, onFree, (const PythonAllocatorDomainType& pyMallocDomain, void* ptr), (override));
		MOCK_METHOD(void, onCalloc, (const PythonAllocatorDomainType& pyMallocDomain, size_t nbElements, size_t elementSize), (override));
		MOCK_METHOD(void, onRealloc, (const PythonAllocatorDomainType& pyMallocDomain, void* reallocPtr, size_t newSize), (override));
};

class TestPythonAllocatorHooking : public testing::Test {

	friend class PythonAllocatorHooking;

	public:
		void SetUp();
		void TearDown();

	protected:
		DummyStatistics* dummyStats;
		MockPythonHandler* mockPythonHandler;
		PythonAllocatorHooking* pythonAllocatorHook;
};



void TestPythonAllocatorHooking::SetUp(){
	this->dummyStats = new DummyStatistics();
	this->mockPythonHandler = new MockPythonHandler(dummyStats);


	PythonInterpreterStarter::startPythonInterpreter(0, nullptr);

	this->pythonAllocatorHook = new PythonAllocatorHooking(this->mockPythonHandler);
	this->pythonAllocatorHook->enable();
}


void TestPythonAllocatorHooking::TearDown(){
	this->pythonAllocatorHook->disable();

	delete this->pythonAllocatorHook;
	delete this->mockPythonHandler;
	delete this->dummyStats;
}

/*
For each test, check that the logging of malloc/free/calloc/realloc has been called.
Tests are on all domains on all functions.
*/

TEST_F(TestPythonAllocatorHooking, TestHookingRawMalloc){ 
	EXPECT_CALL(*mockPythonHandler, onMalloc(PYMEM_DOMAIN_RAW, 1)).Times(1);

	PyMem_RawMalloc(1);
}

TEST_F(TestPythonAllocatorHooking, TestHookingRawFree){
	EXPECT_CALL(*mockPythonHandler, onMalloc(PYMEM_DOMAIN_RAW, 1)).Times(1);
	EXPECT_CALL(*mockPythonHandler, onFree(PYMEM_DOMAIN_RAW, _)).Times(1);

	void* ptr = PyMem_RawMalloc(1);
	PyMem_RawFree(ptr);
}

TEST_F(TestPythonAllocatorHooking, TestHookingRawCalloc){
	EXPECT_CALL(*mockPythonHandler, onCalloc(PYMEM_DOMAIN_RAW, 1, 1)).Times(1);
	
	PyMem_RawCalloc(1, 1);
}

TEST_F(TestPythonAllocatorHooking, TestHookingRawRealloc){
	EXPECT_CALL(*mockPythonHandler, onMalloc(PYMEM_DOMAIN_RAW, 1)).Times(1);
	EXPECT_CALL(*mockPythonHandler, onRealloc(PYMEM_DOMAIN_RAW, _, 2)).Times(1);
	
	void* ptr = PyMem_RawMalloc(1);
	PyMem_RawRealloc(ptr, 2);
}



TEST_F(TestPythonAllocatorHooking, TestHookingMemMalloc){
	EXPECT_CALL(*mockPythonHandler, onMalloc(PYMEM_DOMAIN_MEM, 1)).Times(1);

	PyMem_Malloc(1);
}

TEST_F(TestPythonAllocatorHooking, TestHookingMemFree){
	EXPECT_CALL(*mockPythonHandler, onMalloc(PYMEM_DOMAIN_MEM, 1)).Times(1);
	EXPECT_CALL(*mockPythonHandler, onFree(PYMEM_DOMAIN_MEM, _)).Times(1);

	void* ptr = PyMem_Malloc(1);
	PyMem_Free(ptr);
}

TEST_F(TestPythonAllocatorHooking, TestHookingMemCalloc){
	EXPECT_CALL(*mockPythonHandler, onCalloc(PYMEM_DOMAIN_MEM, 1, 1)).Times(1);

	void* ptr = PyMem_Calloc(1, 1);
}

TEST_F(TestPythonAllocatorHooking, TestHookingMemRealloc){
	EXPECT_CALL(*mockPythonHandler, onMalloc(PYMEM_DOMAIN_MEM, 1)).Times(1);
	EXPECT_CALL(*mockPythonHandler, onRealloc(PYMEM_DOMAIN_MEM, _, 2)).Times(1);
	
	void* ptr = PyMem_Malloc(1);
	PyMem_Realloc(ptr, 2);
}


TEST_F(TestPythonAllocatorHooking, TestHookingObjMalloc){
	EXPECT_CALL(*mockPythonHandler, onMalloc(PYMEM_DOMAIN_OBJ, 1)).Times(1);

	PyObject_Malloc(1);
}

TEST_F(TestPythonAllocatorHooking, TestHookingObjFree){
	EXPECT_CALL(*mockPythonHandler, onMalloc(PYMEM_DOMAIN_OBJ, 1)).Times(1);
	EXPECT_CALL(*mockPythonHandler, onFree(PYMEM_DOMAIN_OBJ, _)).Times(1);

	void* ptr = PyObject_Malloc(1);
	PyObject_Free(ptr);
}

TEST_F(TestPythonAllocatorHooking, TestHookingObjCalloc){
	EXPECT_CALL(*mockPythonHandler, onCalloc(PYMEM_DOMAIN_OBJ, 1, 1)).Times(1);

	void* ptr = PyObject_Calloc(1, 1);
}

TEST_F(TestPythonAllocatorHooking, TestHookingObjRealloc){
	EXPECT_CALL(*mockPythonHandler, onMalloc(PYMEM_DOMAIN_OBJ, 1)).Times(1);
	EXPECT_CALL(*mockPythonHandler, onRealloc(PYMEM_DOMAIN_OBJ, _, 2)).Times(1);
	
	void* ptr = PyObject_Malloc(1);
	PyObject_Realloc(ptr, 2);
}
