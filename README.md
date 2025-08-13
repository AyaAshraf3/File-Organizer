# File Organizer (Option 1)

## Option Chosen
**Option 1 – File Organizer**  
This program organizes files in a given folder based on their type (Images, Documents, Videos, Others, or any custom categories you define).  
File categories are loaded from a `config.json` file instead of being hardcoded.  

It also supports:
- **Simulate mode**: Preview the moves without actually changing files.
- **Undo mode**: Restore files to their original location after moving them.

---

## How to Run

### **Requirements**
- Python 3.7 or newer
- `config.json` file with your category configuration
- Git (optional, for cloning the repository)

### **Installation**
Clone the repository or download the script and `config.json` file:
```bash
git clone https://github.com/yourusername/file-organizer.git
cd file-organizer
```

### **Configuration**
Create a file named config.json in the same directory as the script:
```json
{
    "categories": {
        "Images": [".jpg", ".jpeg", ".png", ".gif", ".bmp"],
        "Documents": [".pdf", ".doc", ".docx", ".txt", ".xls", ".xlsx"],
        "Videos": [".mp4", ".avi", ".mov", ".mkv"]
    }
}
```
You can add or remove categories and extensions as needed.

### **Usage**
```bash
# Normal mode (moves files)
python file_organizer.py <folder_path>
```
```bash
# Simulate mode (dry run - shows what would happen)
python file_organizer.py <folder_path> --simulate
```
```bash
# Undo last file organization
python file_organizer.py --undo
```

### **Example:**

```bash
python file_organizer.py "D:/Downloads"
python file_organizer.py "D:/Downloads" --simulate
python file_organizer.py --undo
```

## Language and Tools Used
- **Language**: Python 3
- **Libraries**:
    - pathlib for file system paths
    - shutil for moving files
    - json for configuration loading

## Extra Features
- Custom Categories: Defined in config.json.

- Dry Run Mode: Use --simulate to preview file moves without applying changes.

- Undo Last Move: Restores files to their original location after moving.

- Automatic Folder Creation: Creates category folders if they don't exist.

- Summary Report: Displays the number of files moved in each category.


## Notes
- The program scans only the specified folder (non-recursive).
- Undo works only for the most recent organization run.
- The config.json file must be present in the same directory as the script.
- File extensions in config.json are case-insensitive.
- Ensure you have permission to move files in the target folder.
