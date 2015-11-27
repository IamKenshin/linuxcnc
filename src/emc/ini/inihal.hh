/*----------------------------------------------------------------------
This work derived from alex joni's halui.cc
Copyright: 2013,2014
Author:    Dewey Garrett <dgarrett@panix.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
----------------------------------------------------------------------*/
#ifndef INIHAL_H
#define INIHAL_H
#include "hal.h"
#include "emcmotcfg.h"

int check_ini_hal_items();
int ini_hal_init(void);
int ini_hal_exit(void);
int ini_hal_init_pins(void);

/* not doing these fields (yet,ever?):
[TRAJ]COORDINATES
[TRAJ]LINEAR_UNITS
[TRAJ]ANGULAR_UNITS
[JOINT_n]TYPE
[JOINT_n]UNITS
[JOINT_n]HOME
[JOINT_n]HOME_OFFSET
[JOINT_n]HOME_SEARCH_VEL
[JOINT_n]HOME_LATCH_VEL
[JOINT_n]HOME_FINAL_VEL
[JOINT_n]HOME_IS_SHARED
[JOINT_n]HOME_USE_INDEX
[JOINT_n]HOME_IGNORE_LIMITS
[JOINT_n]HOME_SEQUENCE
[JOINT_n]VOLATILE_HOME
[JOINT_n]LOCKING_INDEXER
[JOINT_n]COMP_FILE_TYPE
[JOINT_n]COMP
*/
#define HAL_FIELDS \
    FIELD(hal_float_t,traj_default_velocity) \
    FIELD(hal_float_t,traj_max_velocity) \
    FIELD(hal_float_t,traj_default_acceleration) \
    FIELD(hal_float_t,traj_max_acceleration) \
\
    FIELD(hal_bit_t,traj_arc_blend_enable) \
    FIELD(hal_bit_t,traj_arc_blend_fallback_enable) \
    FIELD(hal_s32_t,traj_arc_blend_optimization_depth) \
    FIELD(hal_float_t,traj_arc_blend_gap_cycles) \
    FIELD(hal_float_t,traj_arc_blend_ramp_freq) \
    FIELD(hal_float_t,traj_arc_blend_tangent_kink_ratio) \
\
    ARRAY(hal_float_t,backlash,EMCMOT_MAX_JOINTS) \
    ARRAY(hal_float_t,min_limit,EMCMOT_MAX_JOINTS) \
    ARRAY(hal_float_t,max_limit,EMCMOT_MAX_JOINTS) \
    ARRAY(hal_float_t,max_velocity,EMCMOT_MAX_JOINTS) \
    ARRAY(hal_float_t,max_acceleration,EMCMOT_MAX_JOINTS) \
    ARRAY(hal_float_t,ferror,EMCMOT_MAX_JOINTS) \
    ARRAY(hal_float_t,min_ferror,EMCMOT_MAX_JOINTS) \

struct PTR {
    template<class T>
    struct field { typedef T *type; };
};

template<class T> struct NATIVE {};
template<> struct NATIVE<hal_bit_t> { typedef bool type; };
template<> struct NATIVE<hal_s32_t> { typedef rtapi_s32 type; };
template<> struct NATIVE<hal_u32_t> { typedef rtapi_u32 type; };
template<> struct NATIVE<hal_float_t> { typedef double type; };
struct VALUE {
    template<class T> struct field { typedef typename NATIVE<T>::type type; };
};

template<class T>
struct inihal_base
{
#define FIELD(t,f) typename T::template field<t>::type f;
#define ARRAY(t,f,n) typename T::template field<t>::type f[n];
HAL_FIELDS
#undef FIELD
#undef ARRAY
};

typedef inihal_base<PTR> ptr_inihal_data;
typedef inihal_base<VALUE> value_inihal_data;

#endif
