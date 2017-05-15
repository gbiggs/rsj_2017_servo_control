// Copyright 2017 Geoffrey Biggs

#include <ros/ros.h>
#include <std_msgs/Float64.h>

#include <string>
#include <vector>

int main(int argc, char **argv) {
  ros::init(argc, argv, "set_servo_pos");
  ros::NodeHandle node;

  std::string servo_command_topic;
  ros::param::param<std::string>(
    "~servo_command_topic",
    servo_command_topic,
    "/finger_servo_controller/command");

  ros::Publisher pub = node.advertise<std_msgs::Float64>(servo_command_topic, 1);

  std::vector<std::string> my_args;
  ros::removeROSArgs(argc, argv, my_args);
  if (my_args.size() < 2) {
    ROS_FATAL("Usage: rosrun set_servo_pos [position]");
    ros::shutdown();
    return 1;
  }
  std_msgs::Float64 servo_pos;
  servo_pos.data = std::stof(my_args[1]);

  ROS_INFO("Setting servo position to %f", servo_pos.data);
  ros::Rate r(1);
  while (ros::ok()) {
    pub.publish(servo_pos);
    ros::spinOnce();
    r.sleep();
  }

  return 0;
}
