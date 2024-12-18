/* ================================ INCLUDES ================================ */

#include <iostream>
#include <random>
#include <string>
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#include <winuser.h>
#endif

#ifdef __linux__
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#define Sleep(ms) sleep((ms) / 1000)
#endif

using namespace std;

/* ================================ VERSION ================================ */

#define JUAMP_VERSION "1.0.0"

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

int get_random_int_to_percent() {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dist(1, 10);

    return dist(gen);
}

void set_console_color(int foreground, int background) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (background << 4) | foreground);
#endif
#ifdef __linux__
    string fg = to_string(foreground);
    string bg = to_string(background);
    cout << "\033[" << fg << ";" << bg << "m";
#endif
    current_background = background;
    current_foreground = foreground;
}

void print(const string& text) {
    std::cout << text;
}

void println(const string& text) {
    cout << text << endl;
}

void printnl() {
    cout << endl;
}

int print_message_box(const string& title, const string& desc) {
#ifdef _WIN32
    int msgboxID = MessageBoxA(
        NULL,
        desc.c_str(),
        title.c_str(),
        MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON2
    );
    return msgboxID;
#else
    cout << title << ": " << desc << endl;
    return 0;
#endif
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

string read(const string prefix, int rfg = 7, int rbg = 0) {
    add_one_hunger();

    int cfg = current_foreground;
    int cbg = current_background;

    print(prefix);

    set_console_color(rfg, rbg);

    string readed;
    getline(cin, readed);

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
    print(to_string(money2));
    print("$. Masz teraz ");
    print(to_string(money));
    println("$.");
    set_console_color(cfg, cbg);
}

void remove_money(double money2) {
    money = money - money2;
    int cfg = current_foreground;
    int cbg = current_background;
    set_console_color(6, 0);
    print("Zapłaciłeś lub straciłeś ");
    print(to_string(money2));
    print("$. Masz teraz tylko ");
    print(to_string(money));
    println("$.");
    set_console_color(cfg, cbg);
}

/* ================================ SHOP ================================ */

#define SHOP_ROPUCHA_CENA_BAGIETKA 3.50
#define SHOP_ROPUCHA_PUNKTY_BAGIETKA 16

/* ================================ PLACES ================================ */

void handle_ropucha() {
    while (true) {
        printnl();
        set_console_color(3, 0);
        println("Jesteś w sklepiku \"Ropucha!\"");
        set_console_color(7, 0);
        println("  1 - Wyjdź ze sklepu");
        println("  2 - Kup bagietkę");

        string readed = read("> ", 2);
        if (readed == "1") {
            return;
        } else if (readed == "2") {
            if (SHOP_ROPUCHA_CENA_BAGIETKA > money) {
                set_console_color(4, 0);
                println("Niestety nie stać cię na taki wydatek!");
                set_console_color(7, 0);
                continue;
            }
            remove_money(SHOP_ROPUCHA_CENA_BAGIETKA);
            hunger = hunger - SHOP_ROPUCHA_PUNKTY_BAGIETKA;
            continue;
        }

        set_console_color(4, 0);
        println("Niepoprawny numer/znak");
        set_console_color(7, 0);
    }
}

#define MARKET_HALL_BAGIETKA_CENA 4.50
#define MARKET_HALL_BAGIETKA_PUNKTY 22
#define MARKET_HALL_JABLKO_CENA 2.00
#define MARKET_HALL_JABLKO_PUNKTY 5
#define MARKET_HALL_GRUSZKA_CENA 2.00
#define MARKET_HALL_GRUSZKA_PUNKTY 5
#define MARKET_HALL_BANAN_CENA 2.00
#define MARKET_HALL_BANAN_PUNKTY 7
#define MARKET_HALL_WODA_CENA 1.50
#define MARKET_HALL_WODA_PUNKTY 6

void handle_market_hall() {
    while (true) {
        int random_item = get_random_int_to_percent() % 5 + 1;
        string item_name;
        double item_price;
        int item_points;

        if (random_item == 1) {
            item_name = "Bagietka";
            item_price = MARKET_HALL_BAGIETKA_CENA;
            item_points = MARKET_HALL_BAGIETKA_PUNKTY;
        } else if (random_item == 2) {
            item_name = "Jabłko";
            item_price = MARKET_HALL_JABLKO_CENA;
            item_points = MARKET_HALL_JABLKO_PUNKTY;
        } else if (random_item == 3) {
            item_name = "Gruszka";
            item_price = MARKET_HALL_GRUSZKA_CENA;
            item_points = MARKET_HALL_GRUSZKA_PUNKTY;
        } else if (random_item == 4) {
            item_name = "Banan";
            item_price = MARKET_HALL_BANAN_CENA;
            item_points = MARKET_HALL_BANAN_PUNKTY;
        } else {
            item_name = "Woda";
            item_price = MARKET_HALL_WODA_CENA;
            item_points = MARKET_HALL_WODA_PUNKTY;
        }

        set_console_color(0x0D, 0);
        println("Nowa oferta");
        set_console_color(6, 0);
        println(item_name);
        set_console_color(7, 0);
        printf("Cena: %.2f\n", item_price);
        printf("Punkty najedzenia: %d punktów\n", item_points);
        println("  1 - Kup");
        println("  2 - Odrzuć");
        println("  3 - Wyjdź");

        string readed = read("> ", 2);
        if (readed == "1") {
            if (item_price > money) {
                set_console_color(4, 0);
                println("Nie stać cię na taki wydatek, ale wolisz się zadłużyć.");
                set_console_color(7, 0);
            }
            remove_money(item_price);
            hunger -= item_points;
            set_console_color(2, 0);
            println("Zakupiono pomyślnie!");
            set_console_color(7, 0);
            continue;
        } else if (readed == "2") {
            continue;
        } else if (readed == "3") {
            break;
        }
    }
}

void handle_casino() {
    set_console_color(7, 0);
    println("<Ochrona> Siema mordko! Witaj w tym kasynowskim świecie!");
    
    while (true) {
        println("<Miły pan> Co tam chcesz obstawiać? Czerwone (R) czy czarne (B), a może wyjść chcesz (E)?");
        string response = read("# ");
        
        if (response[0] == 'E' || response[0] == 'e') {
            println("<Miły pan> Żegnam Cię, szczęścia w przyszłości!");
            break;
        }
        
        println("Obstawiasz 250$.");
        int random_num = get_random_int_to_percent() % 2;
        
        if ((response[0] == 'R' || response[0] == 'r') && random_num == 0) {
            println("Wygrałeś! Czerwone trafiło!");
            add_money(250);
        } else if ((response[0] == 'B' || response[0] == 'b') && random_num == 1) {
            println("Wygrałeś! Czarne trafiło!");
            add_money(250);
        } else {
            println("Przegrałeś. Spróbuj jeszcze raz.");
            remove_money(250);
        }
    }
}

void handle_work() {
    set_console_color(7, 0);
    println("<Szef> Witam! Popracujesz se dzisiaj mocno!");
    for (size_t i = 0; i < 30; i++)
    {
        add_one_hunger();
        Sleep(500);
    }
    println("<Szef> No, wystarczy! Możesz iść!");
}

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
        }

        set_console_color(4, 0);
        println("Niepoprawny numer/znak");
        set_console_color(7, 0);
    }
}

