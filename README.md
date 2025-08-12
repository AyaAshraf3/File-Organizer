# File Organizer (Option 1)

## Option Chosen
**Option 1 – File Organizer**  
This program organizes files in a given folder by their type (Images, Documents, Videos, Others).

---

## How to Run

### **Requirements**
- C++17 compiler (e.g., `g++`, `clang++`, or MSVC)
- Git (optional, for cloning the repository)

### **Compilation**
```bash
g++ -std=c++17 -o file_organizer file_organizer.cpp
```

### **Usage**
```bash
# Normal mode (moves files)
./file_organizer <folder_path>
```
```bash
# Simulate mode (dry run - shows what would happen)
./file_organizer <folder_path> --simulate
```
# Example:

```bash
./file_organizer "D:/Downloads"
./file_organizer "D:/Downloads" --simulate
```

### **Language and Tools Used**
- Language: C++17
- Libraries: Standard C++ <filesystem> for file handling
- Tools: g++ compiler (MinGW on Windows / GCC or Clang on Linux & macOS)

### **Extra Features**
- Dry Run Mode: Use --simulate to preview file moves without making changes.

- Automatic Folder Creation: Creates Images, Documents, Videos, and Others folders if they don't exist.

- Summary Report: Displays the number of files moved in each category.

### **Notes**
- The program scans only the specified folder (non-recursive).
- File categorization is based on file extension (case-insensitive).
- Supported extensions can be easily updated in the code.