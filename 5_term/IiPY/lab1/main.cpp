#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const string BATTERY_FILEPATH{"/sys/class/power_supply/BAT0/"};
const string POWER_MODE_PATH{"/sys/firmware/acpi/platform_profile"};

int main() {
    cout << "Charging status:\t" << ifstream{BATTERY_FILEPATH + "status"}.rdbuf()
         << "Battery type:\t\t" << ifstream{BATTERY_FILEPATH + "technology"}.rdbuf()
         << "Battery percentage:\t" << ifstream{BATTERY_FILEPATH + "capacity"}.rdbuf()
         << "Power mode:\t\t\t" << ifstream{POWER_MODE_PATH}.rdbuf();

    cout << endl << "Extra Task" << endl;

    ifstream energy_file{BATTERY_FILEPATH + "energy_now"};
    int energy;
    energy_file >> energy;

    ifstream power_file{BATTERY_FILEPATH + "power_now"};
    int power;
    power_file >> power;

    auto float_time = static_cast<double>(energy) / power;
    auto hours = static_cast<int>(float_time);
    auto minutes = static_cast<int>((float_time - hours) * 60);

    cout << "Battery remaining time:\t" << hours << ':' << setw(2) << setfill('0') << minutes << endl;


}
