use std::io::{self, Write};
use std::num::ParseIntError;
use rand::Rng;

const NUMBERS: &str = "0123456789";
const SPECIAL_CHARS: &str = "!@#$%^&*_";
const LOWERCASE: &str = "abcdefghijklmnopqrstuvwxyz";
const UPPERCASE: &str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

fn get_password_length() -> usize {
    loop {
        print!("Enter length of password: ");
        io::stdout().flush().unwrap();
        let mut input = String::new();
        if io::stdin().read_line(&mut input).is_err() {
            continue;
        }
        match input.trim().parse::<usize>() {
            Ok(len) if len >= 10 => return len,
            _ => {
                println!("Password must be at least 10 characters long. Try again.");
            }
        }
    }
}

fn get_user_choice(prompt: &str) -> char {
    loop {
        print!("{}", prompt);
        io::stdout().flush().unwrap();
        let mut input = String::new();
        if io::stdin().read_line(&mut input).is_err() {
            continue;
        }
        if let Some(choice) = input.trim().chars().next() {
            if choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N' {
                return choice;
            }
        }
        println!("You must enter y or n.");
    }
}

fn get_number_of_passwords() -> usize {
    loop {
        print!("How many passwords do you want to generate? ");
        io::stdout().flush().unwrap();
        let mut input = String::new();
        if io::stdin().read_line(&mut input).is_err() {
            continue;
        }
        match input.trim().parse::<usize>() {
            Ok(n) if n > 0 => return n,
            _ => println!("Please enter a valid positive integer."),
        }
    }
}

fn calculate_password_strength(password: &str) -> i32 {
    let mut strength = 0;
    let len = password.len();

    // Length
    if len >= 15 {
        strength += 3;
    } else if len >= 10 {
        strength += 2;
    } else {
        strength += 1;
    }

    // Character Variety
    let mut has_lowercase = false;
    let mut has_uppercase = false;
    let mut has_digit = false;
    let mut has_special = false;

    for c in password.chars() {
        if c.is_lowercase() {
            has_lowercase = true;
        } else if c.is_uppercase() {
            has_uppercase = true;
        } else if c.is_digit(10) {
            has_digit = true;
        } else {
            has_special = true;
        }
    }

    strength += has_lowercase as i32 + has_uppercase as i32 + has_digit as i32 + has_special as i32;

    // Repetition and Consecutive Characters
    let chars: Vec<char> = password.chars().collect();
    for i in 1..chars.len() {
        if chars[i] == chars[i - 1] {
            strength -= 1;
        }
    }

    strength
}

fn generate_passwords(alphanum: &str, len: usize) {
    let num_passwords = get_number_of_passwords();
    println!("\nGenerating {} passwords...\n", num_passwords);

    // Prepare table header
    println!("{:<width$} | {:<10}", "Password", "Strength", width = len);
    println!("{}", "-".repeat(len + 13));

    let charset: Vec<char> = alphanum.chars().collect();
    let mut rng = rand::thread_rng();

    for _ in 0..num_passwords {
        let mut password = String::with_capacity(len);
        for _ in 0..len {
            let idx = rng.gen_range(0..charset.len());
            password.push(charset[idx]);
        }
        let strength = calculate_password_strength(&password);
        println!("{:<width$} | {:<10}", password, strength, width = len);
    }
}

fn main() {
    let mut alphanum = String::new();
    let len = get_password_length();
    println!();

    let include_numbers = get_user_choice("Include numbers? (y/n): ");
    if include_numbers == 'y' || include_numbers == 'Y' {
        alphanum.push_str(NUMBERS);
    }

    let include_special = get_user_choice("Include special characters? (y/n): ");
    if include_special == 'y' || include_special == 'Y' {
        alphanum.push_str(SPECIAL_CHARS);
    }

    let include_lowercase = get_user_choice("Include lowercase letters? (y/n): ");
    if include_lowercase == 'y' || include_lowercase == 'Y' {
        alphanum.push_str(LOWERCASE);
    }

    let include_uppercase = get_user_choice("Include uppercase letters? (y/n): ");
    if include_uppercase == 'y' || include_uppercase == 'Y' {
        alphanum.push_str(UPPERCASE);
    }

    println!();
    generate_passwords(&alphanum, len);
    println!();
    println!("Next to each password is a number indicating its strength.");
    println!("Copy and paste your password(s) to a safe location.");
    print!("Press ENTER to exit...");
    io::stdout().flush().unwrap();
    
    let mut exit_line = String::new();
    let _ = io::stdin().read_line(&mut exit_line);
}