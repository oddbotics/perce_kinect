/*
 * \oddbot_perc_test_reverse.h
 *
 * \author Mitch Kosowski, CMU - mkosowsk@andrew.cmu.edu
 * \date October 20, 2014
 */

#ifndef ODDBOT_PERCE_TEST_REVERSE_H_
#define ODDBOT_PERCE_TEST_REVERSE_H_

#include "ros/ros.h"
#include "sensor_msgs/JointState.h"

class oddbot_perce_test_reverse{
	public:
		oddbot_perce_test_reverse();
		void send_jointstate_out();
	private:
		
		sensor_msgs::JointState jointstate_out_msg;
		ros::Publisher commandjointstate_pub;
		ros::Subscriber currentjointstate_sub;
		void get_info(const sensor_msgs::JointState::ConstPtr& jointstate_in_msg);
		int subnet;
};

int main(int argc, char** argv);

#endif
