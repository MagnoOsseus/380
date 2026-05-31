#include <pch.h>
#include "FarmSimState.h"
#include "Agent/BehaviorAgent.h"

namespace
{
    // Estado global compartido por los nodos del proyecto.
    FarmSimState g_state;

    double now()
    {
        // Tiempo total de simulación en segundos.
        return engine->get_timer().GetTotalSeconds();
    }
}

namespace FarmSim
{
    FarmSimState &state()
    {
        return g_state;
    }

    double hour_of_day()
    {
        const double cycle = fmod(now(), DayCycleSeconds);
        return (cycle / DayCycleSeconds) * 24.0;
    }

    bool is_nighttime()
    {
        const double h = hour_of_day();

        if (NightStartHour <= NightEndHour)
        {
            return (h >= NightStartHour && h < NightEndHour);
        }

        // Este caso cubre noches que cruzan medianoche.
        return (h >= NightStartHour || h < NightEndHour);
    }

    bool is_daytime()
    {
        return (is_nighttime() == false);
    }

    int day_index()
    {
        return static_cast<int>(now() / DayCycleSeconds);
    }

    void trigger_panic(double panicDuration, double alertDuration)
    {
        g_state.panicActive = true;
        g_state.wolfAlert = true;

        g_state.panicUntil = now() + panicDuration;
        g_state.wolfAlertUntil = now() + alertDuration;

        g_state.wolfTargetChickenByWolf.clear();
    }

    void clear_alert()
    {
        g_state.panicActive = false;
        g_state.wolfAlert = false;
        g_state.panicUntil = 0.0;
        g_state.wolfAlertUntil = 0.0;
    }

    void clear_wolf_alert_only()
    {
        g_state.wolfAlert = false;
        g_state.wolfAlertUntil = 0.0;
    }

    bool panic_active()
    {
        if (g_state.panicActive == true && now() >= g_state.panicUntil)
        {
            g_state.panicActive = false;
        }

        return g_state.panicActive;
    }

    bool wolf_alert_active()
    {
        if (g_state.wolfAlert == true && now() >= g_state.wolfAlertUntil)
        {
            g_state.wolfAlert = false;
        }

        return g_state.wolfAlert;
    }

    Vec3 random_point_near(const Vec3 &origin, float radius)
    {
        const float dx = RNG::range(-radius, radius);
        const float dz = RNG::range(-radius, radius);
        return Vec3(origin.x + dx, 0.0f, origin.z + dz);
    }

    Vec3 random_map_point()
    {
        const float maxCoord = terrain->mapSizeInWorld;
        return Vec3(RNG::range(0.0f, maxCoord), 0.0f, RNG::range(0.0f, maxCoord));
    }

    BehaviorAgent *nearest_by_type(const char *type, const Vec3 &from, const BehaviorAgent *ignore)
    {
        const auto &list = agents->get_all_agents_by_type(type);

        BehaviorAgent *best = nullptr;
        float bestDistSq = FLT_MAX;

        // Busca el agente válido más cercano sin usar raíz cuadrada.
        for (auto *base : list)
        {
            auto *candidate = dynamic_cast<BehaviorAgent *>(base);

            if (candidate == nullptr || candidate == ignore)
            {
                continue;
            }

            const auto delta = candidate->get_position() - from;
            const float distSq = delta.LengthSquared();

            if (distSq < bestDistSq)
            {
                bestDistSq = distSq;
                best = candidate;
            }
        }

        return best;
    }

    BehaviorAgent *nearest_chicken(const Vec3 &from, const BehaviorAgent *ignore)
    {
        return nearest_by_type("Chicken", from, ignore);
    }

    BehaviorAgent *wolf_agent()
    {
        const auto &wolves = agents->get_all_agents_by_type("Wolf");

        if (wolves.empty() == true)
        {
            return nullptr;
        }

        return dynamic_cast<BehaviorAgent *>(wolves.front());
    }

    BehaviorAgent *farmer_agent()
    {
        const auto &farmers = agents->get_all_agents_by_type("Farmer");

        if (farmers.empty() == true)
        {
            return nullptr;
        }

        return dynamic_cast<BehaviorAgent *>(farmers.front());
    }

    bool is_near(const BehaviorAgent *a, const BehaviorAgent *b, float radius)
    {
        if (a == nullptr || b == nullptr)
        {
            return false;
        }

        const auto delta = a->get_position() - b->get_position();
        return (delta.LengthSquared() <= (radius * radius));
    }

