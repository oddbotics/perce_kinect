#include "perce_kinect/brain_perce_test.h"

oddbot_perce_test_reverse::oddbot_perce_test_reverse(){
	//subscribe to oddbot_boot
	//publish to oddbot_boot_stop
  ros::NodeHandle nodeHandle;
  commandjointstate_pub = nodeHandle.advertise<sensor_msgs::JointState>("jointstate_in", 1000);
  currentjointstate_sub = nodeHandle.subscribe("jointstate_out", 1000, &oddbot_perce_test_reverse::get_info, this);
//  subnet = get_subnet();
}
// Callback message
void oddbot_perce_test_reverse::get_info(const sensor_msgs::JointState::ConstPtr& jointstate_in_msg){
	if(jointstate_in_msg->position.size() > 0){
		ROS_INFO("Getting this joint state: %lf",jointstate_in_msg->position[0]);
	}
}

void oddbot_perce_test_reverse::send_jointstate_out(){
  // Set the joint state message
  // just a proof of concept now
  jointstate_out_msg.position.assign(1, 3.0);
  // Publish the jointstate_out
  commandjointstate_pub.publish(jointstate_out_msg);
  ROS_INFO("sending %lf",jointstate_out_msg.position[0]);
}


int main(int argc, char** argv){
	
	//stop when stop running flag is true
	ros::init(argc, argv, "oddbot_perce_test_reverse");

  oddbot_perce_test_reverse pt = oddbot_perce_test_reverse();
  
  ROS_INFO("reverse perception kinect node started!");  

  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    pt.send_jointstate_out();
    ros::spinOnce();
    loop_rate.sleep();
  }
  
  return 0;
}
