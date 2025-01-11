#include "declarations.hpp"
#include <iostream>

Location get_location_by_id(const string& id) {
    for (const auto& location : locations) {
        if (location.id == id) {
            return location;
        }
    }
    set_console_color(1);
    println("Internal JUAMP error. Please send a detailed description to Gorciu.");
    set_console_color(7);
    while (true) continue;
}

void display_location(Location location) {
    println("ID: " + location.id);
    println("Nazwa: " + location.name);
    println("Kierunki:");

    for (const auto& [key, value] : location.directions) {
        println(key + " -> " + value);
    }
}

void do_command(string command) {
    const Location loc = get_location_by_id(location_id);

    for (const auto& [key, value] : loc.directions) {
        if (command == key) {
            location_id = value;
            return;
        }
    }

    if (command == "rozejrzyj") {
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

void handle_game() {
    while (true) {
        string clocation = location_id;
    
        do_command(read(name + " >>"));

        if (clocation != location_id) {
            display_location(get_location_by_id(location_id));
        }

        save_game();
    }
}