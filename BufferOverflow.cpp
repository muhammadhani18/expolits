#include <iostream>
#include <cstring>
using namespace std;

int main( void )
{
 int authentication = 0;
 char cUsername[ 10 ];
 char cPassword[ 10 ];

 cout << "Username: ";
 cin >> cUsername;

 cout << "Pass: ";
 cin >> cPassword;

 if( strcmp( cUsername, "admin" ) == 0 && strcmp( cPassword, "adminpass" ) == 0 )
 {
  authentication = 1;
 }
 if( authentication )
 {
  cout << "Access granted\n";
  cout << ( char )authentication;
 }
 else
 {
  cout << "Wrong username and password\n";
 }
 return 0;
}
