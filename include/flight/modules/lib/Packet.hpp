//
// Created by AC on 4/24/2020.
//

#ifndef FLIGHT_PACKET_HPP
#define FLIGHT_PACKET_HPP

#include <string>
#include <vector>
#include <chrono>
#include <flight/modules/lib/Enums.hpp>
#include <flight/modules/lib/Log.hpp>

using namespace std;

class Packet;

void to_json(json& j, const Packet& packet);
void from_json(const json& j, Packet& packet);

// Packet class groups together logs of similar priority
class Packet {
private:
    vector<Log> logs;
    long double timestamp;
    LogPriority priority;

public:
    Packet() = default;

    explicit Packet(LogPriority logPriority, long double timestamp)
        : priority(logPriority),
          timestamp(timestamp){}

    void add(const Log& log);
    vector<Log> getLogs();

    friend void to_json(json& j, const Packet& packet);
    friend void from_json(const json& j, Packet& packet);

    struct compareTo {
        bool operator()(const Packet& lhs, const Packet& rhs) {
            if (lhs.priority != rhs.priority) {
                return lhs.priority < rhs.priority;
            } else {
                return lhs.timestamp < rhs.timestamp;
            }
        }
    };
};

#endif //FLIGHT_PACKET_HPP
