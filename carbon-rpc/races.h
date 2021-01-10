#pragma once
#include <map>
#include <string>

std::map<std::string, const char*> CIRCUIT_MAP = {
	{ "STEYNE AQUEDUCT", "map_cc_rw_steyne_aqueduct" },
	{ "BEACHFRONT", "map_cc_beachfront" },
	{ "KEMPTON DOCKS", "map_br_cc_kempton_docks" },
	{ "DOVER STREET", "map_cc_dover_street" },
	{ "BROOKS STREET", "map_cc_brooks_street" },
	{ "NORTH BROADWAY", "map_cc_north_broadway" },
	{ "SAVANNAH STREET", "map_cc_savannah_street" },
	{ "PARADISE HOTEL", "map_cc_paradise_hotel" },
	{ "UNIVERSITY WAY", "map_cc_university_way" },
	{ "LIBRARY SQUARE", "map_cc_rw_library_square" },
	{ "SKYLINE AVENUE", "map_br_cc_skyline_avenue" },
	{ "OCEAN VIEW", "map_cc_ocean_view" },
	{ "CONDO ROW", "map_cc_condo_row" },
	{ "MAIN STREET", "map_cc_main_street" },
	{ "SUTHERDEN BELL TOWER", "map_cc_rw_sutherden_bell_tower" },
	{ "SILK ROAD", "map_cc_silk_road" },
	{ "NORTH ROAD", "map_br_cc_north_road" },
	{ "GARDEN BOULEVARD", "map_cc_garden_boulevard" },
	{ "SALAZAR STREET", "map_cc_salazar_street" },
	{ "ROYAL AVENUE", "map_cc_royal_avenue" },
	{ "SOUTH FORTUNA", "map_cc_south_fortuna" },
	{ "LUCKY TOWERS", "map_cc_lucky_towers" },
	{ "CAMPBELL TUNNEL", "map_cc_campbell_tunnel" },
	{ "ROBINSON BAY", "map_cc_robinson_bay" }
};

std::map<std::string, const char*> SPRINT_MAP = {
	{ "DOVER AND LEPUS", "map_sp_dover_and_lepus" },
	{ "PETERSBURG DAM", "map_sp_petersburg_dam" },
	{ "MISSION STREET", "map_sp_mission_street" },
	{ "WATERFRONT ROAD", "map_sp_waterfront_road" },
	{ "DESPERATION RIDGE", "map_sp_desperation_ridge" },
	{ "SILVERTON WAY", "map_sp_silverton_way" },
	{ "DEADFALL JUNCTION", "map_cn_dt_sp_deadfall_junction" },
	{ "STARLIGHT STREET", "map_sp_starlight_street" },
	{ "EAGLE DRIVE", "map_sp_eagle_drive" },
	{ "SPADE STREET", "map_sp_spade_street" },
	{ "VERONA TUNNEL", "map_sp_verona_tunnel" },
	{ "YORK ROAD", "map_sp_york_road" },
	{ "AGOSTINI AVENUE", "map_sp_agostini_avenue" },
	{ "NORTH BELLEZZA", "map_sp_north_bellezza" },
	{ "LOFTHY HEIGHTS DOWNHILL", "map_sp_lofthy_heights_downhill" },
	{ "LINCOLN BOULEVARD", "map_sp_lincoln_boulevard" },
	{ "CHINATOWN TRAM", "map_sp_chinatown_tram" },
	{ "GOLD VALLEY RUN", "map_cn_sp_gold_valley_run" },
	{ "DEVIL'S CREEK PASS", "map_sp_devils_creek_pass" },
	{ "MASON STREET", "map_sp_mason_street" },
	{ "COPPER RIDGE", "map_sp_copper_ridge" },
	{ "MASON ST BRIDGE", "map_sp_mason_st_bridge" },
	{ "FRANCIS TUNNEL", "map_sp_francis_tunnel" },
	{ "ETERNITY PASS", "map_sp_eternity_pass" },
	{ "JOURNEYMAN'S BANE", "map_sp_journeymans_bane" },
	{ "KNIFE'S EDGE", "map_sp_knifes_edge" },
	{ "MESA BRIDGE", "map_sp_mesa_bridge" },
	{ "BLACKWELL BRIDGE", "map_sp_blackwell_bridge" },
	{ "LOOKOUT POINT", "map_dt_sp_lookout_point" }
};

std::map<std::string, const char*> CHECKPOINT_MAP = {
	{ "MORGAN BEACH OFFRAMP", "map_cp_morgan_beach_offramp" },
	{ "ESKURI PLAZA", "map_cp_eskuri_plaza" },
	{ "BLACKWALL ROAD", "map_cp_blackwall_road" },
	{ "THE NEON MILE", "map_cp_the_neon_mile" },
	{ "TROY", "map_cp_troy" },
	{ "GRAY STREET", "map_cp_gray_street" },
	{ "UNIVERSITY AVENUE", "map_cp_university_avenue" },
	{ "RABINOWITZ DRIVE", "map_cp_rabinowitz_drive" },
	{ "HILLS BOROUGH PARKWAY", "map_cp_hills_borough_parkway" },
	{ "KNIGHT STREET", "map_cp_knight_street" }
};

