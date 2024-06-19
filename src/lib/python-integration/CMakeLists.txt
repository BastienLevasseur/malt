#TODO: Add the header at some point 

include_directories(${Python3_INCLUDE_DIRS})
######################################################
set(MALT_LIB_SRC
    DummyAllocationMap.cpp
    DummyLocation.cpp
    DummyStatistics.cpp

    MaltPythonAllocator.cpp

    PythonAllocatorDomainType.hpp    
    PythonBacktraceStack.cpp
    PythonDomainAllocatorWrapper.cpp
    PythonGuard.cpp
    PythonHandler.cpp
    PythonInterpreterStarter.cpp
)

######################################################
add_library(malt-python-integration OBJECT ${MALT_LIB_SRC})
SET_TARGET_PROPERTIES(malt-python-integration PROPERTIES COMPILE_FLAGS -fPIC)
target_link_libraries(malt-python-integration PUBLIC ${Python3_LIBRARIES})

#add_executable(malt-python SimpleExecutable.cpp)

#if (ENABLE_TESTS)
#	add_subdirectory(tests)
#endif (ENABLE_TESTS)