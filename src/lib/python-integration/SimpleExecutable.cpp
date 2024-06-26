#include "DummyStatistics.hpp"
#include "PythonHandler.hpp"
#include "PythonAllocatorHooking.hpp"
#include "PythonInterpreterStarter.hpp"
#include "PythonLocationTranslater.hpp"
#include <iostream>

using namespace MALT;

int main(int argc, char** argv){
    
	DummyStatistics* dummyStats = new DummyStatistics();
	PythonLocationTranslater* locationTranslater = new PythonLocationTranslater();
	PythonHandler* pythonHandler = new PythonHandler(dummyStats, locationTranslater);

	for (int i = 0; i < argc ; i++){
		std::cout << "Argv " << i << " is : " << argv[i] << std::endl;
	}
	
	getchar();
    PythonInterpreterStarter::startPythonInterpreter(argc, argv);

	PythonAllocatorHooking* maltPythonAllocator = new PythonAllocatorHooking(pythonHandler);

	maltPythonAllocator->enable();

	int returnStatus = Py_RunMain();
	
	maltPythonAllocator->disable();

	int pythonInterpretorError = Py_FinalizeEx();

	std::cout << *dummyStats << std::endl;

	locationTranslater->ensureIDsAreUnique();
	std::cout << *locationTranslater << std::endl;

	if (pythonInterpretorError != 0){
		std::cerr << "There was an error while ending the Python interpretor : " << pythonInterpretorError << std::endl;
	}

	delete maltPythonAllocator;
	delete pythonHandler;
	delete dummyStats;

	return returnStatus;
}
