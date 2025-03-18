#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <regex>  // Include the regex library

using namespace std;

class Patient {
public:
    Patient(const string& aadhaar, const string& name, const int age, const string& diagnosis)
        : aadhaar(aadhaar), name(name), age(age), diagnosis(diagnosis) {}

    void display() const {
        cout << "Aadhaar: " << aadhaar << "\nName: " << name << "\nAge: " << age << "\nDiagnosis: " << diagnosis << "\n\n";
    }

    const string& getAadhaar() const { return aadhaar; }

private:
    string aadhaar;
    string name;
    int age;
    string diagnosis;
};

// Function to validate Aadhaar number
bool isAadhaarValid(const string& aadhaar) {
    // Use a regular expression to check for exactly 12 digits
    return regex_match(aadhaar, regex("\\d{12}"));
}

int main() {
    // Create separate containers for doctors and patients
    map<string, Patient*> patients;
    vector<string> diagnosesReports;

    char userRole = 'D';  // Default to doctor

    while (userRole == 'D' || userRole == 'P') {
        if (userRole == 'D') {
            cout << "Doctor's Portal - Aadhaar-based Hospital Management System Menu:\n";
            cout << "1. Add a Patient\n";
            cout << "2. Display All Patients\n";
            cout << "3. Display Specific Patient\n";  // New menu item
            cout << "0. Switch to Patient Portal\n";
            cout << "Enter your choice: ";

            int choice;
            cin >> choice;

            if (choice == 1) {
                string aadhaar, name, diagnosis;
                int age;

                cout << "Enter patient's Aadhaar number (It should only contain 12 digits): ";
                cin >> aadhaar;

                if (!isAadhaarValid(aadhaar)) {
                    cout << "Invalid Aadhaar number. Aadhaar must be exactly 12 digits.\n";
                } else if (patients.find(aadhaar) != patients.end()) {
                    cout << "Patient with Aadhaar number " << aadhaar << " already exists.\n";
                } else {
                    cout << "Enter patient name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter patient age: ";
                    cin >> age;
                    cout << "Enter diagnosis: ";
                    cin.ignore();
                    getline(cin, diagnosis);

                    patients[aadhaar] = new Patient(aadhaar, name, age, diagnosis);
                    cout << "Patient added successfully!\n";
                }
            } else if (choice == 2) {
                if (patients.empty()) {
                    cout << "No patients to display.\n";
                } else {
                    cout << "List of Patients:\n";
                    for (const auto& pair : patients) {
                        pair.second->display();
                    }
                }
            } else if (choice == 3) {
                string aadhaar;
                cout << "Enter patient's Aadhaar number to display their information: ";
                cin >> aadhaar;

                if (patients.find(aadhaar) != patients.end()) {
                    patients[aadhaar]->display();
                } else {
                    cout << "Patient with Aadhaar number " << aadhaar << " does not exist.\n";
                }
            } else if (choice == 0) {
                cout << "Switching to Patient Portal.\n";
                userRole = 'P';
            } else {
                cout << "Invalid choice. Please enter a valid option.\n";
            }
        } else if (userRole == 'P') {
            cout << "Patient's Portal - Aadhaar-based Hospital Management System Menu:\n";
            cout << "1. Provide Additional Diagnoses Information\n";
            cout << "2. View Past Diagnoses\n";
            cout << "0. Switch to Doctor Portal\n";
            cout << "Enter your choice: ";

            int choice;
            cin >> choice;

            if (choice == 1) {
                string aadhaar, diagnosis;

                cout << "Enter your Aadhaar number (It should only contain 12 digits): ";
                cin >> aadhaar;
                if (!isAadhaarValid(aadhaar)) {
                    cout << "Invalid Aadhaar number. Aadhaar must be exactly 12 digits.\n";
                } else if (patients.find(aadhaar) == patients.end()) {
                    cout << "A patient with Aadhaar number " << aadhaar << " does not exist.\n";
                } else {
                    cout << "Enter diagnosis information: ";
                    cin.ignore();
                    getline(cin, diagnosis);

                    // Store the diagnosis report
                    diagnosesReports.push_back("Aadhaar: " + aadhaar + "\nDiagnosis: " + diagnosis);
                    cout << "Diagnosis information recorded successfully!\n";
                }
            } else if (choice == 2) {
                if (diagnosesReports.empty()) {
                    cout << "No past diagnoses available.\n";
                } else {
                    cout << "List of Past Diagnoses:\n";
                    for (const string& report : diagnosesReports) {
                        cout << report << "\n";
                    }
                }
            } else if (choice == 0) {
                cout << "Switching to Doctor Portal.\n";
                userRole = 'D';
            } else {
                cout << "Invalid choice. Please enter a valid option.\n";
            }
        }
    }

    // Free the allocated Patient objects before exiting
    for (const auto& pair : patients) {
        delete pair.second;
    }

    return 0;
}