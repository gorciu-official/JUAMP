#include <declarations.h>

void add_newspaper_event()
{
    int event = get_random_number() % 7;
    switch (event)
    {
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
    }
}

void handle_newspaper()
{
    add_newspaper_event();
    printnl();
    add_newspaper_event();
}