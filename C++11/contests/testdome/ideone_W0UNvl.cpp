#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map>

class AreAnagrams
{
public:
	static bool areStringsAnagrams(std::string a, std::string b)
	{
        if( a.size() != b.size() )
            return false;
        
        std::unordered_map<char,int> map;
		for( auto idx = 0; idx < a.size() ; ++idx  )
        {
            if( map.count( a[idx]) )
            {
                map[a[idx]] += 1;   
            }
            else
            {
                map[a[idx]] = 1;
            }
            std::cout << "map[" << a[idx] << "]: " << map[a[idx]] <<std::endl;
        }   
		
		for( auto idx = 0; idx < b.size() ; ++idx  )
        {
            if( map.count( b[idx]) )
            {
                map[b[idx]] -= 1;   
            }
            else
            {
                return false;
            }
            std::cout << "map[" << b[idx] << "]: " << map[b[idx]] <<std::endl;
      	}
        
        for( auto & kvpair: map )
        {
            if( kvpair.second != 0 )
            {
                return false;
            }
        }
        
        return true;
    }
};

int main(int argc, const char* argv[])
{
	std::cout << AreAnagrams::areStringsAnagrams("momdad", "dadmom");
	return 0;
}