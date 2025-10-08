#include "../declarations.hpp";

void check_school_penalty() {
    if (age > 14) return;
    int now = time(nullptr);
    if (last_school_time == 0) last_school_time = now;
    if (now - last_school_time > 600) {
        set_console_color(4, 0);
        println("Nie byłeś w szkole przez zdecydowanie zbyt długo! Kara: -50$");
        set_console_color(7, 0);
        remove_money(50);
        last_school_time = now;
    }
}