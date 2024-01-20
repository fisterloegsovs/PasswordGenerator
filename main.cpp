#include<iostream>
#include<string>
#include<limits>
#include<random>

std::string numbers = "0123456789";
std::string special_chars = "!@#$%^&*_";
std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int getPasswordLength() {
    int len = 0;
    do {
        std::cout << "Enter length of password: ";
        if (!(std::cin >> len)) {
            std::cout << "You must enter a valid integer." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (len < 10){
            std::cout << "Password must be at least 10 character long" << std::endl << "Try again." << std::endl;
        }
    } while(len < 10);
    return len;
}

char getUserChoice(const std::string& prompt) {
    char choice;
    do {
        std::cout << prompt;
        std::cin >> choice;
        if (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
            std::cout << "You must enter y or n." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');
    return choice;
}

void generatePasswords(const std::string& alphanum, int len) {
    std::random_device rd;
    std::mt19937 g(rd());

    int n;

    std::cout << "How many passwords do you want to generate? ";
    std::cin >> n;

    std::cout << "Generating " << n << " passwords..." << std::endl << std::endl;

    for (int j = 0; j < n; j++) {
        std::cout << "Generated password: ";
        for(int i=0; i<len; i++){
            std::uniform_int_distribution<int> dist(0, alphanum.size() - 1);
            std::cout << alphanum[dist(g)];
        }   
        std::cout << std::endl;
    }
}

int main(){
    std::string alphanum = "";
    int len = getPasswordLength();

    if(getUserChoice("Include numbers? (y/n): ") == 'y' || 'Y'){
        alphanum += numbers;
    }

    if(getUserChoice("Include special characters? (y/n): ") == 'y' || 'Y'){
        alphanum += special_chars;
    }

    if(getUserChoice("Include lowercase letters? (y/n): ") == 'y' || 'Y'){
        alphanum += lowercase;
    }

    if(getUserChoice("Include uppercase letters? (y/n): ") == 'y' || 'Y'){
        alphanum += uppercase;
    }

    std::cout << std::endl;

    generatePasswords(alphanum, len);

    return 0;
}
