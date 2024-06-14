#TODO: Add the header at some point 

# Search for a Python3 interpreter and development kit
find_package(Python3 REQUIRED COMPONENTS Interpreter Development QUIET)
include_directories(${Python3_INCLUDE_DIRS})

######################################################
set(MALT_LIB_SRC
    DummyAllocationMap.cpp
    DummyLocation.cpp
    DummyStatistics.cpp

    MaltPythonAllocator.cpp

    PythonAllocatorDomain.hpp    
    PythonBacktraceStack.cpp
    PythonHandler.cpp
)

######################################################
add_library(malt-python-integration OBJECT ${MALT_LIB_SRC})
SET_TARGET_PROPERTIES(malt-python-integration PROPERTIES COMPILE_FLAGS -fPIC)

target_link_options(malt-python-integration PUBLIC ${Python3_LINK_OPTIONS})
target_link_libraries(malt-python-integration PUBLIC ${Python3_LIBRARIES})

#if (ENABLE_TESTS)
#	add_subdirectory(tests)
#endif (ENABLE_TESTS)