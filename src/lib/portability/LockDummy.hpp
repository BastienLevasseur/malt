/*****************************************************
             PROJECT  : MALT
             VERSION  : 1.2.0
             DATE     : 03/2020
             AUTHOR   : Valat Sébastien
             LICENSE  : CeCILL-C
*****************************************************/

#ifndef MALT_MUTEX_DUMMY_HPP
#define MALT_MUTEX_DUMMY_HPP

/*******************  NAMESPACE  ********************/
namespace MALT
{

/*********************  CLASS  **********************/
struct LockDummy
{
	LockDummy(void) {};
	~LockDummy(void) {};
	void lock(void) {};
	void unlock(void) {};
	bool tryLock(void) {return true;};
};

}

#endif //MALT_MUTEX_DUMMY_HPP
