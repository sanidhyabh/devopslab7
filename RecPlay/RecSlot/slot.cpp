#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


struct User {
    string username;
    string password;
    
};


const int NUM_COURTS = 3;
const int NUM_SLOTS = 9; 

int badmintonAvailability[NUM_COURTS][NUM_SLOTS] = {0};
int tennisAvailability[NUM_COURTS][NUM_SLOTS] = {0};
int basketballAvailability[NUM_COURTS][NUM_SLOTS] = {0};
bool courtUnderMaintenance[NUM_COURTS] = {false}; 

void bookCourt(int courtNumber, int sport, string username) {
    if (courtUnderMaintenance[courtNumber - 1]) {
        cout << "Court " << courtNumber << " is currently under maintenance. Sorry, no bookings allowed.\n";
        return;
    }

    int* availabilityArray;
    const char* sportName;

    if (sport == 1) {
        availabilityArray = badmintonAvailability[courtNumber - 1];
        sportName = "Badminton";
    } else if (sport == 2) {
        availabilityArray = tennisAvailability[courtNumber - 1];
        sportName = "Tennis";
    } else if (sport == 3) {
        availabilityArray = basketballAvailability[courtNumber - 1];
        sportName = "Basketball";
    } else {
        cout << "Invalid sport selection.\n";
        return;
    }

    for (int slot = 0; slot < NUM_SLOTS; ++slot) {
        if (availabilityArray[slot] == 0) {
            cout << "Slot " << (slot + 1) << " is available.\n";
        }
    }

    cout << "Enter the slot number you want to book: ";
    int selectedSlot;
    cin >> selectedSlot;

    if (selectedSlot >= 1 && selectedSlot <= NUM_SLOTS &&
        availabilityArray[selectedSlot - 1] == 0) {
        availabilityArray[selectedSlot - 1] = 1;
        cout << "Slot " << selectedSlot << " on Court " << courtNumber << " for " << sportName << " has been booked.\n";
    } else {
        cout << "Invalid slot number or slot is already booked.\n";
    }
    ofstream bookedFile("./booked.txt", ios::app);  // Open file in append mode
    if (bookedFile.is_open()) {
            bookedFile << "Court " << courtNumber << ", Slot " << selectedSlot << ", " << sportName << ", Booked by " << username << "\n";
            bookedFile.close();
    } 
    else {
        cout << "Error opening the booked slots file.\n";
    }
}

void displaySlotsForSport(int courtNumber, int sportChoice) {
    const char* sportName;

    if (sportChoice == 1) {
        sportName = "Badminton";
    } else if (sportChoice == 2) {
        sportName = "Tennis";
    } else if (sportChoice == 3) {
        sportName = "Basketball";
    } else {
        cout << "Invalid sport selection.\n";
        return;
    }

    int startTime = 6;  
    int endTime = 9;    

    cout << "Available slots for " << sportName << ":\n";
    int slotsPerHour = NUM_SLOTS / (endTime - startTime);

    for (int hour = startTime; hour < endTime; hour++) {
        cout << "Slots for " << hour << ":00 - " << (hour + 1) << ":00:\n";
        for (int slot = (hour - startTime) * slotsPerHour; slot < (hour - startTime + 1) * slotsPerHour; ++slot) {
            if (sportChoice == 1 && badmintonAvailability[courtNumber - 1][slot] == 0) {
                cout << "Slot " << (slot + 1) << " for " << sportName << " is available.\n";
            } else if (sportChoice == 2 && tennisAvailability[courtNumber - 1][slot] == 0) {
                cout << "Slot " << (slot + 1) << " for " << sportName << " is available.\n";
            } else if (sportChoice == 3 && basketballAvailability[courtNumber - 1][slot] == 0) {
                cout << "Slot " << (slot + 1) << " for " << sportName << " is available.\n";
            }
        }
    }
}

