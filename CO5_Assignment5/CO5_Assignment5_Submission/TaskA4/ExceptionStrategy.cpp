#include <iostream>
#include <stdexcept>
#include <string>
class BillingError:public std::runtime_error{public:using std::runtime_error::runtime_error;};
class ClaimError:public BillingError{public:using BillingError::BillingError;};
class MissingPatientError:public BillingError{public:using BillingError::BillingError;};
double validateCharge(double amount){
    if(amount<0)throw std::invalid_argument("negative charge");
    if(amount>1000000)throw std::out_of_range("charge exceeds limit");
    return amount;
}
double approveClaim(double billed,double cover){
    if(billed<0||cover<0)throw std::invalid_argument("negative amount");
    if(billed>cover)throw ClaimError("claim exceeds policy cover");
    return billed;
}
int main(){
    for(double value:{500.0,-5.0,2000000.0}){
        try{std::cout<<"validated "<<validateCharge(value)<<'\n';}
        catch(const std::exception& e){std::cout<<"rejected: "<<e.what()<<'\n';}
    }
    try{approveClaim(60000,50000);}
    catch(const ClaimError& e){std::cout<<"claim error: "<<e.what()<<'\n';}
}