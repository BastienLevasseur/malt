#include "DummyLocation.hpp"

DummyLocation::DummyLocation(const char* filename, const char* framename, const int lineNumber, void* address){
	this->filename = std::string(filename);
	this->framename = std::string(framename);
	this->lineNumber = lineNumber;
	this->address = address;
}

DummyLocation::DummyLocation(const DummyLocation& orig){
	this->filename = orig.filename;
	this->framename = orig.framename;
	this->lineNumber = orig.lineNumber;
	this->address = orig.address;
}

DummyLocation::~DummyLocation(void){
	;
}


std::string DummyLocation::getFilename(void){
	return this->filename;
}

std::string DummyLocation::getFramename(void){
	return this->framename;
}

int DummyLocation::getLineNumber(void){
	return this->lineNumber;
}

void* DummyLocation::getAddress(void){
    return this->address;
}


std::ostream& operator << (std::ostream& out, const DummyLocation& location){
	std::stringstream ans;

	ans << "File: " << location.filename << ", ";
	ans << "Frame: " << location.framename << ", ";
	ans << "Line: " << location.lineNumber << ", ";
	ans << "Address: " << location.address;

	out << ans.str();
	return out;
}


bool DummyLocation::operator == (const DummyLocation& rhs) const{
	return ((this->filename == rhs.filename) && (this->framename == rhs.framename) 
	&& (this->lineNumber == rhs.lineNumber) && (this->address == rhs.address));
}


bool DummyLocation::operator != (const DummyLocation& rhs) const {
    return ((this->filename != rhs.filename) || (this->framename != rhs.framename) 
	|| (this->lineNumber != rhs.lineNumber) || (this->address != rhs.address));
}


bool DummyLocation::operator < (const DummyLocation& rhs) const {
	return ((this->filename < rhs.filename) || (this->framename < rhs.framename)
	|| (this->lineNumber < rhs.lineNumber) || (this->address < rhs.address));
}


template <class T>
inline void std::hash<DummyLocation>::hash_combine(std::size_t &seed, const T &v){
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

size_t std::hash<DummyLocation>::operator () (const DummyLocation& location) const {
	size_t hashValue;
	hash_combine(hashValue, location.filename);
	hash_combine(hashValue, location.framename);
	hash_combine(hashValue, location.lineNumber);
	hash_combine(hashValue, location.address);

	return hashValue;
}
