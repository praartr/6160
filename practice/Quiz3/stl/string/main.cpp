#include <iostream>
#include <string>
class Student {
public:
Student(const char* s) : name( new std::string(s)) {}
~Student() { delete name; }
Student(const Student& s) : name(new std::string(*(s.name))) {}
const std::string& getName() const {return *name;}
void setName(const char* n) {(*name) = n;}
private:
std::string * name;
};

int main() {
Student student("Dragonborn");
Student teacher(student);
//teacher.setName("Dovahkiin");
std::cout << teacher.getName() << std::endl;
//std::cout << student.getName() << std::endl;
/*std::string Earth="earth", Venus="venus";
std::cout << Earth+Venus << std::endl;
std::cout << (Venus < Earth) << std::endl;
//const char* c = "mercury";
std::string Mercury("Mercury");
std::cout << Mercury << std::endl;
*/
}
