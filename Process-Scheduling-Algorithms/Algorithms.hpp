//-- Check RKACPB Project Builder
# ifndef RKACPB
    # pragma message \
        "This Project is Part of 40021441054102 Projects. You are Using It as a Standalone Project"
    # pragma message \
        "If You Want to Compile This Project Under Support, You Must Use RKACPB from https://github.com/RamtinKosari/RKACPB"
    # pragma message \
        "Compiling without RKACPB Support."
# else
    # pragma message \
        "40021441054102 Project Configured and Initialized Successfully, Compiling Under RKACPB Support"
# endif // RKACPB
//-- Check Operating System
# ifdef _WIN32
    # pragma message \
        "Operating System: Windows"
# elif __linux__
    # pragma message \
        "Operating System: Linux"
# elif __APPLE__ || __MACH__
    # pragma message \
        "Operating System: MacOS"
# elif __ANDROID__
    # pragma message \
        "Operating System: FreeBSD"
# else
    # warning message \
        "Operating System: Unknown"
# endif // Check Operating System

//-- Algorithms
# ifndef ALGORITHMS_DR_HAGHIGHAT
    /**
     * @file Algorithms.hpp
     * @author Ramtin Kosari (ramtinkosari@gmail.com)
     * @brief Operating System Lab Project - Process Scheduling Algorithms
     * @date 2024-05-29
     * @def ALGORITHMS_DR_HAGHIGHAT
     * @brief Process Scheduling Algorithms Macro
     * @details This Macro is Defined to Include Process Scheduling Algorithms
     */
    # define ALGORITHMS_DR_HAGHIGHAT
    //-- Include Configs
    # ifndef ALGORITHMS_DR_HAGHIGHAT_CONFIGS
        # include "Configs.hpp"
    # endif // ALGORITHMS_DR_HAGHIGHAT_CONFIGS
    //-- Include IOStream
    # ifndef _GLIBCXX_IOSTREAM
        # include <iostream>
    # endif // _GLIBCXX_IOSTREAM
    //-- Include Vector
    # ifndef _GLIBCXX_VECTOR
        # include <vector>
    # endif // _GLIBCXX_VECTOR
    //-- Include Chrono
    # ifndef _GLIBCXX_CHRONO
        # include <chrono>
    # endif // _GLIBCXX_CHRONO
    //-- Include Random
    # ifndef _GLIBCXX_RANDOM
        # include <random>
    # endif // _GLIBCXX_RANDOM
    //-- Include Algorithm
    # ifndef _GLIBCXX_ALGORITHM
        # include <algorithm>
    # endif // _GLIBCXX_ALGORITHM
    //-- Include Thread
    # ifndef _GLIBCXX_THREAD
        # include <thread>
    # endif // _GLIBCXX_THREAD
    //-- Include Queue
    # ifndef _GLIBCXX_QUEUE
        # include <queue>
    # endif // _GLIBCXX_QUEUE
    /**
     * @class ProcessScheduler
     * @brief ProcessScheduler Class
     * @details This Class is Used to Schedule Processes Using Different Algorithms
     * 
     * @param algorithm_duration Process Time of Algorithm
     * @param begin_time Begin Time of Algorithm
     * @param end_time End Time of Algorithm
     * @param data Data Vector
     */
    class ProcessScheduler {
        private:
            /**
             * @brief Represents the Starting Time Point.
             * @details The Variable is Initialized in the Constructor and Used to Calculate the Processing Time of the Algorithm.
             */
            std::chrono::high_resolution_clock::time_point begin_time;
            /**
             * @brief Represents the Ending Time Point.
             * @details The Variable is Initialized in the Destructor and Used to Calculate the Processing Time of the Algorithm.
             */
            std::chrono::high_resolution_clock::time_point end_time;
            /**
             * @brief Represents the Duration of the Algorithm.
             * @details The Variable is Calculated in the Destructor and Used to Show the Processing Time of the Algorithm.
             */
            std::chrono::duration<double> algorithm_duration;
            /**
             * @brief Represents Process
             * @details This Structure is Used to Store Process Information
             * @param completion_time Completion Time of Process
             * @param turnaround_time Turnaround Time of Process
             * @param remaining_time Remaining Time of Process
             * @param waiting_time Waiting Time of Process
             * @param arrival_time Arrival Time of Process
             * @param process_id Process ID
             * @param burst_time Burst Time of Process
             * @param priority Priority of Process
             */
            struct Process {
                std::int64_t completion_time;
                std::int64_t turnaround_time;
                std::int64_t remaining_time;
                std::int64_t waiting_time;
                std::int64_t arrival_time;
                std::int64_t process_id;
                std::int64_t burst_time;
                std::int64_t priority;
            } process;
            /**
             * @brief Represents List of Processes
             * @details This Vector is Used to Store List of Processes
             */
            std::vector<Process> PIDs;
        public:
            /**
             * @brief ProcessScheduler Constructor
             * @details This Constructor Initializes ProcessScheduler Class
             */
            ProcessScheduler();
            /**
             * @brief Method to Generate Random Processes
             * @details This Method Generates Random Processes
             */
            void GenerateRandomProcesses();
            /**
             * @brief Method to Simulate Processes Time Line
             * @details This Method Simulates Processes Time Line
             */
            void simulateProcessesTimeLine();
            // ------------------- //
            // -- Batch Systems -- //
            // ------------------- //
            /**
             * @brief First Come First Serve Algorithm
             * @details This Function Schedules Processes Using First Come First Serve Algorithm
             * @note This Algorithm is being Used in Batch Processing Systems
             */
            void FCFS();
            /**
             * @brief Shortest Job First Algorithm
             * @details This Function Schedules Processes Using Shortest Job First Algorithm
             * @note This Algorithm is being Used in Batch Processing Systems
             */
            void SJF();
            /**
             * @brief Shortest Remaining Time First Algorithm
             * @details This Function Schedules Processes Using Shortest Remaining Time First Algorithm
             * @note This Algorithm is being Used in Batch Processing Systems
             */
            void SRTF();
            /**
             * @brief Highest Response Ratio Next Algorithm
             * @details This Function Schedules Processes Using Highest Response Ratio Next Algorithm
             * @note This Algorithm is being Used in Batch Processing Systems
             */
            void HRRN();
            // ------------------------- //
            // -- Interactive Systems -- //
            // ------------------------- //
            /**
             * @brief Round Robin Algorithm
             * @details This Function Schedules Processes Using Round Robin Algorithm
             * @note This Algorithm is being Used in Interactive Systems
             */
            void RR();
            /**
             * @brief Multilevel Feedback Queue Algorithm
             * @details This Function Schedules Processes Using Multilevel Feedback Queue Algorithm
             * @note This Algorithm is being Used in Interactive Systems
             */
            void MLFQ();
            /**
             * @brief Multilevel Queue Algorithm
             * @details This Function Schedules Processes Using Multilevel Queue Algorithm
             * @note This Algorithm is being Used in Interactive Systems
             */
            void MLQ();
            /**
             * @brief Priority Scheduling Algorithm
             * @details This Function Schedules Processes Using Priority Scheduling Algorithm
             * @note This Algorithm is being Used in Interactive Systems
             */
            void PS();
            /**
             * @brief Shortest Process Next Algorithm
             * @details This Function Schedules Processes Using Shortest Process Next Algorithm
             * @note This Algorithm is being Used in Interactive Systems
             */
            void SPN();
            /**
             * @brief Guaranteed Scheduling Algorithm
             * @details This Function Schedules Processes Using Guaranteed Scheduling Algorithm
             * @note This Algorithm is being Used in Interactive Systems
             */
            void GS();
            /**
             * @brief Lottery Scheduling Algorithm
             * @details This Function Schedules Processes Using Lottery Scheduling Algorithm
             * @note This Algorithm is being Used in Interactive Systems
             */
            void LS();
            // ----------------------- //
            // -- Real-Time Systems -- //
            // ----------------------- //
            /**
             * @brief Rate Monotonic Scheduling Algorithm
             * @details This Function Schedules Processes Using Rate Monotonic Scheduling Algorithm
             * @note This Algorithm is being Used in Real-Time Systems
             */
            void RMS();
            /**
             * @brief Earliest Deadline First Algorithm
             * @details This Function Schedules Processes Using Earliest Deadline First Algorithm
             * @note This Algorithm is being Used in Real-Time Systems
             */
            void EDF();
            /**
             * @brief Least Laxity First Algorithm
             * @details This Function Schedules Processes Using Least Laxity First Algorithm
             * @note This Algorithm is being Used in Real-Time Systems
             */
            void LLF();
            // --------------------- //
            // -- Other Functions -- //
            // --------------------- //
            //-- Helper Function to Check if All Queues are Empty
            bool allQueuesEmpty(const std::vector<std::queue<Process*>>& queues) {
                std::cout << WARNING << "Checking if All Queues are Empty" << RESET << std::endl;
                for (const auto& q : queues) {
                    if (!q.empty()) {
                        return false;
                    }
                }
                return true;
            }
    };
# endif // ALGORITHMS_DR_HAGHIGHAT