void userLogin(string username) {
    
    while (true) {
        cout << "\n***** Slot Booking System *****\n";
        cout << "1. Book Slot\n";
        cout << "2. Check Booked Slots\n";
        cout << "3. Logout\n";  
        int choice;
        cin >> choice;

       

        switch (choice) {
            case 1: {
                int court, sport;
                
                cout << "Select the sport:\n";
                cout << "1. Badminton\n";
                cout << "2. Tennis\n";
                cout << "3. Basketball\n";
                cout << "Enter 1 for Badminton, 2 for Tennis, or 3 for Basketball: \n";
                cin >> sport;

                
                displaySlotsForSport(2, sport);  
                
                cout << "Do you want to book a slot? (Y/N): ";
                char bookChoice;
                cin >> bookChoice;
                if (bookChoice == 'Y' || bookChoice == 'y') {
                    bookCourt(2, sport, username); 
                }

                break; 
            }

            case 2: {
                int court, sport;
                
                cout << "Select the sport:\n";
                cout << "1. Badminton\n";
                cout << "2. Tennis\n";
                cout << "3. Basketball\n";
                cout << "Enter your choice: ";
                cin >> sport;

                
                displaySlotsForSport(2, sport);
                
                break; 
            }

            case 3:
                cout << "Exiting the program. Goodbye!" << endl;
                return; 
                

            default:
                cout << "Invalid choice. Please enter a valid option (1-3)." << endl;
                continue;
        }
    }
}

int main() {
    vector<User> users; 

    int choice;
    while (true) {
       cout << "1. Login " << endl;
        cout << "2. Sign up" << endl;
        cout<< "3. Exit" << endl;
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        

        switch (choice) {
            case 1: {
                string username, password, info;
                cout << "Enter your username: ";
                cin >> username;
                cout << "Enter your password: ";
                cin >> password;
                
                info= username + " " + password;

                
                ifstream inputFile("./usernames.txt");
                if (!inputFile.is_open()) {
                    std::cerr << "Error opening the file." << std::endl;
                    return 1;
                }
                vector<std::string> usernames;
                string line;
                while (std::getline(inputFile, line)) {
                    usernames.push_back(line);
                }
                inputFile.close();


                
                int left = 0;
                int right = usernames.size() - 1;
                bool found = false;

                while (left <= right) {
                    int mid = (left + right) / 2;
                    if (usernames[mid] == info) {
                        found = true;
                        break;
                    } else if (usernames[mid] < info) {
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                }
                
                if (found) {
                    std::cout << "Login successful!" << std::endl;
                    cout<<"Welcome "<<username<<"!"<<endl;
                    // cout<<"Press 0 to logout at any point" << endl;
                    userLogin(username);
                } else {
                    std::cout << "Invalid username or password." << std::endl;
                }
                
                inputFile.close();
                break;
            }

            case 2: {
                string newUsername, newPassword;
                cout << "Enter new username: ";
                cin >> newUsername;
                cout << "Enter new password: ";
                cin >> newPassword;
                
                string info= newUsername + " " + newPassword;
                ifstream inputFile("./usernames.txt");
                if (!inputFile.is_open()) {
                    std::cerr << "Error opening the file." << std::endl;
                    return 1;
                }
                
                vector<std::string> usernames;
                string line;
                while (std::getline(inputFile, line)) {
                    usernames.push_back(line);
                }
                inputFile.close();

                
                int left = 0;
                int right = usernames.size() - 1;
                int insertionPoint = -1;

                while (left <= right) {
                    int mid = (left + right) / 2;
                    if (usernames[mid] == info) {
                        std::cout << "Username already exists." << std::endl;
                        return 0;
                    } else if (usernames[mid] < info) {
                        left = mid + 1;
                        insertionPoint = mid + 1;
                    } else {
                        right = mid - 1;
                        insertionPoint = mid;
                    }
                }

                
                if (insertionPoint == -1) {
                    usernames.insert(usernames.begin(), info);
                } else {
                    usernames.insert(usernames.begin() + insertionPoint, info);
                }

                
                ofstream outputFile("./usernames.txt");
                if (!outputFile.is_open()) {
                    std::cerr << "Error opening the file for writing." << std::endl;
                    return 1;
                }
                for (const auto& username : usernames) {
                    outputFile << username << std::endl;
                }
                outputFile.close();

                std::cout << "New user added: " << newUsername << std::endl;
                break;
            }
            case 3:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0; 
            default:
                cout << "Invalid choice. Please enter a valid option (1-3)." << endl;
                continue;
                if (choice == 3) {
                    cout << "Exiting the program. Goodbye!" << endl;
                    break;
                }
        }
    }
    return 0;
} 