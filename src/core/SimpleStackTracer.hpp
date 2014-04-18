/*****************************************************
             PROJECT  : MATT
             VERSION  : 0.1.0-dev
             DATE     : 01/2014
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef MATT_SIMPLE_BACKTRACE_STORAGE_HPP
#define MATT_SIMPLE_BACKTRACE_STORAGE_HPP

/********************  HEADERS  *********************/
//extern
#include <map>
#include <vector>
#include <ostream>
// #include <json/TypeToJson.h>
//locals
#include "SymbolResolver.hpp"
#include <stacks/BacktraceStack.hpp>
#include "SimpleCallStackNode.hpp"
#include "ValgrindOutput.hpp"
#include <common/STLInternalAllocator.hpp>
#include <common/Array.hpp>

/*******************  NAMESPACE  ********************/
namespace MATT
{

/*******************  FUNCTION  *********************/
//typedef std::vector<SimpleCallStackNode*> SimpleBacktraceVector;
typedef std::vector<SimpleCallStackNode*,STLInternalAllocator<SimpleCallStackNode*> > SimpleBacktraceVector;
// typedef MATT::Array<SimpleCallStackNode*> SimpleBacktraceVector;
// typedef std::map<StackHash,SimpleBacktraceVector> SimpleBacktraceVectorMap;
typedef std::map<StackHash,SimpleBacktraceVector,std::less<StackHash>,STLInternalAllocator<std::pair<StackHash,SimpleBacktraceVector> > > SimpleBacktraceVectorMap;

/*********************  CLASS  **********************/
class SimpleStackTracer
{
	public:
		SimpleStackTracer(void);
		~SimpleStackTracer(void);
		SimpleCallStackNode& getBacktraceInfo(const Stack& stack, int skipDepth = 0);
		void resolveSymbols(SymbolResolver & symbolResolver);
		void fillValgrindOut(MATT::ValgrindOutput& out, MATT::SymbolResolver& symbolResolver) const;
	public:
		friend std::ostream & operator << (std::ostream & out,const SimpleStackTracer & tracer);
		friend void convertToJson(htopml::JsonState & json, const SimpleStackTracer & value);
	private:
		SimpleBacktraceVectorMap callmaps;
		size_t count;
};

}

#endif //MATT_SIMPLE_BACKTRACE_STORAGE_HPP
