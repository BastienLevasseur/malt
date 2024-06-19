#ifndef PythonDomainAllocatorWrapper_hpp
#define PythonDomainAllocatorWrapper_hpp

#include "PythonHandler.hpp"
#include "PythonGuard.hpp"
#include "PythonAllocatorDomainType.hpp"

namespace MALT {

//Rename the Python Allocator type into a better name
typedef PyMemAllocatorEx PythonAllocatorDomain;

class PythonDomainAllocatorWrapper {

	public:
		PythonDomainAllocatorWrapper(PythonHandler* pythonHandler, PythonAllocatorDomainType domain, PythonGuard* guard, PythonAllocatorDomain* originalAllocator);
		~PythonDomainAllocatorWrapper();
		
		void* onMalloc(void* context, size_t size);

    	void onFree(void* context, void* ptr);

    	void* onCalloc(void* context, size_t nelem, size_t elsize);

    	void* onRealloc(void* context, void* ptr, size_t size);

	private:
		PythonGuard* guard;
		PythonHandler* pythonHandler;

		PythonAllocatorDomainType domain;
		PythonAllocatorDomain* originalAllocator;
};

}

#endif //PythonDomainAllocatorWrapper_hpp