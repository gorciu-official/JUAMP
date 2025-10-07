#include "declarations.hpp"
#include <vector>

void handle_home_talking() {
    printnl();
    if (!was_talking_before) {
        set_console_color(2, 0);
        println("Rozmawiasz po raz pierwszy. Będziesz widział menu, z którego będziesz");
        println("mógł wybierać swoje odpowiedzi. Za każdym razem będziesz rozmawiał z inną");
        println("osobą. Rozmowa z mamą jest najlepsza, gdyż możesz tym sprawić, że");
        println("mama urodzi brata albo siostrę (dziwne, ale tak).");
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

        int is_okay = get_random_number() % 2 + 1; // 2 = false
        if (is_okay == 2) {
            set_console_color(4, 0);
            println("Rodzeństwo się obraziło, bo nie dałeś ściągnąć na kartkówce.");
            set_console_color(7, 0);
            return;
        }
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
                talk("Tata", "Nie, dzięki.");
                continue;
            } else if (task == "2") {
                int is_dad_ok = get_random_number() % 2 + 1;
                if (is_dad_ok == 1) {
                    talk("Tata", "Dobrze, ale czuję się trochę zmęczony.");
                } else {
                    talk("Tata", "Szczerze, nie czuję się najlepiej.");
                }
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
                talk("Mama", "Wszystkiego najlepszego z okazji twoich już " + std::to_string(age) + " urodzin.\nCieszę się, że jesteś ze mną.");
                break;
            }
            if (mum_tokens % 100 == 0) {
                int rn2 = get_random_number() % 2 + 1;
                if (rn2 == 1) {
                    talk("Mama", "Chciałabym Ci coś powiedzieć. Jedziemy do szpitala.\nWygląda na to, że dzisiaj urodzę twojego brata.");
                    Sleep(5000);
                    brothers++;
                    break;
                } else {
                    talk("Mama", "Chciałabym Ci coś powiedzieć. Jedziemy do szpitala.\nWygląda na to, że dzisiaj urodzę twoją siostrę.");
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
            println("Jaka pogoda?");
            set_console_color(2, 0);
            print("3) ");
            set_console_color(7, 0);
            println("Idę do swojego pokoju na chwilę [koniec rozmowy].");
            string task = read("# ", 3);
            if (task == "1") {
                talk("Mama", "Nie, nie potrzebuję pomocy.");
                continue;
            } else if (task == "2") {
                talk("Mama", "Sam zobacz.");
                Sleep(5000);
                system("curl wttr.in?lang=pl");
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
    }
}

void handle_park_talking() {
    std::vector<std::vector<std::pair<string, string>>> dialogues = {
        {
            {"Ty", "Nic się panu nie stało?"},
            {"Mężczyzna", "Nie, nic się nie stało. Co u Ciebie?"},
            {"Ty", "Wszystko w porządku. Co pan tu robi?"},
            {"Mężczyzna", "Spaceruję sobie. Nudzi mi się. W domu nie mam niczego do roboty.\n Babka zawsze mnie wypycha na dwór."},
            {"Ty", "Aha. To ja idę dalej. Miłego spaceru."},
            {"Mężczyzna", "Dziękuję."}
        },
        {
            {"Ty", "Dzień dobry, co słychać?"},
            {"Kobieta", "Dzień dobry, wszystko dobrze. A u Ciebie?"},
            {"Ty", "Też dobrze. Co pani tu robi?"},
            {"Kobieta", "Przyszłam na spacer z psem. Lubię spędzać czas na świeżym powietrzu."},
            {"Ty", "To miłego spaceru."},
            {"Kobieta", "Dziękuję, nawzajem."}
        },
        {
            {"Ty", "Cześć, jak się masz?"},
            {"Chłopak", "Cześć, dobrze. A Ty?"},
            {"Ty", "Też dobrze. Co robisz w parku?"},
            {"Chłopak", "Przyszedłem pobiegać. Lubię aktywnie spędzać czas."},
            {"Ty", "To powodzenia w bieganiu."},
            {"Chłopak", "Dzięki, miłego dnia."}
        }
    };

    while (true) {
        int random_index = get_random_number() % dialogues.size();

        printnl();
        set_console_color(7, 0);
        for (const auto& dialogue : dialogues[random_index]) {
            const auto& who = dialogue.first;
            const auto& what = dialogue.second;
            talk(who, what);
            Sleep(500);
        }

        printnl();
        set_console_color(3, 0);
        println("Czy chcesz zagadać do kogoś innego? (T/N)");
        string choice = read("> ", 0xD);
        if (choice != "T" && choice != "t") {
            break;
        }

        println("Idziesz dalej. Szukasz osoby, która chciałaby porozmawiać.");
        Sleep(3000);
        continue;
    }
}

void handle_ropucha_talking() {
    talk("Sprzedawczyni z \"Ropucha\"", "Witaj. Chcesz coś kupić?");
    int num = get_random_number() % 5;
    switch (num) {
        case 0:
            talk("Ty", "Nie, proszę mi tu nie wciskać kredytu na mieszkanie.");
            talk("Sprzedawczyni z \"Ropucha\"", "Ale ja nie jestem bankiem...");
            talk("Ty", "Och! Ja znam te wasze sztuczki. Na nic się nie nabiorę. ŻADNEGO KREDYTU!");
            talk("Sprzedawczyni z \"Ropucha\"", "Niszczysz mi reputację. PROSZĘ WYJŚĆ.");
            remove_reputation(2);
            break;

        case 1:
            talk("Ty", "Nie. Gnębi mnie taka jedna rzecz. Ile to dwa plus dwa?");
            talk("Sprzedawczyni z \"Ropucha\"", "NIE MÓWI SIĘ PLUS TYLKO DODAĆ!");
            talk("Ty", "No dobra, do widzenia.");

        case 2:
            talk("Ty", "Nie, dziękuję. Niczego nie potrzebuję.");
            talk("Sprzedawczyni z \"Ropucha\"", "W porządku, zapraszam ponownie.");
            add_reputation(2);
            break;

        case 3:
            talk("Ty", "Nie, dziękuję.");
            talk("Sprzedawczyni z \"Ropucha\"", "Zapraszam więc ponownie.");
            add_reputation(2);
            break;
                
        default:
            talk("Ty", "Nie, mam autyzm.");
            talk("Sprzedawczyni z \"Ropucha\"", "xD... Wyjdź mi ze sklepu natychmiast!");
            remove_reputation(1);
            break;
    }
}