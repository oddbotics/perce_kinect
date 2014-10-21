/*
 * \perce_boot_kinect.h
 *
 * \author Chris Dunkers, CMU - cmdunkers@cmu.edu
 * \date October 13, 2014
 */

#ifndef PERCE_BOOT_KINECT_H_
#define PERCE_BOOT_KINECT_H_

#include "ros/ros.h"
#include "oddbot_msgs/OddbotBoot.h"
#include "oddbot_msgs/OddbotBootStop.h"
#include "oddbot_lib/get_subnet.h"


class perce_boot_kinect{
	public:
		perce_boot_kinect();
		bool get_subnet_msg_stop();
		void send_info();
	private:
		bool subnet_msg_stop;
		oddbot_msgs::OddbotBoot module_info_msg;
		ros::Publisher boot_pub;
		ros::Subscriber stop_sub;
		void get_info(const oddbot_msgs::OddbotBootStop::ConstPtr& stop_msg);
		int subnet;
};

int main(int argc, char** argv);

#endif
