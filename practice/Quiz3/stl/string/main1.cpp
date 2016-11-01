#include<iostream>
class string {
public:
string()             { std::cout << "default " << std::endl; }
string(const char*)  { std::cout << "convert" << std::endl; }
string(const string&) { std::cout << "copy" << std::endl; }
~string()            { std::cout << "destructor" << std::endl;}
string& operator=(const string&) { std::cout << "assign" << std::endl; return *this; }

};

void function(string param)
{
std::cout << "inside finction" << std::endl;
param = "dog";
}

int main()
{
string x("cat");
function(x);
}
