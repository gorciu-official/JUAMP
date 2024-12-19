#include "declarations.h"

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
                println("       " + std::to_string(age) + " urodzin!");
                break;
            }
            if (mum_tokens % 100 == 0) {
                int rn2 = get_random_number() % 2 + 1;
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