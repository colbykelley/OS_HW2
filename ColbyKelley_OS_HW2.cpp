#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;


// Process class representing a process
class Process {  // Class named 'Process'
private:            
    int id;     // Private the id, and the tickets
    int tickets;
public:
    Process(int id, int tickets) : id(id), tickets(tickets) {}  // Constructor to initialize Process with an id and number of tickets
    int getId() const {   // Getter method for process id
        return id;
    }
    int getTickets() const {  // Getter method for number of tickets
        return tickets;
    }
};   // End of 'Process' class



class Scheduler {   // Class named 'Scheduler' which is managing the lottery scheduling algorithm
private:
    vector<Process> processes; // Private the vector to store processes
public:
    void addProcess(const Process& process) {    // Method to add a process to the scheduler
        processes.push_back(process);
    }
    void allocateTickets() {    // Method to allocate lottery tickets to each process
        int totalTickets = 0;   // Initialize total number of tickets

        for (const Process& process : processes) {      // Calculate the total number of tickets
            totalTickets += process.getTickets();
        }
        // Randomly assign tickets to each process based on proportion
        for (Process& process : processes) {
            double proportion = static_cast<double>(process.getTickets()) / totalTickets;  // Calculate the proportion of tickets for the current process
            // Assign tickets proportional to the total number of tickets
            process = Process(process.getId(), static_cast<int>(proportion * 100));
        }
    }
    // Method to select the winner process using a random number generator
    Process selectWinner() const {
        int randomNumber = rand() % 100 + 1;  // Generate a random number between 1 and 100 (inclusive)
       
       // Find the process whose ticket range contains the random number
        int cumulativeTickets = 0; // Initialize cumulative tickets
        for (const Process& process : processes) {
            cumulativeTickets += process.getTickets();
            if (randomNumber <= cumulativeTickets) {
                return process; // Return the winning process
            }
        }
        // This line should never be reached, but if it is, throw error
        throw runtime_error("Error: No process selected.");
    }
};   // End of 'Scheduler' class



// int main code
int main() {
    // Seed the random number generator
    srand(time(NULL));
    // Create processes and add them to the scheduler
    Scheduler scheduler;
    scheduler.addProcess(Process(1, 10));
    scheduler.addProcess(Process(2, 20));
    scheduler.addProcess(Process(3, 30));
    // Allocate tickets to processes
    scheduler.allocateTickets();
    // Select winner
    Process winner = scheduler.selectWinner();
    // Display the winning process
    cout << "Process " << winner.getId() << " wins the lottery!" << endl;

    return 0;
}
