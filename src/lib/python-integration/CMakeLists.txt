#TODO: Add the header at some point 

include_directories(${Python3_INCLUDE_DIRS})
######################################################
set(MALT_LIB_SRC
    DummyAllocationMap.cpp
    
    DummyStatistics.cpp
    DummyLocationTranslater.cpp

    PythonAllocatorDomainType.hpp    
    PythonAllocatorHooking.cpp
    PythonBacktraceStack.cpp
    PythonDomainAllocatorWrapper.cpp
    PythonGuard.cpp
    PythonHandler.cpp
    PythonInterpreterStarter.cpp
    PythonLocation.cpp
)

######################################################
add_library(malt-python-integration OBJECT ${MALT_LIB_SRC})
SET_TARGET_PROPERTIES(malt-python-integration PROPERTIES COMPILE_FLAGS -fPIC)
target_link_libraries(malt-python-integration PUBLIC ${Python3_LIBRARIES})

add_executable(malt-python SimpleExecutable.cpp)
target_link_libraries(malt-python malt-python-integration malt-base)
install()
if (ENABLE_TESTS)
	add_subdirectory(tests)
endif (ENABLE_TESTS)