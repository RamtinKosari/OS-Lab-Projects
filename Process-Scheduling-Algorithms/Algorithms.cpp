# ifndef ALGORITHMS_DR_HAGHIGHAT
    # include "Algorithms.hpp"
    /**
     * @brief ProcessScheduler Constructor
     * @details This Constructor Initializes ProcessScheduler Class
     */
    ProcessScheduler::ProcessScheduler() {
        //-- Initialize Random Seed
        std::srand(std::time(nullptr));
        //-- Initialize Begin Time
        begin_time = std::chrono::high_resolution_clock::now();
    }
    /**
     * @brief Method to Generate Random Processes
     * @details This Method Generates Random Processes
     */
    void ProcessScheduler::GenerateRandomProcesses() {
        //-- Generate Random Number of Processes
        std::int64_t number_of_processes = NUMBER_OF_PROCESSES;
        //-- Generate Random Processes
        std::cout << LOG << "Generating Random Processes ..." << std::endl;
        for (std::int64_t i = 0; i < number_of_processes; i++) {
            process.process_id = i + 1;
            process.arrival_time = std::rand() % 10 + 1;
            process.burst_time = std::rand() % 10 + 1;
            process.priority = std::rand() % 10 + 1;
            process.remaining_time = process.burst_time;
            PIDs.push_back(process);
            std::cout << TAB SUCCESS << "Generated PID: " CYAN << process.process_id << RESET " - Arrival Time: " CYAN << process.arrival_time << RESET " - Burst Time: " CYAN << process.burst_time << RESET " - Priority: " CYAN << process.priority << RESET << std::endl;
        }
    }
    /**
     * @brief Method to Simulate Processes Time Line
     * @details This Method Simulates Processes Time Line
     */
    void ProcessScheduler::simulateProcessesTimeLine() {
        //-- Start Simulation
        std::cout << LOG << "Starting Simulation ..." << std::endl;
        //-- Current Time
        int current_time = 0;
        //-- Process Index
        int process_index = 0;
        //-- Number of Processes
        int num_processes = PIDs.size();
        //-- Simulate Processes Time Line
        while (process_index < num_processes) {
            if (current_time >= PIDs[process_index].arrival_time) {
                std::cout << TAB ARRIVED " Time " CYAN << current_time << RESET ": Process " CYAN << PIDs[process_index].process_id << std::endl;
                current_time += PIDs[process_index].burst_time;
                std::cout << TAB FINISHED " Time " CYAN << current_time << RESET ": Process " CYAN << PIDs[process_index].process_id << std::endl;
                process_index++;
            } else {
                std::cout << TAB NO_PROCESS " Time " CYAN << current_time << std::endl;
                current_time++;
            }
            //-- Delay
            std::this_thread::sleep_for(std::chrono::milliseconds(SHOW_TIMELINE_DELAY));
        }
        std::cout << LOG << "Simulation completed." << std::endl;
    }
    /**
     * @brief First Come First Serve Algorithm
     * @details This Function Schedules Processes Using First Come First Serve Algorithm
     * @note This Algorithm is being Used in Batch Processing Systems
     */
    void ProcessScheduler::FCFS() {
        //-- First Come First Serve Algorithm
        std::cout << LOG << "First Come First Serve Algorithm ..." << std::endl;
        //-- Sort Processes by Arrival Time
        std::sort(PIDs.begin(), PIDs.end(), [](Process a, Process b) {
            return a.arrival_time < b.arrival_time;
        });
        //-- Calculate Completion Time
        for (std::int64_t i = 0; i < PIDs.size(); i++) {
            if (i == 0) {
                PIDs[i].completion_time = PIDs[i].arrival_time + PIDs[i].burst_time;
            } else {
                if (PIDs[i].arrival_time > PIDs[i - 1].completion_time) {
                    PIDs[i].completion_time = PIDs[i].arrival_time + PIDs[i].burst_time;
                } else {
                    PIDs[i].completion_time = PIDs[i - 1].completion_time + PIDs[i].burst_time;
                }
            }
        }
        //-- Calculate Turnaround Time
        for (std::int64_t i = 0; i < PIDs.size(); i++) {
            PIDs[i].turnaround_time = PIDs[i].completion_time - PIDs[i].arrival_time;
        }
        //-- Calculate Waiting Time
        for (std::int64_t i = 0; i < PIDs.size(); i++) {
            PIDs[i].waiting_time = PIDs[i].turnaround_time - PIDs[i].burst_time;
        }
        //-- Display Process Information
        for (std::int64_t i = 0; i < PIDs.size(); i++) {
            std::cout << TAB << "PID: " CYAN << PIDs[i].process_id << RESET " - Arrival Time: " CYAN << PIDs[i].arrival_time << RESET " - Burst Time: " CYAN << PIDs[i].burst_time << RESET " - Completion Time: " CYAN << PIDs[i].completion_time << RESET " - Turnaround Time: " CYAN << PIDs[i].turnaround_time << RESET " Waiting Time: " CYAN << PIDs[i].waiting_time << RESET << std::endl;
        }
    }
    /**
     * @brief Shortest Job First Algorithm
     * @details This Function Schedules Processes Using Shortest Job First Algorithm
     * @note This Algorithm is being Used in Batch Processing Systems
     */
    void ProcessScheduler::SJF() {
        //-- Shortest Job First Algorithm
        std::cout << LOG << "Shortest Job First Algorithm ..." << std::endl;
        //-- Sort Processes by Burst Time
        std::sort(PIDs.begin(), PIDs.end(), [](Process a, Process b) {
            return a.burst_time < b.burst_time;
        });
        //-- Calculate Completion Time
        for (std::int64_t i = 0; i < PIDs.size(); i++) {
            if (i == 0) {
                PIDs[i].completion_time = PIDs[i].arrival_time + PIDs[i].burst_time;
            } else {
                if (PIDs[i].arrival_time > PIDs[i - 1].completion_time) {
                    PIDs[i].completion_time = PIDs[i].arrival_time + PIDs[i].burst_time;
                } else {
                    PIDs[i].completion_time = PIDs[i - 1].completion_time + PIDs[i].burst_time;
                }
            }
        }
        //-- Calculate Turnaround Time
        for (std::int64_t i = 0; i < PIDs.size(); i++) {
            PIDs[i].turnaround_time = PIDs[i].completion_time - PIDs[i].arrival_time;
        }
        //-- Calculate Waiting Time
        for (std::int64_t i = 0; i < PIDs.size(); i++) {
            PIDs[i].waiting_time = PIDs[i].turnaround_time - PIDs[i].burst_time;
        }
        //-- Display Process Information
        for (std::int64_t i = 0; i < PIDs.size(); i++) {
            std::cout << TAB << "PID: " CYAN << PIDs[i].process_id << RESET " - Arrival Time: " CYAN << PIDs[i].arrival_time << RESET " - Burst Time: " CYAN << PIDs[i].burst_time << RESET " - Completion Time: " CYAN << PIDs[i].completion_time << RESET " - Turnaround Time: " CYAN << PIDs[i].turnaround_time << RESET " Waiting Time: " CYAN << PIDs[i].waiting_time << RESET << std::endl;
        }
    }
    /**
     * @brief Shortest Remaining Time First Algorithm
     * @details This Function Schedules Processes Using Shortest Remaining Time First Algorithm
     * @note This Algorithm is being Used in Batch Processing Systems
     */
    void ProcessScheduler::SRTF() {
        //-- Shortest Remaining Time First Algorithm
        std::cout << LOG << "Shortest Remaining Time First Algorithm ..." << std::endl;
        //-- Sort Processes by Remaining Time
        std::sort(PIDs.begin(), PIDs.end(), [](Process a, Process b) {
            return a.remaining_time < b.remaining_time;
        });
        //-- Calculate Completion Time
        for (std::int64_t i = 0; i < PIDs.size(); i++) {
            if (i == 0) {
                PIDs[i].completion_time = PIDs[i].arrival_time + PIDs[i].burst_time;
            } else {
                if (PIDs[i].arrival_time > PIDs[i - 1].completion_time) {
                    PIDs[i].completion_time = PIDs[i].arrival_time + PIDs[i].burst_time;
                } else {
                    PIDs[i].completion_time = PIDs[i - 1].completion_time + PIDs[i].burst_time;
                }
            }
        }
        //-- Calculate Turnaround Time
        for (std::int64_t i = 0; i < PIDs.size(); i++) {
            PIDs[i].turnaround_time = PIDs[i].completion_time - PIDs[i].arrival_time;
        }
        //-- Calculate Waiting Time
        for (std::int64_t i = 0; i < PIDs.size(); i++) {
            PIDs[i].waiting_time = PIDs[i].turnaround_time - PIDs[i].burst_time;
        }
        //-- Display Process Information
        for (std::int64_t i = 0; i < PIDs.size(); i++) {
            std::cout << TAB << "PID: " CYAN << PIDs[i].process_id << RESET " - Arrival Time: " CYAN << PIDs[i].arrival_time << RESET " - Burst Time: " CYAN << PIDs[i].burst_time << RESET " - Completion Time: " CYAN << PIDs[i].completion_time << RESET " - Turnaround Time: " CYAN << PIDs[i].turnaround_time << RESET " Waiting Time: " CYAN << PIDs[i].waiting_time << RESET << std::endl;
        }
    }
    /**
     * @brief Highest Response Ratio Next Algorithm
     * @details This Function Schedules Processes Using Highest Response Ratio Next Algorithm
     * @note This Algorithm is being Used in Batch Processing Systems
     */
    void ProcessScheduler::HRRN() {
        //-- Highest Response Ratio Next Algorithm
        std::cout << LOG << "Highest Response Ratio Next Algorithm ..." << std::endl;
        //-- Sort Processes by Arrival Time
        std::sort(PIDs.begin(), PIDs.end(), [](Process a, Process b) {
            return a.arrival_time < b.arrival_time;
        });
        //-- Define Process Queue
        std::queue<Process*> process_queue;
        //-- Define Current Time
        int current_time = 0;
        //-- Define Process Index
        int process_index = 0;
        //-- Define Number of Processes
        int num_processes = PIDs.size();
        //-- Simulate Processes Time Line
        while (process_index < num_processes || !process_queue.empty()) {
            while (process_index < num_processes && PIDs[process_index].arrival_time <= current_time) {
                process_queue.push(&PIDs[process_index]);
                std::cout << TAB ARRIVED " Time " CYAN << current_time << RESET ": Process " CYAN << PIDs[process_index].process_id << std::endl;
                process_index++;
            }

            if (!process_queue.empty()) {
                Process* current_process = process_queue.front();
                process_queue.pop();
                int exec_time = current_process->burst_time;
                std::cout << TAB EXECUTE "Process " CYAN << current_process->process_id << RESET " for " CYAN << exec_time << RESET " Time Units" << std::endl;
                current_time += exec_time;

                // Check for new arrivals during execution
                while (process_index < num_processes && PIDs[process_index].arrival_time <= current_time) {
                    process_queue.push(&PIDs[process_index]);
                    std::cout << TAB ARRIVED " Time " CYAN << current_time << RESET ": Process " CYAN << PIDs[process_index].process_id << std::endl;
                    process_index++;
                }

                current_process->completion_time = current_time;
                current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;
                current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;
                std::cout << TAB FINISHED " Time " CYAN << current_time << RESET ": Process " CYAN << current_process->process_id << std::endl;
            } else {
                std::cout << TAB NO_PROCESS " Time " CYAN << current_time << std::endl;
                current_time++;
            }
            //-- Delay
            std::this_thread::sleep_for(std::chrono::milliseconds(SHOW_TIMELINE_DELAY));
        }
    }
    /**
     * @brief Round Robin Algorithm
     * @details This Function Schedules Processes Using Round Robin Algorithm
     * @note This Algorithm is being Used in Interactive Systems
     */
    void ProcessScheduler::RR() {
        //-- Round Robin Algorithm
        std::cout << LOG << "Round Robin Algorithm ..." << std::endl;
        //-- Sort Processes by Arrival Time
        std::sort(PIDs.begin(), PIDs.end(), [](const Process& a, const Process& b) {
            return a.arrival_time < b.arrival_time;
        });
        //-- Define Process Queue
        std::queue<Process*> process_queue;
        //-- Define Current Time
        int current_time = 0;
        //-- Define Process Index
        int process_index = 0;
        //-- Define Number of Processes
        int num_processes = PIDs.size();
        //-- Simulate Processes Time Line
        while (process_index < num_processes || !process_queue.empty()) {
            while (process_index < num_processes && PIDs[process_index].arrival_time <= current_time) {
                process_queue.push(&PIDs[process_index]);
                std::cout << TAB ARRIVED " Time " CYAN << current_time << RESET ": Process " CYAN << PIDs[process_index].process_id << std::endl;
                process_index++;
            }

            if (!process_queue.empty()) {
                Process* current_process = process_queue.front();
                process_queue.pop();
                int exec_time = std::min(std::int64_t(QUANTUM_TIME), current_process->remaining_time);
                std::cout << TAB EXECUTE "Process " CYAN << current_process->process_id << RESET " for " CYAN << exec_time << RESET " Quantoms" << std::endl;
                current_process->remaining_time -= exec_time;
                current_time += exec_time;

                // Check for new arrivals during execution
                while (process_index < num_processes && PIDs[process_index].arrival_time <= current_time) {
                    process_queue.push(&PIDs[process_index]);
                    std::cout << TAB ARRIVED " Time " CYAN << current_time << RESET ": Process " CYAN << PIDs[process_index].process_id << std::endl;
                    process_index++;
                }

                if (current_process->remaining_time > 0) {
                    process_queue.push(current_process);
                } else {
                    current_process->completion_time = current_time;
                    current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;
                    current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;
                    std::cout << TAB FINISHED " Time " CYAN << current_time << RESET ": Process " CYAN << current_process->process_id << std::endl;
                }
            } else {
                std::cout << TAB NO_PROCESS " Time " CYAN << current_time << std::endl;
                current_time++;
            }
            //-- Delay
            std::this_thread::sleep_for(std::chrono::milliseconds(SHOW_TIMELINE_DELAY));
        }
    }
    /**
     * @brief Multilevel Feedback Queue Algorithm
     * @details This Function Schedules Processes Using Multilevel Feedback Queue Algorithm
     * @note This Algorithm is being Used in Interactive Systems
     */
    void ProcessScheduler::MLFQ() {
        //-- Multilevel Feedback Queue Algorithm
        std::cout << LOG << "Multilevel Feedback Queue Algorithm ..." << std::endl;
        //-- Sort Processes by Arrival Time
        std::sort(PIDs.begin(), PIDs.end(), [](const Process& a, const Process& b) {
            return a.arrival_time < b.arrival_time;
        });
        //-- Define Process Queues
        std::queue<Process*> process_queue[3];
        //-- Define Current Time
        int current_time = 0;
        //-- Define Process Index
        int process_index = 0;
        //-- Define Number of Processes
        int num_processes = PIDs.size();
        //-- Simulate Processes Time Line
        while (process_index < num_processes || !process_queue[0].empty() || !process_queue[1].empty() || !process_queue[2].empty()) {
            while (process_index < num_processes && PIDs[process_index].arrival_time <= current_time) {
                process_queue[0].push(&PIDs[process_index]);
                std::cout << TAB ARRIVED " Time " CYAN << current_time << RESET ": Process " CYAN << PIDs[process_index].process_id << std::endl;
                process_index++;
            }

            for (int i = 0; i < 3; i++) {
                if (!process_queue[i].empty()) {
                    Process* current_process = process_queue[i].front();
                    process_queue[i].pop();
                    int exec_time = std::min(std::int64_t(QUANTUM_TIME), current_process->remaining_time);
                    std::cout << TAB EXECUTE "Process " CYAN << current_process->process_id << RESET " for " CYAN << exec_time << RESET " Quantoms" << std::endl;
                    current_process->remaining_time -= exec_time;
                    current_time += exec_time;

                    // Check for new arrivals during execution
                    while (process_index < num_processes && PIDs[process_index].arrival_time <= current_time) {
                        process_queue[0].push(&PIDs[process_index]);
                        std::cout << TAB ARRIVED " Time " CYAN << current_time << RESET ": Process " CYAN << PIDs[process_index].process_id << std::endl;
                        process_index++;
                    }

                    if (current_process->remaining_time > 0) {
                        if (i < 2) {
                            process_queue[i + 1].push(current_process);
                        } else {
                            process_queue[i].push(current_process);
                        }
                    } else {
                        current_process->completion_time = current_time;
                        current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;
                        current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;
                        std::cout << TAB FINISHED " Time " CYAN << current_time << RESET ": Process " CYAN << current_process->process_id << std::endl;
                    }
                    break;
                }
            }
            if (process_queue[0].empty() && process_queue[1].empty() && process_queue[2].empty()) {
                std::cout << TAB NO_PROCESS " Time " CYAN << current_time << std::endl;
                current_time++;
            }
            //-- Delay
            std::this_thread::sleep_for(std::chrono::milliseconds(SHOW_TIMELINE_DELAY));
        }
    }
    /**
     * @brief Shortest Process Next Algorithm
     * @details This Function Schedules Processes Using Shortest Process Next Algorithm
     * @note This Algorithm is being Used in Interactive Systems
     */
    void ProcessScheduler::SPN() {
        //-- Shortest Process Next Algorithm
        std::cout << LOG << "Shortest Process Next Algorithm ..." << std::endl;
        //-- Sort Processes by Arrival Time
        std::sort(PIDs.begin(), PIDs.end(), [](const Process& a, const Process& b) {
            return a.arrival_time < b.arrival_time;
        });
        //-- Define Process Queue
        std::queue<Process*> process_queue;
        //-- Define Current Time
        int current_time = 0;
        //-- Define Process Index
        int process_index = 0;
        //-- Define Number of Processes
        int num_processes = PIDs.size();
        //-- Simulate Processes Time Line
        while (process_index < num_processes || !process_queue.empty()) {
            while (process_index < num_processes && PIDs[process_index].arrival_time <= current_time) {
                process_queue.push(&PIDs[process_index]);
                std::cout << TAB ARRIVED " Time " CYAN << current_time << RESET ": Process " CYAN << PIDs[process_index].process_id << std::endl;
                process_index++;
            }

            if (!process_queue.empty()) {
                Process* current_process = process_queue.front();
                process_queue.pop();
                int exec_time = current_process->burst_time;
                std::cout << TAB EXECUTE "Process " CYAN << current_process->process_id << RESET " for " CYAN << exec_time << RESET " Time Units" << std::endl;
                current_time += exec_time;

                // Check for new arrivals during execution
                while (process_index < num_processes && PIDs[process_index].arrival_time <= current_time) {
                    process_queue.push(&PIDs[process_index]);
                    std::cout << TAB ARRIVED " Time " CYAN << current_time << RESET ": Process " CYAN << PIDs[process_index].process_id << std::endl;
                    process_index++;
                }

                current_process->completion_time = current_time;
                current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;
                current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;
                std::cout << TAB FINISHED " Time " CYAN << current_time << RESET ": Process " CYAN << current_process->process_id << std::endl;
            } else {
                std::cout << TAB NO_PROCESS " Time " CYAN << current_time << std::endl;
                current_time++;
            }
            //-- Delay
            std::this_thread::sleep_for(std::chrono::milliseconds(SHOW_TIMELINE_DELAY));
        }
    }
    /**
     * @brief Guaranteed Scheduling Algorithm
     * @details This Function Schedules Processes Using Guaranteed Scheduling Algorithm
     * @note This Algorithm is being Used in Interactive Systems
     */
    void ProcessScheduler::GS() {
        //-- Guaranteed Scheduling Algorithm
        std::cout << LOG << "Guaranteed Scheduling Algorithm ..." << std::endl;
        //-- Sort Processes by Arrival Time
        std::sort(PIDs.begin(), PIDs.end(), [](const Process& a, const Process& b) {
            return a.arrival_time < b.arrival_time;
        });
        //-- Define Process Queue
        std::queue<Process*> process_queue;
        //-- Define Current Time
        int current_time = 0;
        //-- Define Process Index
        int process_index = 0;
        //-- Define Number of Processes
        int num_processes = PIDs.size();
        //-- Simulate Processes Time Line
        while (process_index < num_processes || !process_queue.empty()) {
            while (process_index < num_processes && PIDs[process_index].arrival_time <= current_time) {
                process_queue.push(&PIDs[process_index]);
                std::cout << TAB ARRIVED " Time " CYAN << current_time << RESET ": Process " CYAN << PIDs[process_index].process_id << std::endl;
                process_index++;
            }

            if (!process_queue.empty()) {
                Process* current_process = process_queue.front();
                process_queue.pop();
                int exec_time = current_process->burst_time;
                std::cout << TAB EXECUTE "Process " CYAN << current_process->process_id << RESET " for " CYAN << exec_time << RESET " Time Units" << std::endl;
                current_time += exec_time;

                // Check for new arrivals during execution
                while (process_index < num_processes && PIDs[process_index].arrival_time <= current_time) {
                    process_queue.push(&PIDs[process_index]);
                    std::cout << TAB ARRIVED " Time " CYAN << current_time << RESET ": Process " CYAN << PIDs[process_index].process_id << std::endl;
                    process_index++;
                }

                current_process->completion_time = current_time;
                current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;
                current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;
                std::cout << TAB FINISHED " Time " CYAN << current_time << RESET ": Process " CYAN << current_process->process_id << std::endl;
            } else {
                std::cout << TAB NO_PROCESS " Time " CYAN << current_time << std::endl;
                current_time++;
            }
            //-- Delay
            std::this_thread::sleep_for(std::chrono::milliseconds(SHOW_TIMELINE_DELAY));
        }
    }
# endif // ALGORITHMS_DR_HAGHIGHAT

//-- Main Function
int main() {
    //-- Initialize ProcessScheduler
    ProcessScheduler scheduler;
    //-- Generate Random Processes
    scheduler.GenerateRandomProcesses();

    
    //-- First Come First Serve Algorithm
    scheduler.FCFS();
    //-- Simulate Processes Time Line
    scheduler.simulateProcessesTimeLine();
    //-- Shortest Job First Algorithm
    scheduler.SJF();
    //-- Simulate Processes Time Line
    scheduler.simulateProcessesTimeLine();
    //-- Shortest Remaining Time First Algorithm
    scheduler.SRTF();
    //-- Simulate Processes Time Line
    scheduler.simulateProcessesTimeLine();
    //-- Highest Response Ratio Next Algorithm
    scheduler.HRRN();
    //-- Simulate Processes Time Line
    scheduler.simulateProcessesTimeLine();


    //-- Round Robin Algorithm
    scheduler.RR();
    //-- MLFQ Algorithm
    scheduler.MLFQ();
    //-- SPN Algorithm
    scheduler.SPN();
    //-- GS Algorithm
    scheduler.GS();
    return 0;
}