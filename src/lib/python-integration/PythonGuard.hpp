#ifndef PythonGuard_hpp
#define PythonGuard_hpp

#include <cstdio>

class PythonGuard{
	public:
		PythonGuard();
		~PythonGuard();

		bool enterOnce();
		void exit();

	private:
		bool guard;
};


#endif //PythonGuard_hpp