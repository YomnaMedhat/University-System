# University System

## Overview
This C++ program implements a university management system that handles course registration, student records, course waitlists, enrollment history, and more. The system makes use of data structures like stacks, queues, linked lists, binary search trees (BST), and hash tables.

## Features
- **Course Registration**: Uses a stack to validate prerequisites for course registration.
- **Course Waitlist**: Implements a queue to manage students waiting for a course.
- **Student Records**: Uses a singly linked list to store student details (ID, name, contact info, etc.).
- **Course Enrollment History**: Uses a doubly linked list to track student enrollments.
- **Search Operations**: Supports linear and binary search for student and course records.
- **Course Records (BST)**: Manages courses using a binary search tree.
- **Course Lookup (Hash Table)**: Uses hashing to store and search course records efficiently.

## Data Structures Used
- **Stack**: Handles prerequisite validation for course registration.
- **Queue**: Manages course waitlists.
- **Singly Linked List (SLL)**: Stores student records.
- **Doubly Linked List (DLL)**: Tracks course enrollment history.
- **Binary Search Tree (BST)**: Manages course records.
- **Hash Table**: Provides efficient course searching.

## How to Run
1. Compile the C++ program using a compiler like g++:
   ```sh
   g++ -o university_system UniversitySystem.cpp
   ```
2. Run the program:
   ```sh
   ./university_system
   ```
3. Follow the on-screen menu to navigate the university system.

## Menu Options
- **1. Course Registration**: Validate and register for a course.
- **2. Course Waitlist**: Add/remove students from the waitlist.
- **3. Student Records**: Add, delete, or display student details.
- **4. Course Enrollment History**: Manage student enrollment records.
- **5. Linear Search**: Search for a student by ID.
- **6. Binary Search**: Search for a course record.
- **7. Course Records (BST)**: Add, display, or drop courses.
- **8. Course Lookup (Hash Table)**: Add or search for a course.
- **0. Exit**: Exit the program.

## Dependencies
- A C++ compiler (e.g., g++)
- Standard C++ libraries (iostream, vector, string, etc.)

## Authors
- Yomna Medhat Saad
- Rania Ossama Hassan
- Mariam Hamada Mahmoud
- Noran Maged Hassan
