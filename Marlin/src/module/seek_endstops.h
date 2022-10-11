#pragma once

/**
 * motion.h
 *
 * High-level motion commands to feed the planner
 * Some of these methods may migrate to the planner class.
 */

#include "../inc/MarlinConfig.h"

extern bool seek_endstop_flag;
extern AxisEnum seek_endstop_axis;
extern uint8_t seek_limit_name;
void seek_endstops(const AxisEnum axis, uint8_t limit_name, float limit_position);
void get_endstop_distance(const AxisEnum axis, uint8_t limit_name);

