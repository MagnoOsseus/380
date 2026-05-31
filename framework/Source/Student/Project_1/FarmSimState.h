#pragma once
#include "Misc/NiceTypes.h"
#include <unordered_map>

class BehaviorAgent;

struct FarmSimState
{
    bool wolfAlert = false;
    bool panicActive = false;

    double wolfAlertUntil = 0.0;
    double panicUntil = 0.0;

    std::unordered_map<size_t, Vec3> wanderTargets;
    std::unordered_map<size_t, double> lastEatTimes;
    std::unordered_map<size_t, double> nextEggTimes;
    std::unordered_map<size_t, int> lastCrowDay;
    std::unordered_map<size_t, size_t> wolfTargetChickenByWolf;
    std::unordered_map<size_t, int> lastChopDay;

    Vec3 chickenRoostArea = Vec3(73.0f, 0.0f, 50.0f);
    Vec3 wolfDenArea = Vec3(10.0f, 0.0f, 10.0f);
    Vec3 feedingArea = Vec3(73.0f, 0.0f, 42.0f);
};

namespace FarmSim
{
    constexpr double DayCycleSeconds = 120.0;
    constexpr double NightDurationHours = 10.0;
    constexpr double NightStartHour = 20.0;
    constexpr double NightEndHour = NightStartHour + NightDurationHours;

    FarmSimState &state();

    double now_seconds();
    double hour_of_day();
    bool is_nighttime();
    bool is_daytime();
    int day_index();

    void trigger_panic(double panicDuration = 20.0, double alertDuration = 20.0);
    void clear_alert();
    void clear_wolf_alert_only();
    bool panic_active();
    bool wolf_alert_active();

    Vec3 random_point_near(const Vec3 &origin, float radius);
    Vec3 random_map_point();

    BehaviorAgent *nearest_by_type(const char *type, const Vec3 &from, const BehaviorAgent *ignore = nullptr);
    BehaviorAgent *nearest_chicken(const Vec3 &from, const BehaviorAgent *ignore = nullptr);
    BehaviorAgent *wolf_agent();
    BehaviorAgent *farmer_agent();

    bool has_live_chickens();
    bool is_near(const BehaviorAgent *a, const BehaviorAgent *b, float radius);

    bool is_hungry(size_t agentId, double hungerIntervalSeconds = 18.0);
    void mark_ate(size_t agentId);
    bool any_animal_hungry();

    bool ready_to_lay_egg(size_t agentId);
    void mark_egg_laid(size_t agentId);

    bool rooster_just_became_day(size_t roosterId);
    void mark_rooster_crowed(size_t roosterId);

    void set_wolf_target(size_t wolfId, size_t chickenId);
    bool get_wolf_target(size_t wolfId, size_t &chickenId);
    void clear_wolf_target(size_t wolfId);

    BehaviorAgent *find_chicken_by_id(size_t chickenId);

    bool farmer_can_chop_today(size_t farmerId);
    void mark_farmer_chopped(size_t farmerId);

    Vec3 get_chicken_roost();
    Vec3 get_wolf_den();
    Vec3 get_feeding_area();
}