    bool is_hungry(size_t agentId, double hungerIntervalSeconds)
    {
        const auto it = g_state.lastEatTimes.find(agentId);

        if (it == g_state.lastEatTimes.end())
        {
            return true;
        }

        return (now() - it->second) >= hungerIntervalSeconds;
    }

    void mark_ate(size_t agentId)
    {
        g_state.lastEatTimes[agentId] = now();
    }

    bool any_animal_hungry()
    {
        const auto &chickens = agents->get_all_agents_by_type("Chicken");
        for (auto *base : chickens)
        {
            auto *chicken = dynamic_cast<BehaviorAgent *>(base);
            if (chicken != nullptr && is_hungry(chicken->get_id()))
            {
                return true;
            }
        }

        const auto &roosters = agents->get_all_agents_by_type("Rooster");
        for (auto *base : roosters)
        {
            auto *rooster = dynamic_cast<BehaviorAgent *>(base);
            if (rooster != nullptr && is_hungry(rooster->get_id()))
            {
                return true;
            }
        }

        return false;
    }

    bool ready_to_lay_egg(size_t agentId)
    {
        auto result = g_state.nextEggTimes.find(agentId);

        if (result == g_state.nextEggTimes.end())
        {
            // La primera llamada programa la siguiente puesta.
            g_state.nextEggTimes[agentId] = now() + RNG::range(25.0f, 55.0f);
            return false;
        }

        return now() >= result->second;
    }

    void mark_egg_laid(size_t agentId)
    {
        g_state.nextEggTimes[agentId] = now() + RNG::range(35.0f, 75.0f);
    }

    bool rooster_just_became_day(size_t roosterId)
    {
        if (is_daytime() == false)
        {
            return false;
        }

        const int today = day_index();
        const auto result = g_state.lastCrowDay.find(roosterId);

        if (result == g_state.lastCrowDay.end())
        {
            // Si no hay registro, puede cantar hoy.
            return true;
        }

        return result->second != today;
    }

    void mark_rooster_crowed(size_t roosterId)
    {
        g_state.lastCrowDay[roosterId] = day_index();
    }

    void set_wolf_target(size_t wolfId, size_t chickenId)
    {
        g_state.wolfTargetChickenByWolf[wolfId] = chickenId;
    }

    bool get_wolf_target(size_t wolfId, size_t &chickenId)
    {
        const auto result = g_state.wolfTargetChickenByWolf.find(wolfId);

        if (result == g_state.wolfTargetChickenByWolf.end())
        {
            return false;
        }

        chickenId = result->second;
        return true;
    }

    void clear_wolf_target(size_t wolfId)
    {
        g_state.wolfTargetChickenByWolf.erase(wolfId);
    }

    BehaviorAgent *find_chicken_by_id(size_t chickenId)
    {
        const auto &chickens = agents->get_all_agents_by_type("Chicken");

        for (auto *base : chickens)
        {
            auto *chicken = dynamic_cast<BehaviorAgent *>(base);

            if (chicken != nullptr && chicken->get_id() == chickenId)
            {
                return chicken;
            }
        }

        return nullptr;
    }

    bool farmer_can_chop_today(size_t farmerId)
    {
        const int today = day_index();
        const auto result = g_state.lastChopDay.find(farmerId);

        if (result == g_state.lastChopDay.end())
        {
            return true;
        }

        return result->second != today;
    }

    void mark_farmer_chopped(size_t farmerId)
    {
        g_state.lastChopDay[farmerId] = day_index();
    }

    Vec3 get_chicken_roost()
    {
        return g_state.chickenRoostArea;
    }

    Vec3 get_wolf_den()
    {
        return g_state.wolfDenArea;
    }

    Vec3 get_feeding_area()
    {
        return g_state.feedingArea;
    }

    Vec3 get_water_trough()
    {
        return g_state.waterTroughArea;
    }

    double hours_into_night()
    {
        if (is_nighttime() == false)
        {
            return 0.0;
        }

        const double h = hour_of_day();

        if (h >= NightStartHour)
        {
            return h - NightStartHour;
        }

        // Sigue contando después de medianoche.
        return (24.0 - NightStartHour) + h;
    }

    bool is_night_mature(double hoursDelay)
    {
        return is_nighttime() && hours_into_night() >= hoursDelay;
    }

    bool is_thirsty(size_t agentId, double thirstIntervalSeconds)
    {
        const auto it = g_state.lastDrinkTimes.find(agentId);

        if (it == g_state.lastDrinkTimes.end())
        {
            return true;
        }

        return (now() - it->second) >= thirstIntervalSeconds;
    }

    void mark_drank(size_t agentId)
    {
        g_state.lastDrinkTimes[agentId] = now();
    }
}
