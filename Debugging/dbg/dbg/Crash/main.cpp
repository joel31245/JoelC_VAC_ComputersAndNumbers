#include <iostream>
//$g++ -g crash.cc -o crash


using namespace std;

int divint(int, int);
int main()
{
   int x = 5, y = 2;
   cout << divint(x, y);

   x =3; y = 0;
   if ( y!=0 )
        cout << divint(x, y);
   else
        cout << "\ninvalid entry - divide by 0";

   return 0;
}

int divint(int a, int b)
{
   return a / b;
}
