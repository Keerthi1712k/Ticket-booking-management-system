# Train Ticket Booking Management System

This project is a command-line **Train Ticket Booking Management System** developed in C++ for managing train ticket bookings. It supports both admin and user functionalities, including train management, booking and canceling tickets, viewing available trains, and managing waiting lists. 

## Features

### Admin Functionalities
- **Admin Login**: Access with predefined credentials.
- **Add Train**: Admins can add trains with specific names, numbers, and total seats.
- **Manage Trains**: Allows editing or deleting of existing trains.
- **Manage Passengers**: View details of passengers on each train.
- **Manage Waiting List**: Display the waiting list for any train.

### User Functionalities
- **User Registration**: Allows new users to register with a unique username and password.
- **User Login**: Users can log in and access booking features.
- **View Trains**: Displays all available trains and their seat availability.
- **Book Ticket**: Users can book a ticket or join the waiting list if seats are unavailable.
- **Cancel Ticket**: Users can cancel tickets, updating seat availability and waiting list accordingly.
- **View Current Status**: Shows the current booking or waiting list status for the logged-in user.

## Technologies Used
- **Programming Language**: C++
- **Data Structures**: `map`, `vector`, `queue`
- **Concepts**: Object-Oriented Programming, File Handling (optional for persistent storage)

## Getting Started

### Prerequisites
- C++ Compiler (e.g., `g++`)

### Installation
1. **Clone the repository**:
   ```bash
   git clone https://github.com/your-username/railway-reservation-system.git
   cd railway-reservation-system
   ```
2. **Compile the Code**:
   ```bash
   g++ -std=c++17 ticket.cpp -o ticket
   ```
3. **Run the Program**:
    ```bash
   ./ticket
   ```
## Usage

### Admin Login:
- Use the predefined admin username and password to access admin features.
    - **Admin username**: `admin`
    - **Admin password**: `password`

### User Registration and Login:
- Register with a unique username and password.
- Use registered credentials to log in and access user features.

### Booking a Ticket:
- After logging in as a user, you can view trains and select a train number to book a ticket.
- If seats are unavailable, the system provides an option to join the waiting list.

### Cancelling a Ticket:
- Logged-in users can cancel their bookings, releasing their seats or updating the waiting list as applicable.

## Code Structure

- **RailwaySystem Class**: The main class that manages trains, users, bookings, and waiting lists.
- **Train and Passenger Structs**: Define the attributes for trains and passenger details.
- **Functions**:
  - `addTrain()`, `manageTrains()`, `managePassengers()`: Admin functionalities
  - `registerUser()`, `userLogin()`, `bookTicket()`, `cancelTicket()`: User functionalities

## Future Enhancements
- **Persistent Storage**: Implement file handling to save and load data for trains, users, and bookings.
- **Enhanced Error Handling**: Add more detailed validation and error messages.
- **Improved UI**: Make the command-line interface more user-friendly and intuitive.

## Contributing

Contributions are welcome! Please fork the repository, make changes, and submit a pull request. For any significant changes, please open an issue to discuss your proposed modifications.

---

### Author
- **Keerthi Priya** – [GitHub](https://github.com/Keerthi1712k)
---

Thank you for using the Railway Reservation System!
