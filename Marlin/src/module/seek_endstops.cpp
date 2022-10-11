#include "motion.h"
#include "endstops.h"
#include "stepper.h"
#include "planner.h"
#include "temperature.h"

#include "../gcode/gcode.h"

#include "../inc/MarlinConfig.h"

bool seek_endstop_flag = false;
AxisEnum seek_endstop_axis;
uint8_t seek_limit_name;

void seek_endstops(const AxisEnum axis, uint8_t limit_name, float limit_position){
    // Get the ABC or XYZ positions in mm
    abce_pos_t target = planner.get_axis_positions_mm();
    const float distance = limit_position - target[axis]; // * (limit_position > target[axis]?1:-1);
    const feedRate_t home_fr_mm_s = homing_feedrate(axis);
    seek_endstop_flag = true;
    seek_endstop_axis = axis;
    seek_limit_name = limit_name;
        

    target[axis] = 0;                         // Set the single homing axis to 0
    planner.set_machine_position_mm(target);  // Update the machine position

    // Set delta/cartesian axes directly
    target[axis] = distance * 1.5f;                  // The move will be towards the endstop, FOS of 1.5 added for maximum distance
    planner.buffer_segment(target, home_fr_mm_s, active_extruder);

    planner.synchronize();

    current_position[axis] = limit_position;
    planner.set_machine_position_mm(current_position);
    update_workspace_offset(axis);
    
    // report_current_position_projected();
}

void get_endstop_distance(const AxisEnum axis, uint8_t limit_name){
  
  homeaxis(axis);
  delay(500);

  int DEFAULT_AXIS_MAX_LENGTH[] = {X_BED_SIZE, Y_BED_SIZE, Z_MAX_POS};
  abce_pos_t target = planner.get_axis_positions_mm();

  target[axis] = DEFAULT_AXIS_MAX_LENGTH[axis];
  const feedRate_t home_fr_mm_s = homing_feedrate(axis);
  seek_endstop_flag = true;
  seek_endstop_axis = axis;
  seek_limit_name = limit_name;
        
  planner.buffer_segment(target, home_fr_mm_s, active_extruder);
  planner.synchronize();
  update_workspace_offset(axis);
  SERIAL_ECHO("Distance: ");
  report_real_position();

  delay(500);
  homeaxis(axis); //added to return back to home position after calculating distance
}