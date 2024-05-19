#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>

class Calculator{
public:
    template<typename T1,typename T2>
    double addition(T1 a, T2 b) {
        return a+b;
    }

    template<typename T1,typename T2>
    double subtraction(T1 a,T2 b) {
        return addition(a,-b);
    }

    template<typename T1,typename T2>
    double division(T1 a,T2 b) {
        try {
            if (b) return a/b;
            else throw std::runtime_error("Division by 0 error");
        } catch (const std::exception& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
            std::cout << "Reenter vals: ";
            std::pair<T1,T2> z;
            z = getvals(2);
            return division(z.first,z.second);
        }
    }

    template<typename T1,typename T2>
    double multiplication(T1 a,T2 b){
        return a*b;
    }

    template<typename T1>
    double square(T1 a){
        return multiplication(a,a);
    }

    template<typename T1, typename T2>
    double exponentiation(T1 a, T2 b){
        return (T1)pow(a,b);
    }

    template<typename T1, typename T2>
    double modulus(T1 a, T2 b) {
        if (b) return subtraction(a,multiplication(int(division(a,b)),b));
        else return a;
    }

    std::pair<double,double> getvals(int a){

        try {
            std::string i;
            std::getline(std::cin, i);
            std::stringstream ss(i);
            std::vector<std::string> subs;
            std::string sub;
            while (std::getline(ss, sub, ' ')) {
                if (sub!="")
                    subs.push_back(sub);
            }
            if (subs.size()!=a) {throw std::runtime_error("Incorrect input count");}
            else if (a==1) return std::make_pair(std::stod(subs[0]),1.0f);
            else return std::make_pair(std::stod(subs[0]),std::stod(subs[1]));
        } catch (const std::exception& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
            std::cout << "Reenter val(s): ";

        }
        return getvals(a);
    }

};