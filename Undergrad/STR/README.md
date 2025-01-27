# Real-Time Systems (STR)

This repository contains laboratory assignments for the Real-Time Systems course, part of the Master's program in Electrical and Computer Engineering.

## Repository Contents

### STR Lab #1: Real-Time Systems Concepts and Kernels

This lab introduces foundational concepts of real-time systems and tasks students with developing a project utilizing a real-time kernel. The focus areas include:

- **Interaction with Physical Systems:** Integration of interface boards, sensors, and actuators, along with the use of data acquisition boards.
- **Real-Time System Basics:** Understanding tasks, processes, synchronization, and shared resource management.
- **FreeRTOS Utilization:** Employing the FreeRTOS kernel for concurrent task management.
- **Practical Project:** Development of a game system ("Rooster Game") simulating a compact 3x3 storage environment with real-time behavior, interfaced via hardware kits or simulators.

This lab introduces key real-time programming constructs like semaphores for synchronization, queues for inter-task communication, and handling critical sections to prevent race conditions. Tools and programming languages used include C/C++ and Visual Studio.

### STR Lab #2: Advanced Real-Time Applications

In this assignment, students develop real-time applications using high-level programming languages. Key learning objectives include:

- **Task Synchronization and Communication:** Utilizing FreeRTOS mechanisms like semaphores, mailboxes, and message queues to manage interactions between tasks.
- **Handling Concurrency Issues:** Addressing problems like race conditions, ensuring safe access to shared resources using critical sections.
- **Programming Tasks:** Creating tasks to manage storage systems while ensuring synchronization and cooperation.

The lab involves the use of Java for high-level programming, along with dynamic-link libraries (DLLs) to facilitate interaction with hardware components. Threads are extensively used to implement robust and efficient task management.

### STR Lab #3: Petri Nets and Real-Time Modeling

This lab dives into using Petri Nets as a tool to visualize and understand the behavior of real-time systems. Exploring how processes flow, how tasks synchronize, and how to avoid common pitfalls like deadlocks. It’s a hands-on approach to modeling task dependencies and managing resources effectively in concurrent systems.

## Theoretical Concepts Covered

Throughout these labs, students gain hands-on experience with essential real-time system concepts, including:

- **Semaphores:** Synchronization tools to manage resource access.
- **Queues:** Mechanisms for inter-task communication.
- **Critical Sections:** Preventing race conditions by defining exclusive access areas in code.
- **Deadlock and Resource Allocation:** Avoiding system freezes and ensuring efficient task scheduling.
- **Concurrency and Parallelism:** Techniques to manage multiple simultaneous tasks effectively.

## Authors

- **Matheus Brito** (57003)  
- **Guilherme Concha** (60143)  
- **José Guerreiro** (60036)

## Institution

Department of Electrical and Computer Engineering (DEEC), NOVA School of Science and Technology (NOVA-FCT).
