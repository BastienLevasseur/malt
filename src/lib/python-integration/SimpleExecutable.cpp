#include "DummyStatistics.hpp"
#include "PythonHandler.hpp"
#include "PythonAllocatorHooking.hpp"
#include "PythonInterpreterStarter.hpp"
#include "DummyLocationTranslater.hpp"
#include <iostream>

using namespace MALT;

int main(int argc, char** argv){
    
	DummyStatistics* dummyStats = new DummyStatistics();
	PythonLocationTranslater* locationTranslater = new PythonLocationTranslater();
	PythonHandler* pythonHandler = new PythonHandler(dummyStats, locationTranslater);

    PythonInterpreterStarter::startPythonInterpreter(argc, argv);

	PythonAllocatorHooking* maltPythonAllocator = new PythonAllocatorHooking(pythonHandler);

	maltPythonAllocator->enable();

	int returnStatus = Py_RunMain();
	
	maltPythonAllocator->disable();

	int pythonInterpretorError = Py_FinalizeEx();

	std::cout << *dummyStats << std::endl;

	if (pythonInterpretorError != 0){
		std::cerr << "There was an error while ending the Python interpretor : " << pythonInterpretorError << std::endl;
	}

	delete maltPythonAllocator;
	delete pythonHandler;
	delete dummyStats;

	return returnStatus;
}
