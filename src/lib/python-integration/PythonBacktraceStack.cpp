#include "PythonBacktraceStack.hpp"

namespace MALT {

/**
 * Fetch a Backtrace of the Python Interpreter.
 * We use C defined NULL since the Python interpreter is written in C.
 * FIXME: Return type will change by the already existing MALT concept
 */
std::vector<DummyLocation> getPythonBacktraceStack(void){
    std::vector<DummyLocation> pythonBacktraceStack;

    //If the Python interpreter is not correctly initialised, can't get the backtrace stack
	if (_PyThreadState_UncheckedGet() == NULL){
		return pythonBacktraceStack;
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

        //FIXME: This will change into MALT location concept
		DummyLocation formatedDummyLocation = DummyLocation(currentFileName, currentFrameName, currentLineNumber, (void*) currentPyCode);
        

        //Valid names with a single chararacter are not alloced, so we don't free them
        if (strncmp((currentFileName + 1), "\0", 1) != 0){
            PyObject_Free((void*) currentFilenameObject);
        }

		if (strncmp((currentFrameName + 1), "\0", 1) != 0){
			PyObject_Free((void*) currentFramenameObject);	
		}
		
		pythonBacktraceStack.push_back(formatedDummyLocation);

        //Go up on the stack
        currentFrame = PyFrame_GetBack(currentFrame);
	}

	return pythonBacktraceStack;
}
}