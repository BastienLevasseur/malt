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

/**
 * On the Python Allocator, if the size alloced is zero it defaults to one.
 * We have to copy this behavior in the MALT Python Allocator.
 * We check if we indeed get an allocation of size 1 upon requesting an allocation of size 0.
 * 
 * FIXME: Investigate this, see the Python source code, starting from file "Objects/obmalloc.c" function _PyObject_Malloc line 1561
 * Mem & Obj domains don't have a guard for handling allocations of size zero.
 * They let the pool allocator return NULL (because size == 0) then use the Raw domain as a fallback.
 * 
 * FIXME: Investigate this, does this mean we count the allocation twice in MALT? One in Obj and one in Raw ??
 */


TEST_F(TestPythonAllocatorHooking, TestNullRawMalloc){ 
	EXPECT_CALL(*mockPythonHandler, onMalloc(PYMEM_DOMAIN_RAW, 1)).Times(1);

	PyMem_RawMalloc(0);
}

TEST_F(TestPythonAllocatorHooking, TestNullRawCalloc){
	EXPECT_CALL(*mockPythonHandler, onCalloc(PYMEM_DOMAIN_RAW, 1, 1)).Times(1);
	
	PyMem_RawCalloc(0, 0);
}

TEST_F(TestPythonAllocatorHooking, TestNullRawRealloc){
	EXPECT_CALL(*mockPythonHandler, onMalloc(PYMEM_DOMAIN_RAW, 2)).Times(1);
	EXPECT_CALL(*mockPythonHandler, onRealloc(PYMEM_DOMAIN_RAW, _, 1)).Times(1);
	
	void* ptr = PyMem_RawMalloc(2);
	PyMem_RawRealloc(ptr, 0);
}



TEST_F(TestPythonAllocatorHooking, TestNullMemMalloc){
	EXPECT_CALL(*mockPythonHandler, onMalloc(PYMEM_DOMAIN_RAW, 1)).Times(1);
	EXPECT_CALL(*mockPythonHandler, onMalloc(PYMEM_DOMAIN_MEM, 1)).Times(1);

	PyMem_Malloc(0);
}


TEST_F(TestPythonAllocatorHooking, TestNullMemCalloc){
	EXPECT_CALL(*mockPythonHandler, onCalloc(PYMEM_DOMAIN_MEM, 1, 1)).Times(1);
	EXPECT_CALL(*mockPythonHandler, onCalloc(PYMEM_DOMAIN_RAW, 1, 1)).Times(1);

	void* ptr = PyMem_Calloc(0, 0);
}

TEST_F(TestPythonAllocatorHooking, TestNullMemRealloc){
	EXPECT_CALL(*mockPythonHandler, onMalloc(PYMEM_DOMAIN_MEM, 2)).Times(1);
	EXPECT_CALL(*mockPythonHandler, onMalloc(PYMEM_DOMAIN_RAW, 1)).Times(1);
	EXPECT_CALL(*mockPythonHandler, onRealloc(PYMEM_DOMAIN_MEM, _, 1)).Times(1);
	
	void* ptr = PyMem_Malloc(2);
	PyMem_Realloc(ptr, 0);
}



TEST_F(TestPythonAllocatorHooking, TestNullObjMalloc){
	EXPECT_CALL(*mockPythonHandler, onMalloc(PYMEM_DOMAIN_OBJ, 1)).Times(1);
	EXPECT_CALL(*mockPythonHandler, onMalloc(PYMEM_DOMAIN_RAW, 1)).Times(1);

	PyObject_Malloc(0);
}

TEST_F(TestPythonAllocatorHooking, TestNullObjCalloc){
	EXPECT_CALL(*mockPythonHandler, onCalloc(PYMEM_DOMAIN_OBJ, 1, 1)).Times(1);
	EXPECT_CALL(*mockPythonHandler, onCalloc(PYMEM_DOMAIN_RAW, 1, 1)).Times(1);

	void* ptr = PyObject_Calloc(0, 0);
}

TEST_F(TestPythonAllocatorHooking, TestNullObjRealloc){
	EXPECT_CALL(*mockPythonHandler, onMalloc(PYMEM_DOMAIN_OBJ, 2)).Times(1);
	EXPECT_CALL(*mockPythonHandler, onMalloc(PYMEM_DOMAIN_RAW, 1)).Times(1);
	EXPECT_CALL(*mockPythonHandler, onRealloc(PYMEM_DOMAIN_OBJ, _, 1)).Times(1);
	
	void* ptr = PyObject_Malloc(2);
	PyObject_Realloc(ptr, 0);
}