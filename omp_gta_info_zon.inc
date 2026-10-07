#if defined _omp_gta_info_zon_included
    #endinput
#endif
#define _omp_gta_info_zon_included

#include <omp_gta_popcycle>
#include <omp_gta_map_zon>

#define GTA_INFO_ZON_FILE "info.zon"
#define GTA_INFO_ZON_MAX_ZONES (400)
#define GTA_INFO_ZON_NAME_LENGTH (16)
#define GTA_INFO_ZON_PARENT_LENGTH (16)
#define GTA_INFO_ZON_MAX_LINE_LENGTH (256)

enum E_GTA_INFO_ZON_TYPE {
    GTA_INFO_ZON_TYPE_INVALID = -1,
    GTA_INFO_ZON_TYPE_NAVI = 0,
    GTA_INFO_ZON_TYPE_LOCAL_NAVI,
    GTA_INFO_ZON_TYPE_INFO,
    GTA_INFO_ZON_TYPE_MAP
};

enum E_GTA_INFO_ZON_RACE_ASSIGNMENT {
    GTA_INFO_ZON_RACE_ASSIGNMENT_NAME[GTA_INFO_ZON_NAME_LENGTH],
    E_GTA_POPCYCLE_RACES:GTA_INFO_ZON_RACE_ASSIGNMENT_RACE
};

enum E_GTA_INFO_ZON_DEALER_ASSIGNMENT {
    GTA_INFO_ZON_DEALER_ASSIGNMENT_NAME[GTA_INFO_ZON_NAME_LENGTH],
    GTA_INFO_ZON_DEALER_ASSIGNMENT_STRENGTH
};

enum E_GTA_INFO_ZON_NO_COPS_ASSIGNMENT {
    GTA_INFO_ZON_NO_COPS_ASSIGNMENT_NAME[GTA_INFO_ZON_NAME_LENGTH],
    bool:GTA_INFO_ZON_NO_COPS_ASSIGNMENT_NO_COPS
};

enum E_GTA_INFO_ZON_GANG_ASSIGNMENT {
    GTA_INFO_ZON_GANG_ASSIGNMENT_NAME[GTA_INFO_ZON_NAME_LENGTH],
    E_GTA_POPCYCLE_GANG:GTA_INFO_ZON_GANG_ASSIGNMENT_GANG,
    GTA_INFO_ZON_GANG_ASSIGNMENT_STRENGTH
};

enum E_GTA_INFO_ZON_DATA {
    GTA_INFO_ZON_NAME[GTA_INFO_ZON_NAME_LENGTH],
    E_GTA_INFO_ZON_TYPE:GTA_INFO_ZON_TYPE,
    Float:GTA_INFO_ZON_MIN_X,
    Float:GTA_INFO_ZON_MIN_Y,
    Float:GTA_INFO_ZON_MIN_Z,
    Float:GTA_INFO_ZON_MAX_X,
    Float:GTA_INFO_ZON_MAX_Y,
    Float:GTA_INFO_ZON_MAX_Z,
    E_GTA_MAPZON_LEVEL:GTA_INFO_ZON_LEVEL,
    GTA_INFO_ZON_PARENT[GTA_INFO_ZON_PARENT_LENGTH],
    E_GTA_POPCYCLE_TYPE:GTA_INFO_ZON_POPULATION_TYPE,
    E_GTA_POPCYCLE_RACES:GTA_INFO_ZON_POPULATION_RACE,
    GTA_INFO_ZON_DEALER_STRENGTH,
    bool:GTA_INFO_ZON_NO_COPS,
    GTA_INFO_ZON_GANG_STRENGTH[GTA_POPCYCLE_GANG_COUNT]
};

enum E_GTA_INFO_ZON_POPTYPE_ASSIGNMENT {
    GTA_INFO_ZON_POPTYPE_ASSIGNMENT_NAME[GTA_INFO_ZON_NAME_LENGTH],
    E_GTA_POPCYCLE_TYPE:GTA_INFO_ZON_POPTYPE_ASSIGNMENT_TYPE
};

static gInfoZonZones[GTA_INFO_ZON_MAX_ZONES][E_GTA_INFO_ZON_DATA];
static gInfoZonZoneCount;
static bool:gInfoZonLoaded;