void handle_home_talking() {
    printnl();
    if (!was_talking_before) {
        set_console_color(2, 0);
        println("Rozmawiasz po raz pierwszy. Będziesz widział menu, z którego będziesz");
        println("mógł wybierać swoje odpowiedzi. Za każdym razem będziesz rozmawiał z inną");
        println("osobą. Rozmowa z mamą jest najlepsza, gdyż możesz tym sprawić, że");
        println("mama urodzi brata albo siostrę.");
        was_talking_before = true;
    }
    set_console_color(7, 0);
    // 1. Mama; 2. Rodzeństwo; 3. Tata
    if (last_talked_with == "Mama") {
        last_talked_with = "Rodzeństwo";
        if (brothers == 0 && sisters == 0) {
            set_console_color(4, 0);
            println("Chciałeś porozmawiać z rodzeństwem, ale zdałeś sobie sprawę, że go nie masz.");
            set_console_color(7, 0);
            return;
        }
        set_console_color(4, 0);
        println("Rodzeństwo się obraziło, bo nie dałeś ściągnąć na kartkówce.");
        set_console_color(7, 0);
    } else if (last_talked_with == "Rodzeństwo") {
        last_talked_with = "Tata";
        println("Rozpoczynasz rozmowę z tatą.");
        while (true) {
            mum_tokens++;
            set_console_color(2, 0);
            print("1) ");
            set_console_color(7, 0);
            println("Potrzebujesz pomocy?");
            set_console_color(2, 0);
            print("2) ");
            set_console_color(7, 0);
            println("Jak się czujesz?");
            set_console_color(2, 0);
            print("3) ");
            set_console_color(7, 0);
            println("Idę do swojego pokoju na chwilę [koniec rozmowy].");
            string task = read("# ", 3);
            if (task == "1") {
                println("<Tata> Nie, ale fajnie, że pytasz.");
                continue;
            } else if (task == "2") {
                println("<Tata> Wspaniale!");
                continue;
            } else if (task == "3") {
                break;
            } else {
                set_console_color(4, 0);
                println("Niepoprawny numer/znak");
                set_console_color(7, 0);
            }
        }
        return;
    } else if (last_talked_with == "Tata") {
        last_talked_with = "Mama";
        println("Rozpoczynasz rozmowę z mamą.");
        while (true) {
            mum_tokens++;
            if (mum_tokens % 27 == 0) {
                age++;
                println("<Mama> Wszystkiego najlepszego z okazji Twoich już");
                println("       " + to_string(age) + " urodzin!");
                break;
            }
            if (mum_tokens % 100 == 0) {
                int rn2 = get_random_int_to_percent() % 2 + 1;
                if (rn2 == 1) {
                    println("<Mama> Chciałabym Ci coś powiedzieć. Jedziemy do szpitala.");
                    println("       Wygląda na to, że dzisiaj urodzę twojego brata.");
                    Sleep(5000);
                    brothers++;
                    break;
                } else {
                    println("<Mama> Chciałabym Ci coś powiedzieć. Jedziemy do szpitala.");
                    println("       Wygląda na to, że dzisiaj urodzę twoją siostrę.");
                    Sleep(5000);
                    sisters++;
                    break;
                }
            }
            set_console_color(2, 0);
            print("1) ");
            set_console_color(7, 0);
            println("Pomóc Ci w czymś?");
            set_console_color(2, 0);
            print("2) ");
            set_console_color(7, 0);
            println("Idę do swojego pokoju na chwilę [koniec rozmowy].");
            string task = read("# ", 3);
            if (task == "1") {
                println("<Mama> Nie, dzięki.");
                continue;
            } else if (task == "2") {
                break;
            } else {
                set_console_color(4, 0);
                println("Niepoprawny numer/znak");
                set_console_color(7, 0);
            }
        }
        return;
    }
}

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
    system("chcp 65001 > nul");
    system("cls");
    set_console_color(4, 0);
    println("JUAMP - symulator życia");
    print("Aktualna wersja: ");
    println(JUAMP_VERSION);
    set_console_color(7, 0);

    bool needConfig = true; // will be usefull on save
    if (needConfig) {
        printnl();
        name = read("Wpisz imię: ");
        print("Twoje miasto: losowanie...");
        Sleep(1000);
        city = "Loresphread";
        print("\b\b\b\b\b\b\b\b\b\b\b\b");
        println(city);
        set_console_color(2, 0);
        println("  Loresphread to niewielkie miasteczko położone w zachodniej");
        println("  części kraju. Jest tam umiarkowany klimat, ale śnieg prawie");
        println("  nigdy nie pada. Na ogół społeczność jest przyjazna i skierowana");
        println("  na poznawanie nowych ludzi, również spoza okolicy.");
        set_console_color(7, 0);
    }

    handle_home();

    set_console_color(7, 0);
    return 0;
}
