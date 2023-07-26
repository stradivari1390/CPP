/**
 * @file ReverseStringStack.cpp
 * @brief This program collects user-input strings into a stack until the user enters "reverse".
 *        Then it prints out the strings in reverse order of entry.
 */

#include <iostream>
#include <string>
#include <stack>

int main() {
    std::stack<std::string> stringStack;
    std::string reverseKeyword = "reverse";

    std::cout << "\nPlease enter some strings. The program will collect the strings\n"
              << "until you enter the keyword \"reverse\". Then it will print out\n"
              << "the strings you have entered, but in reverse order. Please start entering strings now.\n";

    for(;;) {
        std::string inputString;
        std::cin >> inputString;
        if(inputString != reverseKeyword) {
            stringStack.push(inputString);
        } else {
            break;
        }
    }

    std::cout << "\nThe strings you entered (if any) in reverse order are:\n";
    while(!stringStack.empty()) {
        std::cout << stringStack.top() << "\n";
        stringStack.pop();
    }
    return 0;
}