/*
* Recreated from:
* https://gist.github.com/JuniorDjjr/2129e1e7640f7969acdfb1c56c263155
*/
static const gInfoZonPopTypeAssignments[][E_GTA_INFO_ZON_POPTYPE_ASSIGNMENT] = {
    // Los Santos
    { "MARKST",  GTA_POPCYCLE_TYPE_SHOPPING_POSH },
    { "UNITY",   GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "LAIR1",   GTA_POPCYCLE_TYPE_AIRPORT },
    { "LAIR2a",  GTA_POPCYCLE_TYPE_AIRPORT },
    { "LAIR2b",  GTA_POPCYCLE_TYPE_AIRPORT },
    { "LBAG1",   GTA_POPCYCLE_TYPE_AIRPORT_RUNWAY },
    { "LBAG2",   GTA_POPCYCLE_TYPE_AIRPORT_RUNWAY },
    { "LBAG3",   GTA_POPCYCLE_TYPE_AIRPORT_RUNWAY },
    { "BLUF1a",  GTA_POPCYCLE_TYPE_PARK },
    { "BLUF2",   GTA_POPCYCLE_TYPE_PARK },
    { "SUN1",    GTA_POPCYCLE_TYPE_ENTERTAINMENT },
    { "SUN3a",   GTA_POPCYCLE_TYPE_ENTERTAINMENT },
    { "SUN3b",   GTA_POPCYCLE_TYPE_ENTERTAINMENT },
    { "SUN3c",   GTA_POPCYCLE_TYPE_ENTERTAINMENT },
    { "SUN4",    GTA_POPCYCLE_TYPE_ENTERTAINMENT },
    { "COM1a",   GTA_POPCYCLE_TYPE_SHOPPING },
    { "COM1b",   GTA_POPCYCLE_TYPE_SHOPPING },
    { "COM2",    GTA_POPCYCLE_TYPE_SHOPPING },
    { "COM3",    GTA_POPCYCLE_TYPE_SHOPPING },
    { "COM4",    GTA_POPCYCLE_TYPE_SHOPPING },
    { "PER1",    GTA_POPCYCLE_TYPE_SHOPPING },
    { "CHC1a",   GTA_POPCYCLE_TYPE_RESIDENTIAL_POOR },
    { "CHC1b",   GTA_POPCYCLE_TYPE_RESIDENTIAL_POOR },
    { "CHC2a",   GTA_POPCYCLE_TYPE_RESIDENTIAL_POOR },
    { "CHC2b",   GTA_POPCYCLE_TYPE_RESIDENTIAL_POOR },
    { "CHC3",    GTA_POPCYCLE_TYPE_GANGLAND },
    { "CHC4a",   GTA_POPCYCLE_TYPE_GANGLAND },
    { "CHC4b",   GTA_POPCYCLE_TYPE_GANGLAND },
    { "CONF1a",  GTA_POPCYCLE_TYPE_BUSINESS },
    { "CONF1b",  GTA_POPCYCLE_TYPE_BUSINESS },
    { "THALL1",  GTA_POPCYCLE_TYPE_BUSINESS },
    { "LDOC1a",  GTA_POPCYCLE_TYPE_INDUSTRY },
    { "LDOC1b",  GTA_POPCYCLE_TYPE_INDUSTRY },
    { "LDOC2",   GTA_POPCYCLE_TYPE_INDUSTRY },
    { "LDOC3a",  GTA_POPCYCLE_TYPE_INDUSTRY },
    { "LDOC3b",  GTA_POPCYCLE_TYPE_INDUSTRY },
    { "LDOC3c",  GTA_POPCYCLE_TYPE_INDUSTRY },
    { "LDOC4",   GTA_POPCYCLE_TYPE_INDUSTRY },
    { "LDT1a",   GTA_POPCYCLE_TYPE_BUSINESS },
    { "LDT1b",   GTA_POPCYCLE_TYPE_BUSINESS },
    { "LDT1c",   GTA_POPCYCLE_TYPE_BUSINESS },
    { "LDT3",    GTA_POPCYCLE_TYPE_BUSINESS },
    { "LDT4",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "LDT5",    GTA_POPCYCLE_TYPE_BUSINESS },
    { "LDT6",    GTA_POPCYCLE_TYPE_BUSINESS },
    { "LDT7",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "EBE1",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "EBE2a",   GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "EBE2b",   GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "EBE3c",   GTA_POPCYCLE_TYPE_BEACH },
    { "ELCO1",   GTA_POPCYCLE_TYPE_RESIDENTIAL_POOR },
    { "ELCO2",   GTA_POPCYCLE_TYPE_GANGLAND },
    { "GAN1",    GTA_POPCYCLE_TYPE_GANGLAND },
    { "GAN2",    GTA_POPCYCLE_TYPE_GANGLAND },
    { "GLN1",    GTA_POPCYCLE_TYPE_GANGLAND },
    { "GLN2a",   GTA_POPCYCLE_TYPE_GANGLAND },
    { "LIND1a",  GTA_POPCYCLE_TYPE_GANGLAND },
    { "LIND1b",  GTA_POPCYCLE_TYPE_INDUSTRY },
    { "LIND2a",  GTA_POPCYCLE_TYPE_INDUSTRY },
    { "LIND2b",  GTA_POPCYCLE_TYPE_INDUSTRY },
    { "LIND3",   GTA_POPCYCLE_TYPE_INDUSTRY },
    { "IWD1",    GTA_POPCYCLE_TYPE_GANGLAND },
    { "IWD2",    GTA_POPCYCLE_TYPE_GANGLAND },
    { "IWD3a",   GTA_POPCYCLE_TYPE_GANGLAND },
    { "IWD3b",   GTA_POPCYCLE_TYPE_GANGLAND },
    { "IWD4",    GTA_POPCYCLE_TYPE_GANGLAND },
    { "IWD5",    GTA_POPCYCLE_TYPE_GANGLAND },
    { "JEF1a",   GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JEF1b",   GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JEF2",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JEF3a",   GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JEF3b",   GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JEF3c",   GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "LFL1a",   GTA_POPCYCLE_TYPE_GANGLAND },
    { "LFL1b",   GTA_POPCYCLE_TYPE_GANGLAND },
    { "LMEX1a",  GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "LMEX1b",  GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "ELS1a",   GTA_POPCYCLE_TYPE_GANGLAND },
    { "ELS1b",   GTA_POPCYCLE_TYPE_GANGLAND },
    { "ELS2",    GTA_POPCYCLE_TYPE_GANGLAND },
    { "ELS3a",   GTA_POPCYCLE_TYPE_GANGLAND },
    { "ELS3b",   GTA_POPCYCLE_TYPE_GANGLAND },
    { "ELS4",    GTA_POPCYCLE_TYPE_GANGLAND },
    { "MAR1",    GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "MAR2",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "MAR3",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "MKT1",    GTA_POPCYCLE_TYPE_SHOPPING_POSH },
    { "MKT2",    GTA_POPCYCLE_TYPE_SHOPPING_POSH },
    { "MKT3",    GTA_POPCYCLE_TYPE_SHOPPING_POSH },
    { "MKT4",    GTA_POPCYCLE_TYPE_SHOPPING_POSH },
    { "MUL1a",   GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH_SECLUDED },
    { "MUL1b",   GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH_SECLUDED },
    { "MUL1c",   GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH_SECLUDED },
    { "MUL2a",   GTA_POPCYCLE_TYPE_PARK },
    { "MUL2b",   GTA_POPCYCLE_TYPE_PARK },
    { "MUL3",    GTA_POPCYCLE_TYPE_PARK },
    { "MUL4",    GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH_SECLUDED },
    { "MUL5a",   GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH_SECLUDED },
    { "MUL5b",   GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH_SECLUDED },
    { "MUL5c",   GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH_SECLUDED },
    { "MUL6",    GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH_SECLUDED },
    { "MUL7a",   GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH_SECLUDED },
    { "MUL7b",   GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH_SECLUDED },
    { "PLS",     GTA_POPCYCLE_TYPE_BEACH },
    { "RIH1a",   GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH_SECLUDED },
    { "RIH1b",   GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH_SECLUDED },
    { "RIH2",    GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH_SECLUDED },
    { "RIH3a",   GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH_SECLUDED },
    { "RIH3b",   GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH_SECLUDED },
    { "RIH4",    GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "RIH5a",   GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "RIH6b",   GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "ROD1a",   GTA_POPCYCLE_TYPE_SHOPPING_POSH },
    { "ROD1b",   GTA_POPCYCLE_TYPE_SHOPPING_POSH },
    { "ROD1c",   GTA_POPCYCLE_TYPE_SHOPPING_POSH },
    { "ROD2a",   GTA_POPCYCLE_TYPE_SHOPPING_POSH },
    { "ROD2b",   GTA_POPCYCLE_TYPE_SHOPPING_POSH },
    { "ROD3a",   GTA_POPCYCLE_TYPE_SHOPPING_POSH },
    { "ROD3b",   GTA_POPCYCLE_TYPE_SHOPPING_POSH },
    { "ROD4a",   GTA_POPCYCLE_TYPE_SHOPPING_POSH },
    { "ROD4b",   GTA_POPCYCLE_TYPE_SHOPPING_POSH },
    { "ROD4c",   GTA_POPCYCLE_TYPE_SHOPPING_POSH },
    { "ROD5a",   GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "ROD5b",   GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "SMB1",    GTA_POPCYCLE_TYPE_BEACH },
    { "SMB2",    GTA_POPCYCLE_TYPE_BEACH },
    { "VIN2",    GTA_POPCYCLE_TYPE_ENTERTAINMENT },
    { "VIN3",    GTA_POPCYCLE_TYPE_ENTERTAINMENT },
    { "VIN1a",   GTA_POPCYCLE_TYPE_ENTERTAINMENT },
    { "VIN1b",   GTA_POPCYCLE_TYPE_ENTERTAINMENT },
    { "VERO1",   GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "VERO2",   GTA_POPCYCLE_TYPE_SHOPPING },
    { "VERO3",   GTA_POPCYCLE_TYPE_SHOPPING },
    { "VERO4a",  GTA_POPCYCLE_TYPE_BEACH },
    { "VERO4b",  GTA_POPCYCLE_TYPE_BEACH },
    { "CRANB",   GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "CALT",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "SUNMA",   GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "SUNNN",   GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "BATTP",   GTA_POPCYCLE_TYPE_ENTERTAINMENT },
    { "ESPN1",   GTA_POPCYCLE_TYPE_SHOPPING },
    { "ESPN2",   GTA_POPCYCLE_TYPE_SHOPPING },
    { "ESPN3",   GTA_POPCYCLE_TYPE_SHOPPING },
    { "BAYV",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "PARA",    GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "JUNIHO",  GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JUNIHI",  GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "CIVI",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "CHINA",   GTA_POPCYCLE_TYPE_SHOPPING },
    { "SFDWT1",  GTA_POPCYCLE_TYPE_BUSINESS },
    { "SFDWT2",  GTA_POPCYCLE_TYPE_BUSINESS },
    { "SFDWT3",  GTA_POPCYCLE_TYPE_BUSINESS },
    { "SFDWT4",  GTA_POPCYCLE_TYPE_SHOPPING },
    { "SFDWT5",  GTA_POPCYCLE_TYPE_SHOPPING },
    { "SFDWT6",  GTA_POPCYCLE_TYPE_SHOPPING },
    { "FINA",    GTA_POPCYCLE_TYPE_BUSINESS },
    { "CITYS",   GTA_POPCYCLE_TYPE_BUSINESS },
    { "WESTP1",  GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "WESTP2",  GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "WESTP3",  GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "THEA1",   GTA_POPCYCLE_TYPE_ENTERTAINMENT },
    { "THEA2",   GTA_POPCYCLE_TYPE_ENTERTAINMENT },
    { "THEA3",   GTA_POPCYCLE_TYPE_ENTERTAINMENT },
    { "GARC",    GTA_POPCYCLE_TYPE_GANGLAND },
    { "HASH",    GTA_POPCYCLE_TYPE_RESIDENTIAL_POOR },
    { "OCEAF1",  GTA_POPCYCLE_TYPE_BEACH },
    { "OCEAF2",  GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "OCEAF3",  GTA_POPCYCLE_TYPE_BEACH },
    { "DOH1",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "DOH2",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "CUNTC1",  GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "CUNTC2",  GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "CUNTC3",  GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "SFGLF1",  GTA_POPCYCLE_TYPE_GOLF_CLUB },
    { "SFGLF2",  GTA_POPCYCLE_TYPE_GOLF_CLUB },
    { "SFGLF3",  GTA_POPCYCLE_TYPE_GOLF_CLUB },
    { "SFGLF4",  GTA_POPCYCLE_TYPE_GOLF_CLUB },
    { "HILLP",   GTA_POPCYCLE_TYPE_PARK },
    { "SILLY1",  GTA_POPCYCLE_TYPE_BUSINESS },
    { "SILLY2",  GTA_POPCYCLE_TYPE_BUSINESS },
    { "SILLY3",  GTA_POPCYCLE_TYPE_BUSINESS },
    { "SILLY4",  GTA_POPCYCLE_TYPE_BUSINESS },
    { "SFAIR1",  GTA_POPCYCLE_TYPE_AIRPORT },
    { "SFAIR2",  GTA_POPCYCLE_TYPE_AIRPORT },
    { "SFAIR3",  GTA_POPCYCLE_TYPE_AIRPORT },
    { "SFAIR4",  GTA_POPCYCLE_TYPE_AIRPORT },
    { "SFAIR5",  GTA_POPCYCLE_TYPE_AIRPORT },
    { "SFBAG1",  GTA_POPCYCLE_TYPE_AIRPORT_RUNWAY },
    { "SFBAG2",  GTA_POPCYCLE_TYPE_AIRPORT_RUNWAY },
    { "SFBAG3",  GTA_POPCYCLE_TYPE_AIRPORT_RUNWAY },
    { "EASB1",   GTA_POPCYCLE_TYPE_INDUSTRY },
    { "EASB2",   GTA_POPCYCLE_TYPE_INDUSTRY },
    { "ESPE1",   GTA_POPCYCLE_TYPE_SHOPPING },
    { "ESPE2",   GTA_POPCYCLE_TYPE_SHOPPING },
    { "ESPE3",   GTA_POPCYCLE_TYPE_SHOPPING },
    { "LINDEN",  GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "YELLOW",  GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "BFC1",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "BFC2",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "RIE",     GTA_POPCYCLE_TYPE_BUSINESS },
    { "LDM",     GTA_POPCYCLE_TYPE_RESIDENTIAL_POOR },
    { "RSW1",    GTA_POPCYCLE_TYPE_RESIDENTIAL_POOR },
    { "RSW2",    GTA_POPCYCLE_TYPE_RESIDENTIAL_POOR },
    { "RSE",     GTA_POPCYCLE_TYPE_RESIDENTIAL_POOR },
    { "LDS",     GTA_POPCYCLE_TYPE_INDUSTRY },
    { "SRY",     GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JTS1",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JTS2",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "LVA1",    GTA_POPCYCLE_TYPE_INDUSTRY },
    { "LVA2",    GTA_POPCYCLE_TYPE_OUT_OF_TOWN_FACTORY },
    { "LVA3",    GTA_POPCYCLE_TYPE_INDUSTRY },
    { "LVA4",    GTA_POPCYCLE_TYPE_INDUSTRY },
    { "VAIR1",   GTA_POPCYCLE_TYPE_AIRPORT },
    { "VAIR2",   GTA_POPCYCLE_TYPE_AIRPORT },
    { "VAIR3",   GTA_POPCYCLE_TYPE_AIRPORT },
    { "LVBAG",   GTA_POPCYCLE_TYPE_AIRPORT_RUNWAY },
    { "GGC1",    GTA_POPCYCLE_TYPE_PARK },
    { "GGC2",    GTA_POPCYCLE_TYPE_ENTERTAINMENT },
    { "BFLD1",   GTA_POPCYCLE_TYPE_PARK },
    { "BFLD2",   GTA_POPCYCLE_TYPE_ENTERTAINMENT },
    { "WWE",     GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "WWE1",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "PINT",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "YBELL2",  GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "YBELL1",  GTA_POPCYCLE_TYPE_GOLF_CLUB },
    { "JTW1",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JTW2",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JTN1",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JTN2",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JTN3",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JTN4",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JTN5",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JTN6",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JTN7",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JTN8",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JTE1",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JTE2",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JTE3",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "JTE4",    GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "HGP",     GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "SPIN",    GTA_POPCYCLE_TYPE_INDUSTRY },
    { "BINT1",   GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "BINT2",   GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "BINT3",   GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "BINT4",   GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "PRP1",    GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "PRP2",    GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "PRP3",    GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "PRP4",    GTA_POPCYCLE_TYPE_RESIDENTIAL_RICH },
    { "REDE1",   GTA_POPCYCLE_TYPE_BUSINESS },
    { "REDE2",   GTA_POPCYCLE_TYPE_BUSINESS },
    { "REDE3",   GTA_POPCYCLE_TYPE_ENTERTAINMENT },
    { "REDW1",   GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "REDW2",   GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "REDW3",   GTA_POPCYCLE_TYPE_INDUSTRY },
    { "REDW4",   GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE },
    { "ROCE1",   GTA_POPCYCLE_TYPE_BUSINESS },
    { "ROCE2",   GTA_POPCYCLE_TYPE_BUSINESS },
    { "OVS",     GTA_POPCYCLE_TYPE_ENTERTAINMENT_BUSY },
    { "CREE",    GTA_POPCYCLE_TYPE_SHOPPING },
    { "STRIP1",  GTA_POPCYCLE_TYPE_ENTERTAINMENT_BUSY },
    { "STRIP2",  GTA_POPCYCLE_TYPE_ENTERTAINMENT_BUSY },
    { "STRIP3",  GTA_POPCYCLE_TYPE_ENTERTAINMENT_BUSY },
    { "STRIP4",  GTA_POPCYCLE_TYPE_ENTERTAINMENT_BUSY },
    { "PILL1",   GTA_POPCYCLE_TYPE_SHOPPING },
    { "PILL2",   GTA_POPCYCLE_TYPE_SHOPPING },
    { "RING",    GTA_POPCYCLE_TYPE_ENTERTAINMENT_BUSY },
    { "ISLE",    GTA_POPCYCLE_TYPE_ENTERTAINMENT_BUSY },
    { "STAR1",   GTA_POPCYCLE_TYPE_ENTERTAINMENT_BUSY },
    { "STAR2",   GTA_POPCYCLE_TYPE_ENTERTAINMENT_BUSY },
    { "ROY",     GTA_POPCYCLE_TYPE_ENTERTAINMENT_BUSY },
    { "CAM",     GTA_POPCYCLE_TYPE_ENTERTAINMENT_BUSY },
    { "LOT",     GTA_POPCYCLE_TYPE_ENTERTAINMENT_BUSY },
    { "PIRA",    GTA_POPCYCLE_TYPE_ENTERTAINMENT_BUSY },
    { "VISA1",   GTA_POPCYCLE_TYPE_ENTERTAINMENT_BUSY },
    { "VISA2",   GTA_POPCYCLE_TYPE_ENTERTAINMENT_BUSY },
    { "CALI1",   GTA_POPCYCLE_TYPE_ENTERTAINMENT_BUSY },
    { "CALI2",   GTA_POPCYCLE_TYPE_ENTERTAINMENT_BUSY },
    { "DRAG",    GTA_POPCYCLE_TYPE_ENTERTAINMENT_BUSY },
    { "PINK",    GTA_POPCYCLE_TYPE_ENTERTAINMENT_BUSY },
    { "HIGH",    GTA_POPCYCLE_TYPE_ENTERTAINMENT_BUSY },
    { "CONST1",  GTA_POPCYCLE_TYPE_OUT_OF_TOWN_FACTORY },
    { "ANGPI",   GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "SHACA",   GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "BACKO",   GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "BEACO",   GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "FARM",    GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "PALO",    GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "MONT",    GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "MONT1",   GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "MTCHI1",  GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "MTCHI2",  GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "MTCHI3",  GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "MTCHI4",  GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "HBARNS",  GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "DILLI",   GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "TOPFA",   GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "BLUEB",   GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "BLUEB1",  GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "PANOP",   GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "BLUAC",   GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "CREEK",   GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "CREEK1",  GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "MAKO",    GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "FERN",    GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "NROCK",   GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "HANKY",   GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "LEAFY",   GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "RED",     GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "FLINTC",  GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "WHET",    GTA_POPCYCLE_TYPE_COUNTRYSIDE },
    { "BIGE",    GTA_POPCYCLE_TYPE_DESERT },
    { "ELQUE",   GTA_POPCYCLE_TYPE_DESERT },
    { "BARRA",   GTA_POPCYCLE_TYPE_DESERT },
    { "CARSO",   GTA_POPCYCLE_TYPE_DESERT },
    { "PAYAS",   GTA_POPCYCLE_TYPE_DESERT },
    { "PROBE",   GTA_POPCYCLE_TYPE_DESERT },
    { "ELCA",    GTA_POPCYCLE_TYPE_DESERT },
    { "FLINTR",  GTA_POPCYCLE_TYPE_DESERT },
    { "ARCO",    GTA_POPCYCLE_TYPE_DESERT },
    { "VALLE",   GTA_POPCYCLE_TYPE_DESERT },
    { "FLINTI",  GTA_POPCYCLE_TYPE_DESERT },
    { "MONINT",  GTA_POPCYCLE_TYPE_DESERT },
    { "ROBINT",  GTA_POPCYCLE_TYPE_DESERT },
    { "TOM",     GTA_POPCYCLE_TYPE_DESERT },
    { "ALDEA",   GTA_POPCYCLE_TYPE_DESERT },
    { "BRUJA",   GTA_POPCYCLE_TYPE_DESERT },
    { "ROBAD",   GTA_POPCYCLE_TYPE_DESERT },
    { "BONE",    GTA_POPCYCLE_TYPE_DESERT },
    { "HAUL",    GTA_POPCYCLE_TYPE_OUT_OF_TOWN_FACTORY },
    { "QUARY",   GTA_POPCYCLE_TYPE_OUT_OF_TOWN_FACTORY },
    { "OCTAN",   GTA_POPCYCLE_TYPE_OUT_OF_TOWN_FACTORY },
    { "PALMS",   GTA_POPCYCLE_TYPE_OUT_OF_TOWN_FACTORY },
    { "EBAY",    GTA_POPCYCLE_TYPE_OUT_OF_TOWN_FACTORY },
    { "EBAY2",   GTA_POPCYCLE_TYPE_OUT_OF_TOWN_FACTORY },
    { "DAM",     GTA_POPCYCLE_TYPE_OUT_OF_TOWN_FACTORY }
};

static const gZoneRaceAssignments[][E_GTA_INFO_ZON_RACE_ASSIGNMENT] =
{
    { "CHC1a", GTA_POPCYCLE_RACES_HISPANIC_BLACK },
    { "CHC1b", GTA_POPCYCLE_RACES_HISPANIC_BLACK },
    { "CHC2a", GTA_POPCYCLE_RACES_HISPANIC_BLACK },
    { "CHC2b", GTA_POPCYCLE_RACES_HISPANIC_BLACK },
    { "CHC3",  GTA_POPCYCLE_RACES_HISPANIC_BLACK },
    { "CHC4a", GTA_POPCYCLE_RACES_HISPANIC_BLACK },
    { "CHC4b", GTA_POPCYCLE_RACES_HISPANIC_BLACK },
    { "ELCO1", GTA_POPCYCLE_RACES_HISPANIC_BLACK },
    { "ELCO2", GTA_POPCYCLE_RACES_HISPANIC_BLACK },
    { "LFL1a", GTA_POPCYCLE_RACES_HISPANIC_BLACK },
    { "LFL1b", GTA_POPCYCLE_RACES_HISPANIC_BLACK },
    { "GAN1",  GTA_POPCYCLE_RACES_BLACK },
    { "GAN2",  GTA_POPCYCLE_RACES_BLACK },
    { "IWD1",  GTA_POPCYCLE_RACES_BLACK },
    { "IWD2",  GTA_POPCYCLE_RACES_BLACK },
    { "IWD3a", GTA_POPCYCLE_RACES_BLACK },
    { "IWD3b", GTA_POPCYCLE_RACES_BLACK },
    { "IWD4",  GTA_POPCYCLE_RACES_BLACK },
    { "IWD5",  GTA_POPCYCLE_RACES_BLACK },
    { "ELS1a", GTA_POPCYCLE_RACES_HISPANIC_WHITE },
    { "ELS1b", GTA_POPCYCLE_RACES_HISPANIC_WHITE },
    { "ELS2",  GTA_POPCYCLE_RACES_HISPANIC_WHITE },
    { "ELS3a", GTA_POPCYCLE_RACES_HISPANIC_WHITE },
    { "ELS3b", GTA_POPCYCLE_RACES_HISPANIC_WHITE },
    { "ELS4",  GTA_POPCYCLE_RACES_HISPANIC_WHITE },
    { "CHINA", GTA_POPCYCLE_RACES_ORIENTAL_WHITE }
};

/*
* In GTA:SA zones have dealer strengths set, use the same values that are at the beginning of the game
*/
static const gZoneDealerAssignments[][E_GTA_INFO_ZON_DEALER_ASSIGNMENT] = {
    { "CHC1a", 4 },
    { "CHC1b", 4 },
    { "CHC2a", 4 },
    { "CHC2b", 4 },
    { "CHC3",  4 },
    { "CHC4a", 4 },
    { "CHC4b", 4 },
    { "EBE1",  2 },
    { "EBE2a", 2 },
    { "EBE2b", 2 },
    { "EBE3c", 2 },
    { "GLN1",  6 },
    { "GLN2a", 2 },
    { "IWD1",  2 },
    { "IWD2",  2 },
    { "IWD3a", 2 },
    { "IWD3b", 2 },
    { "IWD4",  2 },
    { "IWD5",  2 },
    { "JEF1a", 6 },
    { "JEF1b", 6 },
    { "JEF2",  6 },
    { "JEF3b", 6 },
    { "JEF3c", 6 },
    { "LFL1a", 4 },
    { "LFL1b", 4 },
    { "ELS1a", 2 },
    { "ELS1b", 2 },
    { "ELS2",  2 },
    { "ELS3a", 2 },
    { "ELS3b", 2 },
    { "ELS4",  2 },
    { "VERO1",  2 },
    { "VERO2",  2 },
    { "VERO3",  2 },
    { "VERO4a", 2 },
    { "VERO4b", 2 }
};

static const gZoneNoCopsAssignments[][E_GTA_INFO_ZON_NO_COPS_ASSIGNMENT] = {
    { "GAN1", true }
};

/*
* In GTA:SA zones have gang strengths set, use the same values that are at the beginning of the game
*/
static const gZoneGangAssignments[][E_GTA_INFO_ZON_GANG_ASSIGNMENT] =
{
    // Los Santos - Temple / Sunrise
    { "SUN1",   GTA_POPCYCLE_GANG_GROVE, 30 },
    { "SUN3a",  GTA_POPCYCLE_GANG_GROVE, 30 },
    { "SUN3b",  GTA_POPCYCLE_GANG_GROVE, 30 },
    { "SUN3c",  GTA_POPCYCLE_GANG_GROVE, 30 },
    { "SUN4",   GTA_POPCYCLE_GANG_GROVE, 30 },
    { "CHC1a",  GTA_POPCYCLE_GANG_VAGOS, 40 },
    { "CHC1b",  GTA_POPCYCLE_GANG_VAGOS, 40 },
    { "CHC2a",  GTA_POPCYCLE_GANG_VAGOS, 40 },
    { "CHC2b",  GTA_POPCYCLE_GANG_VAGOS, 40 },
    { "CHC3",   GTA_POPCYCLE_GANG_VAGOS, 40 },
    { "CHC4a",  GTA_POPCYCLE_GANG_VAGOS, 40 },
    { "CHC4b",  GTA_POPCYCLE_GANG_VAGOS, 40 },
    { "EBE1",   GTA_POPCYCLE_GANG_VAGOS, 30 },
    { "EBE2a",  GTA_POPCYCLE_GANG_VAGOS, 30 },
    { "EBE2b",  GTA_POPCYCLE_GANG_VAGOS, 30 },
    { "EBE3c",  GTA_POPCYCLE_GANG_VAGOS, 30 },
    { "ELCO1",  GTA_POPCYCLE_GANG_AZTECAS, 40 },
    { "ELCO2",  GTA_POPCYCLE_GANG_AZTECAS, 40 },
    { "GAN1",   GTA_POPCYCLE_GANG_GROVE, 25 },
    { "GAN2",   GTA_POPCYCLE_GANG_GROVE, 25 },
    { "GLN1",   GTA_POPCYCLE_GANG_BALLAS, 40 },
    { "GLN2a",  GTA_POPCYCLE_GANG_BALLAS, 40 },
    { "LIND1a", GTA_POPCYCLE_GANG_BALLAS, 20 },
    { "LIND1b", GTA_POPCYCLE_GANG_BALLAS, 20 },
    { "LIND2a", GTA_POPCYCLE_GANG_BALLAS, 20 },
    { "LIND2b", GTA_POPCYCLE_GANG_BALLAS, 20 },
    { "LIND3",  GTA_POPCYCLE_GANG_BALLAS, 20 },
    { "IWD1",   GTA_POPCYCLE_GANG_BALLAS, 20 },
    { "IWD2",   GTA_POPCYCLE_GANG_BALLAS, 20 },
    { "IWD3a",  GTA_POPCYCLE_GANG_BALLAS, 20 },
    { "IWD3b",  GTA_POPCYCLE_GANG_BALLAS, 20 },
    { "IWD4",   GTA_POPCYCLE_GANG_BALLAS, 10 },
    { "IWD5",   GTA_POPCYCLE_GANG_BALLAS, 20 },
    { "JEF1a",  GTA_POPCYCLE_GANG_BALLAS, 40 },
    { "JEF1b",  GTA_POPCYCLE_GANG_BALLAS, 40 },
    { "JEF2",   GTA_POPCYCLE_GANG_BALLAS, 40 },
    { "JEF3b",  GTA_POPCYCLE_GANG_BALLAS, 40 },
    { "JEF3c",  GTA_POPCYCLE_GANG_BALLAS, 40 },
    { "LFL1a",  GTA_POPCYCLE_GANG_VAGOS, 40 },
    { "LFL1b",  GTA_POPCYCLE_GANG_VAGOS, 40 },
    { "LMEX1a", GTA_POPCYCLE_GANG_AZTECAS, 30 },
    { "LMEX1b", GTA_POPCYCLE_GANG_AZTECAS, 30 },
    { "ELS1a",  GTA_POPCYCLE_GANG_BALLAS, 30 },
    { "ELS1b",  GTA_POPCYCLE_GANG_BALLAS, 30 },
    { "ELS2",   GTA_POPCYCLE_GANG_BALLAS, 30 },
    { "ELS3a",  GTA_POPCYCLE_GANG_BALLAS, 30 },
    { "ELS3b",  GTA_POPCYCLE_GANG_BALLAS, 30 },
    { "PLS",    GTA_POPCYCLE_GANG_GROVE, 10 },
    { "SMB1",   GTA_POPCYCLE_GANG_GROVE, 10 },
    { "SMB2",   GTA_POPCYCLE_GANG_GROVE, 10 },
    { "VIN2",   GTA_POPCYCLE_GANG_GROVE, 10 },
    { "VERO1",  GTA_POPCYCLE_GANG_BALLAS, 10 },
    { "VERO2",  GTA_POPCYCLE_GANG_BALLAS, 10 },
    { "VERO3",  GTA_POPCYCLE_GANG_BALLAS, 10 },
    { "VERO4a", GTA_POPCYCLE_GANG_BALLAS, 10 },
    { "VERO4b", GTA_POPCYCLE_GANG_BALLAS, 10 },
    { "CALT",   GTA_POPCYCLE_GANG_TRIADS, 10 },
    { "BATTP",  GTA_POPCYCLE_GANG_SF_RIFA, 25 },
    { "ESPN1",  GTA_POPCYCLE_GANG_DA_NANG_BOYS, 10 },
    { "ESPN2",  GTA_POPCYCLE_GANG_DA_NANG_BOYS, 10 },
    { "ESPN3",  GTA_POPCYCLE_GANG_DA_NANG_BOYS, 10 },
    { "CHINA",  GTA_POPCYCLE_GANG_TRIADS, 40 },
    { "THEA1",  GTA_POPCYCLE_GANG_TRIADS, 10 },
    { "THEA3",  GTA_POPCYCLE_GANG_SF_RIFA, 10 },
    { "GARC",   GTA_POPCYCLE_GANG_SF_RIFA, 40 },
    { "DOH2",   GTA_POPCYCLE_GANG_SF_RIFA, 10 },
    { "EASB1",  GTA_POPCYCLE_GANG_DA_NANG_BOYS, 10 },
    { "EASB2",  GTA_POPCYCLE_GANG_DA_NANG_BOYS, 10 }
};

static stock InfoZon_Reset() {
    gInfoZonLoaded = false;
    gInfoZonZoneCount = 0;
}

static stock bool:InfoZon_IsLineEmpty(const line[]) {
    for(new i = 0; line[i] != '\0'; i++) {
        if(line[i] != ' ' && line[i] != '\t' && line[i] != '\r' && line[i] != '\n') {
            return false;
        }
    }

    return true;
}

static stock bool:InfoZon_IsCommentLine(const line[]) {
    new i;

    while(line[i] == ' ' || line[i] == '\t')
        i++;

    return line[i] == '#';
}

static stock bool:InfoZon_IsSectionMarker(const line[]) {
    new start;

    while(line[start] == ' ' || line[start] == '\t')
        start++;

    new end = start;

    while(line[end] != '\0' && line[end] != '\r' && line[end] != '\n' && line[end] != ' ' && line[end] != '\t') {
        end++;
    }

    new length = end - start;

    if(length == 4) {
        if(tolower(line[start]) == 'z' && tolower(line[start + 1]) == 'o' && tolower(line[start + 2]) == 'n' && tolower(line[start + 3]) == 'e') {
            return true;
        }
    }

    if(length == 3) {
        if(tolower(line[start]) == 'e' && tolower(line[start + 1]) == 'n' && tolower(line[start + 2]) == 'd') {
            return true;
        }
    }

    return false;
}

static stock InfoZon_FindZoneByName(const name[]) {
    for(new zone = 0; zone < gInfoZonZoneCount; zone++) {
        if(!strcmp(gInfoZonZones[zone][GTA_INFO_ZON_NAME], name, true))
            return zone;
    }

    return -1;
}

static stock bool:InfoZon_CopyTrimmedRange(const source[], start, end, destination[], destinationSize) {
    while(start < end && (source[start] == ' ' || source[start] == '\t'))
        start++;

    while(end > start && (source[end - 1] == ' ' || source[end - 1] == '\t' || source[end - 1] == '\r' || source[end - 1] == '\n')) {
        end--;
    }

    new length = end - start;

    if(length <= 0 || length >= destinationSize)
        return false;

    for(new i = 0; i < length; i++)
        destination[i] = source[start + i];

    destination[length] = '\0';
    return true;
}

static stock bool:InfoZon_ParseInteger(const value[], &result) {
    new i;
    new sign = 1;

    if(value[0] == '-') {
        sign = -1;
        i++;
    } else if(value[0] == '+') {
        i++;
    }

    if(value[i] == '\0')
        return false;

    result = 0;

    for(; value[i] != '\0'; i++) {
        if(value[i] < '0' || value[i] > '9')
            return false;

        result = (result * 10) + (value[i] - '0');
    }

    result *= sign;
    return true;
}

static stock bool:InfoZon_ValidateAssignments() {
    new bool:valid = true;

    for(new i = 0; i < sizeof(gInfoZonPopTypeAssignments); i++) {
        new E_GTA_POPCYCLE_TYPE:populationType = gInfoZonPopTypeAssignments[i][GTA_INFO_ZON_POPTYPE_ASSIGNMENT_TYPE];

        if(populationType <= GTA_POPCYCLE_TYPE_UNKNOWN || _:populationType >= GTA_POPCYCLE_TYPE_COUNT) {
            printf("[omp-gta-info-zon] ERROR: Population type assignment for zone '%s' has invalid type %d.", gInfoZonPopTypeAssignments[i][GTA_INFO_ZON_POPTYPE_ASSIGNMENT_NAME], _:populationType);

            valid = false;
            continue;
        }

        if(InfoZon_FindZoneByName(gInfoZonPopTypeAssignments[i][GTA_INFO_ZON_POPTYPE_ASSIGNMENT_NAME]) == -1) {
            printf("[omp-gta-info-zon] ERROR: Population type assignment references unknown zone '%s'.", gInfoZonPopTypeAssignments[i][GTA_INFO_ZON_POPTYPE_ASSIGNMENT_NAME]);

            valid = false;
        }
    }

    for(new i = 0; i < sizeof(gZoneRaceAssignments); i++) {

        new E_GTA_POPCYCLE_RACES:populationRaces = gZoneRaceAssignments[i][GTA_INFO_ZON_RACE_ASSIGNMENT_RACE];

        switch(populationRaces) {
            case GTA_POPCYCLE_RACES_BLACK,
                GTA_POPCYCLE_RACES_HISPANIC_BLACK,
                GTA_POPCYCLE_RACES_HISPANIC_WHITE,
                GTA_POPCYCLE_RACES_ORIENTAL_WHITE: {
            }
            default: {
                printf("[omp-gta-info-zon] ERROR: Population race assignment for zone '%s' has invalid races %d.", gZoneRaceAssignments[i][GTA_INFO_ZON_RACE_ASSIGNMENT_NAME], _:populationRaces);

                valid = false;
                continue;
            }
        }


        if(InfoZon_FindZoneByName(gZoneRaceAssignments[i][GTA_INFO_ZON_RACE_ASSIGNMENT_NAME]) == -1) {
            printf("[omp-gta-info-zon] ERROR: Population race assignment references unknown zone '%s'.", gZoneRaceAssignments[i][GTA_INFO_ZON_RACE_ASSIGNMENT_NAME]);

            valid = false;
        }
    }

    for(new i = 0; i < sizeof(gZoneDealerAssignments); i++) {

        new strength = gZoneDealerAssignments[i][GTA_INFO_ZON_DEALER_ASSIGNMENT_STRENGTH];

        if(strength < 0) {
            printf("[omp-gta-info-zon] ERROR: Dealer assignment for zone '%s' has invalid strength %d.", gZoneDealerAssignments[i][GTA_INFO_ZON_DEALER_ASSIGNMENT_NAME], strength);

            valid = false;
            continue;
        }

        if(InfoZon_FindZoneByName(gZoneDealerAssignments[i][GTA_INFO_ZON_DEALER_ASSIGNMENT_NAME]) == -1) {
            printf("[omp-gta-info-zon] ERROR: Dealer assignment references unknown zone '%s'.", gZoneDealerAssignments[i][GTA_INFO_ZON_DEALER_ASSIGNMENT_NAME]);

            valid = false;
        }
    }

    for(new i = 0; i < sizeof(gZoneNoCopsAssignments); i++) {
        if(InfoZon_FindZoneByName(gZoneNoCopsAssignments[i][GTA_INFO_ZON_NO_COPS_ASSIGNMENT_NAME]) == -1) {
            printf("[omp-gta-info-zon] ERROR: No-cops assignment references unknown zone '%s'.", gZoneNoCopsAssignments[i][GTA_INFO_ZON_NO_COPS_ASSIGNMENT_NAME]);

            valid = false;
        }
    }

    for(new i = 0; i < sizeof(gZoneGangAssignments); i++) {
        new E_GTA_POPCYCLE_GANG:gang = gZoneGangAssignments[i][GTA_INFO_ZON_GANG_ASSIGNMENT_GANG];

        if(gang < GTA_POPCYCLE_GANG_BALLAS || gang >= GTA_POPCYCLE_GANG_COUNT) {
            printf("[omp-gta-info-zon] ERROR: Gang assignment for zone '%s' has invalid gang %d.", gZoneGangAssignments[i][GTA_INFO_ZON_GANG_ASSIGNMENT_NAME], _:gang);

            valid = false;
            continue;
        }

        if(InfoZon_FindZoneByName(gZoneGangAssignments[i][GTA_INFO_ZON_GANG_ASSIGNMENT_NAME]) == -1) {
            printf("[omp-gta-info-zon] ERROR: Gang assignment references unknown zone '%s'.", gZoneGangAssignments[i][GTA_INFO_ZON_GANG_ASSIGNMENT_NAME]);

            valid = false;
        }
    }

    return valid;
}

static stock bool:InfoZon_ParseFloat(const value[], &Float:result) {
    new i;
    new sign = 1;

    if(value[0] == '-') {
        sign = -1;
        i++;
    } else if(value[0] == '+') {
        i++;
    }

    if(value[i] == '\0')
        return false;

    new bool:hasDigit;
    new bool:hasDecimal;
    new Float:number;
    new Float:fraction = 0.1;

    for(; value[i] != '\0' && value[i] != 'e' && value[i] != 'E'; i++) {
        if(value[i] == '.') {
            if(hasDecimal)
                return false;

            hasDecimal = true;
            continue;
        }

        if(value[i] < '0' || value[i] > '9')
            return false;

        hasDigit = true;

        if(hasDecimal) {
            number += float(value[i] - '0') * fraction;
            fraction *= 0.1;
        } else {
            number = number * 10.0 + float(value[i] - '0');
        }
    }

    if(!hasDigit)
        return false;

    if(value[i] == 'e' || value[i] == 'E') {
        i++;

        new exponentSign = 1;

        if(value[i] == '-') {
            exponentSign = -1;
            i++;
        } else if(value[i] == '+') {
            i++;
        }

        if(value[i] == '\0')
            return false;

        new exponent;
        new bool:hasExponentDigit;

        for(; value[i] != '\0'; i++) {
            if(value[i] < '0' || value[i] > '9')
                return false;

            hasExponentDigit = true;
            exponent = (exponent * 10) + (value[i] - '0');
        }

        if(!hasExponentDigit)
            return false;

        if(exponentSign < 0) {
            for(new j = 0; j < exponent; j++)
                number /= 10.0;
        } else {
            for(new j = 0; j < exponent; j++)
                number *= 10.0;
        }
    }

    result = number * float(sign);
    return true;
}

static stock bool:InfoZon_IsValidZone(zone) {
    return (gInfoZonLoaded && zone >= 0 && zone < gInfoZonZoneCount);
}

static stock bool:InfoZon_ApplyPopulationTypes() {
    for(new i = 0; i < sizeof(gInfoZonPopTypeAssignments); i++) {
        new zone = InfoZon_FindZoneByName(gInfoZonPopTypeAssignments[i][GTA_INFO_ZON_POPTYPE_ASSIGNMENT_NAME]);

        if(zone == -1)
            continue;

        gInfoZonZones[zone][GTA_INFO_ZON_POPULATION_TYPE] = gInfoZonPopTypeAssignments[i][GTA_INFO_ZON_POPTYPE_ASSIGNMENT_TYPE];
    }

    return true;
}

static stock bool:InfoZon_ApplyPopulationRaces() {
    for(new i = 0; i < sizeof(gZoneRaceAssignments); i++) {
        new zone = InfoZon_FindZoneByName(gZoneRaceAssignments[i][GTA_INFO_ZON_RACE_ASSIGNMENT_NAME]);

        if(zone == -1)
            continue;

        gInfoZonZones[zone][GTA_INFO_ZON_POPULATION_RACE] = gZoneRaceAssignments[i][GTA_INFO_ZON_RACE_ASSIGNMENT_RACE];
    }

    return true;
}

static stock bool:InfoZon_ApplyDealerStrengths() {
    for(new i = 0; i < sizeof(gZoneDealerAssignments); i++) {
        new zone = InfoZon_FindZoneByName(gZoneDealerAssignments[i][GTA_INFO_ZON_DEALER_ASSIGNMENT_NAME]);

        if(zone == -1)
            continue;

        gInfoZonZones[zone][GTA_INFO_ZON_DEALER_STRENGTH] = gZoneDealerAssignments[i][GTA_INFO_ZON_DEALER_ASSIGNMENT_STRENGTH];
    }

    return true;
}

static stock bool:InfoZon_ApplyNoCops() {
    for(new i = 0; i < sizeof(gZoneNoCopsAssignments); i++) {
        new zone = InfoZon_FindZoneByName(gZoneNoCopsAssignments[i][GTA_INFO_ZON_NO_COPS_ASSIGNMENT_NAME]);

        if(zone == -1)
            continue;

        gInfoZonZones[zone][GTA_INFO_ZON_NO_COPS] = gZoneNoCopsAssignments[i][GTA_INFO_ZON_NO_COPS_ASSIGNMENT_NO_COPS];
    }

    return true;
}

static stock bool:InfoZon_ApplyGangStrengths() {
    for(new i = 0; i < sizeof(gZoneGangAssignments); i++) {
        new E_GTA_POPCYCLE_GANG:gang = gZoneGangAssignments[i][GTA_INFO_ZON_GANG_ASSIGNMENT_GANG];

        new zone = InfoZon_FindZoneByName(gZoneGangAssignments[i][GTA_INFO_ZON_GANG_ASSIGNMENT_NAME]);

        if(zone == -1)
            continue;

        gInfoZonZones[zone][GTA_INFO_ZON_GANG_STRENGTH][gang] += gZoneGangAssignments[i][GTA_INFO_ZON_GANG_ASSIGNMENT_STRENGTH];
    }

    return true;
}

static stock bool:InfoZon_ParseLine(const line[], zone) {
    if(zone < 0 || zone >= GTA_INFO_ZON_MAX_ZONES)
        return false;

    new fields[10][32];
    new field;
    new fieldStart;
    new length = strlen(line);

    for(new i = 0; i <= length; i++) {
        if(line[i] == ',' || line[i] == '\0' || line[i] == '\r' || line[i] == '\n') {
            if(field >= sizeof(fields))
                return false;

            if(!InfoZon_CopyTrimmedRange(line, fieldStart, i, fields[field], sizeof(fields[]))) {
                return false;
            }

            field++;
            fieldStart = i + 1;

            if(line[i] != ',')
                break;
        }
    }

    if(field != sizeof(fields))
        return false;

    if(strlen(fields[0]) >= GTA_INFO_ZON_NAME_LENGTH)
        return false;

    if(strlen(fields[9]) >= GTA_INFO_ZON_PARENT_LENGTH)
        return false;

    new zoneType;
    new level;

    new Float:minX;
    new Float:minY;
    new Float:minZ;

    new Float:maxX;
    new Float:maxY;
    new Float:maxZ;

    if(!InfoZon_ParseInteger(fields[1], zoneType))
        return false;

    if(zoneType < _:GTA_INFO_ZON_TYPE_NAVI || zoneType > _:GTA_INFO_ZON_TYPE_MAP) {
        return false;
    }

    if(!InfoZon_ParseFloat(fields[2], minX))
        return false;

    if(!InfoZon_ParseFloat(fields[3], minY))
        return false;

    if(!InfoZon_ParseFloat(fields[4], minZ))
        return false;

    if(!InfoZon_ParseFloat(fields[5], maxX))
        return false;

    if(!InfoZon_ParseFloat(fields[6], maxY))
        return false;

    if(!InfoZon_ParseFloat(fields[7], maxZ))
        return false;

    if(!InfoZon_ParseInteger(fields[8], level))
        return false;

    if(level < _:GTA_MAPZON_LEVEL_COUNTRYSIDE || level > _:GTA_MAPZON_LEVEL_LAS_VENTURAS) {
        return false;
    }

    if(minX > maxX || minY > maxY || minZ > maxZ)
        return false;

    format(gInfoZonZones[zone][GTA_INFO_ZON_NAME], GTA_INFO_ZON_NAME_LENGTH, "%s", fields[0]);

    gInfoZonZones[zone][GTA_INFO_ZON_TYPE] = E_GTA_INFO_ZON_TYPE:zoneType;

    gInfoZonZones[zone][GTA_INFO_ZON_MIN_X] = minX;
    gInfoZonZones[zone][GTA_INFO_ZON_MIN_Y] = minY;
    gInfoZonZones[zone][GTA_INFO_ZON_MIN_Z] = minZ;

    gInfoZonZones[zone][GTA_INFO_ZON_MAX_X] = maxX;
    gInfoZonZones[zone][GTA_INFO_ZON_MAX_Y] = maxY;
    gInfoZonZones[zone][GTA_INFO_ZON_MAX_Z] = maxZ;

    gInfoZonZones[zone][GTA_INFO_ZON_LEVEL] = E_GTA_MAPZON_LEVEL:level;

    format(gInfoZonZones[zone][GTA_INFO_ZON_PARENT], GTA_INFO_ZON_PARENT_LENGTH, "%s", fields[9]);

    gInfoZonZones[zone][GTA_INFO_ZON_POPULATION_TYPE] = GTA_POPCYCLE_TYPE_RESIDENTIAL_AVERAGE;

    gInfoZonZones[zone][GTA_INFO_ZON_POPULATION_RACE] = GTA_POPCYCLE_RACES_DEFAULT;

    gInfoZonZones[zone][GTA_INFO_ZON_DEALER_STRENGTH] = 0;
    gInfoZonZones[zone][GTA_INFO_ZON_NO_COPS] = false;

    for(new E_GTA_POPCYCLE_GANG:gang = GTA_POPCYCLE_GANG_BALLAS; gang < GTA_POPCYCLE_GANG_COUNT; gang++) {
        gInfoZonZones[zone][GTA_INFO_ZON_GANG_STRENGTH][gang] = 0;
    }

    return true;
}

/*
* --------------------------------------------------------------------------
* USABLE FUNCTIONS
* --------------------------------------------------------------------------
*/

stock bool:LoadInfoZon(const filename[] = GTA_INFO_ZON_FILE) {
    InfoZon_Reset();

    new File:file = fopen(filename, io_read);

    if(!file) {
        printf("[omp-gta-info-zon] ERROR: Failed to open %s", filename);
        return false;
    }

    new line[GTA_INFO_ZON_MAX_LINE_LENGTH];

    while(fread(file, line)) {
        new length = strlen(line);

        if(length >= GTA_INFO_ZON_MAX_LINE_LENGTH - 1 && line[length - 1] != '\n') {
            printf("[omp-gta-info-zon] ERROR: Line exceeds maximum length of %d characters.", GTA_INFO_ZON_MAX_LINE_LENGTH - 1);

            fclose(file);
            InfoZon_Reset();
            return false;
        }

        if(InfoZon_IsLineEmpty(line) || InfoZon_IsCommentLine(line) || InfoZon_IsSectionMarker(line)) {
            continue;
        }

        if(gInfoZonZoneCount >= GTA_INFO_ZON_MAX_ZONES) {
            printf("[omp-gta-info-zon] ERROR: Maximum zone count of %d exceeded.", GTA_INFO_ZON_MAX_ZONES);

            fclose(file);
            InfoZon_Reset();
            return false;
        }

        if(!InfoZon_ParseLine(line, gInfoZonZoneCount)) {
            printf("[omp-gta-info-zon] ERROR: Failed to parse zone %d: %s", gInfoZonZoneCount, line);

            fclose(file);
            InfoZon_Reset();
            return false;
        }

        gInfoZonZoneCount++;
    }

    fclose(file);

    if(gInfoZonZoneCount <= 0) {
        print("[omp-gta-info-zon] ERROR: No info zones were loaded.");
        InfoZon_Reset();
        return false;
    }

    if(!InfoZon_ValidateAssignments()) {
        print("[omp-gta-info-zon] ERROR: Could not validate zone assignments.");
        InfoZon_Reset();
        return false;
    }

    if(!InfoZon_ApplyPopulationTypes()) {
        InfoZon_Reset();
        return false;
    }
    if(!InfoZon_ApplyPopulationRaces()) {
        InfoZon_Reset();
        return false;
    }
    if(!InfoZon_ApplyDealerStrengths()) {
        InfoZon_Reset();
        return false;
    }
    if(!InfoZon_ApplyNoCops()) {
        InfoZon_Reset();
        return false;
    }
    if(!InfoZon_ApplyGangStrengths()) {
        InfoZon_Reset();
        return false;
    }


    gInfoZonLoaded = true;

    printf("[omp-gta-info-zon] Loaded %d info zones.", gInfoZonZoneCount);

    return true;
}

stock bool:IsInfoZonLoaded() {
    return gInfoZonLoaded;
}

stock GetInfoZonZoneCount() {
    if(!IsInfoZonLoaded())
        return 0;

    return gInfoZonZoneCount;
}

/*
* Checks if a point is in a specific info.zon zone
*/
stock bool:IsPointInInfoZon(zone, Float:x, Float:y, Float:z) {
    if(!InfoZon_IsValidZone(zone))
        return false;

    return (
        x >= gInfoZonZones[zone][GTA_INFO_ZON_MIN_X] &&
        x <= gInfoZonZones[zone][GTA_INFO_ZON_MAX_X] &&
        y >= gInfoZonZones[zone][GTA_INFO_ZON_MIN_Y] &&
        y <= gInfoZonZones[zone][GTA_INFO_ZON_MAX_Y] &&
        z >= gInfoZonZones[zone][GTA_INFO_ZON_MIN_Z] &&
        z <= gInfoZonZones[zone][GTA_INFO_ZON_MAX_Z]
    );
}


/*
* Returns the smallest info.zon zone containing a certain location.
*/
stock GetInfoZonIndexAt(Float:x, Float:y, Float:z) {
    if(!IsInfoZonLoaded())
        return -1;

    new bestZone = -1;
    new Float:bestSize;

    for(new i = 0; i < gInfoZonZoneCount; i++) {
        if(!IsPointInInfoZon(i, x, y, z))
            continue;

        new Float:size = (gInfoZonZones[i][GTA_INFO_ZON_MAX_X] - gInfoZonZones[i][GTA_INFO_ZON_MIN_X]) + (gInfoZonZones[i][GTA_INFO_ZON_MAX_Y] - gInfoZonZones[i][GTA_INFO_ZON_MIN_Y]);

        if(bestZone == -1 || size < bestSize) {
            bestZone = i;
            bestSize = size;
        }
    }

    return bestZone;
}

/*
* Returns the info.zon zone name, for example "SFDWT3".
*/
stock bool:GetInfoZonName(zone, output[], size = sizeof(output)) {
    if(size <= 0)
        return false;

    output[0] = '\0';

    if(!InfoZon_IsValidZone(zone))
        return false;

    format(output, size, "%s", gInfoZonZones[zone][GTA_INFO_ZON_NAME]);
    return true;
}

/*
* Returns the info.zon zone index with the specified name.
*/
stock GetInfoZonIndexByName(const name[]) {
    if(!IsInfoZonLoaded())
        return -1;

    return InfoZon_FindZoneByName(name);
}

/*
* Returns the population type for a zone. For example, GTA_POPCYCLE_TYPE_AIRPORT
*/
stock E_GTA_POPCYCLE_TYPE:GetInfoZonPopulationType(zone) {
    if(!InfoZon_IsValidZone(zone)) {
        return GTA_POPCYCLE_TYPE_UNKNOWN;
    }

    return gInfoZonZones[zone][GTA_INFO_ZON_POPULATION_TYPE];
}

/*
* Returns the population type for specifc coordinates. For example, GTA_POPCYCLE_TYPE_AIRPORT
*/
stock E_GTA_POPCYCLE_TYPE:GetInfoZonPopulationTypeAt(Float:x, Float:y, Float:z) {
    new zone = GetInfoZonIndexAt(x, y, z);

    if(zone == -1)
        return GTA_POPCYCLE_TYPE_UNKNOWN;

    return GetInfoZonPopulationType(zone);
}

/*
* Returns which races can spawn in a specific zone. For example, returns GTA_POPCYCLE_RACES_HISPANIC_WHITE
*/
stock E_GTA_POPCYCLE_RACES:GetInfoZonPopulationRace(zone) {
    if(!InfoZon_IsValidZone(zone)) {
        return GTA_POPCYCLE_RACES_DEFAULT;
    }

    return gInfoZonZones[zone][GTA_INFO_ZON_POPULATION_RACE];
}

/*
* Returns the dealers strength inside a zone. In GTA:SA this changes how many dealers spawn in a zone
*/
stock GetInfoZonDealerStrength(zone) {
    if(!InfoZon_IsValidZone(zone)) {
        return 0;
    }

    return gInfoZonZones[zone][GTA_INFO_ZON_DEALER_STRENGTH];
}

/*
* Checks if the zone has the "no cops" flag set. In GTA:SA this prevents random cops spawning in a zone
*/
stock bool:IsInfoZonNoCops(zone) {
    if(!InfoZon_IsValidZone(zone)) {
        return false;
    }

    return gInfoZonZones[zone][GTA_INFO_ZON_NO_COPS];
}

/*
* Returns the gangs strength inside a zone. In GTA:SA this changes how many gang members spawn in a zone
*/
stock GetInfoZonGangStrength(zone, E_GTA_POPCYCLE_GANG:gang) {
    if(!InfoZon_IsValidZone(zone) || gang < GTA_POPCYCLE_GANG_BALLAS || gang >= GTA_POPCYCLE_GANG_COUNT) {
        return 0;
    }

    return gInfoZonZones[zone][GTA_INFO_ZON_GANG_STRENGTH][gang];
}

/*
* Returns the GTA zone type. For example, returns GTA_INFO_ZON_TYPE_NAVI
* In GTA:SA all zones have GTA_INFO_ZON_TYPE_NAVI. 
*/
stock E_GTA_INFO_ZON_TYPE:GetInfoZonType(zone) {
    if(!InfoZon_IsValidZone(zone))
        return GTA_INFO_ZON_TYPE_INVALID;

    return gInfoZonZones[zone][GTA_INFO_ZON_TYPE];
}

/*
* Returns the GTA level assigned to the zone. For example, returns GTA_MAPZON_LEVEL_LOS_SANTOS.
*/
stock E_GTA_MAPZON_LEVEL:GetInfoZonLevel(zone) {
    if(!InfoZon_IsValidZone(zone))
        return GTA_MAPZON_LEVEL_INVALID;

    return gInfoZonZones[zone][GTA_INFO_ZON_LEVEL];
}

/*
* Returns the info.zon parent zone name.
*/
stock bool:GetInfoZonParent(zone, output[], size = sizeof(output)) {
    if(size <= 0)
        return false;

    output[0] = '\0';

    if(!InfoZon_IsValidZone(zone))
        return false;

    format(output, size, "%s", gInfoZonZones[zone][GTA_INFO_ZON_PARENT]);

    return true;
}

/*
* Returns the info.zon zone bounding box.
*/
stock bool:GetInfoZonBounds(zone, &Float:minX, &Float:minY, &Float:minZ, &Float:maxX, &Float:maxY, &Float:maxZ) {
    if(!InfoZon_IsValidZone(zone)) {
        minX = 0.0;
        minY = 0.0;
        minZ = 0.0;
        maxX = 0.0;
        maxY = 0.0;
        maxZ = 0.0;
        return false;
    }

    minX = gInfoZonZones[zone][GTA_INFO_ZON_MIN_X];
    minY = gInfoZonZones[zone][GTA_INFO_ZON_MIN_Y];
    minZ = gInfoZonZones[zone][GTA_INFO_ZON_MIN_Z];

    maxX = gInfoZonZones[zone][GTA_INFO_ZON_MAX_X];
    maxY = gInfoZonZones[zone][GTA_INFO_ZON_MAX_Y];
    maxZ = gInfoZonZones[zone][GTA_INFO_ZON_MAX_Z];

    return true;
}

/*
* Tests loaded info.zon
*/
stock bool:TestInfoZon() {
    if(!IsInfoZonLoaded()) {
        print("[omp-gta-info-zon] TEST FAILED: info.zon is not loaded.");
        return false;
    }

    new zoneCount = GetInfoZonZoneCount();

    if(zoneCount <= 0) {
        print("[omp-gta-info-zon] TEST FAILED: No zones were loaded.");
        return false;
    }

    printf("[omp-gta-info-zon] TEST: %d zones loaded.", zoneCount);

    new validZones, invalidZones, populationRaceZones, dealerZones, noCopsZones, gangZones, gangAssignments;

    for(new zone = 0; zone < zoneCount; zone++) {
        new name[GTA_INFO_ZON_NAME_LENGTH], parent[GTA_INFO_ZON_PARENT_LENGTH];

        new Float:minX, Float:minY, Float:minZ, Float:maxX, Float:maxY, Float:maxZ;

        if(!GetInfoZonName(zone, name, sizeof(name))) {
            printf("[omp-gta-info-zon] TEST ERROR: Failed to get name for zone %d.", zone);

            invalidZones++;
            continue;
        }

        if(!GetInfoZonParent(zone, parent, sizeof(parent))) {
            printf("[omp-gta-info-zon] TEST ERROR: Failed to get parent for zone %d ('%s').", zone, name);

            invalidZones++;
            continue;
        }

        if(!GetInfoZonBounds(zone, minX, minY, minZ, maxX, maxY, maxZ)) {
            printf("[omp-gta-info-zon] TEST ERROR: Failed to get bounds for zone %d ('%s').", zone, name);

            invalidZones++;
            continue;
        }

        if(minX > maxX || minY > maxY || minZ > maxZ) {
            printf("[omp-gta-info-zon] TEST ERROR: Invalid bounds for zone %d ('%s').", zone, name);

            invalidZones++;
            continue;
        }

        if(GetInfoZonIndexByName(name) == -1) {
            printf("[omp-gta-info-zon] TEST ERROR: Zone '%s' at index %d could not be resolved by name.", name, zone);

            invalidZones++;
            continue;
        }

        new Float:centerX = (minX + maxX) / 2.0, Float:centerY = (minY + maxY) / 2.0, Float:centerZ = (minZ + maxZ) / 2.0;

        if(!IsPointInInfoZon(zone, centerX, centerY, centerZ)) {
            printf("[omp-gta-info-zon] TEST ERROR: Center point is not inside zone %d ('%s').", zone, name);

            invalidZones++;
            continue;
        }

        new E_GTA_INFO_ZON_TYPE:type = GetInfoZonType(zone);

        new E_GTA_MAPZON_LEVEL:level = GetInfoZonLevel(zone);

        if(type < GTA_INFO_ZON_TYPE_NAVI || type > GTA_INFO_ZON_TYPE_MAP) {
            printf("[omp-gta-info-zon] TEST ERROR: Invalid zone type %d for zone %d ('%s').", _:type, zone, name);

            invalidZones++;
            continue;
        }

        if(level < GTA_MAPZON_LEVEL_COUNTRYSIDE || level > GTA_MAPZON_LEVEL_LAS_VENTURAS) {
            printf("[omp-gta-info-zon] TEST ERROR: Invalid level %d for zone %d ('%s').", _:level, zone, name);

            invalidZones++;
            continue;
        }

        new E_GTA_POPCYCLE_TYPE:populationType = GetInfoZonPopulationType(zone);

        if(populationType <= GTA_POPCYCLE_TYPE_UNKNOWN || _:populationType >= GTA_POPCYCLE_TYPE_COUNT) {
            printf("[omp-gta-info-zon] TEST ERROR: Invalid population type %d for zone %d ('%s').", _:populationType, zone, name);

            invalidZones++;
            continue;
        }

        new E_GTA_POPCYCLE_RACES:populationRaces =
            GetInfoZonPopulationRace(zone);

        switch(populationRaces) {
            case GTA_POPCYCLE_RACES_DEFAULT: {
                // No population race restriction.
            }

            case GTA_POPCYCLE_RACES_BLACK,
                 GTA_POPCYCLE_RACES_HISPANIC_BLACK,
                 GTA_POPCYCLE_RACES_HISPANIC_WHITE,
                 GTA_POPCYCLE_RACES_ORIENTAL_WHITE: {
                populationRaceZones++;
            }

            default: {
                printf("[omp-gta-info-zon] TEST ERROR: Invalid population races for zone %d ('%s'): %d.", zone, name, _:populationRaces);

                invalidZones++;
                continue;
            }
        }

        new dealerStrength = GetInfoZonDealerStrength(zone);

        if(dealerStrength > 0)
            dealerZones++;

        if(IsInfoZonNoCops(zone))
            noCopsZones++;

        new bool:hasGang;

        for(new E_GTA_POPCYCLE_GANG:gang = GTA_POPCYCLE_GANG_BALLAS; gang < GTA_POPCYCLE_GANG_COUNT; gang++) {

            new strength =
                GetInfoZonGangStrength(zone, gang);

            if(strength > 0) {
                hasGang = true;
                gangAssignments++;
            }
        }

        if(hasGang)
            gangZones++;

        validZones++;
    }

    if(!InfoZon_ValidateAssignments()) {
        print("[omp-gta-info-zon] TEST ERROR: One or more GTA assignments reference unknown zones.");

        return false;
    }

    for(new i = 0; i < sizeof(gZoneRaceAssignments); i++) {
        new zone = GetInfoZonIndexByName(gZoneRaceAssignments[i][GTA_INFO_ZON_RACE_ASSIGNMENT_NAME]);

        if(zone == -1) {
            printf("[omp-gta-info-zon] TEST ERROR: Population race zone '%s' could not be resolved.", gZoneRaceAssignments[i][GTA_INFO_ZON_RACE_ASSIGNMENT_NAME]);

            return false;
        }

        new E_GTA_POPCYCLE_RACES:populationRaces = GetInfoZonPopulationRace(zone);

        if(populationRaces != gZoneRaceAssignments[i][GTA_INFO_ZON_RACE_ASSIGNMENT_RACE]) {
            printf("[omp-gta-info-zon] TEST ERROR: Population races mismatch for zone '%s': expected %d, got %d.", gZoneRaceAssignments[i][GTA_INFO_ZON_RACE_ASSIGNMENT_NAME], _:gZoneRaceAssignments[i][GTA_INFO_ZON_RACE_ASSIGNMENT_RACE], _:populationRaces);

            return false;
        }
    }

    new dummy[GTA_INFO_ZON_NAME_LENGTH];

    if(GetInfoZonName(-1, dummy, sizeof(dummy))) {
        print("[omp-gta-info-zon] TEST ERROR: GetInfoZonName(-1) unexpectedly succeeded.");

        return false;
    }

    if(GetInfoZonIndexByName("__INVALID_INFO_ZON__") != -1) {
        print("[omp-gta-info-zon] TEST ERROR: Unknown zone name unexpectedly resolved.");

        return false;
    }

    if(IsPointInInfoZon(-1, 0.0, 0.0, 0.0)) {
        print("[omp-gta-info-zon] TEST ERROR: IsPointInInfoZon(-1) unexpectedly succeeded.");

        return false;
    }

    printf("[omp-gta-info-zon] TEST: valid=%d invalid=%d population-race-zones=%d dealers=%d no-cops=%d gang-zones=%d gang-assignments=%d",validZones,invalidZones, populationRaceZones, dealerZones, noCopsZones, gangZones, gangAssignments);

    if(invalidZones != 0) {
        printf("[omp-gta-info-zon] TEST FAILED: %d invalid zone(s) found.", invalidZones);

        return false;
    }

    print("[omp-gta-info-zon] TEST PASSED.");
    return true;
}
