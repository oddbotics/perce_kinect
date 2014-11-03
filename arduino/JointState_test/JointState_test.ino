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
  //make sure to deal with float 64 values (especially negatives
  //deal with array of strings and values up to 255 
//  pan_servo_position_cmd = to_degrees(cmd_msg.position[i]);
//  tilt_servo_position_cmd = to_degrees(cmd_msg.position[i]);
}

float to_degrees(float rad){
 
  float deg = rad * (180.0/M_PI);
  return deg;
}

float to_rad(float deg){
 
  float rad = deg * (M_PI/180.0);
  return rad;
}

// establish a subscriber
ros::Subscriber<sensor_msgs::JointState> command_sub("/perce_herkulex_command", messageCb );

// establish a publisher
sensor_msgs::JointState herkulex_feedback;
ros::Publisher feedback_pub("/perce_herkulex_feedback", &herkulex_feedback);

// setup the ros node
void setup()
{
  nh.initNode();
  nh.advertise(feedback_pub);
  nh.advertise(info_pub);
  nh.subscribe(command_sub);
  
  //set the desired servo settings
  
  loop_delay = 1000.0/((float)rate);
  
  herkulex_feedback.name.resize(2);
  herkulex_feedback.position.resize(2);
  herkulex_feedback.name[0] = "perce_herkulex_pan";
  herkulex_feedback.name[1] = "perce_herkulex_tilt";
}

// the main loop to control the herkulex servos used for pan and tilt
void loop()
{
  if(has_new_servo_command){
   has_new_servo_command = false;
   //set the servos to the new desired position 
  }
  
  //get feedback 
  herkulex_feedback.header.stamp = ros::Time::now();
  herkulex_feedback.position[0] = 0.0; //get position for pan servo
  herkulex_feedback.position[1] = 0.0; //get position for tilt servo

  //publish feedback
  feedback_pub.publish(&herkulex_feedback);  
  
  nh.spinOnce();
  delay(loop_delay);
}
