// =================================== PRECOMIPILER ===================================

#ifndef __cplusplus
#error JUAMP is a C++ game.
#endif

#ifdef _WIN32
#include <windows.h>
#else
#if __linux__
#include <sys/ioctl.h>
#include <unistd.h>
#else
#endif
#endif

// =================================== DEPENDENCIES ===================================

#include "toml.hpp" // run building for the first time to fix error
#include <iostream>

typedef std::string string;

// =================================== GAME DATA ===================================

string name = "";
string gender = "b"; // b - chłop, g - baba
int age = 0;
double money = 0;
int reputation = 1000;

// player atributtes
int strenght = 0;
int speed = 0;
int inteligency = 0;
int condition = 0;

// =================================== INTERNALS ===================================

void print(string what) {
    std::cout << what;
}

void println(string what) {
    std::cout << what << std::endl;
}

void set_console_color(int color) {
    std::cout << "\033[" << 30 + color << "m";
}

int get_console_width() {
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int columns;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

        return columns;
    #else
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_col;
    #endif
}

int get_console_height() {
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int rows;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        return rows;
    #else
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_row;
    #endif
}

void display_error_box(const string& message) {
    int console_width = get_console_width();
    int console_height = get_console_height();

    int box_width = message.length() + 4; 
    int box_height = 5; 

    int box_x = (console_width - box_width) / 2;
    int box_y = (console_height - box_height) / 2;

    for (int i = 0; i < box_y; ++i) std::cout << '\n';
    std::cout << std::string(box_x, ' ') << "+" << std::string(box_width - 2, '-') << "+\n";

    std::cout << std::string(box_x, ' ') << "|" << std::string(box_width - 2, ' ') << "|\n";

    std::cout << std::string(box_x, ' ') << "| " << message
              << std::string(box_width - message.length() - 3, ' ') << "|\n";

    std::cout << std::string(box_x, ' ') << "|" << std::string(box_width - 2, ' ') << "|\n";

    std::cout << std::string(box_x, ' ') << "+" << std::string(box_width - 2, '-') << "+\n";
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pak() {
#ifdef _WIN32
    system("pause > nul");
#else
    system("stty -echo -icanon; char=$(dd bs=1 count=1 2>/dev/null); stty echo icanon;");
#endif
}

void better_dts(double number) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << number;
    std::string str = oss.str();
    return str;
}

void print_logo() {
    string logo =  "\n    _____  _____  _____   _       ____    ____  _______   \n   |_   _||_   _||_   _| / \\     |_   \\  /   _||_   __ \\  \n     | |    | |    | |  / _ \\      |   \\/   |    | |__) |\n _   | |    | '    ' | / ___ \\     | |\\  /| |    |  ___/  \n| |__' |     \\ \\__/ /_/ /   \\ \\_  _| |_\\/_| |_  _| |_     \n`.____.'      `.__.'|____| |____||_____||_____||_____|\n";
    println(logo);
}

string read(string prefix) {
    string pref = prefix + " ";
    std::cout << pref;
    string out;
    std::getline(std::cin, out);
    return out;
}

// =================================== SAVES ===================================

string current_save = "";

void load_game() {
    try {
        clear_screen();
        set_console_color(6);
        print_logo();
        set_console_color(7);
        println("Proszę podać nazwę save do utworzenia/do załadowania, aby kontynuować rozgrywkę w JUAMP.");

        current_save = ;

        auto config = toml::parse(full_save_name);

        name = config["name"].value_or("Unknown");
        age = config["age"].value_or(0);
        money = config["money"].value_or(0.0f);
        reputation = config["reputation"].value_or(0);
        strenght = config["strenght"].value_or(0);
        speed = config["speed"].value_or(0);
        inteligency = config["inteligency"].value_or(0);
        condition = config["condition"].value_or(0);
    } catch (const toml::parse_error& err) {
        return false;
    }
}

void save_game() {
    toml::table save{
        {"name", name},
        {"age", age},
        {"money", money},
        {"reputation", reputation},
        {"strenght", strenght},
        {"speed", condition},
        {"inteligency", inteligency},
        {"condition", condition}
    };
    
    string full_save_name = "saves" + current_save + ".toml";
    std::ofstream file(full_save_name);
    file << full_save_name;
}

// =================================== GAME ===================================

int main() {
    while (true) {
        int console_width = get_console_width();
        int console_height = get_console_height();
        if (console_width >= 50 && console_height >= 15) break;
        clear_screen();
        set_console_color(2);
        display_error_box("Aby zapewnić jakiekolwiek wrażenia z gry powiększ terminal i naciśnij Enter.");
        pak();
    }
    set_console_color(6);
    print_logo();
    return 0;
}