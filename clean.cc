#include <iostream>
#include <filesystem>
#include <string>
using namespace std;

namespace fs = std::filesystem;

static bool is_need_clean(std::string file_name) {
    if (file_name.size() < 3) {
        return false;
    }

    if (file_name == ".gitignore") {
        return false;
    }

    if (file_name.substr(file_name.size() - 3) == ".cc") {
        return false;
    }
    if (file_name.substr(file_name.size() - 2) == ".c") {
        return false;
    }
    if (file_name.substr(file_name.size() - 2) == ".h") {
        return false;
    }

    return true;
}

static void traverse_directory(const fs::path& root_path) {
    for (const auto& entry : fs::directory_iterator(root_path)) {
        if (entry.is_directory() && !entry.path().filename().string().empty() && entry.path().filename().string()[0] != '.') {
            traverse_directory(entry.path());
        } else if (entry.is_regular_file()) {
            if (is_need_clean(entry.path().filename())) {
                fs::remove(entry.path());
                cout << entry.path().string() << endl;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    fs::path root_path = "./";
    traverse_directory(root_path);
    return 0;
}
