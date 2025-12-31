// ------- QT IMPORTS -------

#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <QTextEdit>
#include <QInputDialog>
#include <QString>

// ------- C++ STDLIB IMPORTS -------
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <regex>
#include <thread>

// ------- JUAMP IMPORTS -------
#include "constants.hpp"

// ------- TYPES -------
using std::string;

// ------- BASE VARIABLES -------
QTextEdit* consoleWidget;
int current_foreground;
int current_background;

// ------- GUI IMPLEMENTATION OF CONSOLE.CPP -------
void print(const std::string& text) {
    if (!consoleWidget) return;

    QString qtText = QString::fromStdString(text);
    QMetaObject::invokeMethod(consoleWidget, [qtText](){
        consoleWidget->append(qtText);
    }, Qt::QueuedConnection);
}

void println(const std::string& text) {
    print(text + '\n');
}

void printnl() {
    println("");
}

int get_console_width() {
    return 800;
}

void print_center_line(std::string what, const char placeholder) {
    int width = get_console_width();
    int padding = (width - what.length()) / 2;
    if (padding > 0) {
        println(std::string(padding, placeholder) + what);
    } else {
        println(what);
    }
}

void set_console_color(int foreground, int background) {
    printf("changing color to %i %i not implemented\n", foreground, background);
    current_foreground = foreground;
    current_background = background;
}

string repeat_string(const string& str, int times) {
    string result;
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

// ------- INPUT -------

std::string read(const std::string& prompt, int rfg, int rbg) {
    bool ok;
    QString result = QInputDialog::getText(consoleWidget, "Input",
                                           QString::fromStdString(prompt),
                                           QLineEdit::Normal, "", &ok);
    if (!ok) return "";
    return result.toStdString();
}

string read(const string prefix, int rfg, int rbg) {
    int cfg = current_foreground;
    int cbg = current_background;

    print(prefix);
    set_console_color(rfg, rbg);

    string readed;
    std::getline(std::cin, readed);

    set_console_color(cfg, cbg);
    return readed;
}

// ------- RANDOM -------

void print_message_box(const std::string& title, const std::string& desc) {
    QMessageBox::information(consoleWidget, QString::fromStdString(title),
                             QString::fromStdString(desc));
}

void pause_nul() {
#ifdef _WIN32
    system("pause > nul");
#elif __linux__
    system("read -s -n 1");
#endif
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

// ------- TILING MANAGERS DETECTION -------

std::string toLowerCase(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return result;
}

std::string getWaylandCompositor() {
    const char* desktop = std::getenv("XDG_CURRENT_DESKTOP");
    if (!desktop) return "";
    return toLowerCase(desktop);
}

bool isTilingWayland(const std::string& compositor) {
    static const char* tiling[] = { "sway", "hyprland", "river", "wayfire" };
    std::string comp = toLowerCase(compositor);
    for (auto n : tiling)
        if (comp.find(n) != std::string::npos)
            return true;
    return false;
}

void showFloatingHint(QWidget* parent) {
    QMessageBox* msg = new QMessageBox(
        QMessageBox::Warning,
        "JUAMP-GUI: Tiling Window Manager Warning",
        "This application works best in floating mode.\n\n"
        "Please enable it for all JUAMP-GUI windows.",
        QMessageBox::Ok,
        parent
    );
    msg->setAttribute(Qt::WA_DeleteOnClose);
    msg->show();
}

// ------- MAIN -------
extern int juamp_main();

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    std::string compositor = getWaylandCompositor();
    std::cout << "Detected compositor: " << compositor << std::endl;

    QWidget window;
    window.setWindowTitle("JUAMP");
    window.resize(800, 400);

    QTextEdit console(&window);
    console.setReadOnly(true);
    consoleWidget = &console;
    console.show();

    window.show();

    if (!compositor.empty() && isTilingWayland(compositor)) {
        showFloatingHint(&window);
    }

    std::thread juampThread([](){
        juamp_main();
    });

    int ret = app.exec();

    juampThread.join();

    return ret;
}