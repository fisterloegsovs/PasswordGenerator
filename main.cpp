#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>

int main(){
    std::string alphanum = "0123456789!@#$%^&*_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int length = alphanum.size();

    int len = 0;
    do {
        std::cout << "Enter length of password: ";
        std::cin >> len;
        if (len < 10){
            std::cout << "Password must be at least 10 character long" << std::endl << "Try again." << std::endl;
        }
    } while(len < 10);

    srand(static_cast<unsigned int>(time(0)));
    std::cout << "Generated password: ";
    for(int i=0; i<len; i++){
        std::cout << alphanum[rand() % length];
    }   
    std::cout << std::endl;

    return 0;
}
