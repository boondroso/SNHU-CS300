/*
 * Project One.cpp
 *
 *  Date: 09/22/2024
 *  Author: Andrew Lemus
 */

#include <iostream>

using namespace std;

// Function to display the current time
void displayTime(int hours, int minutes, int seconds) {
    cout << "Current Time (24 hour clock): " << hours << ":" << minutes << ":"  << seconds << endl;
    if (hours > 12) {
        cout << "Current Time (12 hour clock): " << hours-12 << ":" << minutes << ":" << seconds << endl;
    }
}


// Function to add hour
void addHour(int &hours) {
    hours = (hours + 1) % 24;   // Ensure it wraps around 24-hour format
}

//Function to add a minute
void addMinute(int& minutes, int& hours) {
    minutes += 1;
    if (minutes >= 60) {
        minutes = 0;
        addHour(hours);     // Add an hour if minutes is greater than 60
    }
}

// Function to add second
void addSecond(int& seconds, int& minutes, int& hours) {
    seconds += 1;
    if (seconds >= 60) {
        seconds = 0;
        addMinute(minutes, hours);
    }
}
int main()
{
    int hours, minutes, seconds;

    // Get inital time
    cout << "Enter initial time: " << endl;
    cout << "Hours (0-23): ";
    cin >> hours;
    cout << "Minutes (0-59): ";
    cin >> minutes;
    cout << "Seconds (0-59): ";
    cin >> seconds;

    bool exitProgram = false;

    // Start the loop for the menu
    while (!exitProgram) {
        int choice;

        //Display Menu
        cout << "\nMenu: " << endl;
        cout << "1. Add an hour" << endl;
        cout << "2. Add a minute" << endl;
        cout << "3. Add a second" << endl;
        cout << "4. Display time" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addHour(hours);
            displayTime(hours, minutes, seconds);
            break;
        case 2:
            addMinute(minutes, hours);
            displayTime(hours, minutes, seconds);
            break;
        case 3:
            addSecond(seconds, minutes, hours);
            displayTime(hours, minutes, seconds);
            break;
        case 4:
            displayTime(hours, minutes, seconds);
            break;
        case 5:
            exitProgram = true; 
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;

        }

    }
}


