/* ================================ INCLUDES ================================ */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include "declarations.hpp"
#include "constants.hpp"
#include "toml.hpp"

/* ================================ JUAMP LAUNCHER ================================ */

string DEFAULT_SAVE_NAME = "savegame";
#ifdef _WIN32
const string SAVE_LOCATION = "saves/";
#else
const string SAVE_LOCATION = "~/.local/state/JUAMP/saves/";
#endif
string SAVE_FILE = SAVE_LOCATION + DEFAULT_SAVE_NAME + ".toml";
Player* player;

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
    system("mkdir -p ~/.local");
    system("mkdir -p ~/.local/state");
    system("mkdir -p ~/.local/state/JUAMP");
    system("mkdir -p ~/.local/state/JUAMP/saves");
#endif

    const auto save_file_choice = read("> ");
    SAVE_FILE = SAVE_LOCATION + (save_file_choice == "" ? DEFAULT_SAVE_NAME : save_file_choice) + ".toml";

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

    player->sisters = save_data["player->sisters"].value_or(0);
    player->brothers = save_data["player.brothers"].value_or(0);
    player->was_outside_before = save_data["was_outside_before"].value_or(player->was_outside_before);
    player->was_talking_before = save_data["was_talking_before"].value_or(player->was_talking_before);
    player->has_reputation_before = save_data["has_reputation_before"].value_or(player->has_reputation_before);
    player->last_talked_with = save_data["last_talked_with"].value_or(player->last_talked_with);
    player->mum_tokens = save_data["mum_tokens"].value_or(player->mum_tokens);
    player->hunger = save_data["hunger"].value_or(player->hunger);
    player->money = save_data["money"].value_or(player->money);
    player->name = save_data["name"].value_or(player->name);
    player->city = save_data["city"].value_or(player->city);
    player->age = save_data["age"].value_or(player->age);
    player->gender = save_data["gender"].value_or(player->gender);
    player->reputation = save_data["reputation"].value_or(100);

    clear_screen();
    return true;
}

/* ================================ NEW GAME QUESTIONS ================================ */

void ask_player_name() {
    set_console_color(3, 0);
    print("Wybierz imię - ");
    set_console_color(7, 0);
    println("będzie ono używane w małej ilości, ale jednak jest potrzebne. Może");
    println("to być Twoje prawdziwe imię, pseudonim, czy zupełnie wymyślona nazwa. Nie ma to znaczenia.");
    while (true) {
        player->name = read("# ");
        if (player->name.empty()) {
            set_console_color(4, 0);
            println("Imię nie może być puste!");
            set_console_color(7, 0);
            continue;
        }
        if (player->name == "Mama" || player->name == "Tata" || player->name == "Brat" || player->name == "Siostra" || 
            player->name == "Babcia" || player->name == "Dziadek") {
            set_console_color(4, 0);
            println("Imię nie może być takie jak nazwy członków rodziny!");
            set_console_color(7, 0);
            continue;
        }
        if (player->name == "JUAMP" || player->name == "juamp" || player->name == "Juamp" || 
            player->name == "Gorciu" || player->name == "gorciu" || player->name == "Gorciu") {
            println("Pogrzało Cię lekko mówiąc.");
            continue;
        }
        break;
    }
}

void ask_player_gender() {
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
        player->gender = (gendersel == "Kobieta") ? 1 : 2;
        break;
    }
}

string assign_random_city() {
    std::vector<string> cities = {"Loresphread", "Applaypom", "Sersoponia", "Delaxer", "Bimalia"};
    return cities[get_random_number() % cities.size()];
}

void describe_city(const string& city) {
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
    }
    set_console_color(7, 0);
}

void new_game_setup() {
    printnl();
    set_console_color(2, 0);
    println("Witaj w JUAMP! Przed rozpoczęciem gry musisz odpowiedzieć na kilka pytań.");
    println("Odpowiedzi na te pytania będą miały większy lub mniejszy wpływ na przebieg gry.");
    printnl();

    ask_player_name();
    ask_player_gender();

    printnl();
    set_console_color(3, 0);
    print("Twoje wylosowane miasto: ");
    set_console_color(7, 0);
    sleep_seconds(1);
    player->city = assign_random_city();
    println(player->city);
    describe_city(player->city);
    println("Kliknij dowolny klawisz, by przejść dalej.");
    pause_nul();
}

/* ================================ GAME ENTRY ================================ */

extern void handle_home();

// gets executed by juamp-main.cpp or gui.cpp
int juamp_main() {
    switch_to_utf8();
    clear_screen();

    bool needConfig = !load_game();
    if (needConfig) new_game_setup();
    else {
        set_console_color(7, 0);
        println("Gra wczytana pomyślnie.");
    }

    handle_home();
    set_console_color(7, 0);
    while (!player->save_player_data()) continue;
    return 0;
}