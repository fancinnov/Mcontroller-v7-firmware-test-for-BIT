/*
 * declination.h
 *
 *  Created on: 2022年10月17日
 *      Author: 25053
 */
#pragma once

#ifndef INCLUDE_COMPASS_DECLINATION_H_
#define INCLUDE_COMPASS_DECLINATION_H_

#include "common.h"

class Declination
{
public:
    /*
     * Calculates the magnetic intensity, declination and inclination at a given WGS-84 latitude and longitude.
     * Assumes a WGS-84 height of zero
     * latitude and longitude have units of degrees
     * declination and inclination are returned in degrees
     * intensity is returned in Gauss
     * Boolean returns false if latitude and longitude are outside the valid input range of +-60 latitude and +-180 longitude
    */
    static bool get_mag_field_ef(float latitude_deg, float longitude_deg, float &intensity_gauss, float &declination_deg, float &inclination_deg);

    /*
      get declination in degrees for a given latitude_deg and longitude_deg
     */
    static float get_declination(float latitude_deg, float longitude_deg);

private:
    static const float SAMPLING_RES;
    static const float SAMPLING_MIN_LAT;
    static const float SAMPLING_MAX_LAT;
    static const float SAMPLING_MIN_LON;
    static const float SAMPLING_MAX_LON;

    static const float declination_table[19][37];
    static const float inclination_table[19][37];
    static const float intensity_table[19][37];
};


#endif /* INCLUDE_COMPASS_DECLINATION_H_ */
