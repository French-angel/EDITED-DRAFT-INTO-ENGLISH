#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <chrono> 
#include <ctime>

using namespace std;
using namespace std::chrono;

void ShowCurrentTime() {
    time_t seconds = time(NULL);
    cout << "Current time in your region: " << ctime(&seconds) << endl;
}

void SelectTimeZone() {
    string timezone;
    cout << "Enter timezone name, e.g., UTC Europe/Moscow Europe/London America/New_York Asia/Tokyo Australia/Sydney" << endl;
    getline(cin, timezone);

    auto now = system_clock::now();
    zoned_time zt{ locate_zone(timezone), now };
    cout << "Time in " << timezone << ": " << zt << endl;
}

void StartTimer() {
    auto start_time = high_resolution_clock::now();
    cout << "Timer is running. Press ENTER to stop." << endl;
    cin.get();
    auto end_time = high_resolution_clock::now();
    auto seconds = duration_cast<seconds>(end_time - start_time);
    cout << "Elapsed time: " << seconds.count() << " seconds" << endl;
}

int main() {
    int choice;
    cout << "Choose an option:" << endl
        << "1 - Show time in a specific timezone" << endl
        << "2 - Show current local time" << endl
        << "3 - Start timer" << endl;
    cin >> choice;
    cin.ignore();
    switch (choice) {
    case 1:
        SelectTimeZone();
        break;
    case 2:
        ShowCurrentTime();
        break;
    case 3:
        StartTimer();
        break;
    default:
        cout << "Invalid choice" << endl;
    }
}
