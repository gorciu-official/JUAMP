/* ================================ INCLUDES ================================ */

#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <regex>

#include <declarations.hpp>

/* ================================ VERSION ================================ */

#define JUAMP_VERSION "8.0.0"

/* ================================ FAMILY ================================ */

int sisters = 0;
int brothers = 0;
bool was_outside_before = false;
bool was_talking_before = false;
bool has_reputation_before = false;
string last_talked_with = "Mama";
int mum_tokens = 0;
int hunger = 0;
int money = 1000;
string name = "";
string city = "";
int age = 12;
int gender = 2; // 1 - kobieta, 2 - mężczyzna (mezczyzna > kobita w tej grze)
int reputation = 100;

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

void print_center_line(string what, const char placeholder = ' ') {
    int width = get_console_width();
    int padding = (width - what.length()) / 2;
    if (padding > 0) {
        std::cout << std::string(padding, placeholder) << what << std::endl;
    } else {
        std::cout << what << std::endl;
    }
}

/* ================================ REPUTATION ================================ */

void add_reputation(int what) {
    if (!has_reputation_before) {
        int cfg = current_foreground;
        int cbg = current_background;
        set_console_color(2, 0);
        println("Właśnie zdobyłeś pierwsze punkty reputacji. Reputacja bezpośrednio odbija się na zachowanie");
        println("bohaterów gry, zwłaszcza krytycznej rodziny. Jeżeli masz niską reputację, istnieje nawet szansa,");
        println("że szef w pracy odmówi zatrudnienia Ciebie. Dbaj o reputację jak o własne życie.");
        set_console_color(cfg, cbg);
        has_reputation_before = true;
    }
    reputation += what;
}

void remove_reputation(int what) {
    reputation -= what;
}

/* ================================ MONEY ================================ */

void add_money(double money2) {
    money = money + money2;
    int cfg = current_foreground;
    int cbg = current_background;
    set_console_color(6, 0);
    string startgender;
    if (gender == 1) {
        startgender = "Otrzymałaś ";
    } else {
        startgender = "Otrzymałeś ";
    }
    print_center_line(startgender + std::to_string(money2) + "$. Masz teraz aż " + std::to_string(money));
    
    set_console_color(cfg, cbg);
}

void remove_money(double money2) {
    money = money - money2;
    int cfg = current_foreground;
    int cbg = current_background;
    set_console_color(6, 0);
    string startgender;
    if (gender == 1) {
        startgender = "Zapłaciłaś lub straciłaś ";
    } else {
        startgender = "Zapłaciłeś lub straciłeś ";
    }
    print_center_line(startgender + std::to_string(money2) + "$. Masz teraz tylko " + std::to_string(money));
    
    set_console_color(cfg, cbg);
}

/* ================================ SAVE SYSTEM ================================ */

string DEFAULT_SAVE_FILE = "saves/savegame.toml";
string SAVE_FILE = DEFAULT_SAVE_FILE;

#include <toml++/toml.hpp>

bool save_game() {
    toml::table save_data{
        {"sisters", sisters},
        {"brothers", brothers},
        {"was_outside_before", was_outside_before},
        {"was_talking_before", was_talking_before},
        {"has_reputation_before", has_reputation_before},
        {"last_talked_with", last_talked_with},
        {"mum_tokens", mum_tokens},
        {"hunger", hunger},
        {"money", money},
        {"name", name},
        {"city", city},
        {"age", age},
        {"gender", gender},
        {"reputation", reputation}
    };

#ifdef _WIN32
    system("if not exist saves mkdir saves");
#else
    system("mkdir -p saves");
#endif

    std::ofstream file(SAVE_FILE);

    if (!file.is_open()) {
        return false;
    }

    file << save_data;
    file.close();

    return true;
}

bool load_game() {
    clear_screen();
    printnl();
    set_console_color(2, 0);
    print_center_line(" JUAMP Launcher ");
    set_console_color(7, 0);
    print_center_line("Aby kontynuować rozgrywkę, należy wpisać nazwę save");
    print_center_line("Jeżeli dopiero zaczynasz, wymyśl nazwę save do nowej gry (może być puste)");
    printnl();

#ifdef _WIN32
    system("if not exist saves mkdir saves");
#else
    system("mkdir -p saves");
#endif
    
    SAVE_FILE = "saves/" + read("> ") + ".toml";

    std::ifstream file(SAVE_FILE);
    if (!file.is_open()) {
        clear_screen();
        return false;
    }

    toml::table save_data;
    try {
        save_data = toml::parse(file);
    } catch (const toml::parse_error&) {
        clear_screen();
        return false;
    }

    sisters = save_data["sisters"].value_or(0);
    brothers = save_data["brothers"].value_or(0);
    was_outside_before = save_data["was_outside_before"].value_or(was_outside_before);
    was_talking_before = save_data["was_talking_before"].value_or(was_talking_before);
    has_reputation_before = save_data["has_reputation_before"].value_or(has_reputation_before);
    last_talked_with = save_data["last_talked_with"].value_or(last_talked_with);
    mum_tokens = save_data["mum_tokens"].value_or(mum_tokens);
    hunger = save_data["hunger"].value_or(hunger);
    money = save_data["money"].value_or(money);
    name = save_data["name"].value_or(name);
    city = save_data["city"].value_or(city);
    age = save_data["age"].value_or(age);
    gender = save_data["gender"].value_or(gender);
    reputation = save_data["reputation"].value_or(100);

    clear_screen();
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
        print_center_line("Witaj na zewnątrz! Stąd możesz dostać się do każdego miejsca, jednak są to tylko podstawowe miejsca.");
        print_center_line("Do reszty możesz dostać się tylko poprzez ulice.");
        was_outside_before = true;
    }
    while (true) {
        printnl();

        if (get_random_number() % 6 == 3) {
            talk("Bezdomny", "Dasz mi 5 dolarów na chleb?");
            println("Możesz zaakceptować ofertę pisząc T, lub odrzucić pisząc cokolwiek innego.");
            string readed = read("> ", 2);
            if (readed == "t" || readed == "T") {
                remove_money(5);
                add_reputation(1);
                talk("Bezdomny", "Dzięki!");
            }

            continue;
        }

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
            remove_reputation(3);
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
        println("Otóż kobiety mają mniej siły i praca zajmie im dłużej niż mężczyźnie. Wybierz mądrze.");
        while (true) {
            string gendersel = read("# ");
            if (gendersel.empty()) {
                set_console_color(4, 0);
                println("Płeć nie może być pusta!");
                set_console_color(7, 0);
                continue;
            }
            if (gendersel != "Kobieta" && gendersel != "Mężczyzna" && gendersel != "Mezczyzna") {
                set_console_color(4, 0);
                println("Przyjmowane wartości to \"Kobieta\" lub \"Mężczyzna\" (z dużej litery).");
                set_console_color(7, 0);
                continue;
            }

            if (gendersel == "Kobieta") {
                gender = 1;
            } else {
                gender = 2;
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
