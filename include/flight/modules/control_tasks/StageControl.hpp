#ifndef FLIGHT_STAGECONTROL_HPP
#define FLIGHT_STAGECONTROL_HPP

#include <flight/modules/control_tasks/Control.hpp>
#include <flight/modules/lib/Enums.hpp>
#include <flight/modules/lib/Errors.hpp>
#include <flight/modules/mcl/Config.hpp>
#include <vector>

class StageControl : public Control {
private:
    long send_time = 0;
    long start_time = 0;
    long request_time = 0;
    long request_interval = 10000;
    long send_interval;
    int stage_index;
    double status;
    Stage curr_stage;
    bool acutated_postburn;

    vector<Stage> stage_names {
        Stage::WAITING,
        Stage::PRESSURIZATION,
        Stage::AUTOSEQUENCE,
        Stage::POSTBURN
    };

    vector<string> stage_strings = global_config.stages.list;

    const double AUTOSEQUENCE_DELAY = 5.0 * 1000;
    const double POSTBURN_DELAY = 10.0 * 1000;

    double calculate_status() const;
    void send_progression_request();
    void send_data();
    void progress();
    void stage_valve_control();

public:
    StageControl();
    void begin() override;
    void execute() override;
};

#endif //FLIGHT_STAGECONTROL_HPP
