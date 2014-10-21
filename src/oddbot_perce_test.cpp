#include "perce_kinect/oddbot_perce_test.h"

oddbot_perce_test::oddbot_perce_test(){
	//subscribe to oddbot_boot
	//publish to oddbot_boot_stop
  ros::NodeHandle nodeHandle;
  commandjointstate_pub = nodeHandle.advertise<sensor_msgs::JointState>("jointstate_out", 1000);
  currentjointstate_sub = nodeHandle.subscribe("jointstate_in", 1000, &oddbot_perce_test::get_info, this);
//  subnet = get_subnet();
}
// Callback message
void oddbot_perce_test::get_info(const sensor_msgs::JointState::ConstPtr& jointstate_in_msg){
	ROS_INFO("test");
	ROS_INFO("%lf",jointstate_in_msg->position[0]);
	if(jointstate_in_msg->position.size() > 0){
		ROS_INFO("Getting this joint state: %lf",jointstate_in_msg->position[0]);
	}
}

void oddbot_perce_test::send_jointstate_out(){
  // Set the joint state message
  // just a proof of concept now
  jointstate_out_msg.position.assign(1, 1.0);
  // Publish the jointstate_out
  commandjointstate_pub.publish(jointstate_out_msg);
  //ROS_INFO("commandjointstate_pub sent %lf",jointstate_out_msg.position[0]);
}


int main(int argc, char** argv){
	
	//stop when stop running flag is true
	ros::init(argc, argv, "oddbot_perce_test");

  oddbot_perce_test pt = oddbot_perce_test();
  
  ROS_INFO("perception kinect node started!");  

  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    pt.send_jointstate_out();
    ros::spinOnce();
    loop_rate.sleep();
  }
  
  return 0;
}
