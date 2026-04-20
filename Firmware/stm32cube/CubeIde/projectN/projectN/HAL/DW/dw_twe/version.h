/*! ------------------------------------------------------------------------------------------------------------------
 * @file    version.h
 * @brief    RTLS version number
 *             Construct the version name as "MAJOR.MINOR.PATCH+YYMMDD"
 *             VER_MAJOR 0..999
 *             VER_MINOR 0..999
 *            VER_PATCH 0..999
 *
 * @attention
 *
 * Copyright 2018 (c) DecaWave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 * @author
 */

#ifndef __VERSION__H__
#define __VERSION__H__

#ifdef __cplusplus
 extern "C" {
#endif


#define VER_MAJOR     4
#define VER_MINOR     1
#define VER_PATCH     0

/**
 * if VER_PATCH is 0, the version will be constructed as
 * to "MAJOR.MINOR.PATCH"
 *
 * if VER_PATCH is set, the version will be constructed as
 * to "MAJOR.MINOR.PATCH+YYMMDD"
 * e.g.    "Oct  7 2016" => "161007"
 **/

#define YEAR_CH2 (__DATE__[ 9])
#define YEAR_CH3 (__DATE__[10])

#define MONTH_IS_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
#define MONTH_IS_FEB (__DATE__[0] == 'F')
#define MONTH_IS_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
#define MONTH_IS_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p')
#define MONTH_IS_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
#define MONTH_IS_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
#define MONTH_IS_JUL (__DATE__[0] == 'J' && __DATE__[2] == 'l')
#define MONTH_IS_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u')
#define MONTH_IS_SEP (__DATE__[0] == 'S')
#define MONTH_IS_OCT (__DATE__[0] == 'O')
#define MONTH_IS_NOV (__DATE__[0] == 'N')
#define MONTH_IS_DEC (__DATE__[0] == 'D')

#define MONTH_CH0 ((MONTH_IS_OCT || MONTH_IS_NOV || MONTH_IS_DEC) ? '1' : '0')

#define MONTH_CH1 \
    (   (MONTH_IS_JAN) ? '1' : \
        (MONTH_IS_FEB) ? '2' : \
        (MONTH_IS_MAR) ? '3' : \
        (MONTH_IS_APR) ? '4' : \
        (MONTH_IS_MAY) ? '5' : \
        (MONTH_IS_JUN) ? '6' : \
        (MONTH_IS_JUL) ? '7' : \
        (MONTH_IS_AUG) ? '8' : \
        (MONTH_IS_SEP) ? '9' : \
        (MONTH_IS_OCT) ? '0' : \
        (MONTH_IS_NOV) ? '1' : \
        (MONTH_IS_DEC) ? '2' : \
        /* default */    '?' \
    )

#define DAY_CH0 ((__DATE__[4] >= '0') ? (__DATE__[4]) : '0')
#define DAY_CH1 (__DATE__[ 5])


#if VER_MAJOR > 100
 #define VMAJOR ((VER_MAJOR / 100) + '0'),\
                   (((VER_MAJOR % 100) / 10) + '0'),\
                   ((VER_MAJOR % 10) + '0')
#elif VER_MAJOR > 10
 #define VMAJOR ((VER_MAJOR / 10) + '0'),\
                   ((VER_MAJOR % 10) + '0')
#else
 #define VMAJOR (VER_MAJOR + '0')
#endif

#if VER_MINOR > 100
 #define VMINOR ((VER_MINOR / 100) + '0'),\
                     (((VER_MINOR % 100) / 10) + '0'),\
                     ((VER_MINOR % 10) + '0')
#elif VER_MINOR > 10
 #define VMINOR ((VER_MINOR / 10) + '0'),\
                   ((VER_MINOR % 10) + '0')
#else
 #define VMINOR (VER_MINOR + '0')
#endif

#if VER_PATCH > 100
 #define VPATCH ((VER_PATCH / 100) + '0'),\
                     (((VER_PATCH % 100) / 10) + '0'),\
                     ((VER_PATCH % 10) + '0')
#elif VER_PATCH > 10
 #define VPATCH ((VER_PATCH / 10) + '0'),\
                   ((VER_PATCH % 10) + '0')
#else
 #define VPATCH (VER_PATCH + '0')
#endif

/* VERSION */
#if(VER_PATCH ==0)

     #define FULL_VERSION { VMAJOR, '.', VMINOR, '.', VPATCH, '\0' }
#else

    #define FULL_VERSION { VMAJOR, '.', VMINOR, '.', VPATCH, '+',\
                      YEAR_CH2, YEAR_CH3, \
                      MONTH_CH0, MONTH_CH1, \
                      DAY_CH0, DAY_CH1,\
                     '\0' }
#endif

#define DATE_VERSION { YEAR_CH2, YEAR_CH3, MONTH_CH0, MONTH_CH1, DAY_CH0, DAY_CH1, '\0' }

#ifdef __cplusplus
}
#endif

#endif /* __VERSION__H__ */
