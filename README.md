# What is it?

This is a simple include to parse GTA:SA "info.zon" file. This file contains information what kind of peds and their race can spawn, as well as in which map area (LS/SF/LV...) does this zone belong to. Retquires https://github.com/wg1337/omp-gta-popcycle and https://github.com/wg1337/omp-gta-map-zon

# How to use it?

1) Place "info.zon" in your "scriptfiles/" folder

2) Include it in your script:
```
#include <omp_gta_info_zon>

public OnFilterScriptInit() {
    ....
    if(!LoadInfoZon()) {
        print("ERROR: Failed to load info.zon");
        return false;
    }
    ....
    return true;
}
```

3) Use the provided functions

# Example
```
#include <omp_gta_info_zon>
#include <omp_gta_peds_ide>

static bool:IsPedRaceAllowedInZone(zone, E_GTA_PEDS_IDE_RACE:race) {
    if(race == GTA_PEDS_IDE_RACE_DEFAULT)
        return true;

    switch(GetInfoZonPopulationRace(zone)) {
        case GTA_POPCYCLE_RACES_DEFAULT: {
            return true;
        }

        case GTA_POPCYCLE_RACES_BLACK: {
            return race == GTA_PEDS_IDE_RACE_BLACK;
        }

        case GTA_POPCYCLE_RACES_HISPANIC_BLACK: {
            return (race == GTA_PEDS_IDE_RACE_HISPANIC || race == GTA_PEDS_IDE_RACE_BLACK
            );
        }

        case GTA_POPCYCLE_RACES_HISPANIC_WHITE: {
            return (race == GTA_PEDS_IDE_RACE_HISPANIC || race == GTA_PEDS_IDE_RACE_WHITE
            );
        }

        case GTA_POPCYCLE_RACES_ORIENTAL_WHITE: {
            return (race == GTA_PEDS_IDE_RACE_ORIENTAL || race == GTA_PEDS_IDE_RACE_WHITE
            );
        }
    }

    return false;
}

stock bool:IsPedModelRaceAllowedInZone(modelid, zone) {
    new E_GTA_PEDS_IDE_RACE:race = GetPedIdeRaceByModel(modelid);
    return IsPedRaceAllowedInZone(zone, race);
}
```
