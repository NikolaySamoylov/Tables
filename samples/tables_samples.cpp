#include "tables.h"



int main()
{
  /*  OrderedTable<> t;
    Monomial m1(1, 111);
    Monomial m2(2, 222);
    Monomial m3(3, 333);
    Monomial m4(5, 242);
    Monomial m5(98, 321);
    Monomial m6(8, 384);
    Polynomial p1;
    Polynomial p2;
    Polynomial p3;
    p1.push_back(m1);
    p2.push_back(m3);
    p3.push_back(m2);
    t.insert(1, p1);
    t.insert(3, p2);
    t.insert(2, p3);
    t.print(); */

    HashTable<> t(2);
    Monomial m1(1, 111);
    Monomial m2(2, 222);
    Monomial m3(3, 333);
    Monomial m4(5, 242);
    Polynomial p1;
    Polynomial p2;
    p1.push_back(m1);
    p1.push_back(m2);
    p2.push_back(m3);
    p2.push_back(m4);
    t.insert(1, p1);
    t.insert(20867, p2);
  return 0;
}