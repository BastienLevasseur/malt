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
        void insertLocations(const PythonAllocatorDomainType& domain, const std::vector<PythonLocation>& locationVector);
        PythonLocation translateID(UniqueID uniqueID); //TODO: Implement

        void ensureIDsAreUnique();
        
        friend std::ostream& operator << (std::ostream &out, PythonLocationTranslater& locationTranslater);
        
    private:
        std::map<PythonLocation, UniqueID> translationMap;
        UniqueID uniqueID;
};

}



#endif //DummyLocationTranslater_hpp