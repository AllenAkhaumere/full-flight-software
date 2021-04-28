//
// Created by Srikar on 4/15/2020.
//

#ifndef FLIGHT_VALVECONTROL_HPP
#define FLIGHT_VALVECONTROL_HPP

#include <flight/modules/control_tasks/Control.hpp>
#include <vector>
#include <string>

class ValveControl : public Control {
    private:
        std::vector<std::pair<std::string, std::string>> valves;

        // all time is calculated in milliseconds
        long send_interval;
        long double last_send_time;
        bool aborted;

        void send_valve_data();
        void abort();
        void undo_abort();
        void check_abort();

    public:
        ValveControl();
        void begin() override;
        void execute() override;
};

#endif //FLIGHT_VALVECONTROL_HPP
