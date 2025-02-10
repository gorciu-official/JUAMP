#include "declarations.hpp"
#include <iostream>

std::vector<std::string> split_by_separator(const string& str, char separator) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end;

    while ((end = str.find(separator, start)) != string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
    }

    result.push_back(str.substr(start));

    return result;
}

int make_talking_selection(std::vector<string> vc) {
    int i = 0;
    for (auto& sel : vc) {
        i++;
        string is = std::to_string(i);
        set_console_color(2);
        print(is + ") ");
        set_console_color(7);
        println(sel);
    }
    while (true) {
        try {
            int what = std::stoi(read(">"));
            return what;
        } catch(const std::exception& e) {
            continue;
        }
        
    }
}

void talk(string schema) {
    if (schema == "samouczek-piotr" && location_id == "plac.main.centered") {
        age = 15;
        println("\"Witaj wędrowcze. Widzę, że pozwoliłeś sobie wejść do naszego miasta. Jeżeli czytałeś o naszym mieście, a śmiem");
        println("twierdzić, że tak nie było, zapewne wiesz że jestem Piotr i pomagam turystom przeżyć na tej wyspie - to moja praca!");
        println("Gdybyś był głupi, jesteś na niezlokalizowanej przez geografów wyspie, na której leży nasz kraj - Nopsania. Zadawaj");
        println("pytania póki możesz, żebyś nie był dziwakiem w tłumie ogarniętych ludzi.\"");
        while (true) {
            int sel = make_talking_selection({"Co jest stolicą tego kraju?", "Co możesz powiedzieć o tym mieście?", "Jak się poruszać?", "Jak załatwiać moje... no wiesz... podstawowe potrzeby?", "Jak ćwiczyć umiejętności?", "Czy są rzeczy, które powinienem wiedzieć?", "To tyle!"});
            if (sel == 1 || sel == 2) {
                println("\"Co ciekawe i zaskakujące, miasto które rozlega się przed tobą to stolica Nopsanii. Hobby wielu mieszkańców");
                println("to pływanie, a więc wybór był oczywisty. Dlatego stolica znajduje się tutaj.\"");
                continue;
            } else if (sel == 3) {
                println("\"Po prostu piszesz dowolny angielski kierunek na klawiaturze. Kierunki z komendy `popatrz` są wskazówką, gdzie możesz");
                println("się ruszyć, a gdzie nie. Jak masz problem z komendami to wpisuj `pomoc`, co da Ci listę wszystkich komend. Wypróbuj je");
                println("jedna po drugiej - samodzielnie.\"");
            } else if (sel == 4) {
                println("\"Jeżeli chodzi o jedzenie i picie, zlokalizuj halę targową - tam zawsze jest coś do jedzenia i zaspokojenia spragnienia.");
                println("Reszta intymnych problemów nie istnieje na Nopsanii. To miejsce zostało kiedyś zaczarowane, aby ułatwić życie ludziom.\"");
            } else if (sel == 5) {
                println("\"Gdzieś na północ od Głównego Placu jest Hala Ćwiczeniowa. Tam możesz użyć komentdy `trenuj`.\"");
            } else if (sel == 6) {
                println("\"Czy są rzeczy, które powinieneś wiedzieć? Na pewno. Ludzie są tu życzliwi, wystarczy że użyjesz komendy `zagadaj`, by");
                println("dowiedzieć się czegoś. Polecam ci również korzystać z komendy `dane`.\"");
            } else if (sel == 7) {
                println("Zdawając sobie sprawę, że już nikt prawdopodobnie Ci nie pomoże, zażyłeś miksturę od Piotra i przeteleportowałeś się.");
                break;
            }
        }
    } else if (schema == "kaplan" && location_id == "plac.main.centered") {
        println("\"Boże, pobłogosław go.\"");
    } else if (schema == "ochroniarz" && location_id == "plac.treninghall") {
        println("\"Co chcesz?\"");
        while (true) {
            int sel = make_talking_selection({"Jak ćwiczyć?", "Jak mogę sprawdzić co mogę ćwiczyć?", "Idę ćwiczyć."});
            if (sel == 1) {
                println("\"Kolejny de... Musisz wpisać `trenuj <umiejetnosc>`. A i coś się psuje jak piszesz polskie znaki.\"");
            } else if (sel == 2) {
                println("\"Musisz wpisać `umiejetnosci`.\"");
            } else if (sel == 3) break;
        }
    } else if (schema == "sprzedawczyni" && location_id == "ropucha") {
        println("\"No kupujesz czy nie? Użyj komendy `lista` jak chcesz mieć listę przedmiotów, które sprzedaję, a `kup <coś>`, jak chcesz kupować.\"");
    } else if (schema == "pani" && location_id == "schronisko") {
        println("\"Dzień dobry, tu Schronisko Przytulisko. Co chcesz zrobić?\"");
        int what = make_talking_selection({"Chcę oddać kota do schroniska", "Chcę oddać psa do schroniska", "Chcę adoptować psa", "Chcę adoptować kota", "Narka!"});
        if (what == 1) {
            if (cats == 0) {
                println("\"Ale ty nie masz kotów!\"");
                return;
            }
            cats = cats - 1;
        }
        if (what == 2) {
            if (dogs == 0) {
                println("\"Ale ty nie masz psów!\"");
                return;
            }
            dogs = dogs - 1;
        }
        if (what == 3) {
            dogs++;
        }
        if (what == 4) {
            cats++;
        }
        println("\"Dziękujemy za skorzystanie z naszych usług.\"");
    } else {
        set_console_color(1);
        println("Nie ma tu nikogo takiego.");
        set_console_color(7);
    }
}

