/**
 * This code logs the user's activities into a file, "log.txt". 
 * The user can choose from the following activities: 
 * 1) Work with Database
 * 2) Work with Operating System
 * 3) Work with Documents
 * 4) Exit
 * The chosen activity is then logged into the file along with a timestamp.
 */

#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <string>

const int MAX_RECORDS = 100;
std::ofstream logFile;

struct ActivityRecord {
    std::string description;
    std::string timestamp;
};

ActivityRecord activityLog[MAX_RECORDS];

std::string currentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* timeinfo = std::localtime(&now_c);
    std::ostringstream oss;
    oss << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string getActivityDescription(int activityNumber) {
    switch (activityNumber) {
        case 1:
            return "Working with Database";
        case 2:
            return "Working with Operating System";
        case 3:
            return "Working with Documents";
        default:
            return "Unknown Activity";
    }
}

int main() {

    int userInput, logIndex = 0;

    while (true) {
        std::cout << "\nChoose from the following options:\n"
                  << "1) Work with Database\n"
                  << "2) Work with Operating System\n"
                  << "3) Work with Documents\n"
                  << "4) Exit\n";

        std::cout << "Enter your choice: ";
        std::cin >> userInput;

        if (userInput == 4) break;

        activityLog[logIndex].description = getActivityDescription(userInput);
        activityLog[logIndex].timestamp = currentDateTime();
        std::cout << activityLog[logIndex].description << "...\n";
        logIndex++;
    }

    logFile.open("log.txt");
    for (int i = 0; i < logIndex; i++) {
        logFile << i + 1 << ") " << activityLog[i].description << " at " << activityLog[i].timestamp << "\n";
    }
    logFile.close();

    return 0;
}
