/* ================================ INCLUDES ================================ */

#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <regex>

#include "declarations.hpp"

/* ================================ VERSION ================================ */

#define JUAMP_VERSION "7.0.0"

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
int sex = 2; // 1 - kobieta, 2 - mężczyzna

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

/* ================================ MONEY ================================ */

void add_money(double money2) {
    money = money + money2;
    int cfg = current_foreground;
    int cbg = current_background;
    set_console_color(6, 0);
    if (sex == 1) {
        print("Otrzymałaś ");
    } else {
        print("Otrzymałeś ");
    }
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
    if (sex == 1) {
        print("Zapłaciłaś lub straciłaś ");
    } else {
        print("Zapłaciłeś lub straciłeś ");
    }
    print(std::to_string(money2));
    print("$. Masz teraz tylko ");
    print(std::to_string(money));
    println("$.");
    set_console_color(cfg, cbg);
}

/* ================================ SAVE SYSTEM ================================ */

#define SAVE_FILE "savegame.dat"

bool save_game() {
    std::ofstream save(SAVE_FILE, std::ios::binary);
    if (!save) {
        return false;
    }

    save.write(reinterpret_cast<char*>(&sisters), sizeof(sisters));
    save.write(reinterpret_cast<char*>(&brothers), sizeof(brothers));
    save.write(reinterpret_cast<char*>(&was_outside_before), sizeof(was_outside_before));
    save.write(reinterpret_cast<char*>(&was_talking_before), sizeof(was_talking_before));

    size_t last_talked_with_size = last_talked_with.size();
    save.write(reinterpret_cast<char*>(&last_talked_with_size), sizeof(last_talked_with_size));
    save.write(last_talked_with.data(), last_talked_with_size);

    save.write(reinterpret_cast<char*>(&mum_tokens), sizeof(mum_tokens));
    save.write(reinterpret_cast<char*>(&hunger), sizeof(hunger));
    save.write(reinterpret_cast<char*>(&money), sizeof(money));

    size_t name_size = name.size();
    save.write(reinterpret_cast<char*>(&name_size), sizeof(name_size));
    save.write(name.data(), name_size);

    size_t city_size = city.size();
    save.write(reinterpret_cast<char*>(&city_size), sizeof(city_size));
    save.write(city.data(), city_size);

    save.write(reinterpret_cast<char*>(&age), sizeof(age));
    save.write(reinterpret_cast<char*>(&sex), sizeof(sex));

    save.close();
    return true;
}

