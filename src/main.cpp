/* ================================ INCLUDES ================================ */

#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>

#include "declarations.h"

/* ================================ VERSION ================================ */

#define JUAMP_VERSION "5.1.0"

/* ================================ FAMILY ================================ */

int sisters = 0;
int brothers = 0;
bool was_outside_before = false;
bool was_talking_before = false;
string last_talked_with = "Mama";
int mum_tokens = 0;
int hunger = 0;
int money = 1000;
string name = "";
string city = "";
int age = 12;

/* ================================ INTERNALS ================================ */

int current_foreground;
int current_background;

int get_random_number() {
    static std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr))); 
    std::uniform_int_distribution<> dist(1, 10);

    return dist(gen);
}

void set_console_color(int foreground, int background) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (background << 4) | foreground);
#endif
#ifdef __linux__
    string fg = std::to_string(foreground);
    string bg = std::to_string(background);
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

void add_one_hunger() {
    hunger++;
    if (hunger == 75) {
        print_message_box("Uwaga!", "Jesteś głodny! Może czas pójść na halę targową i kupić coś do jedzenia.");
    }
    if (hunger == 90) {
        print_message_box("OSTATNIE OSTRZEŻENIE!", "Jesteś naprawdę głodny. Musisz kupić coś do jedzenia. Jeżeli nie zareagujesz na to ostrzeżenie, Twoja rozgrywka może się bezpowrotnie skończyć.");
    }
    if (hunger > 115) {
        print_message_box("Rozgrywka zakończona!", "Zignorowałeś ostrzeżenia dotyczące głodu twojej postaci. Nie jesteś w stanie kontynuować rozgrywki.");
        while (true) {
            continue;
        }
    }
}

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

/* ================================ MONEY ================================ */

void add_money(double money2) {
    money = money + money2;
    int cfg = current_foreground;
    int cbg = current_background;
    set_console_color(6, 0);
    print("Otrzymałeś ");
    print(std::to_string(money2));
    print("$. Masz teraz ");
    print(std::to_string(money));
    println("$.");
    set_console_color(cfg, cbg);
}

void remove_money(double money2) {
    money = money - money2;
    int cfg = current_foreground;
    int cbg = current_background;
    set_console_color(6, 0);
    print("Zapłaciłeś lub straciłeś ");
    print(std::to_string(money2));
    print("$. Masz teraz tylko ");
    print(std::to_string(money));
    println("$.");
    set_console_color(cfg, cbg);
}

/* ================================ PLACES ================================ */

extern void handle_ropucha();
extern void handle_market_hall();
extern void handle_casino();
extern void handle_work();
extern void handle_train_station();

void handle_outside() {
    if (!was_outside_before) {
        printnl();
        set_console_color(2, 0);
        println("Witaj na zewnątrz! Stąd możesz dostać się do każdego miejsca, jednak w");
        println("\"zbiory miejsc\" możesz dostać się tylko poprzez ulice.");
        was_outside_before = true;
    }
    while (true) {
        printnl();
        set_console_color(3, 0);
        println("Jesteś na dworze!");
        set_console_color(7, 0);
        println("  1 - Wróć do domu");
        println("  2 - Odwiedź mały sklepik \"Ropucha\"");
        println("  3 - Idź na halę targową");
        println("  4 - Idź do kasyna");
        println("  5 - Idź na dworzec ");

        string readed = read("> ", 2);
        if (readed == "1") {
            return;
        } else if (readed == "2") {
            handle_ropucha();
            continue;
        } else if (readed == "3") {
            handle_market_hall();
            continue;
        } else if (readed == "4") {
            handle_casino();
            continue;
        } else if (readed == "5") {
            handle_train_station();
            continue;
        }

        set_console_color(4, 0);
        println("Niepoprawny numer/znak");
        set_console_color(7, 0);
    }
}

extern void handle_home_talking();

