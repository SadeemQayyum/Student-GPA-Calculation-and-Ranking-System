#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <chrono>   // time measurement ke liye
using namespace std;
using namespace std::chrono;  // chrono shorthand

//Constants
const int MAX_STUDENTS = 100;
const int NUM_SUBJECTS = 5;

// Subject Structure
struct Subject{
    float marks;        // marks out of 100
    int   creditHours;  // credit hours max 4
    float gradePoints;  // computed grade points (0.0 to 4.0)
    char  grade;        // letter grade for this subject
};

//Student Structure
struct Student {
    string  name;
    int     rollNumber;
    Subject subjects[NUM_SUBJECTS];  // 5 subjects
    float   gpa;                     // weighted GPA (auto calculated)
    int     totalCreditHours;        // sum of all credit hours
};

//Global Student Array
Student students[MAX_STUDENTS];
int     studentCount=0;

//  Timing History (last run of each algorithm) 
double lastBubbleTime     = -1;  // -1 means "not run yet"
double lastSelectionTime  = -1;
double lastLinearTime     = -1;
double lastBinaryTime     = -1;

// --- Helper: print time in readable format ----------------------------------
void printTime(const string &label, double microseconds) {
    cout << "\n  +------------------------------------------+\n";
    cout << "  |  [TIME]  " << left << setw(32) << label << "|\n";
    if (microseconds < 1000.0)
        cout << "  |  Time taken : " << fixed << setprecision(5)
             << microseconds << " microseconds        |\n";
    else
        cout << "  |  Time taken : " << fixed << setprecision(5)
             << (microseconds / 1000.0) << " milliseconds        |\n";
    cout << "  +------------------------------------------+\n";
}

// --- Algorithm Comparison Table ---------------------------------------------
void showComparison() {
    cout << "\n  +==============================================================+\n";
    cout << "  |          ALGORITHM TIMING COMPARISON                         |\n";
    cout << "  +==============================================================+\n";
    cout << "  | " << left << setw(20) << "Algorithm"
         << setw(20) << "Time (microsec)"
         << setw(20) << "Complexity" << " |\n";
    cout << "  +--------------------+-------------------+--------------------+\n";

    auto printRow = [](const string &name, double t, const string &complexity) {
        cout << "  | " << left << setw(20) << name;
        if (t < 0) {
            cout << setw(20) << "Not run yet";
        } else if (t < 1000.0) {
            ostringstream oss;
            oss << fixed << setprecision(5) << t << " us";
            cout << setw(20) << oss.str();
        } else {
            ostringstream oss;
            oss << fixed << setprecision(5) << (t/1000.0) << " ms";
            cout << setw(20) << oss.str();
        }
        cout << setw(20) << complexity << " |\n";
    };

    printRow("Bubble Sort",    lastBubbleTime,    "O(n^2)");
    printRow("Selection Sort", lastSelectionTime, "O(n^2)");
    cout << "  +--------------------+-------------------+--------------------+\n";
    printRow("Linear Search",  lastLinearTime,    "O(n)");
    printRow("Binary Search",  lastBinaryTime,    "O(log n)");

    cout << "  +==============================================================+\n";
    cout << "  (Run each algorithm first to see its time)\n";
}


void marksToGradePoints(Subject &sub){
    float m=sub.marks;

    if      (m>=90){sub.gradePoints=4.0f;sub.grade='A';}  
    else if (m>=80){sub.gradePoints=4.0f;sub.grade='A';}  
    else if (m>=75){sub.gradePoints=3.3f;sub.grade='B';}  
    else if (m>=71){sub.gradePoints=3.0f;sub.grade='B';}
    else if (m>=68){sub.gradePoints=2.7f;sub.grade='B';}  
    else if (m>=64){sub.gradePoints=2.3f;sub.grade='C';}  
    else if (m>=61){sub.gradePoints=2.0f;sub.grade='C';}
    else if (m>=58){sub.gradePoints=1.7f;sub.grade='C';}  
    else if (m>=54){sub.gradePoints=1.3f;sub.grade='D';}  
    else if (m>=50){sub.gradePoints=1.0f;sub.grade='D';}
    else {sub.gradePoints= 0.0f;sub.grade='F';}
}


void computeGPA(Student &s){
    float weightedSum=0;
    int   totalCredits=0;

    for (int i=0;i<NUM_SUBJECTS;i++){
        marksToGradePoints(s.subjects[i]);
        weightedSum +=s.subjects[i].gradePoints * s.subjects[i].creditHours;
        totalCredits +=s.subjects[i].creditHours;
    }

    s.totalCreditHours=totalCredits;
    s.gpa = (totalCredits > 0) ? weightedSum/totalCredits : 0.0f;
}