bool load_game() {
    std::ifstream load(SAVE_FILE, std::ios::binary);
    if (!load) {
        return false;
    }

    load.read(reinterpret_cast<char*>(&sisters), sizeof(sisters));
    load.read(reinterpret_cast<char*>(&brothers), sizeof(brothers));
    load.read(reinterpret_cast<char*>(&was_outside_before), sizeof(was_outside_before));
    load.read(reinterpret_cast<char*>(&was_talking_before), sizeof(was_talking_before));

    size_t last_talked_with_size;
    load.read(reinterpret_cast<char*>(&last_talked_with_size), sizeof(last_talked_with_size));
    last_talked_with.resize(last_talked_with_size);
    load.read(&last_talked_with[0], last_talked_with_size);

    load.read(reinterpret_cast<char*>(&mum_tokens), sizeof(mum_tokens));
    load.read(reinterpret_cast<char*>(&hunger), sizeof(hunger));
    load.read(reinterpret_cast<char*>(&money), sizeof(money));

    size_t name_size;
    load.read(reinterpret_cast<char*>(&name_size), sizeof(name_size));
    name.resize(name_size);
    load.read(&name[0], name_size);

    size_t city_size;
    load.read(reinterpret_cast<char*>(&city_size), sizeof(city_size));
    city.resize(city_size);
    load.read(&city[0], city_size);

    load.read(reinterpret_cast<char*>(&age), sizeof(age));
    load.read(reinterpret_cast<char*>(&sex), sizeof(sex));

    load.close();
    return true;
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
        println("Witaj na zewnątrz! Stąd możesz dostać się do każdego miejsca, jednak są to tylko podstawowe miejsca.");
        println("Do reszty możesz dostać się tylko poprzez ulice.");
        was_outside_before = true;
    }
    while (true) {
        printnl();
        set_console_color(3, 0);
        println("Jesteś na dworze!");
        set_console_color(7, 0);
        println("  1 - Wróć do domu");
        println("  2 - Odwiedź sklepik \"Ropucha\"");
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
    clear_screen();
    while (true) {
        printnl();

        if (money < 0) {
            set_console_color(7, 0);
            talk("Mama", "JAK ŚMIAŁEŚ SIĘ ZADŁUŻYĆ? TO POWAŻNY PROBLEM DLA NASZEJ RODZINY! WSTYD NA CAŁĄ MIEJSCOWOŚĆ!\nRozumiem że mamy tu wiele fajnych rzeczy, ale nie możemy sobie na nie pozwolić tak często. Lepiej zarabiać\n pieniądze, a nie wydawać je na głupoty! Wynocha do pracy!");
            handle_work();
            continue;
        }

        if (money < 30) {
            set_console_color(7, 0);
            talk("Tata", "Mama będzie miała dość spory problem, jeżeli nie zarobisz pieniędzy. Musisz coś zrobić, aby zarobić pieniądze.\nWiesz jak mama potrafi się zdenerwować, kiedy nie masz pieniędzy.\n Lepiej zacznij działać, zanim będzie za późno. Ubierz się i idź do pracy.");
            Sleep(3000);
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
#endif
    clear_screen();

    bool needConfig = !load_game();
    if (needConfig) {
        printnl();
        set_console_color(2, 0);
        println("Witaj w JUAMP! Przed rozpoczęciem gry musisz odpowiedzieć na kilka pytań.");
        println("Odpowiedzi na te pytania będą miały większy lub mniejszy wpływ na przebieg gry.");
        printnl();
        set_console_color(3, 0);
        print("Wybierz imię - ");
        set_console_color(7, 0);
        println("będzie ono używane w małej ilości, ale jednak jest potrzebne. Może");
        println("to być Twoje prawdziwe imię, pseudonim, czy zupełnie wymyślona nazwa. Nie ma to znaczenia.");
        while (true) {
            name = read("# ");
            if (name.empty()) {
                set_console_color(4, 0);
                println("Imię nie może być puste!");
                set_console_color(7, 0);
                continue;
            }
            if (name == "Mama" || name == "Tata" || name == "Brat" || name == "Siostra" || name == "Babcia" || name == "Dziadek") {
                set_console_color(4, 0);
                println("Imię nie może być takie jak nazwy członków rodziny!");
                set_console_color(7, 0);
                continue;
            }
            if (name == "JUAMP" || name == "juamp" || name == "Juamp" || name == "Gorciu" || name == "gorciu" || name == "Gorciu") {
                println("Pogrzało Cię lekko mówiąc.");
                continue;
            }
            break;
        }
        printnl();
        set_console_color(3, 0);
        print("Wybierz płeć - ");
        set_console_color(7, 0);
        println("będzie ona używana głównie w dialogach i raczej nic nie zmieni w grze poza jedną rzeczą.");
        println("Otóż kobiety mają mniej siły i w praca zajmie im dłużej niż mężczyźnie. Wybierz mądrze.");
        while (true) {
            name = read("# ");
            if (name.empty()) {
                set_console_color(4, 0);
                println("Płeć nie może być pusta!");
                set_console_color(7, 0);
                continue;
            }
            if (name != "Kobieta" && name != "Mężczyzna" && name != "Mezczyzna") {
                set_console_color(4, 0);
                println("Przyjmowane wartości to \"Kobieta\" lub \"Mężczyzna\" (z dużej litery).");
                set_console_color(7, 0);
                continue;
            }

            if (name == "Kobieta") {
                sex = 1;
            } else {
                sex = 2;
            }
            break;
        }
        printnl();
        set_console_color(3, 0);
        print("Twoje wylosowane miasto: ");
        set_console_color(7, 0);
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
        println("Kliknij dowolny klawisz, by przejść dalej.");
        pause_nul();
    } else {
        set_console_color(7, 0);
        println("Gra wczytana pomyślnie.");
    }

    handle_home();

    set_console_color(7, 0);
    while (!save_game()) continue; // tries to save game until it's saved
    return 0;
}
