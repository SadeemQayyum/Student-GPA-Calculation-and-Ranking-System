

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// ── Constants ─────────────────────────────────────────────────
const int MAX_STUDENTS = 100;
const int NUM_SUBJECTS = 5;

// ── Subject Structure ──────────────────────────────────────────
struct Subject {
    float marks;        // marks out of 100
    int   creditHours;  // credit hours max 4
    float gradePoints;  // computed grade points (0.0 to 4.0)
    char  grade;        // letter grade for this subject
};

// ── Student Structure ──────────────────────────────────────────
struct Student {
    string  name;
    int     rollNumber;
    Subject subjects[NUM_SUBJECTS];  // 5 subjects
    float   gpa;                     // weighted GPA (auto calculated)
    int     totalCreditHours;        // sum of all credit hours
};

// ── Global Student Array ───────────────────────────────────────
Student students[MAX_STUDENTS];
int     studentCount = 0;


void marksToGradePoints(Subject &sub) {
    float m = sub.marks;

    if      (m >= 90) { sub.gradePoints = 4.0f; sub.grade = 'A'; }  
    else if (m >= 80) { sub.gradePoints = 4.0f; sub.grade = 'A'; }  
    else if (m >= 75) { sub.gradePoints = 3.3f; sub.grade = 'B'; }  
    else if (m >= 71) { sub.gradePoints = 3.0f; sub.grade = 'B'; }
    else if (m >= 68) { sub.gradePoints = 2.7f; sub.grade = 'B'; }  
    else if (m >= 64) { sub.gradePoints = 2.3f; sub.grade = 'C'; }  
    else if (m >= 61) { sub.gradePoints = 2.0f; sub.grade = 'C'; }
    else if (m >= 58) { sub.gradePoints = 1.7f; sub.grade = 'C'; }  
    else if (m >= 54) { sub.gradePoints = 1.3f; sub.grade = 'D'; }  
    else if (m >= 50) { sub.gradePoints = 1.0f; sub.grade = 'D'; }
    else              { sub.gradePoints = 0.0f; sub.grade = 'F'; }
}


void computeGPA(Student &s) {
    float weightedSum  = 0;
    int   totalCredits = 0;

    for (int i = 0; i < NUM_SUBJECTS; i++) {
        marksToGradePoints(s.subjects[i]);  // convert marks to grade points
        weightedSum  += s.subjects[i].gradePoints * s.subjects[i].creditHours;
        totalCredits += s.subjects[i].creditHours;
    }

    s.totalCreditHours = totalCredits;
    s.gpa = (totalCredits > 0) ? (weightedSum / totalCredits) : 0.0f;
}


void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "  [!] System full.\n";
        return;
    }

    Student &s = students[studentCount];

    cout << "\n  Enter Name        : "; cin.ignore(); getline(cin, s.name);
    cout << "  Enter Roll Number : "; cin >> s.rollNumber;

    cout << "\n  Enter marks and credit hours for each subject:\n";

    for (int i = 0; i < NUM_SUBJECTS; i++) {
        cout << "\n  Subject " << (i + 1) << ":\n";
        cout << "    Marks (0-100)   : "; cin >> s.subjects[i].marks;

        // Validate credit hours — must be 1 to 4
        do {
            cout << "    Credit Hours (1-4): "; cin >> s.subjects[i].creditHours;
            if (s.subjects[i].creditHours < 1 || s.subjects[i].creditHours > 4)
                cout << "    [!] Credit hours must be 1 to 4. Try again.\n";
        } while (s.subjects[i].creditHours < 1 || s.subjects[i].creditHours > 4);
    }

    computeGPA(s);  // automatically calculate weighted GPA
    studentCount++;

    cout << "\n  [OK] Student added successfully!"
         << "\n       Weighted GPA  : " << fixed << setprecision(2) << s.gpa
         << "\n       Total Credits : " << s.totalCreditHours << "\n";
}


void bubbleSort() {
    for (int i = 0; i < studentCount - 1; i++) {
        bool swapped = false;  // track if any swap happened this pass

        for (int j = 0; j < studentCount - 1 - i; j++) {
            if (students[j].gpa < students[j + 1].gpa) {
                swap(students[j], students[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;  // no swaps = already sorted, exit early
    }
}


void selectionSort() {
    for (int i = 0; i < studentCount - 1; i++) {
        int maxIdx = i;  // assume current position has highest GPA

        // Scan rest of array to find actual highest GPA
        for (int j = i + 1; j < studentCount; j++) {
            if (students[j].gpa > students[maxIdx].gpa)
                maxIdx = j;
        }

        // Swap highest found into correct position
        if (maxIdx != i)
            swap(students[i], students[maxIdx]);
    }
}


int linearSearch(int roll) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == roll)
            return i;   // found at index i
    }
    return -1;  // not found
}


int binarySearch(int roll) {
    // Make a temp copy sorted by rollNumber for binary search
    Student temp[MAX_STUDENTS];
    for (int i = 0; i < studentCount; i++) temp[i] = students[i];

    // Sort temp by rollNumber ascending (selection sort)
    for (int i = 0; i < studentCount - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < studentCount; j++)
            if (temp[j].rollNumber < temp[minIdx].rollNumber)
                minIdx = j;
        swap(temp[i], temp[minIdx]);
    }

    int lo = 0, hi = studentCount - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;  // safe midpoint (prevents overflow)

        if (temp[mid].rollNumber == roll) {
            // Found in temp — get index from original GPA-sorted array
            for (int i = 0; i < studentCount; i++)
                if (students[i].rollNumber == roll) return i;
        }
        else if (temp[mid].rollNumber < roll)
            lo = mid + 1;   // roll is in right half
        else
            hi = mid - 1;   // roll is in left half
    }

    return -1;  // not found
}