void handle_home() {
    while (true) {
        printnl();

        if (money < 0) {
            set_console_color(7, 0);
            println("<Mama> JAK ŚMIAŁEŚ SIĘ ZADŁUŻYĆ??? Wolę zero złotych niż tyle ile masz!");
            println("       Przynosisz wstyd naszej rodzinie. Wynocha do pracy!");
            handle_work();
            continue;
        }

        set_console_color(3, 0);
        println("Jesteś w domu!");
        set_console_color(7, 0);
        println("  1 - Wyjdź na zewnątrz");
        println("  2 - Zagadaj do kogoś");
        println("  E - Wyjdź z gry");

        string readed = read("> ", 2);
        if (readed == "1") {
            handle_outside();
        } else if (readed == "2") {
            handle_home_talking();
        } else if (readed == "E") {
            return;
        } else {
            set_console_color(4, 0);
            println("Niepoprawny numer/znak");
            set_console_color(7, 0);
        }
    }
}

/* ================================ MAIN PROGRAM ================================ */

int main() {
#ifdef _WIN32
    system("chcp 65001 > nul");
    system("cls");
#else
    system("clear");
#endif
    set_console_color(4, 0);
    println("JUAMP - symulator życia");
    print("Aktualna wersja: ");
    println(JUAMP_VERSION);
    set_console_color(7, 0);

    bool needConfig = true; // will be usefull on save
    if (needConfig) {
        printnl();
        name = read("Wpisz imię: ");
        print("Twoje miasto: ");
        Sleep(1000);
        std::vector<string> cities = {"Loresphread", "Applaypom", "Sersoponia", "Delaxer", "Bimalia"};
        city = cities[get_random_number() % cities.size()];
        println(city);
        set_console_color(2, 0);
        if (city == "Loresphread") {
            println("  Loresphread to niewielkie miasteczko położone w zachodniej");
            println("  części kraju. Jest tam umiarkowany klimat, ale śnieg prawie");
            println("  nigdy nie pada. Na ogół społeczność jest przyjazna i skierowana");
            println("  na poznawanie nowych ludzi, również spoza okolicy.");
        } else if (city == "Applaypom") {
            println("  Applaypom to miasto, które jest znane z przemysłu i technologii.");
            println("  W mieście znajduje się wiele firm, które produkują różne produkty");
            println("  technologiczne. W mieście jest również wiele miejsc, w których");
            println("  można się dobrze bawić. Według ludzi - miasto to \"krajowe Chiny\".");
        } else if (city == "Sersoponia") {
            println("  Serseponia to miasto, które jest znane z kultury i sztuki. W mieście");
            println("  znajduje się wiele muzeów, galerii sztuki, teatrów i innych miejsc,");
            println("  w których można się rozwijać w dziedzinie kultury. W mieście jest");
            println("  również wiele gór, gdyż jest ono położone na południu kraju.");
        } else if (city == "Delaxer") {
            println("  Delaxer to mała wieś, która jest położona na wschodzie kraju.");
            println("  Wioska jest znana z tego, że żyje tam wiele zwierząt, które można");
            println("  spotkać na co dzień. Wioska jest również znana z tego, że jest tam");
            println("  o wiele więcej pól, na których można uprawiać rośliny, niż w całej");
            println("  reszcie kraju.");
        } else if (city == "Bimalia") {
            println("  Bimalia to drugie po Nopsanii największe miasto w kraju pod względem");
            println("  liczby ludności. Jest to raj dla dorosłych. W mieście znajduje się wiele");
            println("  klubów nocnych, restauracji, kin i innych miejsc, w których można spędzać");
            println("  czas.");
        } else {
            println("Uncaught TypeError: Cannot read properties of undefined (reading \"description\")");
            println(" at main:258:12");
            return 12;
        }
        set_console_color(7, 0);
    }

    handle_home();

    set_console_color(7, 0);
    return 0;
}
