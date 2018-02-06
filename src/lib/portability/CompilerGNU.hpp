/*****************************************************
             PROJECT  : MALT
             VERSION  : 1.0.0
             DATE     : 02/2018
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef MALT_COMPILER_GNU_HPP
#define MALT_COMPILER_GNU_HPP

/********************  HEADERS  *********************/
//standard
#include <string>

/*******************  NAMESPACE  ********************/
namespace MALT
{

/*********************  CLASS  **********************/
class CompilerGNU
{
	public:
		static std::string demangleCppNames(const std::string & value);
};

}

#endif //MALT_COMPILER_GNU_HPP
