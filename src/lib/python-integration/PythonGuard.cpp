#include "PythonGuard.hpp"
#include <common/Debug.hpp>
#include <cassert>

PythonGuard::PythonGuard(){
    this->guard = false;
}

PythonGuard::~PythonGuard(){
    assert(this->guard == false);
    ;
}

bool PythonGuard::enterOnce(){
    if (this->guard == true){
        //Already locked
        return false;
    }else{
        //Unlocked
        this->guard = true;
        return true;
    }
}

void PythonGuard::exit(){
    if (this->guard == true){
        this->guard = false;
    }else{
        MALT_WARNING("Python guard was exited without entering.");
    }
}
