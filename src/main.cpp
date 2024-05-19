
#include <iostream>
#include "PointStructurePart1.h"
#include "CalculatorPart2.h"
#include "MatrixPart3.h"

int main() {

    // ----------------  P1: Point structure starts  ---------------------
//#define POINT
#ifdef POINT
    std::cout<<"Part 1: Point calculations\n\n\n";

    Point a = Point(1,2,3);
    Point b = Point(-1,-2,-1);
    a.print();
    b.print();
    std::cout << "distance between a and b is: " << a.distance(b) << std::endl;
    std::cout << "0 distances for both are " << a.zero_distance() << " " << b.zero_distance() << " accordingly\n";
    std::cout << "regions for a and b are" << a.region() << " " << b.region() <<std::endl;
    if (a.is_in_same_region(b))
        std::cout<< "they are both in the same region\n";
    else
        std::cout<< "they are not in the same region\n";

    if (a.region()==FIRST)
        std::cout<<"true\n"<<std::endl;
    if (b.region()==SECOND)
        std::cout<<"true\n"<<std::endl;

#endif


    // ----------------  P2: Calculator Class starts  ---------------------
//#define  CALC
#ifdef  CALC

    std::cout<<"\n\n\nPart 2: Calculator \n\n\n";


    Calculator x;
    std::cout<<"Choose Function\n\n";
    std::cout<<"1. Addition\n";
    std::cout<<"2. Substraction\n";
    std::cout<<"3. Division\n";
    std::cout<<"4. Multiplication\n";
    std::cout<<"5. Square\n";
    std::cout<<"6. Exponentiation\n";
    std::cout<<"7. Modulus\n";
    std::cout<<"8. Exit\n\n";
    std::string s;
    double i,j;
    bool r=true;

    while(r){

        while (true){
            std::cout<<"Enter Command: ";

            std::cin>>s;
            if (s.length()!=1 || s=="\n" || s==" "){
                std::cout<<"incorrect value\n\n";
                std::cout<<"Choose Function\n\n";
                std::cout<<"1. Addition\n";
                std::cout<<"2. Substraction\n";
                std::cout<<"3. Division\n";
                std::cout<<"4. Multiplication\n";
                std::cout<<"5. Square\n";
                std::cout<<"6. Exponentiation\n";
                std::cout<<"7. Modulus\n";
                std::cout<<"8. Exit\n\n";}
            else break;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::pair<double,double> pr;
        switch (s[0]) {
            case '1':
                std::cout<<"Enter 2 numbers to add: ";
                pr = x.getvals(2);
                i = pr.first;
                j = pr.second;
                std::cout<<"Result of addition: "<< x.addition(i,j) << std::endl;
                break;
            case '2':
                std::cout<<"Enter 2 numbers to substract: ";
                pr = x.getvals(2);
                i = pr.first;
                j = pr.second;
                std::cout<<"Result of substraction: "<< x.subtraction(i,j) << std::endl;
                break;
            case '3':
                std::cout<<"Enter 2 numbers to divide: ";
                pr = x.getvals(2);
                i = pr.first;
                j = pr.second;
                std::cout<<"Result of division: "<< x.division(i,j) << std::endl;
                break;
            case '4':
                std::cout<<"Enter 2 numbers to multiply: ";
                pr = x.getvals(2);
                i = pr.first;
                j = pr.second;
                std::cout<<"Result of multiplication: "<< x.multiplication(i,j) << std::endl;
                break;
            case '5':
                std::cout<<"Enter a number to get square of: ";
                pr = x.getvals(1);
                i = pr.first;
                std::cout<<"Result of square: "<< x.square(i) << std::endl;
                break;
            case '6':
                std::cout<<"Enter 2 number to exponentiate: ";
                pr = x.getvals(2);
                i = pr.first;
                j = pr.second;
                std::cout<<"Result of exponentiation: "<< x.exponentiation(i,j) << std::endl;
                break;
            case '7':
                std::cout<<"Enter 2 number2 to get modulus: ";
                pr = x.getvals(2);
                i = pr.first;
                j = pr.second;
                std::cout<<"Result of modulus: "<< x.modulus(i,j) << std::endl;
                break;
            case '8':
                r= false;
                std::cout<<"End of calculation\n\n";
                break;
            default:
                std::cout<<"incorrect value\n\n";
                std::cout<<"Choose Function\n\n";
                std::cout<<"1. Addition\n";
                std::cout<<"2. Substraction\n";
                std::cout<<"3. Division\n";
                std::cout<<"4. Multiplication\n";
                std::cout<<"5. Square\n";
                std::cout<<"6. Exponentiation\n";
                std::cout<<"7. Modulus\n";
                std::cout<<"8. Exit\n\n";
                break;
        }
    }

#endif


    // ----------------  P3: Matrix Class  ---------------------
//#define MATRIX
#ifdef MATRIX

    std::cout<<"\n\n\nPart 3: Matrix \n\n\n";

    matrix::Matrix<double> d({{1,1,1},{2,4,3}});
    matrix::Matrix<double> e({{1,2,3},{3,4,5}});

    std::cout<<d.dot(e)<<std::endl;

    matrix::Matrix<double> a({{1,2,3},{4,5,6}});
    matrix::Matrix<double> b({{7,8},{9,10},{11,12}});

    a.multiply(b).print();

    a.neg().print();
    a.neg();

    a.identity().print();

    a.transpose().print();

    std::cout<<a.trace()<<std::endl;





#endif
    return 0;
}
