#include "DummyLocationTranslater.hpp"
#include <algorithm>
#include <cassert>
#include <set>

namespace MALT{


PythonLocationTranslater::PythonLocationTranslater(){
    this->translationMap = std::map<PythonLocation, UniqueID>();
    //TODO: Make another map: UniqueID -> PythonLocation*
    //TODO: Fill it just before the resolve

    this->uniqueID = 0;
}


PythonLocationTranslater::~PythonLocationTranslater(void){
    ;
}

void PythonLocationTranslater::insertLocations(const PythonAllocatorDomainType& domain, const std::vector<PythonLocation>& locationVector){

    for (auto& locationIterator : locationVector){

        auto emplacePair = this->translationMap.emplace(locationIterator, this->uniqueID);

        if (emplacePair.second == true){
            /* If true then this location was never visited before, we return a new UniqueID */
            this->uniqueID++;
        }else{
            /* Else, this location has been visited before, we return some other UniqueID */
            assert(locationIterator == emplacePair.first->first);
        }
    }
    std::cout << "Location inserted" << std::endl;
}


//TODO: Make function GetID(PythonLocation) 

void PythonLocationTranslater::ensureIDsAreUnique(){
    std::set<UniqueID> idSet;

    for (auto& mapIterator : this->translationMap){
        auto pairInsert = idSet.insert(mapIterator.second);
        assert(pairInsert.second == true);
    }
}


std::ostream& operator << (std::ostream &out, PythonLocationTranslater& locationTranslater){
    std::stringstream ans;

    ans << "Size : " << locationTranslater.translationMap.size() << "\n";

    for (auto& mapIterator : locationTranslater.translationMap){
        ans << mapIterator.first << " --> " << mapIterator.second << "\n";
    }

	out << ans.str();
	return out;
}

}