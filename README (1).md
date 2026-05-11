# 🎓 Student Grade & Ranking System

> A console-based C++ application for managing student grades, computing weighted GPAs, and ranking students — built as a Data Structures & Algorithms project.

---

## 📌 Overview

This system allows you to add students with their subject marks and credit hours, automatically computes their **weighted GPA**, and lets you **sort**, **search**, and **display** a ranked leaderboard — all from a simple terminal menu.

---

## ✨ Features

| Feature | Description |
|---|---|
| ➕ Add Student | Input name, roll number, marks & credit hours for 5 subjects |
| 📊 Weighted GPA | Auto-calculated from grade points × credit hours |
| 🔤 Letter Grades | Per-subject grades (A, B, C, D, F) based on marks |
| 🫧 Bubble Sort | Sort leaderboard by GPA using Bubble Sort |
| 🔃 Selection Sort | Sort leaderboard by GPA using Selection Sort |
| 🔍 Linear Search | Find a student by roll number (sequential scan) |
| ⚡ Binary Search | Find a student by roll number (sorted copy + binary search) |
| 🏆 Leaderboard | Ranked table showing all students with GPA and grade |

---

## 🗂️ Project Structure

```
sadeem_Student_grade_system.cpp   ← single-file C++ source
```

---

## ⚙️ How It Works

### Grade Point Conversion

| Marks Range | Grade Points | Letter Grade |
|---|---|---|
| 90 – 100 | 4.0 | A |
| 80 – 89 | 4.0 | A |
| 75 – 79 | 3.3 | B |
| 71 – 74 | 3.0 | B |
| 68 – 70 | 2.7 | B |
| 64 – 67 | 2.3 | C |
| 61 – 63 | 2.0 | C |
| 58 – 60 | 1.7 | C |
| 54 – 57 | 1.3 | D |
| 50 – 53 | 1.0 | D |
| < 50 | 0.0 | F |

### Weighted GPA Formula

```
GPA = Σ (Grade Points × Credit Hours) / Σ Credit Hours
```

---

## 🚀 Getting Started

### Prerequisites
- A C++ compiler (g++, clang++, MSVC, etc.)
- C++11 or later

### Compile & Run

```bash
# Compile
g++ -std=c++11 -o grade_system sadeem_Student_grade_system.cpp

# Run
./grade_system
```

On Windows:
```bash
g++ -std=c++11 -o grade_system.exe sadeem_Student_grade_system.cpp
grade_system.exe
```

---

## 🖥️ Menu Options

```
1. Add Student
2. Sort by GPA  (Bubble Sort)
3. Sort by GPA  (Selection Sort)
4. Search       (Linear Search)
5. Search       (Binary Search)
6. Display Leaderboard
0. Exit
```

---

## 📋 Sample Output

```
  ================================================
    Student Grade & Ranking System
    Author  : Sadeem
    Course  : Data Structures & Algorithms
  ================================================

  ================================================================
  Rank  Name                      Roll  Credits    GPA  Grade
  ----------------------------------------------------------------
  1     Ali Hassan                1001       15   3.87      A
  2     Sara Khan                 1003       14   3.21      B
  3     Umar Farooq               1002       13   2.65      C
  ================================================================
```

---

## 📐 Constraints

- Maximum **100 students** supported
- Each student has exactly **5 subjects**
- Credit hours per subject: **1 to 4**
- Marks per subject: **0 to 100**

---

## 🧠 Algorithms Used

| Algorithm | Used For | Time Complexity |
|---|---|---|
| Bubble Sort | GPA ranking | O(n²) |
| Selection Sort | GPA ranking | O(n²) |
| Linear Search | Find by roll number | O(n) |
| Binary Search | Find by roll number (on sorted copy) | O(n log n) |

> **Note:** Binary search sorts a temporary copy of the array by roll number before searching, so the main GPA-sorted order is preserved.

---

## 👩‍💻 Author

**Sadeem**
*Data Structures & Algorithms — C++ Project*

---

## 📄 License

This project is for educational purposes.
