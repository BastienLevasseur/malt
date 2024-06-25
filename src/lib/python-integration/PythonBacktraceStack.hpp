#ifndef PythonBacktraceStack_hpp
#define PythonBacktraceStack_hpp

#include "Python.h"
#include "PythonLocation.hpp"
#include <vector>

namespace MALT{
    std::vector<PythonLocation> getPythonBacktraceStack(void);
}
#endif //PythonBacktraceStack_hpp