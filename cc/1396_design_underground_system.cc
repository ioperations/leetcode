// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
An underground railway system is keeping track of customer travel times between
different stations. They are using this data to calculate the average time it
takes to travel from one station to another.

Implement the UndergroundSystem class:

void checkIn(int id, string stationName, int t)
A customer with a card ID equal to id, checks in at the station stationName at
time t. A customer can only be checked into one place at a time. void
checkOut(int id, string stationName, int t) A customer with a card ID equal to
id, checks out from the station stationName at time t. double
getAverageTime(string startStation, string endStation) Returns the average time
it takes to travel from startStation to endStation. The average time is computed
from all the previous traveling times from startStation to endStation that
happened directly, meaning a check in at startStation followed by a check out
from endStation. The time it takes to travel from startStation to endStation may
be different from the time it takes to travel from endStation to startStation.
There will be at least one customer that has traveled from startStation to
endStation before getAverageTime is called. You may assume all calls to the
checkIn and checkOut methods are consistent. If a customer checks in at time t1
then checks out at time t2, then t1 < t2. All events happen in chronological
order.
*/

#include <algorithm>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

#include <gtest/gtest.h>

namespace {
class UndergroundSystem {
   public:
    UndergroundSystem() {}

    void CheckIn(int id, string station_name, int t) {
        // auto it = find_if( m_wait.begin(), m_wait.end(), [&](const
        // std::pair<int, Node>& n) { return id == n.first; }); if (it !=
        // m_wait.end()) return;

        Node tmp;
        tmp.station = station_name;
        tmp.time = t;
        m_wait[id] = tmp;
    }

    void CheckOut(int id, string station_name, int t) {
        auto it = find_if(
            m_wait.begin(), m_wait.end(),
            [&](const std::pair<int, Node> &n) { return id == n.first; });
        if (it == m_wait.end()) return;
        Node n = it->second;
        std::string s = n.station >= station_name ? n.station : station_name;
        std::string d = n.station < station_name ? n.station : station_name;

        m_already[make_pair(s, d)].push_back(t - n.time);
    }

    double GetAverageTime(string start_station, string end_station) {
        std::string s =
            start_station >= end_station ? start_station : end_station;
        std::string d =
            start_station < end_station ? start_station : end_station;
        double sum = 0;
        auto &z = m_already[make_pair(s, d)];
        for_each(z.begin(), z.end(), [&](int n) { sum += n; });

        return z.size() ? sum / z.size() : 0;
    }
    ~UndergroundSystem() {
        m_wait.clear();
        m_already.clear();
    }

   private:
    struct Node {
        std::string station;
        int time;
    };
    std::map<int, Node> m_wait;

    std::map<std::pair<std::string, std::string>, std::vector<int>> m_already;
};

#include <unordered_map>

class Solution2 {
   public:
    // startStation:endStation -> {totalTime, numberOfTrips}
    unordered_map<string, pair<long long, int>> station_times;
    // customerId -> startStation
    unordered_map<int, pair<string, int>> in_transit;
    Solution2() {
        station_times.clear();
        in_transit.clear();
    }

    void CheckIn(int id, string station_name, int t) {
        if (in_transit.find(id) != in_transit.end()) return;
        in_transit[id] = {station_name, t};
    }

    void CheckOut(int id, string station_name, int t) {
        auto &info = in_transit[id];
        string start_station = info.first;
        int start_time = info.second;
        string key = start_station + ":" + station_name;
        int time = t - start_time;

        if (station_times.find(key) != station_times.end()) {
            auto &old_times = station_times[key];
            old_times.first += time;
            old_times.second++;
        } else {
            station_times[key] = {time, 1};
        }
        in_transit.erase(id);
    }

