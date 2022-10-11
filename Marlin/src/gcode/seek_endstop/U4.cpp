#include "../gcode.h"
#include "../../module/motion.h"
#include "../../module/endstops.h"
#include "../../module/stepper.h"
#include "../../module/planner.h"
#include "../../module/seek_endstops.h"


void GcodeSuite::U4(){

    // if (parser.seenval(axis_codes[0])) {
    //             const float l = parser.value_axis_units((AxisEnum)0);
    //             if(l >170 && l < 200){
    //                  get_endstop_distance(X_AXIS, LS8);
    //             }
    //             else if (l >270 && l < 300){
    //                 get_endstop_distance(X_AXIS, LS4);
    //             }
    // }
    // 120 - 80
    LOOP_LOGICAL_AXES(i) {
        switch (i){
        case 0:
            if (parser.seenval(axis_codes[i])) {
                const float l = parser.value_axis_units((AxisEnum)i);
                if(l >170 && l < 200){
                     get_endstop_distance(X_AXIS, X_MS1_PIN);
                }
            }
            break;

        case 1:
            if (parser.seenval(axis_codes[i])) {
                const float l = parser.value_axis_units((AxisEnum)i);
                if(l > 85 && l < 100){
                    get_endstop_distance(Y_AXIS, Y_MS1_PIN);
                }
            }
            break;
        
        default:
            break;
        }
    }
}