void displayLeaderboard() {
    if (studentCount == 0) {
        cout << "\n  No students in the system.\n";
        return;
    }

    // Column widths: Rank(5) Name(25) Roll(10) Credits(10) GPA(8) Grade(6)
    cout << "\n  " << string(64, '=') << "\n";
    cout << "  "
         << left  << setw(5)  << "Rank"
         << left  << setw(25) << "Name"
         << right << setw(8)  << "Roll"
         << right << setw(9)  << "Credits"
         << right << setw(7)  << "GPA"
         << right << setw(7)  << "Grade" << "\n";
    cout << "  " << string(64, '-') << "\n";

    for (int i = 0; i < studentCount; i++) {
        // Determine overall letter grade from GPA value
        char overallGrade;
        float g = students[i].gpa;
        if      (g >= 3.7f) overallGrade = 'A';
        else if (g >= 3.0f) overallGrade = 'B';
        else if (g >= 2.0f) overallGrade = 'C';
        else if (g >= 1.0f) overallGrade = 'D';
        else                overallGrade = 'F';

        // Truncate name to 24 chars if too long to keep alignment
        string displayName = students[i].name;
        if (displayName.length() > 24)
            displayName = displayName.substr(0, 21) + "...";

        cout << "  "
             << left  << setw(5)  << (i + 1)
             << left  << setw(25) << displayName
             << right << setw(8)  << students[i].rollNumber
             << right << setw(9)  << students[i].totalCreditHours
             << right << setw(7)  << fixed << setprecision(2) << students[i].gpa
             << right << setw(7)  << overallGrade << "\n";
    }

    cout << "  " << string(64, '=') << "\n";
}


void displayStudent(int idx) {
    if (idx < 0) {
        cout << "  [!] Student not found.\n";
        return;
    }

    Student &s = students[idx];

    cout << "\n  " << string(50, '-') << "\n"
         << "  Name           : " << s.name            << "\n"
         << "  Roll No.       : " << s.rollNumber       << "\n"
         << "  Total Credits  : " << s.totalCreditHours << "\n"
         << "  Weighted GPA   : " << fixed << setprecision(2) << s.gpa << " / 4.0\n"
         << "  " << string(50, '-') << "\n";

    cout << "\n  Subject Breakdown:\n";
    cout << "  " << string(52, '-') << "\n";
    cout << "  "
         << left  << setw(10) << "Subject"
         << right << setw(8)  << "Marks"
         << right << setw(9)  << "Credits"
         << right << setw(10) << "GradePts"
         << right << setw(8)  << "Grade" << "\n";
    cout << "  " << string(52, '-') << "\n";

    for (int i = 0; i < NUM_SUBJECTS; i++) {
        cout << "  "
             << left  << setw(10) << (i + 1)
             << right << setw(8)  << fixed << setprecision(1) << s.subjects[i].marks
             << right << setw(9)  << s.subjects[i].creditHours
             << right << setw(10) << setprecision(1) << s.subjects[i].gradePoints
             << right << setw(8)  << s.subjects[i].grade << "\n";
    }

    cout << "  " << string(52, '-') << "\n";
}


int main() {
    cout << "\n  ================================================\n"
         << "    Student Grade & Ranking System\n"
         << "    Author  : Sadeem\n"
         << "    Course  : Data Structures & Algorithms\n"
         << "  ================================================\n";

    int choice;
    do {
        cout << "\n  1. Add Student\n"
             << "  2. Sort by GPA  (Bubble Sort)\n"
             << "  3. Sort by GPA  (Selection Sort)\n"
             << "  4. Search       (Linear Search)\n"
             << "  5. Search       (Binary Search)\n"
             << "  6. Display Leaderboard\n"
             << "  0. Exit\n"
             << "  Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                if (studentCount == 0) { cout << "  No students.\n"; break; }
                bubbleSort();
                cout << "  [OK] Sorted with Bubble Sort.\n";
                displayLeaderboard();
                break;

            case 3:
                if (studentCount == 0) { cout << "  No students.\n"; break; }
                selectionSort();
                cout << "  [OK] Sorted with Selection Sort.\n";
                displayLeaderboard();
                break;

            case 4: {
                int roll;
                cout << "  Enter roll number: "; cin >> roll;
                displayStudent(linearSearch(roll));
                break;
            }

            case 5: {
                int roll;
                cout << "  Enter roll number: "; cin >> roll;
                displayStudent(binarySearch(roll));
                break;
            }

            case 6:
                displayLeaderboard();
                break;

            case 0:
                cout << "\n  Goodbye! - Sadeem\n\n";
                break;

            default:
                cout << "  [!] Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
