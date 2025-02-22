#include<iostream>
#include<string>
#include<limits>
#include<random>
#include <iomanip>

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

int calculatePasswordStrength(const std::string& password) {
    int strength = 0;

    // Length
    if (password.length() >= 15) strength += 3;
    else if (password.length() >= 10) strength += 2;
    else strength += 1;

    // Character Variety
    bool hasLowercase = false, hasUppercase = false, hasDigit = false, hasSpecialChar = false;
    for (char c : password) {
        if (std::islower(c)) hasLowercase = true;
        else if (std::isupper(c)) hasUppercase = true;
        else if (std::isdigit(c)) hasDigit = true;
        else hasSpecialChar = true;
    }
    strength += hasLowercase + hasUppercase + hasDigit + hasSpecialChar;

    // Repetition and Consecutive Characters
    for (size_t i = 1; i < password.length(); i++) {
        if (password[i] == password[i-1]) strength -= 1; // Consecutive characters
    }

    return strength;
}

void generatePasswords(const std::string& alphanum, int len) {
    std::random_device rd;
    std::mt19937 g(rd());

    int numPasswords = getNumberOfPasswords();

    std::cout << "Generating " << numPasswords << " passwords..." << std::endl << std::endl;

    // Print table header
    std::cout << std::left << std::setw(len) << "Password" << " | " << std::setw(10) << "Strength" << std::endl;
    std::cout << std::string(len + 13, '-') << std::endl;

    for (int j = 0; j < numPasswords; j++) {
        std::string password = "";
        for(int i=0; i<len; i++){
            std::uniform_int_distribution<int> dist(0, alphanum.size() - 1);
            password += alphanum[dist(g)];
        }   
        int strength = calculatePasswordStrength(password);
        // Print password and strength in table format
        std::cout << std::left << std::setw(len) << password << " | " << std::setw(10) << strength << std::endl;
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
    std::cout << "Next to each password is a number indicating its strength." << std::endl;
    std::cout << "Copy and paste your password(s) to a safe location." << std::endl;
    std::cout << "Press ENTER to exit...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::cin.get();


    return 0;
}
