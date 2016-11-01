#include <iostream>
#include <vector>
#include <list>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <map>
class Planets {

public:

Planets(const std::string& n, unsigned int v) : name(n), value(v) {}
const std::string& getName() const{
 return name;
}
private:
std::string name;
unsigned int value;

};
std::ostream& operator<<(std::ostream& out, const Planets* p) {
return out << p->getName() ;

}
void init(std::vector<std::string>& names) {
names.push_back("Mercury");
names.push_back("Venus");
names.push_back("Earth");
names.push_back("Mars");
names.push_back("Jupiter");
}

void insert(std::map<std::string,int> &poke) {
poke["Earth"]=1;
poke["Mercury"]=2;
poke["Venus"]=3;
}

void print(const std::map<std::string,int>& pokedex) {

std::map<std::string,int>::const_iterator iter = pokedex.begin();

 while(iter != pokedex.end()) {
 std::cout << iter->first << std::endl;
 std::cout << iter->second << std::endl;
 ++iter;
 
 }
}
/*class SortFunctor {

public:
bool operator()(const Planets* lhs, const Planets* rhs) const{
 return lhs->getName() < rhs->getName();
}

};

class FindFunctor {

public:
FindFunctor(const std::string& n): nameToFind(n){}
bool operator()(const){
return nameToFind == p->getName();
}
private: 
std::string nameToFind;

};*/
int main() {
std::map<std::string, int> pokedex;
insert(pokedex);
print(pokedex);
//pokedex.sort(SortFunctor());
std::map<std::string,int>::iterator ptr 
         = pokedex.find("Venus");
//print(pokedex);
if(ptr!=pokedex.end())
pokedex.erase(ptr);
print(pokedex);
}
