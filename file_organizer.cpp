#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

namespace fs = std::filesystem;

// File categories
const std::vector<std::string> image_ext = {".jpg", ".jpeg", ".png", ".gif", ".bmp"};
const std::vector<std::string> doc_ext   = {".pdf", ".doc", ".docx", ".txt", ".xls", ".xlsx"};
const std::vector<std::string> video_ext = {".mp4", ".avi", ".mov", ".mkv"};

// Convert string to lowercase
std::string to_lower(const std::string &s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Check if extension matches a list
bool has_extension(const fs::path &file, const std::vector<std::string> &ext_list) {
    std::string ext = to_lower(file.extension().string());
    return std::find(ext_list.begin(), ext_list.end(), ext) != ext_list.end();
}

void organize_files(const fs::path &folder_path, bool simulate) {
    // Categories
    std::unordered_map<std::string, int> counters = {
        {"Images", 0}, {"Documents", 0}, {"Videos", 0}, {"Others", 0}
    };

    // Create category folders if not existing
    for (auto &category : {"Images", "Documents", "Videos", "Others"}) {
        fs::create_directories(folder_path / category);
    }

    // Iterate files (non-recursive)
    for (const auto &entry : fs::directory_iterator(folder_path)) {
        if (!entry.is_regular_file()) continue; // Skip dirs and special files

        fs::path src = entry.path();
        fs::path dest_folder;

        if (has_extension(src, image_ext)) {
            dest_folder = folder_path / "Images";
            counters["Images"]++;
        }
        else if (has_extension(src, doc_ext)) {
            dest_folder = folder_path / "Documents";
            counters["Documents"]++;
        }
        else if (has_extension(src, video_ext)) {
            dest_folder = folder_path / "Videos";
            counters["Videos"]++;
        }
        else {
            dest_folder = folder_path / "Others";
            counters["Others"]++;
        }

        fs::path dest = dest_folder / src.filename();

        if (simulate) {
            std::cout << "[SIMULATE] Move: " << src << " -> " << dest << "\n";
        } else {
            try {
                fs::rename(src, dest);
            } catch (const fs::filesystem_error &e) {
                std::cerr << "Error moving file: " << e.what() << "\n";
            }
        }
    }

    // Print summary
    std::cout << "\nSummary:\n";
    for (auto &[category, count] : counters) {
        std::cout << category << ": " << count << "\n";
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <folder_path> [--simulate]\n";
        return 1;
    }

    fs::path folder_path = argv[1];
    bool simulate = (argc > 2 && std::string(argv[2]) == "--simulate");

    if (!fs::exists(folder_path) || !fs::is_directory(folder_path)) {
        std::cerr << "Error: Provided path is not a valid directory.\n";
        return 1;
    }

    organize_files(folder_path, simulate);
    return 0;
}
