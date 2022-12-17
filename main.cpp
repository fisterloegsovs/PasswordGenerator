#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

const char alphanum[] = "0123456789!@#$%^&*_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
int length = sizeof(alphanum);

int main(){
    int len = 0;
    cout << "Enter length of password: ";
    cin >> len;
    if (len<10){
        cout << "Password must be at least 10 character long\n" << "Try again.\n";
        main();
    } else {
        srand(time(0));
        cout << "Generated password: ";
        for(int i=0; i<len; i++){
            cout << alphanum[rand() % length];
        }   
    cout << "\n";
    }
    
    return 0;
}