#include "PythonLocation.hpp"

PythonLocation::PythonLocation(const char* filename, const char* framename, const int lineNumber){
	this->filename = std::string(filename);
	this->framename = std::string(framename);
	this->lineNumber = lineNumber;
}

PythonLocation::PythonLocation(const PythonLocation& orig){
	this->filename = orig.filename;
	this->framename = orig.framename;
	this->lineNumber = orig.lineNumber;
}

PythonLocation::~PythonLocation(void){
	;
}


std::string PythonLocation::getFilename(void){
	return this->filename;
}

std::string PythonLocation::getFramename(void){
	return this->framename;
}

int PythonLocation::getLineNumber(void){
	return this->lineNumber;
}


std::ostream& operator << (std::ostream& out, const PythonLocation& location){
	std::stringstream ans;

	ans << "File: " << location.filename << ", ";
	ans << "Frame: " << location.framename << ", ";
	ans << "Line: " << location.lineNumber;

	out << ans.str();
	return out;
}


bool PythonLocation::operator == (const PythonLocation& rhs) const{
	return ((this->filename == rhs.filename) && (this->framename == rhs.framename) 
	&& (this->lineNumber == rhs.lineNumber));
}


bool PythonLocation::operator != (const PythonLocation& rhs) const {
    return ((this->filename != rhs.filename) || (this->framename != rhs.framename) 
	|| (this->lineNumber != rhs.lineNumber));
}


bool PythonLocation::operator < (const PythonLocation& rhs) const {
	return ((this->filename < rhs.filename) || (this->framename < rhs.framename)
	|| (this->lineNumber < rhs.lineNumber));
}


template <class T>
inline void std::hash<PythonLocation>::hash_combine(std::size_t &seed, const T &v){
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

size_t std::hash<PythonLocation>::operator () (const PythonLocation& location) const {
	size_t hashValue;
	hash_combine(hashValue, location.filename);
	hash_combine(hashValue, location.framename);
	hash_combine(hashValue, location.lineNumber);

	return hashValue;
}
