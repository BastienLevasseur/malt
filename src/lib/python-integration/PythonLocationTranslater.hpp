#ifndef DummyLocationTranslater_hpp
#define DummyLocationTranslater_hpp

#include <map>
#include <vector>
#include "PythonLocation.hpp"
#include "PythonAllocatorDomainType.hpp"


namespace MALT{

typedef size_t UniqueID; 

class PythonLocationTranslater {

    public:
        PythonLocationTranslater();
        ~PythonLocationTranslater(void);
        UniqueID insertLocation(PythonLocation& location);

        void fillTranslationMap();
        PythonLocation translateID(UniqueID& uniqueID);

        void ensureIDsAreUnique();

        bool containsLocation(PythonLocation& location);
        
        friend std::ostream& operator << (std::ostream &out, PythonLocationTranslater& locationTranslater);
        
    private:
        std::map<PythonLocation, UniqueID> mapLocToID;
        std::map<UniqueID, PythonLocation> mapIDToLoc;
        bool mapIDToLocFilled;
        UniqueID uniqueID;
};

}



#endif //DummyLocationTranslater_hpp