#include "sgn.h"

int main()
{

     SGN x1
        ,x2((char*)"556")
        ,x3(-556)
        ,x4(37888888);
     x1=x2-x3;
     x4=x4-x2;
     x4.print();

}
