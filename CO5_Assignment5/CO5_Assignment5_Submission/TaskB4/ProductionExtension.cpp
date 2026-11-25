#include <iostream>
#include <memory>
#include <vector>
#include <string>
class Bill{
public:virtual ~Bill()=default;virtual double total()const=0;virtual std::string type()const=0;
};
class OutPatientBill:public Bill{
    double c,t;
public:OutPatientBill(double x,double y):c(x),t(y){}
    double total()const override{return c+t;}std::string type()const override{return "OP";}
};
class TelemedicineBill:public Bill{
    double consultation,platformFee;
public:TelemedicineBill(double c,double f):consultation(c),platformFee(f){}
    double total()const override{return consultation+platformFee;}
    std::string type()const override{return "Telemedicine";}
};
class Payer{public:virtual ~Payer()=default;virtual double covered(const Bill&)const=0;};
class SelfPay:public Payer{public:double covered(const Bill&b)const override{return b.total();}};
class CorporatePayer:public Payer{
    double rate;
public:explicit CorporatePayer(double r):rate(r){}
    double covered(const Bill&b)const override{return b.total()*rate/100.0;}
};
int main(){
    std::vector<std::unique_ptr<Bill>> bills;
    bills.push_back(std::make_unique<OutPatientBill>(500,1200));
    bills.push_back(std::make_unique<TelemedicineBill>(800,100));
    SelfPay self;CorporatePayer corporate(85);
    for(const auto& b:bills)
        std::cout<<b->type()<<" total "<<b->total()
                 <<" | corporate cover "<<corporate.covered(*b)
                 <<" | self pay "<<self.covered(*b)<<'\n';
}