Location get_location_by_id(const string& id) {
    for (const auto& location : locations) {
        if (location.id == id) {
            return location;
        }
    }
    set_console_color(1);
    println("Internal JUAMP error. Please send a detailed description to Gorciu (code 0x01).");
    set_console_color(7);
    while (true) continue;
}

void display_location(Location location) {
    set_console_color(2);
    println(location.name);
    set_console_color(7);
    println(location.description);
    set_console_color(5);
    print("Kierunki: ");

    for (const auto& [key, value] : location.directions) {
        print(key + " ");
    }
    println("");
    set_console_color(7);
}

int get_new_level() {
    int plvl = lvl;
    int everything = inteligency + strenght + condition + speed;
    int newlvl = everything % 30 + 1;
    if (newlvl != lvl) {
        println("Zdobyłeś nowy poziom!");
    }
    return newlvl;
}

void do_command(string command) {
    const Location loc = get_location_by_id(location_id);

    for (const auto& [key, value] : loc.directions) {
        if (command == key) {
            add_hunger(5 / std::max(1, condition / 5));
            location_id = value;
            return;
        }
    }

    std::vector<string> cmd = split_by_separator(command, ' ');

    string base_command = "";
    string arg1 = "";

    int i = 0;
    for (auto &t : cmd) {
        if (i == 0) base_command = t;
        if (i == 1) arg1 = t;
        i++;
    }

    if (base_command == "w" || base_command == "e" || base_command == "n" || base_command == "s" || base_command == "up" || base_command == "down") {
        set_console_color(1);
        println("Nie możesz tu pójść.");
        set_console_color(7);
        return;
    };

    if (base_command == "popatrz") {
        display_location(get_location_by_id(location_id));
        return;
    }

    if (base_command == "wyjdz") {
        save_game();
        set_console_color(6);
        println("Dziękujemy za rozgrywkę!");
        set_console_color(7);
        println("Gra została zapisana. Naciśnij Ctrl+C lub zamknij te okno, aby zakończyć.");
        while (true) continue;
        return;
    }

    if (base_command == "zagadaj") {
        talk(arg1);
        return;
    }

    if (base_command == "umiejetnosci") {
        set_console_color(6);
        println("Kończenie zaplanowane na aktualizację 9.1.0");
        set_console_color(7);
        println("Aktualnie możesz trenować tylko współczynniki -  \"sila\", \"szybkosc\", \"iteligencja\" i \"kondycja\"!");
        return;
    }

    if (base_command == "trenuj") {
        if (location_id == "plac.treninghall") {
            if (arg1 != "sila" && arg1 != "szybkosc" && arg1 != "inteligencja" && arg1 != "kondycja") return;
            if (arg1 == "sila") strenght++;
            if (arg1 == "szybkosc") speed++;
            if (arg1 == "inteligencja") speed++;
            add_hunger(30);
            set_console_color(2);
            println("Udało się!");
            set_console_color(7);
            lvl = get_new_level();
        } else {
            set_console_color(1);
            println("Nie możesz tu trenować");
            set_console_color(7);
        }
        return;
    }

    if (base_command == "lista") {
        if (location_id == "ropucha") {
            println("gazeta - 3.50$       bulka - 1.20$");
            println("tymsok - 1.99$");
        } else {
            set_console_color(1);
            println("Nie możesz tu nic kupić");
            set_console_color(7);
        }
        return;
    }

    if (base_command == "kup") {
        if (location_id == "ropucha") {
            if (arg1 != "gazeta" && arg1 != "tymsok" && arg1 != "bułka") return;
            if (arg1 == "gazeta") {
                money -= 3.50;
            }
            if (arg1 == "tymsok") {
                money -= 1.99;
                hunger = hunger - 5;
            }
            if (arg1 == "bulka") {
                money -= 1.20;
            }
            set_console_color(3);
            println("Kupiono przedmiot.");
            set_console_color(7);
        } else {
            set_console_color(1);
            println("Nie możesz tu nic kupić");
            set_console_color(7);
        }
        return;
    }
    
    println("Hmm?");
}

void handle_game(bool need_to_start_dialogue) {
    try {
        clear_screen();
        set_console_color(6);
        print_logo();
        set_console_color(7);
        println("Wpisz \"pomoc\" w razie wątpliwości.\n");

        if (need_to_start_dialogue) talk("samouczek-piotr");

        display_location(get_location_by_id(location_id));

        while (true) {
            string clocation = location_id;
        
            do_command(read(name + " >>"));

            if (clocation != location_id) {
                display_location(get_location_by_id(location_id));
            }

            save_game();
        }
    } catch (std::exception e) {
        set_console_color(1);
        println("Internal JUAMP error. Please send a detailed description to Gorciu (code 0x02).");
        set_console_color(7);
    }
}