void addStudent() {
    if (studentCount>=MAX_STUDENTS){
        cout<<" [!] System full.\n";
        return;
    }

    Student &s=students[studentCount];

    cout<<"\n Enter Name : "; cin.ignore(); getline(cin,s.name);
    cout<<" \n Enter Roll Number : "; cin>>s.rollNumber;

    cout<<"\n Enter marks and credit hours for each subject:\n";

    for(int i=0;i<NUM_SUBJECTS;i++){
        cout<<"\n Subject "<<(i + 1)<<" :\n";
        cout<< " Marks (0-100) : "; cin>>s.subjects[i].marks;

        do {
            cout << "    Credit Hours (1-4): "; cin >> s.subjects[i].creditHours;
            if (s.subjects[i].creditHours < 1 || s.subjects[i].creditHours > 4)
                cout << "    [!] Credit hours must be 1 to 4. Try again.\n";
        } while (s.subjects[i].creditHours < 1 || s.subjects[i].creditHours > 4);
    }

    computeGPA(s);
    studentCount++;

    cout << "\n  [OK] Student added successfully!"
         << "\n       Weighted GPA  : " << fixed << setprecision(2) << s.gpa
         << "\n       Total Credits : " << s.totalCreditHours << "\n";
}


//  BUBBLE SORT - with timing 
void bubbleSort() {
    auto start = high_resolution_clock::now();   //  start

    for (int i = 0; i < studentCount - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < studentCount - 1 - i; j++) {
            if (students[j].gpa < students[j + 1].gpa) {
                swap(students[j], students[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }

    auto end = high_resolution_clock::now();     //  stop
    lastBubbleTime = duration_cast<nanoseconds>(end - start).count() / 1000.0;  // microseconds mein save

    printTime("Bubble Sort", lastBubbleTime);
}


//  SELECTION SORT - with timing 
void selectionSort() {
    auto start = high_resolution_clock::now();   //  start

    for (int i = 0; i < studentCount - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < studentCount; j++) {
            if (students[j].gpa > students[maxIdx].gpa)
                maxIdx = j;
        }
        if (maxIdx != i)
            swap(students[i], students[maxIdx]);
    }

    auto end = high_resolution_clock::now();     //  stop
    lastSelectionTime = duration_cast<nanoseconds>(end - start).count() / 1000.0;

    printTime("Selection Sort", lastSelectionTime);
}


//  LINEAR SEARCH - with timing 
int linearSearch(int roll) {
    auto start = high_resolution_clock::now();   //  start

    int result = -1;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == roll) {
            result = i;
            break;
        }
    }

    auto end = high_resolution_clock::now();     //  stop
    lastLinearTime = duration_cast<nanoseconds>(end - start).count() / 1000.0;

    printTime("Linear Search", lastLinearTime);
    return result;
}


//  BINARY SEARCH - with timing 
int binarySearch(int roll) {
    auto start = high_resolution_clock::now();   //  start

    // Temp copy sorted by rollNumber
    Student temp[MAX_STUDENTS];
    for (int i = 0; i < studentCount; i++) temp[i] = students[i];

    for (int i = 0; i < studentCount - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < studentCount; j++)
            if (temp[j].rollNumber < temp[minIdx].rollNumber)
                minIdx = j;
        swap(temp[i], temp[minIdx]);
    }

    int lo = 0, hi = studentCount - 1, result = -1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        if (temp[mid].rollNumber == roll) {
            for (int i = 0; i < studentCount; i++)
                if (students[i].rollNumber == roll) { result = i; break; }
            break;
        }
        else if (temp[mid].rollNumber < roll)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    auto end = high_resolution_clock::now();     //  stop
    lastBinaryTime = duration_cast<nanoseconds>(end - start).count() / 1000.0;

    printTime("Binary Search", lastBinaryTime);
    return result;
}


void displayLeaderboard() {
    if (studentCount == 0) {
        cout << "\n  No students in the system.\n";
        return;
    }

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
        char overallGrade;
        float g = students[i].gpa;
        if      (g >= 3.7f) overallGrade = 'A';
        else if (g >= 3.0f) overallGrade = 'B';
        else if (g >= 2.0f) overallGrade = 'C';
        else if (g >= 1.0f) overallGrade = 'D';
        else                overallGrade = 'F';

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
         << "    Course  : Analysis of Algorithms\n"
         << "  ================================================\n";

    int choice;
    do {
        cout << "\n  1. Add Student\n"
             << "  2. Sort by GPA  (Bubble Sort)\n"
             << "  3. Sort by GPA  (Selection Sort)\n"
             << "  4. Search       (Linear Search)\n"
             << "  5. Search       (Binary Search)\n"
             << "  6. Display Leaderboard\n"
             << "  7. Algorithm Timing Comparison\n"   // <-- NEW option
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

            case 7:                    // <-- Timing comparison
                showComparison();
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
