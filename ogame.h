#pragma once
#include <cstdint>
#include <cmath>
#include <array>
#include <vector>
#include <map>

namespace ogame {
    using LVL = uint_fast8_t;
    using RES = uint_fast64_t;
    using SEC = int_fast64_t;
    using REQ = std::vector<std::pair<int, LVL> >;
    using TEMP = int_fast16_t;
    inline constexpr LVL max_lvl = 40;

    enum class MINE {
        METAL_MINE,
        CRYSTAL_MINE,
        DEUTERIUM_EXTRACTOR,
    };

    enum class ENERGY_RESOURCE
    {
        SOLAR_PLANT,
        FUSION_REACTOR,
        SOLAR_SATELITE
    };

    enum CONSTRUCTIONS
    {
        METAL_MINE,
        CRYSTAL_MINE,
        DEUTERIUM_EXTRACTOR,
        SOLAR_PLANT,
        FUSION_REACTOR,
        SOLAR_SATELITE
    };

    enum CONSTRUCTION_QUEUE
    {
        BUILDING,
        TECHNOLOGY,
        SHIPYARD
    };

    struct RESOURCES {
        RES m;
        RES c;
        RES d;
        RES e;
    };

    struct CONSTRUCTION {
        CONSTRUCTIONS construction;
        CONSTRUCTION_QUEUE queue_index;
        double cost_ratio;
        REQ requirements;
        RESOURCES default_cost;
    };

    enum PLAYER_CLASS {
        COLLECTOR,
        GENERAL,
        DISCOVERER
    };

    struct PLAYER_OPTIONS {
        PLAYER_CLASS player_class = PLAYER_CLASS::COLLECTOR;
        int universe_speed = 1;
        bool has_engineer = false;
        bool has_geologist = false;
        bool has_technocrat = false;
        bool has_admiral = false;
        bool has_commander = false;
    };

    enum ENCHANCEMENT {
        M_10,
        M_20,
        M_30,
        M_40,
        C_10,
        C_20,
        C_30,
        C_40,
        D_10,
        D_20,
        D_30,
        D_40
    }

    struct PLANET_OPTIONS {
        int position = 8;
        TEMP max_planet_temperature = 75;
        int number_of_crawlers = 0;
        std::list<ENCHANCEMENT> active_enchancements = {};
    };

    //MINES
    constexpr RES get_metal_extraction(LVL lvl, const PLANET_OPTIONS& planet_options, const PLAYER_OPTIONS& player_options);
    constexpr RES get_crystal_extraction(LVL lvl, const PLANET_OPTIONS& planet_options, const PLAYER_OPTIONS& player_options)
    constexpr RES get_deuterium_extraction(LVL lvl, const PLANET_OPTIONS& planet_options, const PLAYER_OPTIONS& player_options)
    constexpr RES get_energy_consumption(MINE m, LVL lvl);
    
    //ENERGY
    constexpr RES get_solar_plant_production(LVL lvl);
    RES get_fusion_reactor_production(LVL lvl, LVL energetic_technology_lvl);
    constexpr RES get_solar_satelite_production(LVL lvl, TEMP max_planet_temperature);

    //FUSION
    constexpr RES get_fusion_deuterium_consumption(LVL lvl);
    
    //ALL
    //CONSTRUCTION
    RES get_construction_cost_m(const CONSTRUCTION& c, LVL lvl);
    RES get_construction_cost_c(const CONSTRUCTION& c, LVL lvl);
    RES get_construction_cost_d(const CONSTRUCTION& c, LVL lvl);
    RES get_construction_cost_e(const CONSTRUCTION& c, LVL lvl);
    RESOURCES get_construction_cost(const CONSTRUCTION& c, LVL lvl);

    //DOWNGRADE
    //constexpr RES get_destruction_cost_m(const CONSTRUCTION& c, LVL lvl);
    //constexpr RES get_destruction_cost_c(const CONSTRUCTION& c, LVL lvl);
    //constexpr RES get_destruction_cost_d(const CONSTRUCTION& c, LVL lvl);
    //constexpr RESOURCES get_construction_cost(const CONSTRUCTION& c, LVL lvl);

    SEC get_building_construction_time(const CONSTRUCTION& c, LVL lvl, LVL robot_factory_lvl, LVL nanite_factory_lvl);
    SEC get_technology_construction_time(const CONSTRUCTION& c, LVL lvl, LVL laboratory_lvl);
    SEC get_ship_construction_time(const CONSTRUCTION& c, LVL lvl, LVL shipyard_lvl, LVL nanite_factory_lvl);

    //UTILS
    consteval std::array<double, max_lvl> generate_lvl_cache()
    {
        std::array<double, max_lvl> cache;
        for (int lvl=0; lvl<max_lvl; lvl++) {
            cache[lvl] = lvl * pow(1.1, lvl);
        }
        return cache;
    }
    inline constexpr std::array<double, max_lvl> lvl_cache = generate_lvl_cache();


    // 0.5, (0 - 40)
    // (1.05 + energetic_technology_lvl * 0.01), lvl, en(0-40), lvl (0-40)
    // cost_ratio, lvl cost_ratio(1.5, 1.6, 1.75, 1.8, 2, 3)

