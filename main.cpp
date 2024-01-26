#include<iostream>
#include<string>
#include<limits>
#include<random>
#include<ctime>

std::string numbers = "0123456789";
std::string special_chars = "!@#$%^&*_";
std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int getPasswordLength() {
    int len = 0;
    do {
        std::cout << "Enter length of password: ";
        if (!(std::cin >> len) || len < 10) {
            std::cout << "Password must be at least 10 characters long. Try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

int getNumberOfPasswords() {
    int n;
    do {
        std::cout << "How many passwords do you want to generate? ";
        if (!(std::cin >> n) || n <= 0) {
            std::cout << "Please enter a valid positive integer." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (n <= 0);
    return n;
}

void generatePasswords(const std::string& alphanum, int len) {
    if (alphanum.empty()) {
        std::cout << "No character sets selected. Exiting." << std::endl;
        return;
    }

    std::mt19937 g(time(0));

    int numPasswords = getNumberOfPasswords();

    std::cout << "Generating " << numPasswords << " passwords..." << std::endl << std::endl;

    for (int j = 0; j < numPasswords; j++) {
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

    std::cout << std::endl;

    char includeNumbers = getUserChoice("Include numbers? (y/n): ");
    if(includeNumbers == 'y' || includeNumbers == 'Y'){
        alphanum += numbers;
    }

    char includeSpecialChars = getUserChoice("Include special characters? (y/n): ");
    if(includeSpecialChars == 'y' || includeSpecialChars == 'Y'){
        alphanum += special_chars;
    } 

    char includeLowercase = getUserChoice("Include lowercase letters? (y/n): ");
    if(includeLowercase == 'y' || includeLowercase == 'Y'){
        alphanum += lowercase;
    }

    char includeUppercase = getUserChoice("Include uppercase letters? (y/n): ");
    if(includeUppercase == 'y' || includeUppercase == 'Y'){
        alphanum += uppercase;
    }

    std::cout << std::endl;

    generatePasswords(alphanum, len);

    std::cout << std::endl;
    std::cout << "Copy and paste your password(s) to a safe location." << std::endl;
    std::cout << "Press ENTER to exit...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::cin.get();


    return 0;
}
