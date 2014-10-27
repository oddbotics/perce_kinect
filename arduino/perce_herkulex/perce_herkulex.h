#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <sensor_msgs/JointState.h>

ros::NodeHandle  nh;

int servo_tilt = 1; 
int servo_pan = 2;

int rate = 10;
int loop_delay = 100;

bool has_new_servo_command = false;

int pan_servo_position_cmd;
int tilt_servo_position_cmd;
