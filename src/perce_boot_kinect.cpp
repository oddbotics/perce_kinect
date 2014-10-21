#include "perce_kinect/perce_boot_kinect.h"


perce_boot_kinect::perce_boot_kinect(){
	//subscribe to oddbot_boot
	//publish to oddbot_boot_stop
  ros::NodeHandle nodeHandle;
  boot_pub = nodeHandle.advertise<oddbot_msgs::OddbotBoot>("boot", 1000);
  stop_sub = nodeHandle.subscribe("boot_stop", 1000, &perce_boot_kinect::get_info, this);
  subnet = get_subnet();
}
// Callback message
void perce_boot_kinect::get_info(const oddbot_msgs::OddbotBootStop::ConstPtr& stop_msg){
	
	//check my IP address	
	if (stop_msg->subnet == subnet) {
    //set stop running flag
    subnet_msg_stop = true;
  }
}

void perce_boot_kinect::send_info(){
  // Set the subnet
  module_info_msg.subnet = subnet;
	// Publish the subnet
  boot_pub.publish(module_info_msg);
}

bool perce_boot_kinect::get_subnet_msg_stop() {
  return subnet_msg_stop;
}


int main(int argc, char** argv){
	
	//stop when stop running flag is true
	ros::init(argc, argv, "perce_boot_kinect");

  perce_boot_kinect module = perce_boot_kinect();
  
  ROS_INFO("perception boot kinect node started!");  

  ros::Rate loop_rate(10);

  while (ros::ok() && !module.get_subnet_msg_stop())
  {
    module.send_info();
    ros::spinOnce();
    loop_rate.sleep();
  }
  
  return 0;
}
