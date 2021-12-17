#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "std_srvs/Empty.h"
#include "second_assignment/UserInput.h"

ros::Publisher pub;
ros::ServiceClient client;

int i;
int counter=0;

void baseCallback(const sensor_msgs::LaserScan::ConstPtr& msg) // constant pointer for the callback
{
    int size = msg->ranges.size();
    char user_req;
    float dist[size], min1, min2, min3, min4, min5;
    float left_bottom[91], left_mid[180], front[180], right_mid[180], right_bottom[90];

    second_assignment::UserInput us_inp;

    geometry_msgs::Twist my_vel;

    //Assigning to a float array.
    for ( i = 0 ; i < size ; i++ )  dist[i] = msg->ranges[i];

    // Subsectioning hint is used, here are the subsections.
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

    // minimum front is written
    // ROS_INFO("MINIMUM FRONT IS   %f  ", min3);

    // if front is close, stop first
    if (min3 < 1.0956){ // 1.1003 returned at second...
        my_vel.linear.x = 0.0;
        my_vel.linear.y = 0.0;
        
        // then check right mid and left mid. make a turn to the other side
        if (min4 < min2){
            ROS_INFO("DIFFERENCE IS %f  ", min2-min4);
            my_vel.angular.z = -100.0; //used to be 100 and working great with integers
            pub.publish(my_vel);
            counter++;
        }

        else {
            my_vel.angular.z = 100.0;
            pub.publish(my_vel);
        }
               // angular 500 is full rotation. 180 degree. 250 = 90 degree
    }
    else{
        user_req = us_inp.response.resp[0];
        
        //ROS_INFO("i read   %s  ", us_inp.response.resp[0]);
        ROS_INFO("i read   %c  ", user_req);
        
        if(user_req=='a'){
            my_vel.linear.x +=0.5;
        }
        else if(user_req=='d'){
            my_vel.linear.x -=0.5;
        }
        else{
            my_vel.linear.x = 4.0;
        }
        my_vel.linear.y = 0.0;
        my_vel.angular.z = 0.0;
        pub.publish(my_vel);
    }

}

bool resetCallback(std_srvs::Empty::Request &req,std_srvs::Empty::Response &res){
    //if (counter==10){
        // ROS_INFO_STREAM("Now sending reset command.");
    // }
    return true;
}
int main (int argc, char **argv)
{
	ros::init(argc, argv, "ebru_reader");
	ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("base_scan",1000,baseCallback);
    pub = nh.advertise<geometry_msgs::Twist>("cmd_vel",1);

    ros::ServiceServer reset_service = nh.advertiseService("/reset_positions",&resetCallback);
    client = nh.serviceClient<second_assignment::UserInput>("/elebeleInput");
    
    ros::spin();
	return 0;
}

    //ROS_INFO("in front as well %dth dist is written  %d  ", i+271, dist[i+271]);
        //ROS_INFO("ACTUAL FRONT %dth dist is written  %d  ", i, front[i]);
    