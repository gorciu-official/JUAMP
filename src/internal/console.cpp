#include "../declarations.hpp"
#include <regex>
#include "../constants.hpp"

int current_foreground;
int current_background;

string read(const string prefix, int rfg, int rbg) {
    add_one_hunger();

    int cfg = current_foreground;
    int cbg = current_background;

    print(prefix);

    set_console_color(rfg, rbg);

    string readed;
    std::getline(std::cin, readed);

    set_console_color(cfg, cbg);

    return readed;
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    set_console_color(4, 0);
    println("JUAMP - symulator życia");
    print("Aktualna wersja: ");
    println(JUAMP_VERSION);
    set_console_color(7, 0);
}

void pause_nul() {
#ifdef _WIN32
    system("pause > nul");
#elif __linux__
    system("read -s -n 1");
#endif
}

string repeat_string(const string& str, int times) {
    string result = "";
    for (int i = 0; i < times; i++) {
        result += str;
    }
    return result;
}

void talk(string who, string what) {
    set_console_color(3, 0);
    print("<" + who + "> ");
    set_console_color(7, 0);
    std::string replacement = "\n" + repeat_string(" ", who.length());
    std::string result = std::regex_replace(what, std::regex("\n"), replacement);
    println(result);
}

int get_console_width() {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width = 80; // Default width
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return width;
#elif __linux__
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
#else
    return 80;
#endif
}

void print_center_line(string what, const char placeholder) {
    int width = get_console_width();
    int padding = (width - what.length()) / 2;
    if (padding > 0) {
        std::cout << std::string(padding, placeholder) << what << std::endl;
    } else {
        std::cout << what << std::endl;
    }
}

void set_console_color(int foreground, int background) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (background << 4) | foreground);
#endif
#ifdef __linux__
    string fg = std::to_string(30 + foreground);
    string bg = std::to_string(40 + background);
    std::cout << "\033[" << fg << ";" << bg << "m";
#endif
    current_background = background;
    current_foreground = foreground;
}

void print(const string& text) {
    std::cout << text;
}

void println(const string& text) {
    std::cout << text << std::endl;
}

void printnl() {
    std::cout << std::endl;
}

int print_message_box(const string& title, const string& desc) {
    std::cout << title << " - " << desc << std::endl;
    return 0;
}