/*
 * Student Record Management System
 * Author: [Your Name]
 * Description: A command-line application to manage student records using file handling in C.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_DEPT 30
#define FILE_NAME "students.dat"

// ─── Data Structure ───────────────────────────────────────────────────────────

typedef struct {
    int    id;
    char   name[MAX_NAME];
    char   department[MAX_DEPT];
    float  cgpa;
    int    age;
} Student;

// ─── Utility ──────────────────────────────────────────────────────────────────

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    printf("\nPress Enter to continue...");
    getchar(); getchar();
}

void printDivider() {
    printf("============================================================\n");
}

void printHeader(const char *title) {
    printDivider();
    printf("   STUDENT RECORD MANAGEMENT SYSTEM\n");
    printf("   %s\n", title);
    printDivider();
}

// ─── Core Operations ──────────────────────────────────────────────────────────

int studentExists(int id) {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) return 0;
    Student s;
    while (fread(&s, sizeof(Student), 1, fp))
        if (s.id == id) { fclose(fp); return 1; }
    fclose(fp);
    return 0;
}

void addStudent() {
    clearScreen();
    printHeader("ADD NEW STUDENT");

    Student s;
    printf("Enter Student ID   : "); scanf("%d", &s.id);

    if (studentExists(s.id)) {
        printf("\n[!] Student with ID %d already exists!\n", s.id);
        pauseScreen(); return;
    }

    printf("Enter Name         : "); scanf(" %[^\n]", s.name);
    printf("Enter Department   : "); scanf(" %[^\n]", s.department);
    printf("Enter Age          : "); scanf("%d", &s.age);
    printf("Enter CGPA (0-10)  : "); scanf("%f", &s.cgpa);

    if (s.cgpa < 0 || s.cgpa > 10) {
        printf("\n[!] Invalid CGPA. Must be between 0 and 10.\n");
        pauseScreen(); return;
    }

    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) { perror("[!] File error"); pauseScreen(); return; }
    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);

    printf("\n[✓] Student record added successfully!\n");
    pauseScreen();
}

void displayAll() {
    clearScreen();
    printHeader("ALL STUDENT RECORDS");

    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) { printf("\n[!] No records found.\n"); pauseScreen(); return; }

    Student s;
    int count = 0;
    printf("%-6s %-20s %-18s %-5s %-6s\n", "ID", "Name", "Department", "Age", "CGPA");
    printDivider();

    while (fread(&s, sizeof(Student), 1, fp)) {
        printf("%-6d %-20s %-18s %-5d %-6.2f\n",
               s.id, s.name, s.department, s.age, s.cgpa);
        count++;
    }
    fclose(fp);

    if (count == 0) printf("No student records found.\n");
    else printf("\nTotal Records: %d\n", count);
    pauseScreen();
}

void searchStudent() {
    clearScreen();
    printHeader("SEARCH STUDENT");

    int id;
    printf("Enter Student ID to search: "); scanf("%d", &id);

    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) { printf("\n[!] No records found.\n"); pauseScreen(); return; }

    Student s;
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == id) {
            printf("\n--- Student Found ---\n");
            printf("ID         : %d\n",   s.id);
            printf("Name       : %s\n",   s.name);
            printf("Department : %s\n",   s.department);
            printf("Age        : %d\n",   s.age);
            printf("CGPA       : %.2f\n", s.cgpa);
            found = 1; break;
        }
    }
    fclose(fp);
    if (!found) printf("\n[!] No student found with ID %d.\n", id);
    pauseScreen();
}

void updateStudent() {
    clearScreen();
    printHeader("UPDATE STUDENT RECORD");

    int id;
    printf("Enter Student ID to update: "); scanf("%d", &id);

    FILE *fp = fopen(FILE_NAME, "r+b");
    if (!fp) { printf("\n[!] No records found.\n"); pauseScreen(); return; }

    Student s;
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == id) {
            printf("\nCurrent Record:\n");
            printf("Name: %s | Dept: %s | Age: %d | CGPA: %.2f\n",
                   s.name, s.department, s.age, s.cgpa);
            printf("\nEnter new details:\n");
            printf("New Name       : "); scanf(" %[^\n]", s.name);
            printf("New Department : "); scanf(" %[^\n]", s.department);
            printf("New Age        : "); scanf("%d", &s.age);
            printf("New CGPA       : "); scanf("%f", &s.cgpa);

            fseek(fp, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);
            printf("\n[✓] Record updated successfully!\n");
            found = 1; break;
        }
    }
    fclose(fp);
    if (!found) printf("\n[!] No student found with ID %d.\n", id);
    pauseScreen();
}

void deleteStudent() {
    clearScreen();
    printHeader("DELETE STUDENT RECORD");

    int id;
    printf("Enter Student ID to delete: "); scanf("%d", &id);

    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) { printf("\n[!] No records found.\n"); pauseScreen(); return; }

    FILE *tmp = fopen("temp.dat", "wb");
    if (!tmp) { fclose(fp); perror("[!] Temp file error"); pauseScreen(); return; }

    Student s;
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == id) { found = 1; continue; }
        fwrite(&s, sizeof(Student), 1, tmp);
    }
    fclose(fp); fclose(tmp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found) printf("\n[✓] Student with ID %d deleted successfully!\n", id);
    else       printf("\n[!] No student found with ID %d.\n", id);
    pauseScreen();
}

void displayToppers() {
    clearScreen();
    printHeader("TOP STUDENTS (CGPA >= 8.5)");

    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) { printf("\n[!] No records found.\n"); pauseScreen(); return; }

    Student s;
    int count = 0;
    printf("%-6s %-20s %-18s %-6s\n", "ID", "Name", "Department", "CGPA");
    printDivider();

    while (fread(&s, sizeof(Student), 1, fp))
        if (s.cgpa >= 8.5) {
            printf("%-6d %-20s %-18s %-6.2f\n", s.id, s.name, s.department, s.cgpa);
            count++;
        }
    fclose(fp);

    if (count == 0) printf("No students with CGPA >= 8.5 found.\n");
    else printf("\nTotal Toppers: %d\n", count);
    pauseScreen();
}

// ─── Main Menu ────────────────────────────────────────────────────────────────

int main() {
    int choice;
    do {
        clearScreen();
        printHeader("MAIN MENU");
        printf("  1. Add Student Record\n");
        printf("  2. Display All Records\n");
        printf("  3. Search Student by ID\n");
        printf("  4. Update Student Record\n");
        printf("  5. Delete Student Record\n");
        printf("  6. Display Top Students (CGPA >= 8.5)\n");
        printf("  0. Exit\n");
        printDivider();
        printf("  Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent();      break;
            case 2: displayAll();      break;
            case 3: searchStudent();   break;
            case 4: updateStudent();   break;
            case 5: deleteStudent();   break;
            case 6: displayToppers();  break;
            case 0: printf("\n[✓] Exiting. Goodbye!\n\n"); break;
            default: printf("\n[!] Invalid choice. Try again.\n"); pauseScreen();
        }
    } while (choice != 0);

    return 0;
}