std::map<std::string, const char*> SPEEDTRAP_MAP = {
	{ "ESKURI WAY", "map_st_eskuri_way" },
	{ "STONEWALL TUNNEL", "map_st_stonewall_tunnel" },
	{ "NEWPORT TRAINYARD", "map_st_newport_trainyard" },
	{ "FOUNDRY ROAD", "map_st_foundry_road" },
	{ "CANMOR ROAD", "map_st_canmor_road" },
	{ "OLYMPIC BOULEVARD", "map_st_olympic_boulevard" },
	{ "BOWEN AVENUE", "map_st_bowen_avenue" },
	{ "MILLION DOLLAR DRIVE", "map_st_million_dollar_drive" },
	{ "PARK DRIVE", "map_st_park_drive" },
	{ "MASON FOUNTAIN", "map_st_mason_fountain" }
}; 

std::map<std::string, const char*> DRIFT_MAP = {
	{ "KNIFE'S EDGE", "map_cn_dt_knifes_edge" },
	{ "DEVIL'S CREAK PASS", "map_dt_devils_creak_pass" },
	{ "JOURNEYMAN'S BANE", "map_dt_journeymans_bane" },
	{ "CITY COURTHOUSE", "map_dt_city_courthouse" },
	{ "LOFTY HEIGHTS DOWNHILL", "map_dt_lofty_heights_downhill" },
	{ "KIMEI TEMPLE", "map_dt_kimei_temple" },
	{ "KINGS PARK", "map_dt_kings_park" },
	{ "LOOKOUT POINT", "map_dt_lookout_point" },
	{ "STARLIGHT STRIP", "map_dt_starlight_strip" },
	{ "OLD QUARTER", "map_dt_old_quarter" },
	{ "GOLD VALLEY RUN", "map_dt_gold_valley_run" },
	{ "NEWPORT IRONWORKS", "map_dt_newport_ironworks" },
	{ "FORTUNA HEIGHTS", "map_dt_fortuna_heights" },
	{ "PALMONT UNIVERSITY", "map_dt_palmont_university" },
	{ "BILLINGS DISTRICT", "map_dt_billings_district" },
	{ "DESPERATION RIDGE", "map_dt_desperation_ridge" },
	{ "PARK DRIVE DRIFT", "map_dt_park_drive_drift" },
	{ "DEADFALL JUNCTION", "map_cn_dt_sp_deadfall_junction" },
	{ "SHADY PINE", "map_dt_shady_pine" },
	{ "COPPER RIDGE", "map_cn_dt_copper_ridge" },
	{ "MAIN STREET DRIFT", "map_dt_main_street_drift" },
	{ "ETERNITY PASS", "map_cn_dt_eternity_pass" }
};

std::map<std::string, const char*> CANYON_MAP = {
	{ "DEADFALL JUNCTION", "map_cn_dt_sp_deadfall_junction" },
	{ "DESPERATION RIDGE", "map_cn_desperation_ridge" },
	{ "JOURNEYMAN'S BANE", "map_cn_journeymans_bane" },
	{ "COPPER RIDGE", "map_cn_dt_copper_ridge" },
	{ "GOLD VALLEY RUN", "map_cn_sp_gold_valley_run" },
	{ "KNIFE'S EDGE", "map_cn_dt_knifes_edge" },
	{ "DEVIL'S CREEK PASS", "map_cn_devils_creek_pass" },
	{ "ETERNITY PASS", "map_cn_dt_eternity_pass" },
	{ "LOOKOUT POINT", "map_cn_lookout_point" },
	{ "LOFTY HEIGHTS DOWNHILL", "map_cn_lofty_heights_downhill" }
};

std::map<std::string, const char*> TAG_MAP = {
	{ "FORTUNA", "map_pt_fortuna" },
	{ "KEMPTON", "map_pt_kempton" },
	{ "DOWNTOWN", "map_pt_downtown" },
	{ "SAN JUAN", "map_pt_san_juan" },
	{ "SILVERTON", "map_pt_silverton" }
};

std::map<std::string, const char*> KNOCKOUT_MAP = {
	{ "FORTUNA", "map_pk_fortuna" },
	{ "KEMPTON", "map_pk_kempton" },
	{ "DOWNTOWN", "map_pt_downtown_silverton" },
	{ "SAN JUAN", "map_pk_san_juan" },
	{ "SILVERTON", "map_pt_downtown_silverton" }
};