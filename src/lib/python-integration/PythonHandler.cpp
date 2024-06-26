#include "PythonHandler.hpp"
#include "PythonLocation.hpp"

//FIXME: Remove it at some point
#define MALT_PYTHON_UNUSED(var) (void)(var)

namespace MALT {

PythonHandler::PythonHandler(DummyStatistics* dummyStats, PythonLocationTranslater* locationTranslater){
	this->dummyStats = dummyStats;
	this->locationTranslater = locationTranslater;
}


PythonHandler::~PythonHandler(){
	;
}

/**
 * Handles a Python malloc, fetch the backtrace stack and print it, updates statistics
 * FIXME: Behavior will change at some point to use MALT internals 
 */
void PythonHandler::onMalloc(const PythonAllocatorDomainType& pyMallocDomain, size_t size){
	assert(size != 0);
	
	this->dummyStats->mallocCountUp(pyMallocDomain);
	this->dummyStats->mallocSumUp(pyMallocDomain, size);

	this->getPythonBacktraceStack();
}


/**
 * Handles a Python free, fetch the backtrace stack and print it, updates statistics
 * FIXME: Behavior will change at some point to use MALT internals 
 */
void PythonHandler::onFree(const PythonAllocatorDomainType& pyMallocDomain, void* freePtr){
	MALT_PYTHON_UNUSED(freePtr);
	this->dummyStats->freeCountUp(pyMallocDomain);
	
	this->getPythonBacktraceStack();
}


/**
 * Handles a Python calloc, fetch the backtrace stack and print it, updates statistics
 * FIXME: Behavior will change at some point to use MALT internals 
 */
void PythonHandler::onCalloc(const PythonAllocatorDomainType& pyMallocDomain, size_t nbElements, size_t elementSize){
	assert(nbElements != 0);
	assert(elementSize != 0);
	this->dummyStats->callocCountUp(pyMallocDomain);
	this->dummyStats->callocSumUp(pyMallocDomain, nbElements*elementSize);

	this->getPythonBacktraceStack();
}


/**
 * Handles a Python realloc, fetch the backtrace stack and print it, updates statistics
 * FIXME: Behavior will change at some point to use MALT internals 
 */
void PythonHandler::onRealloc(const PythonAllocatorDomainType& pyMallocDomain, void* reallocPtr, size_t newSize){
	MALT_PYTHON_UNUSED(reallocPtr);
	MALT_PYTHON_UNUSED(newSize);
	assert(newSize != 0);

	this->dummyStats->reallocCountUp(pyMallocDomain);

	this->getPythonBacktraceStack();
}


void PythonHandler::getPythonBacktraceStack(void){

    //If the Python interpreter is not correctly initialised, can't get the backtrace stack
	if (_PyThreadState_UncheckedGet() == NULL){
		return;
	}

    //Get the Python Frame
	PyFrameObject* currentFrame = PyThreadState_GetFrame(PyGILState_GetThisThreadState());

	PyCodeObject* currentPyCode = NULL;
	PyObject* currentFilenameObject = NULL;
	PyObject* currentFramenameObject = NULL;
    char* currentFileName = NULL;
    char* currentFrameName = NULL;
	int currentLineNumber = 0;

    //Fetch while we are not on the top of the stack
	while(currentFrame != NULL){

		currentPyCode = PyFrame_GetCode(currentFrame);
		assert(currentPyCode != NULL);

        //Fetch the file name and frame name i.e. function name in the current PyCode
        //FIXME: Currently, this makes many allocations, maybe there's a way to avoid this
		currentFilenameObject = PyUnicode_AsASCIIString(currentPyCode->co_filename);
		currentFramenameObject = PyUnicode_AsASCIIString(currentPyCode->co_name);

        assert(currentFilenameObject != NULL);
		assert(currentFramenameObject != NULL);

        currentFileName = PyBytes_AsString(currentFilenameObject);
        currentFrameName = PyBytes_AsString(currentFramenameObject);

		//TODO: Look into https://docs.python.org/3/reference/datamodel.html#codeobject.co_lines
		//TODO: And this https://peps.python.org/pep-0626/
		//This should be way more performant, currently this is the major overhead
        //Intuition : Py_Addr2Line is called way too many times, can we refractor the filename, framename and line number into one call of Addr2Line ??
		currentLineNumber = PyFrame_GetLineNumber(currentFrame);

        //TODO: Before creating a PythonLocation, checek if it wasn't already created. Need to make a map string -> UniqueID
		//Then decode by doing UniqueID -> String
		PythonLocation pythonLocation = PythonLocation(currentFileName, currentFrameName, currentLineNumber);
		this->locationTranslater->insertLocation(pythonLocation);

        //Free the names that were allocated, we decrease the reference counter and let the GC do the job
		Py_DECREF(currentFilenameObject);
		Py_DECREF(currentFramenameObject);

        //Go up on the stack
        currentFrame = PyFrame_GetBack(currentFrame);
	}
}

}