    double GetAverageTime(string start_station, string end_station) {
        string key = start_station + ":" + end_station;
        auto &info = station_times[key];
        double avg = (double)info.first / (double)info.second;
        return avg;
    }
};

/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */


TEST(t0, t1) {
    /*
Input
    ["UndergroundSystem","checkIn","checkIn","checkIn","checkOut","checkOut",
"checkOut","getAverageTime","getAverageTime","checkIn","getAverageTime","checkOut","getAverageTime"]

[[],[45,"Leyton",3],[32,"Paradise",8],[27,"Leyton",10],[45,"Waterloo",15],
[27,"Waterloo",20],[32,"Cambridge",22],["Paradise","Cambridge"],["Leyton","Waterloo"],
[10,"Leyton",24],["Leyton","Waterloo"],[10,"Waterloo",38],["Leyton","Waterloo"]]

Output
[null,null,null,null,null,null,null,14.00000,11.00000,null,11.00000,null,12.00000]

Explanation
UndergroundSystem undergroundSystem = new UndergroundSystem();
undergroundSystem.checkIn(45, "Leyton", 3);
undergroundSystem.checkIn(32, "Paradise", 8);
undergroundSystem.checkIn(27, "Leyton", 10);
undergroundSystem.checkOut(45, "Waterloo", 15);  // Customer 45 "Leyton" ->
"Waterloo" in 15-3 = 12
undergroundSystem.checkOut(27, "Waterloo", 20);  // Customer 27 "Leyton" ->
"Waterloo" in 20-10 = 10

undergroundSystem.checkOut(32, "Cambridge", 22); //
Customer 32 "Paradise" -> "Cambridge" in 22-8 = 14
undergroundSystem.getAverageTime("Paradise", "Cambridge"); // return 14.00000.
One trip "Paradise" -> "Cambridge", (14) / 1 = 14

undergroundSystem.getAverageTime("Leyton", "Waterloo");    // return 11.00000.
Two trips "Leyton" -> "Waterloo", (10 + 12) / 2 = 11
undergroundSystem.checkIn(10, "Leyton", 24);

undergroundSystem.getAverageTime("Leyton", "Waterloo");    // return 11.00000
undergroundSystem.checkOut(10, "Waterloo", 38);  // Customer 10 "Leyton" ->
"Waterloo" in 38-24 = 14

undergroundSystem.getAverageTime("Leyton", "Waterloo");
// return 12.00000. Three trips "Leyton" -> "Waterloo", (10 + 12 + 14) / 3 = 12
    */
    Solution2 *rgs = new Solution2();

    rgs->CheckIn(45, "Leyton", 3);
    rgs->CheckIn(32, "Paradise", 8);
    rgs->CheckIn(27, "Leyton", 10);
    rgs->CheckOut(45, "Waterloo", 15);
    rgs->CheckOut(27, "Waterloo", 20);
    rgs->CheckOut(32, "Cambridge", 22);

    double ret = rgs->GetAverageTime("Paradise", "Cambridge");
    EXPECT_EQ(ret, 14.0);
    ret = rgs->GetAverageTime("Leyton", "Waterloo");
    EXPECT_EQ(ret, 11.0);

    rgs->CheckIn(10, "Leyton", 24);

    ret = rgs->GetAverageTime("Leyton", "Waterloo");
    EXPECT_EQ(ret, 11.0);
    rgs->CheckOut(10, "Waterloo", 38);

    ret = rgs->GetAverageTime("Leyton", "Waterloo");
    EXPECT_EQ(ret, 12.0);

    delete rgs;
}

TEST(t0, t2) {
    Solution2 *rgs = new Solution2();

    rgs->CheckIn(10, "Leyton", 3);
    rgs->CheckOut(10, "Paradise", 8);
    // Customer 10 "Leyton" -> "Paradise" in 8-3 = 5

    double ret = rgs->GetAverageTime("Leyton", "Paradise");
    // return 5.00000, (5) / 1 = 5
    EXPECT_EQ(ret, 5.0);
    rgs->CheckIn(5, "Leyton", 10);
    // Customer 5 "Leyton" -> "Paradise" in 16-10 = 6
    rgs->CheckOut(5, "Paradise", 16);
    ret = rgs->GetAverageTime("Leyton", "Paradise");
    // return 5.50000, (5 + 6) / 2 = 5.5
    EXPECT_EQ(ret, 5.5);

    rgs->CheckIn(2, "Leyton", 21);
    rgs->CheckOut(2, "Paradise", 30);
    // Customer 2 "Leyton" -> "Paradise" in 30-21 = 9
    ret = rgs->GetAverageTime("Leyton", "Paradise");
    // return 6.66667, (5 + 6 + 9) / 3 = 6.66667
    EXPECT_NEAR(ret, 6.66667, 0.0001);

    delete rgs;
}

TEST(t0, t3) {
    Solution2 *rgs = new Solution2();

    rgs->CheckIn(1, "Leeds", 3);

    rgs->CheckIn(2, "York", 8);
    rgs->CheckOut(1, "York", 10);
    rgs->CheckOut(2, "Leeds", 15);
    rgs->CheckIn(1, "York", 20);
    rgs->CheckIn(2, "Leeds", 22);
    double ret = rgs->GetAverageTime("Leeds", "York");
    EXPECT_EQ(ret, 7);

    ret = rgs->GetAverageTime("York", "Leeds");
    EXPECT_EQ(ret, 7);

    rgs->CheckOut(1, "Leeds", 24);

    ret = rgs->GetAverageTime("York", "Leeds");
    EXPECT_EQ(ret, 5.5);

    rgs->CheckOut(2, "York", 38);
    ret = rgs->GetAverageTime("Leeds", "York");
    EXPECT_EQ(ret, 11.5);

    // ["UndergroundSystem","checkIn","checkIn","checkOut","checkOut",
    // "checkIn","checkIn","getAverageTime","getAverageTime",
    // "checkOut","getAverageTime","checkOut","getAverageTime"]

    // [[],[1,"Leeds",3],[2,"York",8],[1,"York",10],[2,"Leeds",15],
    // [1,"York",20],[2,"Leeds",22],["Leeds","York"],["York","Leeds"],
    // [1,"Leeds",24],["York","Leeds"],[2,"York",38],["Leeds","York"]]

    delete rgs;
}
}  // namespace
