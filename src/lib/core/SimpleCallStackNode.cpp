/*****************************************************
             PROJECT  : MALT
             VERSION  : 0.1.0
             DATE     : 03/2015
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

/********************  HEADERS  *********************/
#include <json/JsonState.h>
#include "SimpleCallStackNode.hpp"

/*******************  NAMESPACE  ********************/
namespace MALT
{

/*******************  FUNCTION  *********************/
SimpleCallStackNode::SimpleCallStackNode(const Stack& stack,int skipDepth)
	:callStack(stack,skipDepth)
{

}

/*******************  FUNCTION  *********************/
std::ostream& operator<<(std::ostream& out, const SimpleCallStackNode& tracer)
{
	out << "[ " << tracer.callStack << " ] " << tracer.info;
	return out;
}

/*******************  FUNCTION  *********************/
void convertToJson(htopml::JsonState& json, const SimpleCallStackNode& value)
{
	json.openStruct();
	json.printField("stack",value.callStack);
	json.printField("infos",value.info);
	json.closeStruct();
}

}
