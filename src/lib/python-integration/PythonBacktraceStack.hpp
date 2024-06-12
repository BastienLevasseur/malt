#ifndef PythonBacktraceStack_hpp
#define PythonBacktraceStack_hpp

#include "Python.h"
#include "DummyLocation.hpp"
#include <vector>

namespace MALT{
    std::vector<DummyLocation> getPythonBacktraceStack(void);
}
#endif //PythonBacktraceStack_hpp