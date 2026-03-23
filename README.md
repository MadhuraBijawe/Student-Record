# 📚 Student Record Management System (C Language)

A command-line based application built in **C** to manage student records efficiently using **file handling** and **structured data storage**.

---

## 🚀 Features

| Feature | Description |
|---|---|
| **Add Record** | Add a new student with ID, name, department, age, and CGPA |
| **Display All** | View all stored student records in a formatted table |
| **Search** | Find a student by their unique ID |
| **Update** | Modify any existing student's details |
| **Delete** | Remove a student record permanently |
| **Toppers** | List students with CGPA ≥ 8.5 |

---

## 🛠️ Tech Stack

- **Language:** C (C99 standard)
- **Concepts:** File Handling, Structs, Binary File I/O, Menu-Driven Design
- **Storage:** Binary flat-file (`students.dat`) for persistent data

---

## 📁 Project Structure

```
student_record_system/
│
├── student_record.c     # Main source file (all logic)
├── students.dat         # Auto-generated binary data file (after first run)
└── README.md            # Project documentation
```

---

## ⚙️ How to Compile & Run

### On Linux / macOS

```bash
# Step 1: Clone or download the project
git clone https://github.com/yourusername/student-record-system.git
cd student-record-system

# Step 2: Compile
gcc student_record.c -o student_record

# Step 3: Run
./student_record
```

### On Windows (using GCC / MinGW)

```bash
gcc student_record.c -o student_record.exe
student_record.exe
```

---

## 🖥️ Usage / Sample Output

```
============================================================
   STUDENT RECORD MANAGEMENT SYSTEM
   MAIN MENU
============================================================
  1. Add Student Record
  2. Display All Records
  3. Search Student by ID
  4. Update Student Record
  5. Delete Student Record
  6. Display Top Students (CGPA >= 8.5)
  0. Exit
============================================================
  Enter your choice: 1

Enter Student ID   : 101
Enter Name         : Rahul Sharma
Enter Department   : Computer Science
Enter Age          : 20
Enter CGPA (0-10)  : 9.1

[✓] Student record added successfully!
```

---

## 📐 Key Concepts Demonstrated

- **Binary File I/O** — `fread()` / `fwrite()` for persistent storage across sessions
- **Struct-based data modeling** — encapsulates student fields in a single `Student` struct
- **File pointer manipulation** — `fseek()` used for in-place record updates
- **Temp file trick** — safe delete by writing non-deleted records to a temp file and replacing the original
- **Input validation** — CGPA range check, duplicate ID detection
- **Cross-platform support** — `system("clear")` / `system("cls")` handled with `#ifdef`

---

## 🗂️ Data File Format

Records are stored in binary format (`students.dat`) using the following struct:

```c
typedef struct {
    int   id;              // Unique student ID
    char  name[50];        // Full name
    char  department[30];  // Department name
    float cgpa;            // CGPA (0.0 – 10.0)
    int   age;             // Age
} Student;
```

Each record occupies a fixed size of `sizeof(Student)` bytes, allowing O(1) random access using `fseek()`.

---

## 🔧 Possible Extensions

- Sort records by CGPA or name using `qsort()`
- Export records to a `.csv` file
- Add department-wise filtering
- Implement a simple login system

---

## 👨‍💻 Author

**Madhura Bijawe**  


---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).
