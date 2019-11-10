/**
    @file dataset.h

    @brief
    It handles project dataset/parameter sets.

    @author Alfonso, Rudy Manalo
    @version
*/

#ifndef DATASET_H_
#define DATASET_H_

#include "Arduino.h"

/*!
    @defined 
    @abstract Dataset macro definitions
    @dicussion Defines project configuration with regards to dataset handling
*/
#define DS_CONTROLLED_TYPE_NUM_K    5
#define DS_ROBOT_K                  0u
#define DS_DRONE_K                  1u
#define DS_CAR_K                    2u
#define DS_PLANE_K                  3u
#define DS_BOAT_K                   4u
//#define VERSION_SIZE_K            3
// dataset version
//#define DS_VERSION_YEAR_K         0u
//#define DS_VERSION_WEEK_K         0u
//#define DS_VERSION_PATHLEVEL_K    0u
//#define DS_VERSION_STATUS_K       0u
//#define DS_VERSION_LAYOUT_K       0u

//const struct DS_VERSION_st
//{
//    uint8_t  version_u8[VERSION_SIZE_K];
//    uint8_t  status_u8;
 //   uint8_t  layout_u8;
//} DS_VERSION_C = 
//{
//    DS_VERSION_YEAR_K,       // year
//    DS_VERSION_WEEK_K,       // week
//    DS_VERSION_PATHLEVEL_K,  // patch level
//    DS_VERSION__STATUS_K,    // internal status
//    DS_VERSION_LAYOUT_K      // layout
//};


const struct CONTROLLED_OBJECT_TYPE_st
{
    uint8_t    type_u8[DS_CONTROLLED_TYPE_NUM_K];
} CONTROLLED_OBJECT_TYPE_C =
{
    DS_ROBOT_K,
    DS_DRONE_K,
    DS_CAR_K,
    DS_PLANE_K,
    DS_BOAT_K
};

#endif // DATASET_H_