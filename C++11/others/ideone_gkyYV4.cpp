#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() // count the number of occurrences of each word on input
{
map<string,int> buf;
for (string s; cin>>s;) ++buf[s];
for (const auto& x : buf)
cout << x.first << ": " << x.second << '\n';
return 0;
}