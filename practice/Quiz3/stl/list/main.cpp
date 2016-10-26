#include <iostream>
#include <vector>
#include <list>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <string>
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

void insert(std::list<Planets*> &poke) {
std::vector<std::string> names;
names.reserve(5);
init(names);
for(unsigned int i=0;i<5;i++)
poke.push_back(new Planets(names[i],i));

}

void print(const std::list<Planets*>& pokedex) {

std::list<Planets*>::const_iterator iter = pokedex.begin();

 while(iter != pokedex.end()) {
 std::cout << *iter << std::endl;
 ++iter;
 
 }
}
class SortFunctor {

public:
bool operator()(const Planets* lhs, const Planets* rhs) const{
 return lhs->getName() < rhs->getName();
}

};

class FindFunctor {

public:
FindFunctor(const std::string& n): nameToFind(n){}
bool operator()(const Planets* p){
return nameToFind == p->getName();
}
private: 
std::string nameToFind;

};
int main() {
std::list<Planets*> pokedex;
insert(pokedex);
print(pokedex);
pokedex.sort(SortFunctor());
std::list<Planets*>::iterator ptr 
         = std::find_if(pokedex.begin(), pokedex.end(), FindFunctor(std::string("Venus")));
pokedex.erase(ptr);
print(pokedex);
}
