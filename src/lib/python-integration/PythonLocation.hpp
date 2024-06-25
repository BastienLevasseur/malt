#ifndef PythonLocation_hpp
#define PythonLocation_hpp

#include <iostream>
#include <sstream>


/* A dummy Location class, will be replaced by the MALT already existing concept */
//TODO: Remove PyCode
class PythonLocation{

private:
	std::string filename;
	std::string framename;
	int lineNumber;

public:
	PythonLocation(const char* filename, const char* framename, const int lineNumber);
	PythonLocation(const PythonLocation& orig);
	~PythonLocation(void);

	std::string getFilename(void);
	std::string getFramename(void);
	int getLineNumber(void);

	friend struct std::hash<PythonLocation>;

	friend std::ostream& operator << (std::ostream& out, const PythonLocation& location);
	bool operator == (const PythonLocation& rhs) const;
	bool operator != (const PythonLocation& rhs) const;
	bool operator < (const PythonLocation& rhs) const;
};

template <> struct std::hash<PythonLocation>{
	template <class T> static inline void hash_combine(std::size_t& seed, const T& v);

	size_t operator () (const PythonLocation& location) const;
};

#endif 