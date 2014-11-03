#include <std_msgs/String.h>
#include <sensor_msgs/JointState.h>
#include <math.h>

ros::NodeHandle  nh;

int servo_tilt = 1; 
int servo_pan = 2;

int rate = 10;
int loop_delay = 100;

bool has_new_servo_command = false;

float pan_servo_position_cmd;
float tilt_servo_position_cmd;

