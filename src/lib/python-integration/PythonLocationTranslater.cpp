#include "PythonLocationTranslater.hpp"
#include <algorithm>
#include <cassert>
#include <set>

namespace MALT{


PythonLocationTranslater::PythonLocationTranslater(){
    this->mapLocToID = std::map<PythonLocation, UniqueID>();
    this->mapIDToLoc = std::map<UniqueID, PythonLocation>();
    this->mapIDToLocFilled = false;
    this->uniqueID = 0;
}


PythonLocationTranslater::~PythonLocationTranslater(void){
    ;
}

void PythonLocationTranslater::insertLocation(const PythonLocation& location){

    auto emplacePair = this->mapLocToID.emplace(location, this->uniqueID);

    if (emplacePair.second == true){
        /* If true then this location was never visited before, we return a new UniqueID */
        this->uniqueID++;
    }else{
        /* Else, this location has been visited before, we return some other UniqueID */
        assert(location == emplacePair.first->first);
    }
    
}


void PythonLocationTranslater::fillTranslationMap(){
    for (auto& mapIterator : this->mapLocToID){
        auto emplacePair = this->mapIDToLoc.emplace(mapIterator.second, mapIterator.first);
        assert(emplacePair.second == true);
    }
    this->mapIDToLocFilled = true;
}


PythonLocation PythonLocationTranslater::translateID(UniqueID& uniqueID){
    if (this->mapIDToLocFilled == false){
        this->fillTranslationMap();
    }

    auto loc = this->mapIDToLoc.find(uniqueID);
    assert(loc != this->mapIDToLoc.end());

    return loc->second;
}

void PythonLocationTranslater::ensureIDsAreUnique(){
    std::set<UniqueID> idSet;

    for (auto& mapIterator : this->mapLocToID){
        auto pairInsert = idSet.insert(mapIterator.second);
        assert(pairInsert.second == true);
    }
}


std::ostream& operator << (std::ostream &out, PythonLocationTranslater& locationTranslater){
    std::stringstream ans;

    ans << "Size : " << locationTranslater.mapLocToID.size() << "\n";

    for (auto& mapIterator : locationTranslater.mapLocToID){
        ans << mapIterator.first << " --> " << mapIterator.second << "\n";
    }

	out << ans.str();
	return out;
}

}