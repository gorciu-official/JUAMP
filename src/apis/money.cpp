#include "../declarations.hpp"

void add_money(double money2) {
    player->money = player->money + money2;
    int cfg = current_foreground;
    int cbg = current_background;
    set_console_color(6, 0);
    string startgender;
    if (player->gender == 1) {
        startgender = "Otrzymałaś ";
    } else {
        startgender = "Otrzymałeś ";
    }
    print_center_line(startgender + std::to_string(money2) + "$. Masz teraz aż " + std::to_string(player->money));
    
    set_console_color(cfg, cbg);
}

void remove_money(double money2) {
    player->money = player->money - money2;
    int cfg = current_foreground;
    int cbg = current_background;
    set_console_color(6, 0);
    string startgender;
    if (player->gender == 1) {
        startgender = "Zapłaciłaś lub straciłaś ";
    } else {
        startgender = "Zapłaciłeś lub straciłeś ";
    }
    print_center_line(startgender + std::to_string(money2) + "$. Masz teraz tylko " + std::to_string(player->money));
    
    set_console_color(cfg, cbg);
}