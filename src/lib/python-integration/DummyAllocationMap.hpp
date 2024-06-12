#ifndef DummyAllocationMap_hpp
#define DummyAllocationMap_hpp

#include <map>

/* A dummy map that maps size -> nbOccurences, will replace by MALT own implementation */
class DummyAllocationMap {
    private:
        std::map<size_t, size_t> allocMap;

    public:
        DummyAllocationMap();
        ~DummyAllocationMap(void);

        void insertAlloc(size_t allocSize);

        std::string getTop(const char* domain) const;
};

#endif //allocationMap_hpp