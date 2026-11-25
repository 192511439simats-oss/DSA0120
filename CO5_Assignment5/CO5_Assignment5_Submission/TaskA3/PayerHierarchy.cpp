#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>

class Bill {
public:
    virtual ~Bill()=default;
    virtual double total() const=0;
    virtual std::string type() const=0;
};
class OutPatientBill:public Bill {
    double consultation,tests;
public:
    OutPatientBill(double c,double t):consultation(c),tests(t){}
    double total()const override{return consultation+tests;}
    std::string type()const override{return "OP";}
};
class InPatientBill:public Bill {
    int days;double rate,procedure;
public:
    InPatientBill(int d,double r,double p):days(d),rate(r),procedure(p){}
    double total()const override{return days*rate+procedure;}
    std::string type()const override{return "IP";}
};
class Payer {
public:
    virtual ~Payer()=default;
    virtual double amountCovered(const Bill& bill)const=0;
};
class SelfPay:public Payer {
public: double amountCovered(const Bill& b)const override{return b.total();}
};
class Insurance:public Payer {
    double limit,coPayPercent;
public:
    Insurance(double l,double c):limit(l),coPayPercent(c){}
    double amountCovered(const Bill& b)const override {
        return std::min(limit,b.total()*(100.0-coPayPercent)/100.0);
    }
};
class GovernmentScheme:public Payer {
    double opPackage,ipPackage;
public:
    GovernmentScheme(double op,double ip):opPackage(op),ipPackage(ip){}
    double amountCovered(const Bill& b)const override {
        return b.type()=="OP"?std::min(opPackage,b.total()):std::min(ipPackage,b.total());
    }
};
// Extension example: a corporate payer can be added as a new derived class.
class CorporateTieUp:public Payer {
    double percentage;
public:
    explicit CorporateTieUp(double p):percentage(p){}
    double amountCovered(const Bill& b)const override{return b.total()*percentage/100.0;}
};
int main(){
    OutPatientBill op(500,1200); InPatientBill ip(3,2500,40000);
    SelfPay self; Insurance insurance(30000,10); GovernmentScheme govt(1500,45000);
    CorporateTieUp corporate(80);
    std::cout<<"OP total "<<op.total()<<'\n';
    std::cout<<"Self-pay "<<self.amountCovered(op)<<'\n';
    std::cout<<"Insurance "<<insurance.amountCovered(ip)<<'\n';
    std::cout<<"Government OP "<<govt.amountCovered(op)<<'\n';
    std::cout<<"Corporate IP "<<corporate.amountCovered(ip)<<'\n';
}