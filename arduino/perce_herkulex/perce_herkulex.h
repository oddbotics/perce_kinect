#include <std_msgs/String.h>
#include <sensor_msgs/JointState.h>
#include <oddbot_msgs/HerkulexCommand.h>
#include <math.h>

ros::NodeHandle  nh;

#define SERVO_PAN 1
#define SERVO_TILT 2 

int rate = 10;
int loop_delay = 100;

bool has_new_servo_command = false;

float pan_servo_position_cmd = 0.0;
float tilt_servo_position_cmd = 0.0;
float pan_servo_position_fdbk = 0.0;
float tilt_servo_position_fdbk= 0.0;
int stat_pan = 0;
int stat_tilt = 0;

float pan_high_bound = 150.0;
float pan_low_bound = -150.0;

float tilt_high_bound = 150.0;
float tilt_low_bound = -150.0;


char *names[] = {"perce_herkulex_pan", "perce_herkulex_tilt"};
float positions[2];
