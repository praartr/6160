#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <string>

class Planets {
public:
Planets(const std::string& str, unsigned int i) : name(str), value(i){}
~Planets() {std::cout << "inside destructor" << std::endl;}
Planets(const Planets& p) {std::cout << " inside copy " << std::endl;}
Planets* operator=(const Planets& p) {std::cout << "inside assign" << std::endl;}
const std::string& getName()const {return name;}
private:
std::string name;
unsigned int value;

};

void insert(std::vector<std::string>& names) {

names.push_back("Earth");
names.push_back("Venus");
names.push_back("Mercury");

}
void init(std::vector<Planets*>& planet ) {
std::vector<std::string> names;
names.reserve(5);
insert(names);
planet.reserve(5);
for(unsigned int i=0;i<3;i++)
planet.push_back(new Planets(names[i],i));

}
void print(const std::vector<Planets*>& planet) {
std::vector<Planets*>::const_iterator ptr = planet.begin();
while(ptr != planet.end()) {
std::cout << (*ptr)->getName() << ",";
++ptr;
}
}

class SortClass {
public:
bool operator()(const Planets* lhs, const Planets* rhs) const {
return lhs->getName() < rhs->getName();
}

};

class FindClass {
public: 
FindClass(const std::string& n) : nameToFind(n) {}
bool operator()(const Planets* p) const {
return nameToFind == p->getName();
}
private:
std::string nameToFind;
};
int main() {
std::vector<Planets*> planet;
init(planet);
print(planet);
sort(planet.begin(), planet.end(), SortClass());

print(planet);
std::vector<Planets*>::iterator ptr = 
find_if(planet.begin(), planet.end(),FindClass(std::string("Mercury")));
if(ptr != planet.end())
planet.erase(ptr);
else
std::cout << "aint there" << std::endl;
print(planet);
}
