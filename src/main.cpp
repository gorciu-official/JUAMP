#include "toml.hpp" // run building for the first time to fix error
#include <iostream>

void set_console_color(int color) {
    std::cout << "\033[" << color << "m";
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

int main() {
    return 0;
}