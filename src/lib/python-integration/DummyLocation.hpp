#ifndef DummyLocation_hpp
#define DummyLocation_hpp

#include <iostream>
#include <sstream>


/* A dummy Location class, will be replaced by the MALT already existing concept */
class DummyLocation{

private:
	std::string filename;
	std::string framename;
	int lineNumber;
	void* address;

public:
	DummyLocation(const char* filename, const char* framename, const int lineNumber, void* address);
	DummyLocation(const DummyLocation& orig);
	~DummyLocation(void);

	std::string getFilename(void);
	std::string getFramename(void);
	int getLineNumber(void);
	void* getAddress(void);

	friend struct std::hash<DummyLocation>;

	friend std::ostream& operator << (std::ostream& out, const DummyLocation& location);
	bool operator == (const DummyLocation& rhs) const;
	bool operator != (const DummyLocation& rhs) const;
	bool operator < (const DummyLocation& rhs) const;
};

template <> struct std::hash<DummyLocation>{
	template <class T> static inline void hash_combine(std::size_t& seed, const T& v);

	size_t operator () (const DummyLocation& location) const;
};

#endif 