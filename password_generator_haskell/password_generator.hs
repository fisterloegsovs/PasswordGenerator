module Main where

import System.IO (hFlush, stdout)
import Data.Char (isLower, isUpper, isDigit)
import Control.Monad (replicateM)
import System.Random (randomRIO)
import Text.Printf (printf)

numbers, specialChars, lowercaseLetters, uppercaseLetters :: String
numbers        = "0123456789"
specialChars   = "!@#$%^&*_"
lowercaseLetters = "abcdefghijklmnopqrstuvwxyz"
uppercaseLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

getPasswordLength :: IO Int
getPasswordLength = do
    putStr "Enter length of password: "
    hFlush stdout
    input <- getLine
    case reads input :: [(Int, String)] of
      [(len, "")] | len >= 10 -> return len
      _ -> do
           putStrLn "Password must be at least 10 characters long. Try again."
           getPasswordLength

getUserChoice :: String -> IO Char
getUserChoice prompt = do
    putStr prompt
    hFlush stdout
    input <- getLine
    case input of
      (c:_) | c `elem` "yYnN" -> return c
      _ -> do
         putStrLn "You must enter y or n."
         getUserChoice prompt

getNumberOfPasswords :: IO Int
getNumberOfPasswords = do
    putStr "How many passwords do you want to generate? "
    hFlush stdout
    input <- getLine
    case reads input :: [(Int, String)] of
      [(n, "")] | n > 0 -> return n
      _ -> do
           putStrLn "Please enter a valid positive integer."
           getNumberOfPasswords

calculatePasswordStrength :: String -> Int
calculatePasswordStrength password =
    let len = length password
        baseStrength | len >= 15 = 3
                     | len >= 10 = 2
                     | otherwise = 1
        hasLower  = any isLower password
        hasUpper  = any isUpper password
        hasDigit  = any isDigit password
        hasSpecial = any (\c -> not (isLower c || isUpper c || isDigit c)) password
        variety = sum [if hasLower then 1 else 0, if hasUpper then 1 else 0,
                       if hasDigit then 1 else 0, if hasSpecial then 1 else 0]
        consecutivePenalty = sum [ if password !! i == password !! (i - 1) then 1 else 0 
                                   | i <- [1 .. len - 1] ]
    in baseStrength + variety - consecutivePenalty

generatePassword :: String -> Int -> IO String
generatePassword charset len = replicateM len $ do
    idx <- randomRIO (0, length charset - 1)
    return (charset !! idx)

generatePasswords :: String -> Int -> IO ()
generatePasswords alphanum len = do
    numPasswords <- getNumberOfPasswords
    putStrLn $ "\nGenerating " ++ show numPasswords ++ " passwords...\n"
    -- Print table header
    printf ("%-" ++ show len ++ "s | %-10s\n") "Password" "Strength"
    putStrLn $ replicate (len + 13) '-'
    sequence_ [ do
                   pwd <- generatePassword alphanum len
                   let strength = calculatePasswordStrength pwd
                   printf ("%-" ++ show len ++ "s | %-10d\n") pwd strength
              | _ <- [1..numPasswords] ]

main :: IO ()
main = do
    len <- getPasswordLength
    putStrLn ""
    includeNumbers  <- getUserChoice "Include numbers? (y/n): "
    includeSpecial  <- getUserChoice "Include special characters? (y/n): "
    includeLower    <- getUserChoice "Include lowercase letters? (y/n): "
    includeUpper    <- getUserChoice "Include uppercase letters? (y/n): "
    let alphanum = concat [ if includeNumbers `elem` "yY" then numbers else ""
                          , if includeSpecial `elem` "yY" then specialChars else ""
                          , if includeLower `elem` "yY" then lowercaseLetters else ""
                          , if includeUpper `elem` "yY" then uppercaseLetters else ""
                          ]
    putStrLn ""
    generatePasswords alphanum len
    putStrLn ""
    putStrLn "Next to each password is a number indicating its strength."
    putStrLn "Copy and paste your password(s) to a safe location."
    putStr "Press ENTER to exit..."
    hFlush stdout
    _ <- getLine
    return ()