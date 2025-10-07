#include <random>
#include <ctime>

int get_random_number() {
    static std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr))); 
    std::uniform_int_distribution<> dist(1, 10);

    return dist(gen);
}

void make_directory(std::string dirname) {
    #ifdef _WIN32
        system(("if not exist saves mkdir " + dirname).c_str());
    #else
        system(("mkdir -p " + dirname).c_str());
    #endif
}

void switch_to_utf8() {
    #ifdef _WIN32
        system("chcp 65001 > nul");
    #endif
    // linux shall be fine
}