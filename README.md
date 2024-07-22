# Student Management System

A C program designed to manage an infinite list of students, handling their academic records throughout their studies. 

## Features

- **Student Representation**: Each student is represented by:
  - Student ID
  - Last Name
  - First Name
  - Date of Birth
  - Date of Enrollment
  - Modules and their grades

- **Academic Structure**:
  - **Bachelor's Degree**: 6 semesters
  - **Master's Degree**: 4 semesters

- **Modules**:
  - Each semester contains various modules.
  - Each module includes:
    - Continuous Assessment Grade
    - Exam Grade
    - Average Grade

## Requirements

- A C compiler (e.g., GCC)
- Standard C library

## Compilation

To compile the program, use the following command:

```bash
gcc -o student_management main.c
