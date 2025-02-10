#include <string>
#include <vector>
#include <map>
#ifdef _WIN32
#include <windows.h>
#define sleepsec(sec) Sleep(sec * 1000)
#else
#define sleepsec(sec) sleep(sec)
#endif

typedef std::string string;

struct Location {
    string id;
    string name;
    string description;
    std::map<string, string> directions;
};

extern std::vector<Location> locations;

extern string name;
extern string gender; // b - chłop, g - baba
extern int age;
extern double money;
extern int reputation;
extern int strenght;
extern int speed;
extern int inteligency;
extern int condition;
extern string location_id;
extern double lvl;
extern int cats;
extern int dogs;
extern int hunger;

extern void print(string what);
extern void println(string what);
extern void save_game();
extern string read(string prefix);
extern void set_console_color(int color);
extern void clear_screen();
extern void print_logo();
extern void add_hunger(int what);