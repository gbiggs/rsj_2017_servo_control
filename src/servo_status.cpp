// Copyright 2017 Geoffrey Biggs

#include <ros/ros.h>
#include <dynamixel_msgs/JointState.h>

#include <string>

void callback(const dynamixel_msgs::JointState::ConstPtr &msg) {
  ROS_INFO("--- Servo status ---");
  ROS_INFO("Name: %s", msg->name.c_str());
  ROS_INFO("ID: %d", msg->motor_ids[0]);
  ROS_INFO("Temperature: %d", msg->motor_temps[0]);
  ROS_INFO("Goal position: %f", msg->goal_pos);
  ROS_INFO("Current position: %f", msg->current_pos);
  ROS_INFO("Position error: %f", msg->error);
  ROS_INFO("Velocity: %f", msg->velocity);
  ROS_INFO("Load: %f", msg->load);
  ROS_INFO("Moving: %s", msg->is_moving ? "yes" : "no");
  ROS_INFO("");
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "servo_status");
  ros::NodeHandle node;

  std::string servo_status_topic;
  ros::param::param<std::string>(
    "~servo_status_topic",
    servo_status_topic,
    "/finger_servo_controller/state");

  ros::Subscriber pub = node.subscribe<dynamixel_msgs::JointState>(
    servo_status_topic,
    10,
    callback);

  ros::spin();

  return 0;
}
