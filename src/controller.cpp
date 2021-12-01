//roscore& && roscd second_assignment && rosrun stage_ros stageros $(rospack find second_assignment)/world/my_world.world
//catkin make && rospack profile && rosrun second_assignment ebru_reader
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"

ros::Publisher pub;

int i;

void baseCallback(const sensor_msgs::LaserScan::ConstPtr& msg) // constant pointer for the callback
{
    int size = msg->ranges.size();
    int dist[size], min1, min2, min3, min4, min5;
    int left_bottom[91], left_mid[180], front[180], right_mid[180], right_bottom[90];

    geometry_msgs::Twist my_vel;

    //Dealing with integer is easier, so ceiling the floats.
    for ( i = 0 ; i < size ; i++ )  dist[i] = ceil(msg->ranges[i]);

    // subsectioning hint is used, here are the subsections.
    for ( i = 0 ; i < 92 ; i++ )    left_bottom[i]  = dist[i];
    for ( i = 0 ; i < 180 ; i++ )   left_mid[i]     = dist[i+91];
    for ( i = 0 ; i < 180 ; i++ )   front[i]        = dist[i+271];
    for ( i = 0 ; i < 180 ; i++ )   right_mid[i]    = dist[i+451];
    for ( i = 0 ; i < 90 ; i++ )    right_bottom[i] = dist[i+631];

    // minimums of each section are obtained
    min1 = left_bottom[0];
    for ( i = 0 ; i < 92 ; i++ ){   if (left_bottom[i] < min1)  min1 = left_bottom[i];}
    
    min2 = left_mid[0];
    for ( i = 0 ; i < 180 ; i++ ){  if (left_mid[i] < min2)  min2 = left_mid[i];}

    min3 = front[0];
    for ( i = 0 ; i < 180 ; i++ ){  if (front[i] < min3)  min3 = front[i];}

    min4 = right_mid[0];
    for ( i = 0 ; i < 180 ; i++ ){  if (right_mid[i] < min4)  min4 = right_mid[i];}

    min5 = right_bottom[0];
    for ( i = 0 ; i < 180 ; i++ ){  if (right_bottom[i] < min5)  min5 = right_bottom[i]; }

    ROS_INFO("MINIMUM FRONT IS   %d  ", min3);

    if (min3 < 2){
        my_vel.linear.x = 0.0;
        my_vel.linear.y = 0.0;

        if (min4 < min2){
            my_vel.angular.z = -100.0;
            pub.publish(my_vel);
        }

        else {
            my_vel.angular.z = 100.0;
            pub.publish(my_vel);
        }
               // angular 500 is full rotation. 180 degree. 250 = 90 degree
    }
    else{
        my_vel.linear.x = 4.0;
        my_vel.linear.y = 0.0;
        my_vel.angular.z = 0.0;
        pub.publish(my_vel);
    }

}

int main (int argc, char **argv)
{
	ros::init(argc, argv, "ebru_reader");
	ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("base_scan",1000,baseCallback);
    pub = nh.advertise<geometry_msgs::Twist>("cmd_vel",1);

    ros::spin();
	return 0;
}

    //ROS_INFO("in front as well %dth dist is written  %d  ", i+271, dist[i+271]);
        //ROS_INFO("ACTUAL FRONT %dth dist is written  %d  ", i, front[i]);
    