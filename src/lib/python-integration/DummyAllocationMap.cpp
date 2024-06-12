#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cassert>

#include "DummyAllocationMap.hpp"


DummyAllocationMap::DummyAllocationMap(){
	this->allocMap = std::map<size_t, size_t>();
}

DummyAllocationMap::~DummyAllocationMap(void){
	;
}

void DummyAllocationMap::insertAlloc(size_t allocSize){
	auto iterator = this->allocMap.find(allocSize);

	if(iterator != this->allocMap.end()){
		iterator->second++;
	}else{
		this->allocMap.emplace(allocSize, 1UL);
	}
}


std::string DummyAllocationMap::getTop(const char* domain) const {
	std::stringstream ans;
	std::vector<int> printed;

	size_t topLimit = 20;
	if (this->allocMap.size() < topLimit){
		topLimit = this->allocMap.size();
	}

	ans << "~~~~ Top allocation sizes : " << domain << " ~~~~\n";

	//FIXME : Find a better way to sort by values descending, maybe use a std::multimap? 
	while(printed.size() != topLimit){
		size_t maxCandidateValue = 0;
		size_t maxCandidateSize = 0;

		for (auto& iterator : this->allocMap){
			if((iterator.second > maxCandidateValue) && (std::find(printed.begin(), printed.end(), iterator.first) == printed.end())){
				maxCandidateValue = iterator.second;
				maxCandidateSize = iterator.first;
			}
		}

		//assert(maxCandidateValue != 0);
		//assert(maxCandidateSize != 0);
		printed.push_back(maxCandidateSize);

		ans << maxCandidateSize << " bytes : " << maxCandidateValue << " allocation(s)\n";
	}
	ans << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	

	return ans.str();
}
