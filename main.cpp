#include <iostream>
#include "include/Company.hpp"

using namespace std;

Company* cmp1;
Company* cmp2;
int main()
{
    cmp1 = new Company;
    cmp1->initialize();
    //cmp1.printStationStatus();
    cmp1->execute_part1();
    delete cmp1;
    
    cmp2 = new Company;
    cmp2->initialize();
    cmp2->execute_part2();
    delete cmp2;

    return 0;
}
//latest version