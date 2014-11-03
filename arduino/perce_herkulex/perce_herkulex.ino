#include <Herkulex.h>

/*
 * rosserial used to communicate with Udoo to control herkulex servos
 * 
 * Author: Chris Dunkers
 * Date: 10/26/2014
 */

#include <ros.h>
#include "perce_herkulex.h"

//callback function for the subscriber
void messageCb( const oddbot_msgs::HerkulexCommand& cmd_msg){
  //store the commands
  int n = 0;
  has_new_servo_command = true;
  int s = sizeof(cmd_msg.name)/sizeof(int);
  for(int i = 0; i < s; i++){
    n = cmd_msg.name[i];
    switch(n){
      case SERVO_PAN: pan_servo_position_cmd = to_degrees(cmd_msg.position[i]);
               break;
      case SERVO_TILT: tilt_servo_position_cmd = to_degrees(cmd_msg.position[i]);
               break;
      default: break;
    }
    n = 0;
  }
}

float to_degrees(float rad){
 
  float deg = rad * (180.0/M_PI);
  return deg;
}

float to_rad(float deg){
 
  float rad = deg * (M_PI/180.0);
  return rad;
}

void check_pan(float * deg){
 if(*deg < pan_low_bound){
  *deg = -150.0; 
 }
 if(*deg > pan_high_bound){
  *deg = 150.0; 
 }  
}

void check_tilt(float * deg){
 if(*deg < tilt_low_bound){
  *deg = -150.0; 
 }
 if(*deg > tilt_high_bound){
  *deg = 150.0; 
 }  
}

// establish a subscriber
ros::Subscriber<oddbot_msgs::HerkulexCommand> command_sub("/perce_herkulex_command", messageCb );

// establish a publisher
sensor_msgs::JointState herkulex_feedback;
ros::Publisher feedback_pub("/perce_herkulex_feedback", &herkulex_feedback);

// setup the ros node
void setup()
{
  nh.initNode();
  nh.advertise(feedback_pub);
  nh.subscribe(command_sub);
  
  //set the desired servo settings
  
  loop_delay = 1000.0/((float)rate);
  
//  herkulex_feedback.name.resize(2);
//  herkulex_feedback.position.resize(2);
  herkulex_feedback.name_length = 2;
  herkulex_feedback.position_length = 2;
  herkulex_feedback.velocity_length = 0; 
  herkulex_feedback.effort_length = 0;
  herkulex_feedback.name = names;
  herkulex_feedback.position = positions;
  
  //init herkulex
  delay(2000);
  Herkulex.beginSerial2(115200);
  Herkulex.reboot(SERVO_PAN);
  Herkulex.reboot(SERVO_TILT);
  delay(500);
  Herkulex.initialize();
  
  //set the servos to the new desired position 
  Herkulex.moveOneAngle(SERVO_PAN, pan_servo_position_cmd, 1000, LED_WHITE);
  Herkulex.moveOneAngle(SERVO_TILT, tilt_servo_position_cmd, 1000, LED_WHITE);
}

// the main loop to control the herkulex servos used for pan and tilt
void loop()
{
  if(has_new_servo_command){
   has_new_servo_command = false;
   check_pan(&pan_servo_position_cmd); //get position for pan servo
   check_tilt(&tilt_servo_position_cmd);
   
   //set the servos to the new desired position 
   Herkulex.moveOneAngle(SERVO_PAN, pan_servo_position_cmd, 1000, LED_WHITE);
   Herkulex.moveOneAngle(SERVO_TILT, tilt_servo_position_cmd, 1000, LED_WHITE);
  }
  
  //if erroring reboot
  stat_pan = Herkulex.stat(SERVO_PAN);
  stat_tilt = Herkulex.stat(SERVO_TILT);
  if(stat_pan != 0){
    //ROS_ERROR("Perception Pan Servo Errored"); 
    Herkulex.clearError(SERVO_PAN);
    Herkulex.reboot(SERVO_PAN);
    delay(500);
    Herkulex.initialize();
  }
  
  if(stat_tilt != 0){
    //ROS_ERROR("Perception Tilt Servo Errored"); 
    Herkulex.clearError(SERVO_TILT);  
    Herkulex.reboot(SERVO_TILT);
    delay(500);
    Herkulex.initialize();  
  }
  
  pan_servo_position_fdbk = Herkulex.getAngle(SERVO_PAN);
  tilt_servo_position_fdbk = Herkulex.getAngle(SERVO_TILT);
  
  //get feedback 
  herkulex_feedback.header.stamp = nh.now();
  herkulex_feedback.position[0] = to_rad(pan_servo_position_fdbk); //get position for pan servo
  herkulex_feedback.position[1] = to_rad(tilt_servo_position_fdbk); //get position for tilt servo

  //publish feedback
  feedback_pub.publish(&herkulex_feedback);  
  
  nh.spinOnce();
  delay(loop_delay);
}
