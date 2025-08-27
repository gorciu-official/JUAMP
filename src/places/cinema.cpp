#include "../declarations.hpp"

#define KINO_CENA 45

void handle_cinema() {
    if (money < KINO_CENA) {
        set_console_color(4, 0);
        println("Nie masz wystarczająco pieniędzy, aby obejrzeć film.");
        return;
    }
    remove_money(KINO_CENA);
    set_console_color(4, 0);
    println("UWAGA! Ta część gry zawiera treści, które są pobierane z zewnętrznych źródeł. Nie ponosimy odpowiedzialności");
    println("  za treści inne niż oczekiwane lub za ewentualne problemy po stronie serwerów. Naciśnij dowolny klawisz, aby kontynuować.");
    pause_nul();
    set_console_color(7, 0);
    println("Powiększ terminal jak najbardziej jak możesz, aby zapewnić najlepsze wrażenia z kina. Masz 5 sekund na przygotowanie się.");
    Sleep(5000);
    int animation = get_random_number() % 5;
    string choice;
    switch (animation) {
        case 0:
            system("curl --max-time 15 --silent http://ascii.live/playstation");
            break;
        case 1:
            system("curl --max-time 15 --silent http://parrot.live");
            break;
        case 2:
            system("curl --max-time 15 --silent http://ascii.live/forrest");
            break;
        case 3:
            system("curl --max-time 15 --silent http://ascii.live/rick");
            break;
        case 4:
            set_console_color(4, 0);
            println("Wylosowano dla Ciebie film horror. Czy chcesz go obejrzeć? (T/N)");
            set_console_color(7, 0);
            choice = read("# ");
            if (choice != "T" && choice != "t") {
                add_money(KINO_CENA);
                break;
            }
            print("C");
            Sleep(500);
            print("z");
            Sleep(500);
            print("y");
            Sleep(500);
            print(" to");
            Sleep(500);
            print(" jest");
            Sleep(500);
            print(" twoje");
            Sleep(500);
            print(" ");
            Sleep(1000);
            print("I");
            Sleep(1000);
            println("P?");
            system("curl ifconfig.me");
            break;
        default:
            set_console_color(4, 0);
            println("Wystąpił błąd podczas wyświetlania filmu. Spróbuj ponownie.");
            add_money(KINO_CENA);
            break;
    }
    set_console_color(7, 0);
}