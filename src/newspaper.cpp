#include "declarations.hpp"

void add_newspaper_event() {
    int event = get_random_number() % 15;
    switch (event) {
        case 0:
            println("W Aspergilli powstał nowy projekt ustawy, który zakłada że każdy mieszkaniec musi w ciągu roku posadzić 5 drzew!");
            println("Jest to przygotowanie do nowego parku miejskiego, który ma powstać w niewykorzystanym miejscu na obrzeżach miasta.");
            println("\"Niestety jest to dodatkowe zajęcie dla urzędników, którzy muszą rejestrować sadzenie drzew i nakładać kary\" - mówi");
            println("Profesor dr hab. inż. Dominik Bielecki, który jest przeciwny temu projektowi ustawy. \"To jest niepotrzebne\" - dodaje.");
            break;
        case 1:
            println("Podwyżka cen za śmieci! \"Teraz za śmieci trzeba płacić 2 razy więcej\" - nowy projekt uchwały");
            println("dotarł do rady miasta, która - co wynika z naszych badań - prawdopodobnie go zaakceptuje. Pani");
            println("prezydent miasta mówi, że podwyżka cen za śmieci jest konieczna, aby zwiększyć świadomość");
            println("ekologiczną mieszkańców miasta i zwiększyć zyski miasta. \"Ekościema\" - tak reagują krytycy.");
            break;
        case 2:
            println("11-latka zabiła 2 osoby w wypadku samochodowym! \"To była poważna tragedia\" - mówią świadkowie wypadku.");
            println("Podkreślają, że małoletnia kierowczyni jechała tak jakby nigdy wcześniej nie prowadziła samochodu oraz że");
            println("ze względu na wiek nie mogła posiadać prawa jazdy. 11-latka została przewieziona do szpitala, gdzie przebywa pod");
            println("opieką najznakomitszych lekarzy z kraju, gdzie walczy o życie. Rodzina zerwała z nią wszelkie kontakty.");
            break;
        case 3:
            println("Festiwal muzyki klasycznej w stolicy kraju odbył się już 32 raz! \"Bilety zostały wyprzedane w rekordowym");
            println("czasie! To dla nas ogromny sukces!\" - mówi organizator festiwalu do naszych reporterów. Na wspomnianym");
            println("festiwalu wystąpiło wiele znanych orkiestr i solistów z całego świata, ale nie zabrakło również nuty");
            println("muzyki disco-polo oraz italo-disco, aby przyciągnąć również starsze pokolenie.");
            break;
        case 4:
            println("W kinach pojawił się nowy film, który bije rekordy popularności! \"To najlepszy film, jaki widziałem w");
            println("życiu!\" - mówi jeden z widzów. Film opowiada historię młodego chłopca, który odkrywa swoje magiczne moce i walczy");
            println("z siłami zła, aby uratować świat. Reżyser filmu zapowiada, że to dopiero początek serii, która ma liczyć");
            println("aż 10 części. \"To będzie chyba nowy Harry Potter\" - dodaje widz.");
            break;
        case 5:
            println("Nowy sklep w centrum miasta przyciąga tłumy! \"Mamy wszystko, czego potrzebujesz\" - mówi właściciel sklepu.");
            println("Sklep oferuje szeroki asortyment produktów, od świeżych warzyw i owoców, przez artykuły gospodarstwa domowego,");
            println("po elektronikę i ubrania. Klienci chwalą sobie niskie ceny i miłą obsługę, ale narzekają na wykorzystanie");
            println("chińskich produktów, które są niskiej jakości. \"To jest skandal i wstyd dla miasta!\" - mówią krytycy.");
            break;
        case 6:
            println("W mieście odbył się charytatywny bieg na rzecz dzieci z domów dziecka. \"To wspaniała inicjatywa, która pomaga");
            println("najbardziej potrzebującym\" - mówi organizator biegu. W wydarzeniu wzięło udział ponad 1000 osób, a zebrane");
            println("fundusze zostaną przeznaczone na zakup niezbędnych artykułów dla dzieci. \"Dzieci w Afryce się bardzo");
            println("ucieszą\" - dodaje organizator, co wzbudziło kontrowersje, że pomaga się dzieciom z innych kontynentów.");
            break;
        case 7:
            println("Sprawdziliśmy, dlaczego social media są tak popularne! \"To jest przyszłość!\" - mówi jeden z ekspertów.");
            println("\"Social-media mogą być naszą codziennością, zwłaszcza że Meta wydała na projekt Virtual Reality masę");
            println("kasy, ale ludzie wolą oglądać koty na TikToku niż korzystać z VR\" - dodaje. Ludzie nie chcą rzeczywistości");
            println("VR, ale za to zaglądają do sieci co chwilę, aby sprawdzić, co nowego dzieje się w ich ulubionych serwisach, a");
            println("dzięki uzależniającym algorytmom spędzają tam coraz więcej czasu. \"Jest to opłacalne\" - podsumowują krytycy.");
            break;
        case 8:
            println("Nowa restauracja w mieście zdobywa serca mieszkańców! \"To najlepsze jedzenie, jakie kiedykolwiek jadłem!\"");
            println("- mówi jeden z klientów. Restauracja oferuje szeroki wybór dań kuchni międzynarodowej, a także lokalne specjały.");
            println("Właściciel restauracji zapowiada, że wkrótce wprowadzi nowe dania do menu. \"Co za dużo, to niezdrowo\" -");
            println("komentują krytycy, ponieważ nie chcą, aby restaruracja postawiła na ilość dań a nie na jakość.");
            break;
        case 9:
            println("W mieście otwarto nowy park rozrywki! \"To miejsce pełne atrakcji dla całej rodziny\" - mówi dyrektor parku.");
            println("Park oferuje różnorodne atrakcje, od karuzel i rollercoasterów, po interaktywne wystawy i pokazy.");
            println("Mieszkańcy miasta są zachwyceni nowym miejscem, które zapewnia rozrywkę na najwyższym poziomie. \"Nasze miasto");
            println("jest z każdą chwilą coraz bardziej atrakcyjne dla turystów\" - kontynuuje.");
            break;
        case 10:
            println("W mieście odbył się koncert charytatywny na rzecz schroniska dla zwierząt. \"To wspaniała inicjatywa, która pomaga");
            println("bezdomnym zwierzętom\" - mówi organizator koncertu. W wydarzeniu wzięło udział wielu znanych artystów, a zebrane");
            println("fundusze zostaną przeznaczone na zakup karmy i leków dla zwierząt. Pomimo wszelkich starań organizatorów, nadal");
            println("nie ma zbyt wielu osób chętnych do wspomagania schroniska. \"To jest smutne\" - dodaje organizator.");
            break;
        case 11:
            println("W mieście otwarto nową galerię sztuki! \"To miejsce, gdzie można podziwiać dzieła lokalnych artystów\" - mówi kurator galerii.");
            println("Galeria oferuje szeroki wybór obrazów, rzeźb i fotografii, a także organizuje warsztaty i spotkania z artystami.");
            println("Mieszkańcy miasta są zachwyceni nowym miejscem, które promuje lokalną sztukę. \"To jest coś, czego nam brakowało\" -");
            println("dodaje jeden z odwiedzających galerię. \"Mam nadzieję, że galeria przetrwa na dłużej\" - komentują krytycy.");
            break;
        case 12:
            println("W mieście odbył się festiwal filmowy! \"To wspaniała okazja, aby zobaczyć najnowsze filmy z całego świata\" - mówi organizator festiwalu.");
            println("W wydarzeniu wzięło udział wielu znanych reżyserów i aktorów, a także młodzi twórcy, którzy mieli okazję zaprezentować swoje filmy.");
            println("Mieszkańcy miasta są zachwyceni różnorodnością filmów i wysokim poziomem organizacji festiwalu.");
            break;
        case 13:
            println("W mieście odbył się festiwal kulinarny! \"To miejsce, gdzie można spróbować potraw z całego świata\" - mówi organizator festiwalu.");
            println("W wydarzeniu wzięło udział wielu znanych kucharzy i restauratorów, a także amatorzy gotowania, którzy mieli okazję zaprezentować swoje umiejętności.");
            println("Mieszkańcy miasta są zachwyceni różnorodnością potraw i wysokim poziomem organizacji festiwalu.");
            break;
        case 14:
            println("W mieście odbył się festiwal mody! \"To miejsce, gdzie można zobaczyć najnowsze trendy w modzie\" - mówi organizator festiwalu.");
            println("W wydarzeniu wzięło udział wielu znanych projektantów i modeli, a także młodzi twórcy, którzy mieli okazję zaprezentować swoje kolekcje.");
            println("Mieszkańcy miasta są zachwyceni różnorodnością ubrań i wysokim poziomem organizacji festiwalu.");
            break;
        default:
            println("Niestety, ale coś mokrego kapnęło na gazetę i nie udało Ci się przeczytać tego artykułu.");
            break;
    }
}

void handle_newspaper() {
    add_newspaper_event();
    printnl();
    add_newspaper_event();
}