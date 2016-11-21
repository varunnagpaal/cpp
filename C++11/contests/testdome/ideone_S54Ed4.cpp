#include <stdexcept>
#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <cstdint>

class TwoSum
{
public:
    static std::pair<uint64_t, uint64_t> findTwoSum( const std::vector<uint64_t>& list, uint64_t sum )
    {
        std::pair<uint64_t, uint64_t> result( -1, -1 );
        if ( list.size() > 2 )
        {
            std::unordered_map<uint64_t, uint64_t> map;
            for ( auto i = 0; i < list.size(); ++i )
            {
                uint64_t firstpart = list[i];
                uint64_t secondpart = sum - firstpart;

                std::cout << "(" << firstpart << ", " << secondpart << ") " << std::endl;

                // Check if key-value pair corresponding to key(second-part) already exist
                // i.e. we have already visited the second part before as first part
                if ( map.count( secondpart ) )
                {
                    result.first = map[secondpart];
                    result.second = i;
                    break;
                }

                // Add firstpart as key with value as its index in list
                // this registers that we have visited this element
                map[firstpart] = i;
            }
        }
        return result;
    }
};


int main( int argc, const char* argv[] )
{
    std::vector<uint64_t> list;
    list.push_back( 1 );
    list.push_back( 3 );
    list.push_back( 5 );
    list.push_back( 7 );
    list.push_back( 9 );

    std::pair<uint64_t, uint64_t> indices = TwoSum::findTwoSum( list, 12 );
    std::cout << indices.first << '\n' << indices.second;

    return 0;
}