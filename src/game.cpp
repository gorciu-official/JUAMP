#include "declarations.hpp"
#include <iostream>

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
    if (schema == "samouczek-piotr") {
        age = 15;
        println("\"Witaj wędrowcze. Widzę, że pozwoliłeś sobie wejść do naszego miasta. Jeżeli czytałeś o naszym mieście, a śmiem");
        println("twierdzić, że tak nie było, zapewne wiesz że jestem Piotr i pomagam turystom przeżyć na tej wyspie - to moja praca!");
        println("Gdybyś był głupi, jesteś na niezlokalizowanej przez geografów wyspie, na której leży nasz kraj - Nopsania. Zadawaj");
        println("pytania póki możesz, żebyś nie był dziwakiem w tłumie ogarniętych ludzi.\"");
        while (true) {
            int sel = make_talking_selection({"Co jest stolicą tego kraju?", "Co możesz powiedzieć o tym mieście?", "Jak się poruszać?", "Jak załatwiać moje... no wiesz... podstawowe potrzeby?", "To tyle!"});
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
                println("Zdawając sobie sprawę, że już nikt prawdopodobnie Ci nie pomoże, zażyłeś miksturę od Piotra i przeteleportowałeś się.");
                break;
            } else {
                set_console_color(1);
                println("Internal JUAMP error. Please send a detailed description to Gorciu (code 0x01).");
                set_console_color(7);
                while (true) continue;
            }
        }
    } else {
        set_console_color(1);
        println("Internal JUAMP error. Please send a detailed description to Gorciu (code 0x01).");
        set_console_color(7);
        while (true) continue;
    }
}

Location get_location_by_id(const string& id) {
    for (const auto& location : locations) {
        if (location.id == id) {
            return location;
        }
    }
    set_console_color(1);
    println("Internal JUAMP error. Please send a detailed description to Gorciu (code 0x02).");
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

void do_command(string command) {
    const Location loc = get_location_by_id(location_id);

    for (const auto& [key, value] : loc.directions) {
        if (command == key) {
            location_id = value;
            return;
        }
    }

    if (command == "popatrz") {
        display_location(get_location_by_id(location_id));
        return;
    }

    if (command == "wyjdz") {
        save_game();
        set_console_color(6);
        println("Dziękujemy za rozgrywkę!");
        set_console_color(7);
        println("Gra została zapisana. Naciśnij Ctrl+C lub zamknij te okno, aby zakończyć.");
        while (true) continue;
        return;
    }
}

void handle_game(bool need_to_start_dialogue) {
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
}