#include "PythonInterpreterStarter.hpp"
#include "Python.h"


namespace MALT{
    void PythonInterpreterStarter::startPythonInterpreter(int argc, char** argv){
    PyConfig pyConfig;

	PyConfig_InitPythonConfig(&pyConfig);

	const wchar_t* pyProgramName = nullptr;

	//FIXME: Hardcoded, need to search with CMake TODO: Is this really needed ?? 
	//const wchar_t* pyLib = Py_DecodeLocale("/user/local/bin/python3.12", nullptr);
	//const wchar_t* pyInterpreter = Py_DecodeLocale("/home/bastienlevasseur/venv3.12/bin/python3.12", nullptr);

	//Set program name
	PyConfig_SetString(&pyConfig, &pyConfig.program_name, pyProgramName);

	//Set base_executable path, which is lib
	//PyConfig_SetString(&pyConfig, &pyConfig.base_executable, pyLib);

	//Set the executable, which is the python interpreter
	//PyConfig_SetString(&pyConfig, &pyConfig.executable, pyInterpreter);

	//Set argc/argv
	PyConfig_SetBytesArgv(&pyConfig, argc, &argv[0]);

	//Set the config
	PyConfig_Read(&pyConfig);

	//Initialize from the config
	Py_InitializeFromConfig(&pyConfig);

	PyConfig_Clear(&pyConfig);
    }
}