#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <limits>
#include <algorithm>
#include <algorithm>

using namespace std;

int getValidChoice(int minChoice, int maxChoice) {
    int choice;
    while (true) {
        if (cin >> choice && choice >= minChoice && choice <= maxChoice) {
            return choice;
        } else {
            cout << "Invalid input. Please choose a valid option (" << minChoice << " to " << maxChoice << "): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

struct Train {
    string trainName;
    int trainNumber;
    int totalSeats;
    int availableSeats;
};

struct Passenger {
    string username;
    string name;
    string contact;
    int trainNumber;
    int seatNumber;
    bool isWaitingList;
    int waitingPosition;
};

struct User {
    string username;
    string password;
    string name;
    string phoneNumber;
};

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "password";

class RailwaySystem {
private:
    map<int, Train> trains;
    map<int, vector<Passenger>> passengers;
    map<int, queue<Passenger>> waitingList;
    map<string, User> users;
    map<string, vector<Passenger>> userBookings;

public:
    bool adminLogin(string username, string password) {
        return (username == ADMIN_USERNAME && password == ADMIN_PASSWORD);
    }

    void addTrain() {
        Train train;
        cout << "Enter Train Name: ";
        cin >> train.trainName;
        cout << "Enter Train Number: ";
        cin >> train.trainNumber;
        cout << "Enter Total Seats: ";
        cin >> train.totalSeats;
        train.availableSeats = train.totalSeats;

        trains[train.trainNumber] = train;
        cout << "Train added successfully!\n";
    }

    void manageTrains() {
        int trainNumber;
        cout << "Enter Train Number to manage: ";
        cin >> trainNumber;

        if (trains.find(trainNumber) != trains.end()) {
            cout << "1. Edit Train\n2. Delete Train\nChoose an option: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                cout << "Enter New Total Seats: ";
                cin >> trains[trainNumber].totalSeats;
                trains[trainNumber].availableSeats = trains[trainNumber].totalSeats;
                cout << "Train updated successfully!\n";
            } else if (choice == 2) {
                trains.erase(trainNumber);
                cout << "Train deleted successfully!\n";
            }
        } else {
            cout << "Train not found!\n";
        }
    }

    void managePassengers() {
        for (const auto& [trainNumber, passengerList] : passengers) {
            cout << "\nTrain Number: " << trainNumber << endl;
            for (const auto& passenger : passengerList) {
                cout << "Username: " << passenger.username
                     << ", Name: " << passenger.name
                     << ", Contact: " << passenger.contact
                     << ", Seat Number: " << passenger.seatNumber << endl;
            }
        }
    }

    void manageWaitingList() {
        int trainNumber;
        cout << "Enter Train Number to view waiting list: ";
        cin >> trainNumber;

        if (waitingList.find(trainNumber) != waitingList.end()) {
            cout << "Waiting List for Train " << trainNumber << ":\n";
            queue<Passenger> tempQueue = waitingList[trainNumber];

            if (tempQueue.empty()) {
                cout << "No passengers in the waiting list.\n";
            } else {
                int count = 1;
                while (!tempQueue.empty()) {
                    Passenger waitingPassenger = tempQueue.front();
                    cout << count << ". Username: " << waitingPassenger.username
                         << ", Name: " << waitingPassenger.name
                         << ", Contact: " << waitingPassenger.contact << endl;
                    tempQueue.pop();
                    count++;
                }
            }
        } else {
            cout << "Train not found or no waiting list for this train.\n";
        }
    }

    bool registerUser() {
        User user;
        cout << "Enter Username: ";
        cin >> user.username;

        if (users.find(user.username) != users.end()) {
            cout << "Username already taken! Try a different one.\n";
            return false;
        }

        cout << "Enter Password: ";
        cin >> user.password;
        cout << "Enter Name: ";
        cin >> user.name;
        cout << "Enter Phone Number: ";
        cin >> user.phoneNumber;

        users[user.username] = user;
        cout << "User registered successfully!\n";
        return true;
    }

    bool userLogin(string username, string password) {
        if (users.find(username) != users.end() && users[username].password == password) {
            cout << "Login successful!\n";
            return true;
        } else {
            //cout << "Invalid username or password. Please try again.\n";
            return false;
        }
    }

    void viewTrains() {
        if (trains.empty()) {
            cout << "No trains available.\n";
            return;
        }

        for (const auto& [trainNumber, train] : trains) {
            cout << "Train Name: " << train.trainName
                 << ", Train Number: " << train.trainNumber
                 << ", Available Seats: " << train.availableSeats << endl;
        }
    }

    void bookTicket(Passenger passenger) {
        int trainNumber = passenger.trainNumber;

        if (trains.find(trainNumber) == trains.end()) {
            cout << "Error: Train with number " << trainNumber << " does not exist.\n";
            return;
        }

        if (trains[trainNumber].availableSeats > 0) {
            trains[trainNumber].availableSeats--;
            passenger.seatNumber = trains[trainNumber].totalSeats - trains[trainNumber].availableSeats;
            passenger.isWaitingList = false;
            passenger.waitingPosition = -1;
            passengers[trainNumber].push_back(passenger);
            userBookings[passenger.username].push_back(passenger);

            cout << "Ticket booked successfully! Seat Number: " << passenger.seatNumber << endl;
        } else {
            cout << "No seats available. There are " << waitingList[trainNumber].size() << " people in the waiting list.\n";
            cout << "1. Add to waiting list\n2. Go back\nChoose an option: ";
            int choice = getValidChoice(1, 2);

            if (choice == 1) {
                passenger.isWaitingList = true;
                passenger.waitingPosition = waitingList[trainNumber].size() + 1;
                waitingList[trainNumber].push(passenger);
                userBookings[passenger.username].push_back(passenger);

                cout << "Added to waiting list. Your position is: " << passenger.waitingPosition << endl;
            } else {
                cout << "Going back...\n";
            }
        }
    }

    void cancelTicket(int trainNumber, int seatNumber, const string& username) {
        auto& passengerList = passengers[trainNumber];
        bool found = false;

        for (auto it = passengerList.begin(); it != passengerList.end(); ++it) {
            if (it->seatNumber == seatNumber && it->username == username) {
                auto& userBookingsList = userBookings[username];
                userBookingsList.erase(remove_if(userBookingsList.begin(), userBookingsList.end(),
                                             [seatNumber](const Passenger& p) { return p.seatNumber == seatNumber; }),
                                   userBookingsList.end());

                passengerList.erase(it);
                trains[trainNumber].availableSeats++;
                found = true;
                cout << "Ticket canceled successfully.\n";

                if (!waitingList[trainNumber].empty()) {
                    Passenger waitingPassenger = waitingList[trainNumber].front();
                    waitingList[trainNumber].pop();

                    auto& waitingBookings = userBookings[waitingPassenger.username];
                    waitingBookings.erase(remove_if(waitingBookings.begin(), waitingBookings.end(),
                                                    [](const Passenger& p) { return p.isWaitingList; }),
                                          waitingBookings.end());

                    waitingPassenger.isWaitingList = false;
                    waitingPassenger.waitingPosition = -1;
                    waitingPassenger.seatNumber = seatNumber;
                    trains[trainNumber].availableSeats--;
                    passengers[trainNumber].push_back(waitingPassenger);
                    userBookings[waitingPassenger.username].push_back(waitingPassenger);
                    cout << "Waiting list passenger " << waitingPassenger.name << " booked with Seat Number: " << waitingPassenger.seatNumber << endl;
                }
                break;
            }
        }
        if (!found) {
            cout << "Ticket not found.\n";
        }
    }

    void viewCurrentStatus(const string& username) {
        if (userBookings[username].empty()) {
            cout << "No current bookings found.\n";
            return;
        }

        cout << "Current booking status for " << username << ":\n";
        for (const auto& booking : userBookings[username]) {
            if (booking.isWaitingList) {
                cout << "Train Number: " << booking.trainNumber << ", Status: Waiting List " << booking.waitingPosition << endl;
            } else {
                cout << "Train Number: " << booking.trainNumber << ", Seat Number: " << booking.seatNumber << endl;
            }
        }
    }
};


int main() {
    RailwaySystem system;
    int choice;

    cout << "Welcome to the Railway Reservation System!\n";

    while (true) {
        cout << "\n1. Admin Login\n2. User Registration\n3. User Login\n4. Exit\nChoose an option: ";
        choice = getValidChoice(1, 4);

        if (choice == 1) {
            // Admin Login
            string adminUsername, adminPassword;
            cout << "Enter Admin Username: ";
            cin >> adminUsername;
            cout << "Enter Admin Password: ";
            cin >> adminPassword;

            if (system.adminLogin(adminUsername, adminPassword)) {
                cout << "Admin logged in successfully!\n";
                while (true) {
                    cout << "\nAdmin Menu:\n1. Add Train\n2. Manage Trains\n3. Manage Passengers\n4. View Waiting List\n5. Logout\nChoose an option: ";
                    int adminChoice = getValidChoice(1, 5);

                    if (adminChoice == 1) {
                        system.addTrain();
                    } else if (adminChoice == 2) {
                        system.manageTrains();
                    } else if (adminChoice == 3) {
                        system.managePassengers();
                    } else if (adminChoice == 4) {
                        system.manageWaitingList();
                    } else if (adminChoice == 5) {
                        cout << "Admin logged out.\n";
                        break;
                    }
                }
            } else {
                cout << "Invalid admin credentials!\n";
            }

        } else if (choice == 2) {
            // User Registration
            if (!system.registerUser()) {
                cout << "User registration failed. Try again.\n";
            }

        } else if (choice == 3) {
            // User Login
            string username, password;
            cout << "Enter Username: ";
            cin >> username;
            cout << "Enter Password: ";
            cin >> password;

            if (system.userLogin(username, password)) {
                while (true) {
                    cout << "\nUser Menu:\n1. View Trains\n2. Book Ticket\n3. Cancel Ticket\n4. View Current Status\n5. Logout\nChoose an option: ";
                    int userChoice = getValidChoice(1, 5);

                    if (userChoice == 1) {
                        system.viewTrains();
                    } else if (userChoice == 2) {
                        Passenger passenger;
                        passenger.username = username;
                        cout << "Enter Name: ";
                        cin >> passenger.name;
                        cout << "Enter Contact: ";
                        cin >> passenger.contact;
                        cout << "Enter Train Number to book: ";
                        cin >> passenger.trainNumber;

                        system.bookTicket(passenger);

                    } else if (userChoice == 3) {
                        int trainNumber, seatNumber;
                        cout << "Enter Train Number: ";
                        cin >> trainNumber;
                        cout << "Enter Seat Number to cancel: ";
                        cin >> seatNumber;

                        system.cancelTicket(trainNumber, seatNumber, username);

                    } else if (userChoice == 4) {
                        system.viewCurrentStatus(username);
                    } else if (userChoice == 5) {
                        cout << "User logged out.\n";
                        break;
                    }
                }
            } else {
                cout << "Invalid username or password.\n";
            }

        } else if (choice == 4) {
            cout << "Thank you for using the Railway Reservation System!\n";
            break;
        }
    }

    return 0;
}