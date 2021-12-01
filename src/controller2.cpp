//roscore& && roscd second_assignment && rosrun stage_ros stageros $(rospack find second_assignment)/world/my_world.world
//catkin make && rospack profile && rosrun second_assignment ebru_reader
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"

int i;

void baseCallback(const sensor_msgs::LaserScan::ConstPtr& msg) // constant pointer for the callback
{
    int size = msg->ranges.size();
    int dist[size], min1, min2, min3, min4, min5;
    int left_bottom[91], left_mid[180], front[180], right_mid[180], right_bottom[90];

    //Dealing with integer is easier, so ceiling the floats.
    for ( i = 0 ; i < size ; i++ )  dist[i] = ceil(msg->ranges[i]);

    // subsectioning hint is used, here are the subsections.
    for ( i = 0 ; i < 92 ; i++ )    left_bottom[i]  = dist[i];
    for ( i = 0 ; i < 180 ; i++ )   left_mid[i]     = dist[i+91];
    for ( i = 0 ; i < 180 ; i++ )   front[i]        = dist[i+271];
    for ( i = 0 ; i < 180 ; i++ )   right_mid[i]    = dist[i+451];
    for ( i = 0 ; i < 90 ; i++ )    right_bottom[i] = dist[i+631];

    min1 = left_bottom[0];
    for ( i = 0 ; i < 92 ; i++ ){
        if (left_bottom[i] < min1)  min1 = left_bottom[i];
    }
    ROS_INFO("min of left bottom is %d  ", min1);

    min2 = left_mid[0];
    for ( i = 0 ; i < 180 ; i++ ){
        if (left_mid[i] < min2)  min2 = left_mid[i];
    }
    ROS_INFO("min of left mid is %d  ", min2);

    min3 = front[0];
    for ( i = 0 ; i < 180 ; i++ ){
        if (front[i] < min3)  min3 = front[i];
    }
    ROS_INFO("min of front is %d  ", min3);
    
    min4 = right_mid[0];
    for ( i = 0 ; i < 180 ; i++ ){
        if (right_mid[i] < min4)  min4 = right_mid[i];
    }
    ROS_INFO("min of right mid is %d  ", min4);

    min5 = right_bottom[0];
    for ( i = 0 ; i < 180 ; i++ ){
        if (right_bottom[i] < min5)  min5 = right_bottom[i];
    }
    ROS_INFO("min of right bottom is %d  ", min5);

}

int main (int argc, char **argv)
{
	ros::init(argc, argv, "ebru_reader");
	ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("base_scan",1000,baseCallback);

    ros::spin();
	return 0;
}

    //ROS_INFO("in front as well %dth dist is written  %d  ", i+271, dist[i+271]);
        //ROS_INFO("ACTUAL FRONT %dth dist is written  %d  ", i, front[i]);
    