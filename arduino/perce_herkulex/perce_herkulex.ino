/*
 * rosserial used to communicate with Udoo to control herkulex servos
 * 
 * Author: Chris Dunkers
 * Date: 10/26/2014
 */

#include <ros.h>
#include "perce_herkulex.h"

//callback function for the subscriber
void messageCb( const sensor_msgs::JointState& cmd_msg){
  //store the commands
  char *n = 0;
  has_new_servo_command = true;
  int size = sizeof(cmd_msg.name)/sizeof(cmd_msg.name[0]);
  for(int i = 0; i < size; i++){
    n = cmd_msg.name[i];
    switch(n[0]){
      case '1': pan_servo_position_cmd = cmd_msg.position[i];
               break;
      case '2': tilt_servo_position_cmd = cmd_msg.position[i];
               break;
      default: break;
    }
    n = 0;
  }
}

// establish a subscriber
ros::Subscriber<sensor_msgs::JointState> command_sub("/perce_herkulex_command", messageCb );

// establish a publisher
sensor_msgs::JointState herkulex_feedback;
std_msgs::String herkulex_info;
ros::Publisher feedback_pub("/perce_herkulex_feedback", &herkulex_feedback);
ros::Publisher info_pub("/perce_herkulex_info", &herkulex_info);

// setup the ros node
void setup()
{
  nh.initNode();
  nh.advertise(feedback_pub);
  nh.advertise(info_pub);
  nh.subscribe(command_sub);
  
  //access the ros parameter server
  
  //set the desired servo settings
  
  loop_delay = 1000.0/((float)rate);
}

// the main loop to control the herkulex servos used for pan and tilt
void loop()
{
  if(has_new_servo_command){
   has_new_servo_command = false;
   //set the servos to the new desired position 
  }
  
  //publish feedback
  feedback_pub.publish(&herkulex_feedback);  
  
  //publish info
  info_pub.publish(&herkulex_info);
  
  nh.spinOnce();
  delay(loop_delay);
}
