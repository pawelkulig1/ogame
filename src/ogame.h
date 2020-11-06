#ifndef __OGAME__H
#define __OGAME__H
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
    inline constexpr int universe_speed = 1;
    inline constexpr double collector_extraction_bonus = 0.25;
    inline constexpr double collector_energy_bonus = 0.1;
    inline constexpr double geologist_extraction_bonus = 0.1;
    inline constexpr double engineer_energy_bonus = 0.1;
    inline constexpr double crawler_extraction_bonus = 0.02;
	inline constexpr double commanding_staff_energy_bonus = 0.1;
	inline constexpr double commanding_staff_extraction_bonus = 0.02;


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
        METAL_MINE_ID,
        CRYSTAL_MINE_ID,
        DEUTERIUM_SYNTHESIZER_ID,
        SOLAR_PLANT_ID,
        FUSION_REACTOR_ID,
        ROBOTICS_FACTORY_ID,
        NANITE_FACTORY_ID,
        SHIPYARD_ID,
        METAL_STORAGE_ID,
        CRYSTAL_STORAGE_ID,
        DEUTERIUM_TANK_ID,
        RESEARCH_LAB_ID,
        TERRAFORMER_ID,
        ALIANCE_DEPOT_ID,
        SPACE_DOCK_ID,
        MISSLE_SILO_ID,

        ESPIONAGE_TECHNOLOGY_ID,
        COMPUTER_TECHNOLOGY_ID,
        WEAPONS_TECHNOLOGY_ID,
        SHIELDING_TECHNOLOGY_ID,
        ARMOUR_TECHNOLOGY_ID,
        ENERGY_TECHNOLOGY_ID,
        COMBUSTION_DRIVE_ID,
        IMPULSE_DRIVE_ID,
        HYPERSPACE_DRIVE_ID,
        HYPERSPACE_TECHNOLOGY_ID,
        LASER_TECHNOLOGY_ID,
        ION_TECHNOLOGY_ID,
        PLASMA_TECHNOLOGY_ID,
        INTERGALACTIC_RESEARCH_NETWORK_ID,
        ASTROPHYSICS_ID,
        GRAVITON_TECHNOLOGY_ID,

        SOLAR_SATELITE_ID,
        SMALL_CARGO_ID,
        COLONY_SHIP_ID
    };

    enum CONSTRUCTION_QUEUE
    {
        BUILDING,
        TECHNOLOGY,
        SHIPYARD_QUEUE
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


	//BUILDINGS
	const CONSTRUCTION METAL_MINE {CONSTRUCTIONS::METAL_MINE_ID, CONSTRUCTION_QUEUE::BUILDING, 
									1.5, {}, RESOURCES{60, 15, 0, 0}};
	
	const CONSTRUCTION CRYSTAL_MINE {CONSTRUCTIONS::CRYSTAL_MINE_ID, CONSTRUCTION_QUEUE::BUILDING, 
									1.6, {}, RESOURCES{48, 24, 0, 0}};
	
	const CONSTRUCTION DEUTERIUM_SYNTHESIZER {CONSTRUCTIONS::DEUTERIUM_SYNTHESIZER_ID, 
                                    CONSTRUCTION_QUEUE::BUILDING, 
									1.5, {}, RESOURCES{225, 75, 0, 0}};

	const CONSTRUCTION SOLAR_PLANT {CONSTRUCTIONS::SOLAR_PLANT_ID, CONSTRUCTION_QUEUE::BUILDING, 
									1.5, {}, RESOURCES{75, 30, 0, 0}};
	
	const CONSTRUCTION FUSION_REACTOR {CONSTRUCTIONS::FUSION_REACTOR_ID, 
                                    CONSTRUCTION_QUEUE::BUILDING, 
									1.8, {{DEUTERIUM_SYNTHESIZER_ID, 5}, {ENERGY_TECHNOLOGY_ID, 3}}, 
									RESOURCES{900, 360, 180, 0}};

	const CONSTRUCTION ROBOTICS_FACTORY{CONSTRUCTIONS::ROBOTICS_FACTORY_ID, CONSTRUCTION_QUEUE::BUILDING, 
									2.0, {}, RESOURCES{400, 120, 200, 0}};

	const CONSTRUCTION NANITE_FACTORY {CONSTRUCTIONS::NANITE_FACTORY_ID, 
                                      CONSTRUCTION_QUEUE::BUILDING, 
									  2.0, {{ROBOTICS_FACTORY_ID, 10}, {COMPUTER_TECHNOLOGY_ID, 10}},
                                      RESOURCES{1000000, 500000, 100000, 0}};

	const CONSTRUCTION SHIPYARD{CONSTRUCTIONS::SHIPYARD_ID, 
                                CONSTRUCTION_QUEUE::BUILDING, 
								2.0, {{SHIPYARD_ID, 2}}, 
                                RESOURCES{400, 200, 100, 0}};

	const CONSTRUCTION METAL_STORAGE {CONSTRUCTIONS::METAL_STORAGE_ID, 
                                     CONSTRUCTION_QUEUE::BUILDING, 
									 2.0, {}, RESOURCES{1000, 0, 0, 0}};

	const CONSTRUCTION CRYSTAL_STORAGE {CONSTRUCTIONS::CRYSTAL_STORAGE_ID, CONSTRUCTION_QUEUE::BUILDING, 
									2.0, {}, RESOURCES{1000, 500, 0, 0}};

	const CONSTRUCTION DEUTERIUM_TANK {CONSTRUCTIONS::DEUTERIUM_TANK_ID, CONSTRUCTION_QUEUE::BUILDING, 
									2.0, {}, RESOURCES{1000, 1000, 0, 0}};

	const CONSTRUCTION RESEARCH_LAB {CONSTRUCTIONS::RESEARCH_LAB_ID, CONSTRUCTION_QUEUE::BUILDING, 
									2.0, {}, RESOURCES{200, 400, 200, 0}};

	const CONSTRUCTION TERRAFORMER {CONSTRUCTIONS::TERRAFORMER_ID, CONSTRUCTION_QUEUE::BUILDING, 
									2.0, {{NANITE_FACTORY_ID, 10}, {ENERGY_TECHNOLOGY_ID, 12}}, RESOURCES{0, 50000, 100000, 1000}};

	const CONSTRUCTION ALIANCE_DEPOT {CONSTRUCTIONS::ALIANCE_DEPOT_ID, CONSTRUCTION_QUEUE::BUILDING, 
									2.0, {}, RESOURCES{20000, 40000, 0, 0}};

	const CONSTRUCTION SPACE_DOCK {CONSTRUCTIONS::SPACE_DOCK_ID, CONSTRUCTION_QUEUE::BUILDING, 
									2.0, {}, RESOURCES{200, 0, 50, 50}};

	const CONSTRUCTION MISSLE_SILO {CONSTRUCTIONS::MISSLE_SILO_ID, CONSTRUCTION_QUEUE::BUILDING, 
									2.0, {{SHIPYARD_ID, 1}}, RESOURCES{20000, 20000, 1000, 0}};

	//TECHNOLOGIES
	
	const CONSTRUCTION ESPIONAGE_TECHNOLOGY {CONSTRUCTIONS::ESPIONAGE_TECHNOLOGY_ID, 
                                            CONSTRUCTION_QUEUE::TECHNOLOGY, 
									        2.0, {{RESEARCH_LAB_ID, 3}}, 
                                            RESOURCES{200, 1000, 200, 0}};

	const CONSTRUCTION COMPUTER_TECHNOLOGY {CONSTRUCTIONS::COMPUTER_TECHNOLOGY_ID, 
                                            CONSTRUCTION_QUEUE::TECHNOLOGY, 
									        2.0, {{RESEARCH_LAB_ID, 1}}, 
                                            RESOURCES{0, 400, 600, 0}};

	const CONSTRUCTION WEAPONS_TECHNOLOGY {CONSTRUCTIONS::WEAPONS_TECHNOLOGY_ID, 
                                           CONSTRUCTION_QUEUE::TECHNOLOGY, 
									       2.0, {{RESEARCH_LAB_ID, 4}}, 
                                           RESOURCES{800, 200, 0, 0}};

	const CONSTRUCTION ARMOUR_TECHNOLOGY {CONSTRUCTIONS::ARMOUR_TECHNOLOGY_ID, 
                                           CONSTRUCTION_QUEUE::TECHNOLOGY, 
									       2.0, {{RESEARCH_LAB_ID, 2}}, 
                                           RESOURCES{800, 200, 0, 0}};
	
	const CONSTRUCTION SHIELDING_TECHNOLOGY {CONSTRUCTIONS::SHIELDING_TECHNOLOGY_ID, 
                                             CONSTRUCTION_QUEUE::TECHNOLOGY, 
                     						 2.0, {{RESEARCH_LAB_ID, 6}, {ENERGY_TECHNOLOGY_ID, 3}}, 
                                             RESOURCES{200, 600, 0, 0}};

	const CONSTRUCTION ENERGY_TECHNOLOGY{CONSTRUCTIONS::ENERGY_TECHNOLOGY_ID, 
                                          CONSTRUCTION_QUEUE::TECHNOLOGY, 
									      2.0, {{RESEARCH_LAB_ID, 1}}, 
                                          RESOURCES{0, 800, 400, 0}};

	const CONSTRUCTION COMBUSTION_DRIVE {CONSTRUCTIONS::COMBUSTION_DRIVE_ID, 
                                          CONSTRUCTION_QUEUE::TECHNOLOGY, 
									      2.0, {{RESEARCH_LAB_ID, 1}, {ENERGY_TECHNOLOGY_ID, 1}}, 
                                          RESOURCES{400, 0, 600, 0}};

	const CONSTRUCTION IMPULSE_DRIVE {CONSTRUCTIONS::IMPULSE_DRIVE_ID, 
                                          CONSTRUCTION_QUEUE::TECHNOLOGY, 
									      2.0, {{RESEARCH_LAB_ID, 2}, {ENERGY_TECHNOLOGY_ID, 1}}, 
                                          RESOURCES{2000, 4000, 600, 0}};

	const CONSTRUCTION HYPERSPACE_DRIVE {CONSTRUCTIONS::HYPERSPACE_DRIVE_ID, 
                                          CONSTRUCTION_QUEUE::TECHNOLOGY, 
									      2.0, {{RESEARCH_LAB_ID, 7}, {ENERGY_TECHNOLOGY_ID, 3}}, 
                                          RESOURCES{10000, 20000, 6000, 0}};

	const CONSTRUCTION HYPERSPACE_TECHNOLOGY {CONSTRUCTIONS::HYPERSPACE_TECHNOLOGY_ID, 
                                          CONSTRUCTION_QUEUE::TECHNOLOGY, 
									      2.0, {{RESEARCH_LAB_ID, 7}, {ENERGY_TECHNOLOGY_ID, 5}, 
                                               {SHIELDING_TECHNOLOGY_ID, 5}}, 
                                          RESOURCES{0, 4000, 2000, 0}};

	const CONSTRUCTION LASER_TECHNOLOGY {CONSTRUCTIONS::LASER_TECHNOLOGY_ID, 
                                          CONSTRUCTION_QUEUE::TECHNOLOGY, 
									      2.0, {{RESEARCH_LAB_ID, 1}, {ENERGY_TECHNOLOGY_ID, 2}}, 
                                          RESOURCES{200, 100, 0, 0}};

	const CONSTRUCTION ION_TECHNOLOGY {CONSTRUCTIONS::ION_TECHNOLOGY_ID, 
                                          CONSTRUCTION_QUEUE::TECHNOLOGY, 
									      2.0, {{RESEARCH_LAB_ID, 4}, {LASER_TECHNOLOGY_ID, 5}, 
                                               {ENERGY_TECHNOLOGY_ID, 4}}, 
                                          RESOURCES{1000, 300, 100, 0}};

	const CONSTRUCTION PLASMA_TECHNOLOGY {CONSTRUCTIONS::PLASMA_TECHNOLOGY_ID, 
                                          CONSTRUCTION_QUEUE::TECHNOLOGY, 
									      2.0, {{RESEARCH_LAB_ID, 4}, {ENERGY_TECHNOLOGY_ID, 8}, 
                                               {LASER_TECHNOLOGY_ID, 10}, {ION_TECHNOLOGY_ID, 5}}, 
                                          RESOURCES{2000, 4000, 1000, 0}};

	const CONSTRUCTION INTERGALACTIC_RESEARCH_NETWORK {CONSTRUCTIONS::INTERGALACTIC_RESEARCH_NETWORK_ID, 
                                          CONSTRUCTION_QUEUE::TECHNOLOGY, 
									      2.0, {{RESEARCH_LAB_ID, 10}, {COMPUTER_TECHNOLOGY_ID, 8}, 
                                               {HYPERSPACE_TECHNOLOGY_ID, 8}}, 
                                          RESOURCES{240000, 400000, 160000, 0}};

	const CONSTRUCTION ASTROPHYSICS {CONSTRUCTIONS::ASTROPHYSICS_ID, 
                                          CONSTRUCTION_QUEUE::TECHNOLOGY, 
									      1.75, {{RESEARCH_LAB_ID, 3}, {ESPIONAGE_TECHNOLOGY_ID, 4}, 
                                                {IMPULSE_DRIVE_ID, 3}}, 
                                          RESOURCES{4000, 8000, 4000, 0}};


	const CONSTRUCTION GRAVITON_TECHNOLOGY {CONSTRUCTIONS::GRAVITON_TECHNOLOGY_ID, 
                                          CONSTRUCTION_QUEUE::TECHNOLOGY, 
									      2.0, {{RESEARCH_LAB_ID, 12}}, 
                                          RESOURCES{0, 0, 0, 300000}};

	const CONSTRUCTION SOLAR_SATELITE {CONSTRUCTIONS::SOLAR_SATELITE_ID, 
                                          CONSTRUCTION_QUEUE::SHIPYARD_QUEUE, 
									      2.0, {{SHIPYARD_ID, 1}}, 
                                          RESOURCES{0, 2000, 500, 0}};
	
    const CONSTRUCTION COLONY_SHIP {CONSTRUCTIONS::COLONY_SHIP_ID, 
                                          CONSTRUCTION_QUEUE::SHIPYARD_QUEUE, 
									      2.0, {{RESEARCH_LAB_ID, 4}, {IMPULSE_DRIVE_ID, 3}}, 
                                          RESOURCES{10000, 20000, 10000, 0}};

	const CONSTRUCTION SMALL_CARGO {CONSTRUCTIONS::SMALL_CARGO_ID, 
                                          CONSTRUCTION_QUEUE::SHIPYARD_QUEUE, 
									      2.0, {{SHIPYARD_ID, 2}, {COMBUSTION_DRIVE_ID, 2}}, 
                                          RESOURCES{2000, 2000, 0, 0}};
    enum PLAYER_CLASS {
        COLLECTOR,
        GENERAL,
        DISCOVERER
    };

    struct PLAYER_OPTIONS {
        PLAYER_CLASS player_class = PLAYER_CLASS::COLLECTOR;
        int universe_speed{1};
        bool has_engineer{false};
        bool has_geologist{false};
        bool has_technocrat{false};
        bool has_admiral{false};
        bool has_commander{false};
        LVL plasma_technology_lvl{0};
		LVL energetic_technology_lvl{0};
    };

    struct PLANET_OPTIONS {
        int position = 8;
        TEMP max_planet_temperature = 75;
        int number_of_crawlers = 0;
        double m_enchancement = 0.0;
        double c_enchancement = 0.0;
        double d_enchancement = 0.0;
        double e_enchancement = 0.0;
    };

    //MINES
    inline constexpr RES get_metal_extraction(LVL lvl, const PLANET_OPTIONS& planet_options, const PLAYER_OPTIONS& player_options);
    inline constexpr RES get_crystal_extraction(LVL lvl, const PLANET_OPTIONS& planet_options, const PLAYER_OPTIONS& player_options);
    inline constexpr RES get_deuterium_extraction(LVL lvl, const PLANET_OPTIONS& planet_options, const PLAYER_OPTIONS& player_options);
    inline constexpr RES get_energy_consumption(MINE m, LVL lvl);
    inline constexpr int get_max_number_of_crawlers(LVL metal_mine, LVL crystal_mine, LVL deuterium_extractor);
    inline constexpr double position_extraction_bonus(int planet_position);

    //ENERGY
    inline constexpr RES get_solar_plant_production(LVL lvl);
    inline RES get_fusion_reactor_production(LVL lvl, LVL energetic_technology_lvl);
    inline constexpr RES get_solar_satelite_production(LVL lvl, TEMP max_planet_temperature);

    //FUSION
    inline constexpr RES get_fusion_deuterium_consumption(LVL lvl);
    
    //CONSTRUCTION
    inline RES get_construction_cost_m(const CONSTRUCTION& c, LVL lvl);
    inline RES get_construction_cost_c(const CONSTRUCTION& c, LVL lvl);
    inline RES get_construction_cost_d(const CONSTRUCTION& c, LVL lvl);
    inline RES get_construction_cost_e(const CONSTRUCTION& c, LVL lvl);
    inline RESOURCES get_construction_cost(const CONSTRUCTION& c, LVL lvl);

    inline SEC get_building_construction_time(const CONSTRUCTION& c, LVL lvl, LVL robot_factory_lvl, LVL nanite_factory_lvl);
    inline SEC get_technology_construction_time(const CONSTRUCTION& c, LVL lvl, LVL laboratory_lvl);
    inline SEC get_ship_construction_time(const CONSTRUCTION& c, LVL lvl, LVL shipyard_lvl, LVL nanite_factory_lvl);

    //UTILS
    inline consteval std::array<double, max_lvl> generate_lvl_cache()
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
    inline std::map<double, std::map<double, double> > power_cache::cache;
    inline int power_cache::cache_usage = 0;
    inline int power_cache::cache_hit = 0;

    //DEFINITIONS ********************************************************************************
    inline constexpr double position_extraction_bonus_c(int planet_position)
    {
        switch (planet_position) {
            case 1:
                return 0.4;
            case 2:
                return 0.3;
            case 3:
                return 0.2;
            default:
                return 0.0;
        }
    }

    inline constexpr double position_extraction_bonus_m(int planet_position)
    {
        switch (planet_position) {
            case 6:
            case 10:
                return 0.17;
            case 7:
            case 9:
                return 0.23;
            case 8:
                return 0.35;
            default:
                return 0.0;
        }
    }

    inline constexpr int get_max_number_of_crawlers(LVL metal_mine, LVL crystal_mine, LVL deuterium_extractor) {
        return (metal_mine + crystal_mine + deuterium_extractor) * 8;
    }

	inline constexpr bool has_all_commanding_staff(const PLAYER_OPTIONS& player_options)
	{
		return (player_options.has_admiral
			   	&& player_options.has_engineer
				&& player_options.has_commander
			   	&& player_options.has_geologist
			   	&& player_options.has_technocrat);
	}

    inline constexpr RES calculate_additional_extraction(RES mine_extraction, 
												  double enchancement, 
												  const PLANET_OPTIONS& planet_options, 
												  const PLAYER_OPTIONS& player_options)
    {
        const bool is_collector = player_options.player_class == PLAYER_CLASS::COLLECTOR;
        const RES collector_bonus = is_collector * round(mine_extraction * collector_extraction_bonus);
        const RES geologist_bonus = player_options.has_geologist * round(mine_extraction * geologist_extraction_bonus);
        const RES enchancement_bonus = round(mine_extraction * enchancement);
        const RES plasma_bonus = round(mine_extraction * (player_options.plasma_technology_lvl / 100.0));
        const RES crawlers_bonus = round(planet_options.number_of_crawlers * crawler_extraction_bonus * (1.0 + (0.5 * is_collector)));
		const RES commanding_staff_bonus = round(mine_extraction * has_all_commanding_staff(player_options) * commanding_staff_extraction_bonus);

        return collector_bonus + geologist_bonus + enchancement_bonus + plasma_bonus + crawlers_bonus + commanding_staff_bonus;
    }

    inline constexpr RES get_metal_extraction(LVL lvl, const PLANET_OPTIONS& planet_options, 
                                       const PLAYER_OPTIONS& player_options)
    {
        static_assert(lvl_cache[1] != 0);

        constexpr RES default_extraction = 30;
        constexpr RES extraction_multiplier = 30;
        const double position_bonus = position_extraction_bonus_m(planet_options.position);
        const RES planet_extraction = floor(player_options.universe_speed * default_extraction * (1 + position_bonus));
        const RES mine_extraction = floor(player_options.universe_speed * extraction_multiplier * lvl_cache[lvl] * (1 + position_bonus));
                                                   
        RES extraction = floor(planet_extraction + mine_extraction
                         + calculate_additional_extraction(mine_extraction, planet_options.m_enchancement, planet_options, player_options));
        return extraction;
    }

    inline constexpr RES get_crystal_extraction(LVL lvl, const PLANET_OPTIONS& planet_options, const PLAYER_OPTIONS& player_options)
    {
        static_assert(lvl_cache[1] != 0);

        constexpr RES default_extraction = 15;
        constexpr RES extraction_multiplier = 20;
        const double position_bonus = position_extraction_bonus_c(planet_options.position);
        const RES planet_extraction = floor(player_options.universe_speed * default_extraction * (1 + position_bonus));
        const RES mine_extraction = floor(player_options.universe_speed * extraction_multiplier * lvl_cache[lvl] * (1 + position_bonus));

        RES extraction = floor(planet_extraction + mine_extraction
                         + calculate_additional_extraction(mine_extraction, planet_options.c_enchancement, planet_options, player_options));
        return extraction;
    }

    inline constexpr RES get_deuterium_extraction(LVL lvl, const PLANET_OPTIONS& planet_options, const PLAYER_OPTIONS& player_options)
    {
        static_assert(lvl_cache[1] != 0);
        constexpr RES extraction_multiplier = 10;
        const RES mine_extraction = floor(extraction_multiplier * lvl_cache[lvl] * (1.44 - 0.004 * planet_options.max_planet_temperature));

        RES extraction = player_options.universe_speed * floor(mine_extraction
                         + calculate_additional_extraction(mine_extraction, planet_options.d_enchancement, planet_options, player_options));
        return extraction;
    }

    inline constexpr RES get_energy_consumption(MINE m, LVL lvl)
    {
        if (m == MINE::METAL_MINE || m == MINE::CRYSTAL_MINE) return ceil(10 * lvl_cache[lvl]);
        return ceil(20 * lvl_cache[lvl]);
    }

    
    //ENERGY
	
	inline constexpr RES calculate_additional_energy(RES production, const PLANET_OPTIONS& planet_options, const PLAYER_OPTIONS& player_options)
	{
        const bool is_collector = player_options.player_class == PLAYER_CLASS::COLLECTOR;
        const RES collector_bonus = is_collector * round(production * collector_energy_bonus);
        const RES engineer_bonus = player_options.has_engineer * round(production * engineer_energy_bonus);
        const RES enchancement_bonus = round(production * planet_options.e_enchancement);
		const RES commanding_staff_bonus = round(has_all_commanding_staff(player_options) * commanding_staff_energy_bonus);
			
		return collector_bonus + engineer_bonus + enchancement_bonus + commanding_staff_bonus;
	}

    inline constexpr RES get_solar_plant_production(LVL lvl, const PLANET_OPTIONS& planet_options, const PLAYER_OPTIONS& player_options)
    {
        constexpr RES production_multiplier = 20;
        const RES production = floor(production_multiplier * lvl_cache[lvl]);
        const RES extraction = player_options.universe_speed * floor(production
                         + calculate_additional_energy(production, planet_options, player_options));
        return extraction;
    }

    inline RES get_fusion_reactor_production(LVL lvl, const PLANET_OPTIONS& planet_options, const PLAYER_OPTIONS& player_options)
    {
        constexpr RES production_multiplier = 30;
        const RES production = floor(production_multiplier * lvl * power_cache::pow((1.05 + player_options.energetic_technology_lvl * 0.01), lvl));

        const RES extraction = player_options.universe_speed * floor(production
                         + calculate_additional_energy(production, planet_options, player_options));
        return extraction;
    }
    
    inline constexpr RES get_solar_satelite_production(const PLANET_OPTIONS& planet_options, const PLAYER_OPTIONS& player_options)
    {
        const RES production = floor((planet_options.max_planet_temperature + 140.0) / 6.0);

        const RES extraction = player_options.universe_speed * floor(production
                         + calculate_additional_energy(production, planet_options, player_options));
        return extraction;
    }

    //FUSION
    inline constexpr RES get_fusion_deuterium_consumption(LVL lvl)
    {
        return ceil(10 * lvl_cache[lvl]);
    }
    
    //ALL
    //CONSTRUCTION
    inline RES get_construction_cost_m(const CONSTRUCTION& c, LVL lvl)
    {
        return c.default_cost.m * power_cache::pow(c.cost_ratio, lvl - 1);
    }

    inline RES get_construction_cost_c(const CONSTRUCTION& c, LVL lvl)
    {
        return c.default_cost.c * power_cache::pow(c.cost_ratio, lvl - 1);
    }

    inline RES get_construction_cost_d(const CONSTRUCTION& c, LVL lvl)
    {
        return c.default_cost.d * power_cache::pow(c.cost_ratio, lvl - 1);
    }

    inline RES get_construction_cost_e(const CONSTRUCTION& c, LVL lvl)
    {
        return c.default_cost.e * power_cache::pow(c.cost_ratio, lvl - 1);
    }

    inline RESOURCES get_construction_cost(const CONSTRUCTION& c, LVL lvl)
    {
        return RESOURCES{get_construction_cost_m(c, lvl), 
                         get_construction_cost_c(c, lvl), 
                         get_construction_cost_d(c, lvl),
                         get_construction_cost_e(c, lvl)};
    }

    inline SEC get_building_construction_time(const CONSTRUCTION& c, LVL lvl, LVL robot_factory_lvl, LVL nanite_factory_lvl)
    {
        double reduction = 1.0;
        if (c.construction != NANITE_FACTORY_ID)
        {
            reduction = std::max(4 - lvl/2.0, 1.0);
        }

        return floor(3600 * (get_construction_cost_m(c, lvl) + get_construction_cost_c(c, lvl)) / ((2500 * reduction * (robot_factory_lvl + 1)) * power_cache::pow(2, nanite_factory_lvl)));
    }

    inline SEC get_technology_construction_time(const CONSTRUCTION& c, LVL lvl, LVL laboratory_lvl)
    {
        return floor(3600 * (get_construction_cost_m(c, lvl) + get_construction_cost_c(c, lvl)) / (1000 * (laboratory_lvl + 1)));
    }

    inline SEC get_ship_construction_time(const CONSTRUCTION& c, LVL shipyard_lvl, LVL nanite_factory_lvl)
    {
        return floor(3600 * (c.default_cost.m + c.default_cost.c) / ((2500 * (shipyard_lvl + 1)) * power_cache::pow(2, nanite_factory_lvl)));
    }

}

#endif
