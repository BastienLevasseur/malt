######################################################
#Use gtest
include_directories(${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS})
include_directories(../)

#####################################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

#####################################################
add_definitions(-DCURRENT_SOURCE_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\")

#####################################################
set(TEST_NAMES TestPythonAllocatorOverride TestPythonAllocation TestPythonAllocationNullSizes)

#####################################################
FOREACH(test_name ${TEST_NAMES})
	add_executable(${test_name} ${test_name}.cpp)
	target_link_libraries(${test_name} ${GTEST_BOTH_LIBRARIES} ${GMOCK_BOTH_LIBRARIES} ${Python3_LIBRARIES} malt-base malt-python-integration)

	malt_add_test(${test_name} ${test_name})
ENDFOREACH(test_name)

