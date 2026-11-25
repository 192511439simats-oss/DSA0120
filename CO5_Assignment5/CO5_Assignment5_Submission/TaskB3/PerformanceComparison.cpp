#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct BillData { int type; double a, b; };
double switchTotal(const BillData& b) {
    switch (b.type) {
        case 0: return b.a + b.b;
        case 1: return b.a * 3 + b.b;
        case 2: return b.a;
        default: return b.a + b.b * 4;
    }
}
class Bill {
public:
    virtual ~Bill() = default;
    virtual double total() const = 0;
};
class OP final : public Bill {
    double a,b;
public: OP(double x,double y):a(x),b(y){}
    double total()const override{return a+b;}
};
class IP final : public Bill {
    double a,b;
public: IP(double x,double y):a(x),b(y){}
    double total()const override{return a*3+b;}
};
class DayCare final : public Bill {
    double a;
public: explicit DayCare(double x):a(x){}
    double total()const override{return a;}
};
class Emergency final : public Bill {
    double a,b;
public: Emergency(double x,double y):a(x),b(y){}
    double total()const override{return a+b*4;}
}
;
int main(int argc,char**argv) {
    const std::size_t n=argc>1?static_cast<std::size_t>(std::stoull(argv[1])):1000000;
    std::vector<BillData> plain; plain.reserve(n);
    std::vector<std::unique_ptr<Bill>> polymorphic; polymorphic.reserve(n);
    for(std::size_t i=0;i<n;++i) {
        const int t=static_cast<int>(i%4);
        plain.push_back({t,100.0,25.0});
        if(t==0) polymorphic.push_back(std::make_unique<OP>(100,25));
        else if(t==1) polymorphic.push_back(std::make_unique<IP>(100,25));
        else if(t==2) polymorphic.push_back(std::make_unique<DayCare>(100));
        else polymorphic.push_back(std::make_unique<Emergency>(100,25));
    }
    volatile double checksum=0;
    auto s1=std::chrono::steady_clock::now();
    for(const auto& b:plain) checksum+=switchTotal(b);
    auto e1=std::chrono::steady_clock::now();
    auto s2=std::chrono::steady_clock::now();
    for(const auto& b:polymorphic) checksum+=b->total();
    auto e2=std::chrono::steady_clock::now();
    std::cout<<"Bills per design: "<<n<<"\n"
             <<"Switch total seconds: "<<std::chrono::duration<double>(e1-s1).count()<<"\n"
             <<"Virtual total seconds: "<<std::chrono::duration<double>(e2-s2).count()<<"\n"
             <<"Combined checksum: "<<checksum<<"\n";
}