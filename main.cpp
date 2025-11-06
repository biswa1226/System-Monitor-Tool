#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

float getCPUUsage() {
    static long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;
    double percent;
    ifstream file("/proc/stat");
    string cpu;
    long long user, nice, sys, idle;
    file >> cpu >> user >> nice >> sys >> idle;
    file.close();

    if (lastTotalUser != 0 || lastTotalUserLow != 0 || lastTotalSys != 0 || lastTotalIdle != 0) {
        long long diffUser = user - lastTotalUser;
        long long diffUserLow = nice - lastTotalUserLow;
        long long diffSys = sys - lastTotalSys;
        long long diffIdle = idle - lastTotalIdle;
        long long total = diffUser + diffUserLow + diffSys + diffIdle;
        percent = (double)(diffUser + diffUserLow + diffSys) / total * 100.0;
    } else {
        percent = 0.0;
    }

    lastTotalUser = user;
    lastTotalUserLow = nice;
    lastTotalSys = sys;
    lastTotalIdle = idle;

    return percent;
}

float getMemoryUsage() {
    ifstream file("/proc/meminfo");
    string key;
    long long memTotal, memFree, buffers, cached;
    while (file >> key) {
        if (key == "MemTotal:") file >> memTotal;
        else if (key == "MemFree:") file >> memFree;
        else if (key == "Buffers:") file >> buffers;
        else if (key == "Cached:") { file >> cached; break; }
        else file.ignore(256, '\n');
    }
    file.close();
    long long used = memTotal - memFree - buffers - cached;
    return (float)used / memTotal * 100.0;
}

int getProcessCount() {
    int count = 0;
    system("ls /proc | grep '^[0-9]' > procs.txt");
    ifstream file("procs.txt");
    string line;
    while (getline(file, line)) count++;
    file.close();
    system("rm procs.txt");
    return count;
}

int main() {
    cout << "--------------------------------------\n";
    cout << "     SYSTEM MONITOR TOOL (Linux)\n";
    cout << "--------------------------------------\n";
    cout << "Press Ctrl+C to exit.\n\n";

    while (true) {
        float cpu = getCPUUsage();
        float mem = getMemoryUsage();
        int proc = getProcessCount();

        cout << "CPU Usage: " << cpu << "%\n";
        cout << "Memory Usage: " << mem << "%\n";
        cout << "Processes Running: " << proc << "\n";
        cout << "--------------------------------------\n";

        this_thread::sleep_for(chrono::seconds(3));
    }

    return 0;
}
