#include <iostream>
#include <string>
struct Guard{
    std::string name;
    explicit Guard(std::string n):name(std::move(n)){}
    ~Guard(){std::cout<<'~'<<name<<' ';}
};
void f(){Guard g("f");throw 42;}
int main(){
    try{Guard m("main");f();std::cout<<"not printed ";}
    catch(int x){std::cout<<"caught "<<x;}
    std::cout<<'\n';
}