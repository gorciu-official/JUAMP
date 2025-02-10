// =================================== PRECOMIPILER ===================================

#ifndef __cplusplus
#error JUAMP is a C++ game.
#endif

#define JUAMP_VERSION "9.0.0"

// =================================== DEPENDENCIES ===================================

#include "toml.hpp" // run building for the first time to fix error
#include <iostream>
#include <iomanip>
#include "declarations.hpp"

#ifdef _WIN32
#include <windows.h>
#else
#if __linux__
#include <sys/ioctl.h>
#include <unistd.h>
#else
#endif
#endif

// =================================== GAME DATA ===================================

string name = "";
string gender = "b"; // b - chłop, g - baba
int age = 0;
double money = 1000;
int reputation = 1000;
string location_id = "";
double lvl = 0;
int hunger = 0;

// player atributtes
int strenght = 0;
int speed = 0;
int inteligency = 0;
int condition = 0;

// player's pets
int dogs = 0;
int cats = 0;

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
    std::cout << string(box_x, ' ') << "+" << string(box_width - 2, '-') << "+\n";

    std::cout << string(box_x, ' ') << "|" << string(box_width - 2, ' ') << "|\n";

    std::cout << string(box_x, ' ') << "| " << message
              << string(box_width - message.length() - 3, ' ') << "|\n";

    std::cout << string(box_x, ' ') << "|" << string(box_width - 2, ' ') << "|\n";

    std::cout << string(box_x, ' ') << "+" << string(box_width - 2, '-') << "+\n";
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

string better_dts(double number) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << number;
    string str = oss.str();
    return str;
}

void print_logo() {
    string logo =  "\n    _____  _____  _____   _       ____    ____  _______   \n   |_   _||_   _||_   _| / \\     |_   \\  /   _||_   __ \\  \n     | |    | |    | |  / _ \\      |   \\/   |    | |__) |\n _   | |    | '    ' | / ___ \\     | |\\  /| |    |  ___/  \n| |__' |     \\ \\__/ /_/ /   \\ \\_  _| |_\\/_| |_  _| |_     \n`.____.'      `.__.'|____| |____||_____||_____||_____|";
    println(logo);
    println("Wersja: " + string(JUAMP_VERSION) + "\n");
}

std::map<string, string> utf8_to_lower_map = {
    {"Ą", "ą"}, {"Ć", "ć"}, {"Ę", "ę"}, {"Ł", "ł"},
    {"Ń", "ń"}, {"Ó", "ó"}, {"Ś", "ś"}, {"Ź", "ź"}, {"Ż", "ż"}
};

bool is_ascii(unsigned char c) {
    return c < 128;
}

string to_lower_utf8(const string& input) {
    string result;
    for (size_t i = 0; i < input.size();) {
        if (is_ascii(input[i])) {
            result += std::tolower(input[i]);
            ++i;
        } else {
            size_t char_len = 1;
            if ((input[i] & 0xE0) == 0xC0) char_len = 2;
            else if ((input[i] & 0xF0) == 0xE0) char_len = 3;
            else if ((input[i] & 0xF8) == 0xF0) char_len = 4;

            string utf8_char = input.substr(i, char_len);
            if (utf8_to_lower_map.count(utf8_char)) {
                result += utf8_to_lower_map[utf8_char];
            } else {
                result += utf8_char;
            }
            i += char_len;
        }
    }
    return result;
}

string read(string prefix) {
    string pref = prefix + " ";
    std::cout << pref;
    string out;
    std::getline(std::cin, out);
    out = to_lower_utf8(out);
    return out;
}

// =================================== SAVES ===================================

string current_save = "";

bool load_game() {
    try {
        clear_screen();
        set_console_color(6);
        print_logo();
        set_console_color(7);
        println("Proszę podać nazwę save do utworzenia/do załadowania, aby kontynuować rozgrywkę w JUAMP.");

        current_save = read("#");

        string full_save_name = "saves/" + current_save + ".toml";

        std::ifstream file(full_save_name);
        if (!file.is_open()) {
            return false;
        }
        auto config = toml::parse(file);

        name = config["name"].value_or("Unknown");
        age = config["age"].value_or(0);
        money = config["money"].value_or(0.0f);
        reputation = config["reputation"].value_or(0);
        strenght = config["strenght"].value_or(0);
        speed = config["speed"].value_or(0);
        inteligency = config["inteligency"].value_or(0);
        condition = config["condition"].value_or(0);
        location_id = config["location"].value_or("");
        lvl = config["lvl"].value_or(0);
        hunger = config["lvl"].value_or(0);
        dogs = config["dogs"].value_or(0);
        cats = config["cats"].value_or(0);

        if (name == "Unknown") return load_game();

        return true;
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
        {"condition", condition},
        {"location", location_id},
        {"lvl", lvl},
        {"hunger", hunger},
        {"dogs", dogs},
        {"cats", cats}
    };

#ifdef _WIN32
    system("if not exist saves md saves");
#else
    system("mkdir -p saves");
#endif
    
    string full_save_name = "saves/" + current_save + ".toml";
    std::ofstream file(full_save_name);
    file << save;
}

void add_hunger(int what) {
    hunger += what;
    if (hunger > 75) {
        set_console_color(4);
        println("Jesteś głodny!");
        set_console_color(7);
    }
    if (hunger > 100) {
        name = "Unknown";
        save_game();
        set_console_color(4);
        println("Straciłeś grę bo za długo byłeś głodny.");
        set_console_color(7);
        while (true) continue;
    }
}

// =================================== GAME ===================================

extern void handle_game(bool need_to_start_dialogue);

int main() {
#ifdef _WIN32
    system("chcp 65001 > nul"); // windows moment
#endif
    while (true) {
        int console_width = get_console_width();
        int console_height = get_console_height();
        if (console_width >= 50 && console_height >= 15) break;
        clear_screen();
        set_console_color(2);
        display_error_box("Aby zapewnić jakiekolwiek wrażenia z gry powiększ terminal i naciśnij Enter.");
        pak();
    }
    bool success = load_game();
    if (!success) {
        clear_screen();
        set_console_color(6);
        print_logo();
        set_console_color(7);

        location_id = "plac.main.centered";

        while (true) {
            set_console_color(3);
            println("Wybierz imię");
            set_console_color(7);
            println("  Imię może być dowolne i praktycznie nie ma znaczenia na przebieg gry.");
            name = read("#");

            if (name.empty()) {
                set_console_color(1);
                println("Wybierz imię a nie...");
                set_console_color(7);
                continue;
            }

            break;
        }

        while (true) {
            set_console_color(3);
            println("Wybierz płeć");
            set_console_color(7);
            println("  Płeć ma tym razem znaczenie, kobiety szybciej się męczą (jest więcej różnic). Wybierz b/g.");
            gender = read("#");

            if (gender != "b" && gender != "c") {
                set_console_color(1);
                println("Raczej niepoprawna ta twoja płeć.");
                set_console_color(7);
                continue;
            }

            break;
        }
    }
    handle_game(!success);
    return 0;
}