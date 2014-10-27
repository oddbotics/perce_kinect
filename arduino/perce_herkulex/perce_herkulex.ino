/*
 * rosserial used to communicate with Udoo to control herkulex servos
 * 
 * Author: Chris Dunkers
 * Date: 10/26/2014
 */

#include <ros.h>
#include "perce_herkulex.h"

void messageCb( const sensor_msgs::JointState& toggle_msg){
  //store the commands
  has_new_servo_command = true;
}

ros::Subscriber<sensor_msgs::JointState> command_sub("/perce_herkulex_command", messageCb );

sensor_msgs::JointState herkulex_feedback;
std_msgs::String herkulex_info;
ros::Publisher feedback_pub("/perce_herkulex_feedback", &herkulex_feedback);
ros::Publisher info_pub("/perce_herkulex_info", &herkulex_info);


void setup()
{
  nh.initNode();
  nh.advertise(feedback_pub);
  nh.advertise(info_pub);
  nh.subscribe(command_sub);
  
  //access the ros parameter server
  
  loop_delay = 1000.0/((float)rate);
  
  //set the desired servo settings
}

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
