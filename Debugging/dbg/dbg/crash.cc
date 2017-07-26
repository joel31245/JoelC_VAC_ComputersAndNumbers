#include <iostream>

using namespace std;  



int divint(int, int);  


int main() 
{ 
   

	int x = 5, y = 2; 
   
	cout << divint(x, y); 
   
   
	x =3; y = 0; 
   
	cout << divint(x, y); 
   
   
	return 0; 

}  


int divint(int a, int b) 
{ 
   
	if (b==0){ cout << "Divide by 0. Error."; return 0; }
	return a / b; 

}   