    class power_cache {
        static std::map<double, std::map<double, double> > cache;
        static int cache_hit;
        static int cache_usage;
    public:
        static double pow(double base, double exp)
        {
            ++cache_usage;
            const auto it_base = cache.find(base);
            if (it_base != cache.end())
            {
                auto it_out = it_base->second.find(exp);
                if (it_out != it_base->second.end())
                {
                    ++cache_hit;
                    return it_out->second;
                }
            }
            const double temp = ::pow(base, exp);
            cache[base][exp] = temp;
            return temp; 
        }

        static double get_cache_ratio()
        {
            return cache_hit/(cache_usage*1.0);
        }

    };
    std::map<double, std::map<double, double> > power_cache::cache;
    int power_cache::cache_usage = 0;
    int power_cache::cache_hit = 0;

    //DEFINITIONS ********************************************************************************

    constexpr RES get_metal_extraction(LVL lvl, const PLANET_OPTIONS& planet_options, const PLAYER_OPTIONS& player_options);
    {
        static_assert(lvl_cache[1] != 0);
        return floor(30 * lvl_cache[lvl] + 30);
    }

    constexpr RES get_crystal_extraction(LVL lvl, const PLANET_OPTIONS& planet_options, const PLAYER_OPTIONS& player_options)
    {
        static_assert(lvl_cache[1] != 0);
        return floor(20 * lvl_cache[lvl] + 15);
    }

    constexpr RES get_deuterium_extraction(LVL lvl, const PLANET_OPTIONS& planet_options, const PLAYER_OPTIONS& player_options)
    {
        static_assert(lvl_cache[1] != 0);
        return floor(10 * lvl_cache[lvl] * 1.44 - 0.004 * max_planet_temperature);
    }

    constexpr RES get_energy_consumption(MINE m, LVL lvl)
    {
        if (m == MINE::METAL_MINE || m == MINE::CRYSTAL_MINE) return ceil(10 * lvl_cache[lvl]);
        return ceil(20 * lvl_cache[lvl]);
    }

    
    //ENERGY
    constexpr RES get_solar_plant_production(LVL lvl)
    {
        return floor(20 * lvl_cache[lvl]);
    }

    RES get_fusion_reactor_production(LVL lvl, LVL energetic_technology_lvl)
    {
        return floor(30 * lvl * power_cache::pow((1.05 + energetic_technology_lvl * 0.01), lvl));
    }
    
    constexpr RES get_solar_satelite_production(LVL lvl, TEMP max_planet_temperature)
    {
        return floor((max_planet_temperature + 140) / 6);
    }

    //FUSION
    constexpr RES get_fusion_deuterium_consumption(LVL lvl)
    {
        return ceil(10 * lvl_cache[lvl]);
    }
    
    //ALL
    //CONSTRUCTION
    RES get_construction_cost_m(const CONSTRUCTION& c, LVL lvl)
    {
        return c.default_cost.m * power_cache::pow(c.cost_ratio, lvl - 1);
    }

    RES get_construction_cost_c(const CONSTRUCTION& c, LVL lvl)
    {
        return c.default_cost.c * power_cache::pow(c.cost_ratio, lvl - 1);
    }

    RES get_construction_cost_d(const CONSTRUCTION& c, LVL lvl)
    {
        return c.default_cost.d * power_cache::pow(c.cost_ratio, lvl - 1);
    }

    RES get_construction_cost_e(const CONSTRUCTION& c, LVL lvl)
    {
        return c.default_cost.e * power_cache::pow(c.cost_ratio, lvl - 1);
    }

    RESOURCES get_construction_cost(const CONSTRUCTION& c, LVL lvl)
    {
        return RESOURCES{get_construction_cost_m(c, lvl), 
                         get_construction_cost_c(c, lvl), 
                         get_construction_cost_d(c, lvl),
                         get_construction_cost_e(c, lvl)};
    }

    //DOWNGRADE
   // constexpr RES get_destruction_cost_m(const CONSTRUCTION& c, LVL lvl)
   // {
   //             
   // }

   // constexpr RES get_destruction_cost_c(const CONSTRUCTION& c, LVL lvl);
   // constexpr RES get_destruction_cost_d(const CONSTRUCTION& c, LVL lvl);
   // constexpr RESOURCES get_construction_cost(const CONSTRUCTION& c, LVL lvl);

    SEC get_building_construction_time(const CONSTRUCTION& c, LVL lvl, LVL robot_factory_lvl, LVL nanite_factory_lvl)
    {
        return floor(3600 * (get_construction_cost_m(c, lvl) + get_construction_cost_c(c, lvl)) / (2500 * (robot_factory_lvl + 1)) * power_cache::pow(0.5, nanite_factory_lvl));
    }

    SEC get_technology_construction_time(const CONSTRUCTION& c, LVL lvl, LVL laboratory_lvl)
    {
        return floor(3600 * (get_construction_cost_m(c, lvl) + get_construction_cost_c(c, lvl)) / 1000 * (laboratory_lvl + 1));
    }

    SEC get_ship_construction_time(const CONSTRUCTION& c, LVL lvl, LVL shipyard_lvl, LVL nanite_factory_lvl)
    {
        return floor(3600 * (get_construction_cost_m(c, lvl) + get_construction_cost_c(c, lvl)) / (2500 * (shipyard_lvl + 1)) * power_cache::pow(0.5, nanite_factory_lvl));
    }

}
