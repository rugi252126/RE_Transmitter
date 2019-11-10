/**
    @file logistic_data.h

    @brief
    It handles the project logistic information versioning.


    @author Alfonso, Rudy Manalo
    @version
*/

#ifndef RE_LOGISTICDATA_H_
#define RE_LOGISTICDATA_H_

#include "Arduino.h"


/*!
    @defined 
    @abstract Project versionning macro definitions
    @dicussion Defines project versioning information
*/
#define VERSION_SIZE_K            3
// SW version
#define SW_VERSION_YEAR_K         19u
#define SW_VERSION_WEEK_K         45u
#define SW_VERSION_PATHLEVEL_K    0u
#define SW_VERSION_STATUS_K       0u
// HW version
#define HW_VERSION_YEAR_K         19u
#define HW_VERSION_WEEK_K         30u
#define HW_VERSION_PATHLEVEL_K    0u
#define HW_VERSION_STATUS_K       0u





const struct SW_VERSION_st
{
    uint8_t  version_u8[VERSION_SIZE_K];
    uint8_t  status_u8;
} SW_VERSION_C =
{
    SW_VERSION_YEAR_K,      // year
    SW_VERSION_WEEK_K,      // week
    SW_VERSION_PATHLEVEL_K, // patch level
    SW_VERSION_STATUS_K     // internal status
};


const struct HW_VERSION_st
{
    uint8_t  version_u8[VERSION_SIZE_K];
    uint8_t  status_u8;
} HW_VERSION_C =
{
    HW_VERSION_YEAR_K,      // year
    HW_VERSION_WEEK_K,      // week
    HW_VERSION_PATHLEVEL_K, // patch level
    HW_VERSION_STATUS_K     // internal status
};

#endif // RE_LOGISTICDATA_H_