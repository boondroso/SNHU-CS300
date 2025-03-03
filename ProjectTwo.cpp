// Name        : ProjectTwo.cpp
// Author      : Andrew Lemus
// Date        : 02/23/2025

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

// Define the structure for Course, which holds information about course number, title, and prerequisites.
struct Course {
    string courseNumber;    // Course number 
    string courseTitle;     // Course title 
    vector<string> prerequisites;  // List of prerequisite course numbers 
};

 // Define CourseTable as an unordered_map where the key is a course number and the value is the Course object.
typedef unordered_map<string, Course> CourseTable;

// Function to read the course data from a file and return a populated CourseTable.
CourseTable readCourseFile(const string& filename) {
    CourseTable courseTable;  // Initialize an empty CourseTable.
    ifstream file(filename);  // Open the file for reading.

    // Check if the file exists and can be opened.
    if (!file) {
        cerr << "Error: File not found." << endl;
        return courseTable;  // Return an empty course table in case of error.
    }

    string line;
    // Read the file line by line.
    while (getline(file, line)) {
        istringstream ss(line);  // Create a stringstream to parse each line.
        vector<string> tokens;
        string token;

        // Split the line by commas to get individual tokens (course data).
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // Check if the line contains at least a course number and title.
        if (tokens.size() < 2) {
            cerr << "Error: Incorrect file format. Each line must have at least Course Number and Title" << endl;
            continue;  // Skip this line if it's incorrectly formatted.
        }

        // Create a Course object and fill it with the parsed data.
        Course courseObj;
        courseObj.courseNumber = tokens[0];  // First token is the course number.
        courseObj.courseTitle = tokens[1];   // Second token is the course title.

        // If there are more tokens, assign them as prerequisites.
        if (tokens.size() > 2) {
            courseObj.prerequisites.assign(tokens.begin() + 2, tokens.end());
        }

        // Add the course to the course table using the course number as the key.
        courseTable[courseObj.courseNumber] = courseObj;
    }
    file.close();  // Close the file after reading all lines.
    return courseTable;  // Return the populated course table.
}

// Function to print the course information.
void printCourseInfo(const CourseTable& courseTable) {
    set<string> sortedKeys;  // Set to store the course numbers, which will be automatically sorted.

    // Insert each course number from the course table into the set.
    for (const auto& pair : courseTable) {
        sortedKeys.insert(pair.first);
    }

    // Iterate through the sorted course numbers and print course info.
    for (const auto& courseNum : sortedKeys) {
        const Course& course = courseTable.at(courseNum);  // Get the course object.
        cout << "Course: " << course.courseNumber << " - " << course.courseTitle << endl;

        // Check if prerequisites are empty or only contain empty strings.
        if (course.prerequisites.empty() || (course.prerequisites.size() == 1 && course.prerequisites[0].empty())) {
            cout << " Prerequisites: None" << endl;
        }
        else {
            // Print prerequisites if they are not empty.
            cout << " Prerequisites: ";
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                cout << course.prerequisites[i];
                if (i < course.prerequisites.size() - 1) {
                    cout << ", ";  // Print a comma between prerequisites.
                }
            }
            cout << endl;
        }
    }
}

// Function to search for a specific course by its course number.
void searchCourse(const CourseTable& courseTable) {
    string courseNum;
    cout << "Enter course number to search for: ";
    cin >> courseNum;  // Get the course number from the user.

    // Look up the course in the course table.
    auto it = courseTable.find(courseNum);
    if (it != courseTable.end()) {
        const Course& course = it->second;  // If found, get the course object.
        cout << "Course: " << course.courseNumber << " - " << course.courseTitle << endl;

        // Check if prerequisites are empty or only contain empty strings.
        if (course.prerequisites.empty() || (course.prerequisites.size() == 1 && course.prerequisites[0].empty())) {
            cout << "Prerequisites: None" << endl;
        }
        else {
            cout << "Prerequisites: ";
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                cout << course.prerequisites[i];
                if (i < course.prerequisites.size() - 1) {
                    cout << ", ";  // Print a comma between prerequisites.
                }
            }
            cout << endl;
        }
    }
    else {
        // If the course number is not found, display an error message.
        cout << "Course not found." << endl;
    }
}

int main() {
    CourseTable courseTable;  // Initialize an empty course table.
    int choice;
    string filename;

    do {
        // Display the menu options.
        cout << "\nMenu:\n";
        cout << "1. Load course data\n";
        cout << "2. Print course list\n";
        cout << "3. Search for course information\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;  // Get the user's choice.

        // Handle invalid input for the choice.
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice, please enter a number\n";
            continue;
        }

        // Perform the corresponding action based on the user's choice.
        switch (choice) {
        case 1:
            // Load course data from a file.
            cout << "Enter file name: ";
            cin >> filename;
            courseTable = readCourseFile(filename);  // Populate the course table by reading the file.
            break;
        case 2:
            // Print the list of courses.
            if (!courseTable.empty()) {
                printCourseInfo(courseTable);  // Call function to print course information.
            }
            else {
                cout << "No courses loaded. Please load the data first." << endl;
            }
            break;
        case 3:
            // Search for a specific course.
            if (!courseTable.empty()) {
                searchCourse(courseTable);  // Call function to search for a course.
            }
            else {
                cout << "No courses loaded. Please load the data first." << endl;
            }
            break;
        default:
            // Handle invalid choices.
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != 4);  // Loop until the user chooses to exit.

    return 0;  // Return 0 to indicate successful program execution.
}
