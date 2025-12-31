// ------- QT IMPORTS -------
#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QString>
#include <QMetaObject>
#include <QWaitCondition>
#include <QMutex>

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

using std::string;

QTextEdit* consoleWidget = nullptr;
QLineEdit* inputField = nullptr;
QMutex inputMutex;
QWaitCondition inputCondition;
QString lastInput;
bool inputReady = false;

string current_fg_hex = "#ffffff";
string current_bg_hex = "#000000";
int current_foreground = 7;
int current_background = 0;

string get_hex_color(int code) {
    switch(code) {
        case 0: return "#000000"; // Black
        case 1: return "#aa0000"; // Red
        case 2: return "#00aa00"; // Green
        case 3: return "#aaaa00"; // Yellow
        case 4: return "#0000aa"; // Blue
        case 5: return "#aa00aa"; // Magenta
        case 6: return "#00aaaa"; // Cyan
        case 7: return "#ffffff"; // White
        default: return "#ffffff";
    }
}

// ------- GUI REPLACEMENTS -------

void print(const std::string& text) {
    if (!consoleWidget) return;
    
    QString safeText = QString::fromStdString(text).toHtmlEscaped().replace("\n", "<br>");
    QString html = 
                    (current_background != 0) ? (QString("<span style='color:%1; background-color:%2; font-family:monospace;'>%3</span>")
                   .arg(QString::fromStdString(current_fg_hex))
                   .arg(QString::fromStdString(current_bg_hex))
                   .arg(safeText)) : (QString("<span style='color:%1; font-family:monospace;'>%2</span>")
                   .arg(QString::fromStdString(current_fg_hex))
                   .arg(safeText));

    QMetaObject::invokeMethod(consoleWidget, "insertHtml", Qt::QueuedConnection, Q_ARG(QString, html));
    QMetaObject::invokeMethod(consoleWidget, "ensureCursorVisible", Qt::QueuedConnection);
}

void println(const std::string& text) {
    print(text + "\n");
}

void printnl() {
    println("");
}

int get_console_width() { return 80; }

void set_console_color(int foreground, int background) {
    current_fg_hex = get_hex_color(foreground);
    current_bg_hex = get_hex_color(background);
    current_background = background;
    current_foreground = foreground;
}

void clear_screen() {
    if (consoleWidget) {
        QMetaObject::invokeMethod(consoleWidget, "clear", Qt::QueuedConnection);
    }
    set_console_color(4, 0);
    println("JUAMP - symulator życia");
    print("Aktualna wersja: ");
    println(JUAMP_VERSION);
    set_console_color(7, 0);
}

void print_center_line(string what, const char placeholder) {
    int width = get_console_width();
    int padding = (width - what.length()) / 2;
    if (padding > 0) {
        println(std::string(padding, placeholder) + what);
    } else {
        println(what);
    }
}

// ------- INPUT -------

string read(const string prefix, int rfg, int rbg) {
    set_console_color(rfg, rbg);
    print(prefix);
    
    if (inputField) {
        QMetaObject::invokeMethod(inputField, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, true));
        QMetaObject::invokeMethod(inputField, "setFocus", Qt::QueuedConnection);
    }

    inputMutex.lock();
    inputReady = false;
    while(!inputReady) {
        inputCondition.wait(&inputMutex);
    }
    std::string result = lastInput.toStdString();
    inputMutex.unlock();

    return result;
}

void talk(string who, string what) {
    set_console_color(3, 0);
    print("<" + who + "> ");
    set_console_color(7, 0);
    println(what);
}

void pause_nul() {
#ifdef _WIN32
    system("pause > nul");
#elif __linux__
    system("read -s -n 1");
#endif
}

void print_message_box(const std::string& title, const std::string& desc) {
    QMetaObject::invokeMethod(qApp, [=]() {
        QMessageBox::information(nullptr, QString::fromStdString(title), QString::fromStdString(desc));
    }, Qt::QueuedConnection);
}

// ------- WINDOW CLASS -------

class JuampWindow : public QWidget {
public:
    JuampWindow() {
        setWindowTitle("JUAMP - Terminal");
        resize(900, 600);
        setStyleSheet("background-color: #1e1e1e;");

        QVBoxLayout* layout = new QVBoxLayout(this);
        
        consoleWidget = new QTextEdit();
        consoleWidget->setReadOnly(true);
        consoleWidget->setStyleSheet(
            "background-color: #000000; color: #ffffff; "
            "font-family: 'Monospace', 'Consolas'; font-size: 11pt; "
            "border: 1px solid #333;"
        );
        
        inputField = new QLineEdit();
        inputField->setEnabled(false);
        inputField->setStyleSheet(
            "background-color: #252526; color: #00ff00; "
            "font-family: 'Monospace'; font-size: 11pt; "
            "border: 1px solid #444; padding: 5px;"
        );

        layout->addWidget(consoleWidget);
        layout->addWidget(inputField);

        connect(inputField, &QLineEdit::returnPressed, this, [=](){
            inputMutex.lock();
            lastInput = inputField->text();
            
            QString echo = QString("<span style='color:%1; font-family:monospace;'>%2</span><br>")
                           .arg(current_fg_hex)
                           .arg(lastInput.toHtmlEscaped());
            
            consoleWidget->insertHtml(echo);
            
            inputField->clear();
            inputField->setEnabled(false);
            inputReady = true;
            inputCondition.wakeAll();
            inputMutex.unlock();
        });
    }
};

// ------- TILING WM  -------
std::string toLowerCase(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c){ return std::tolower(c); });
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

    JuampWindow window;
    window.show();

    if (!compositor.empty() && isTilingWayland(compositor)) {
        showFloatingHint(&window);
    }

    std::thread juampThread([](){
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        juamp_main();
    });

    int ret = app.exec();

    inputMutex.lock();
    inputReady = true;
    inputCondition.wakeAll();
    inputMutex.unlock();

    if (juampThread.joinable()) juampThread.detach();
    return ret;
}