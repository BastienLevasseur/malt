#TODO: Add the header at some point 

######################################################
set(MALT_LIB_SRC
    PythonBacktraceStack.cpp
    DummyLocation.cpp
)

######################################################
add_library(malt-python-integration OBJECT ${MALT_LIB_SRC})
SET_TARGET_PROPERTIES(malt-python-integration PROPERTIES COMPILE_FLAGS -fPIC)
