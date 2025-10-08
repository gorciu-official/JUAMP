#include "../declarations.hpp"
#include <ctime>

void handle_school() {
    clear_screen();
    set_console_color(3, 0);
    print_center_line("Jesteś w szkole.");
    set_console_color(7, 0);
    println("Spędzasz trochę [za dużo] czasu na nauce...");
    sleep_seconds(10);
    was_at_school = true;
    last_school_time = time(nullptr);
    println("Wychodzisz ze szkoły.");
    pause_nul();
}