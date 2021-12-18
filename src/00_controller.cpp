#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "second_assignment/UserInput.h"
#include "std_srvs/Empty.h"

ros::ServiceServer vel_service;

ros::Publisher pub;

float vel_min = -3.5; // without declaring min, robot can turn back after some decrements :D

float vel_now = 1.0; // initial velocity change value
float inc_dec = 0.5; // increment-decrement value

// subsectioning and taking the min
float subsections(int start, int end, float dist[])
{
    int min;
    int size = end - start + 1;
    float subs[size];
    for (int i = 0; i < size; i++)
    {
        subs[i] = dist[i + start];
    }
    min = subs[0];
    for (int i = 0; i < size; i++)
    {
        if (subs[i] < min)
            min = subs[i];
    }
    return min;
}

void baseCallback(const sensor_msgs::LaserScan::ConstPtr &msg) // constant pointer for the callback
{
    int i;
    int size = msg->ranges.size();
    char user_req;
    float dist[size], min2, min3, min4;
    float left_bottom[91], left_mid[180], front[180], right_mid[180], right_bottom[90];

    second_assignment::UserInput us_inp;

    geometry_msgs::Twist my_vel;

    // Assigning to a float array.
    for (i = 0; i < size; i++)
        dist[i] = msg->ranges[i];

    // Subsectioning hint is used, here are the subsections' mins.
    min2 = subsections(91, 270, dist);  // left_mid 180
    min3 = subsections(271, 450, dist); // front 180
    min4 = subsections(451, 630, dist); // right_mid 180

    // if front is close, stop first
    if (min3 < 0.5)
    { // 1.1003 returned at second... ///1.0956 worked usuallybut...
        my_vel.linear.x = 0.5;
        my_vel.linear.y = 0.5;

        // then check right mid and left mid. make a turn to the other side
        if (min4 < min2)
        {
            my_vel.angular.z = -120.0;
            pub.publish(my_vel);
        }

        else
        {
            my_vel.angular.z = 120.0;
            pub.publish(my_vel);
        }
        // angular 500 is full rotation. 180 degree. 250 = 90 degree
    }
    else
    {
        my_vel.linear.x = 3.5 + vel_now; // user's wish have been realized. user feels acknowledged. user is happy.
        my_vel.linear.y = 0.0;           // https://www.youtube.com/watch?v=dU6EMlfjPFA
        my_vel.angular.z = 0.0;
        pub.publish(my_vel);
    }
}

bool serviceCallback(second_assignment::UserInput::Request &req, second_assignment::UserInput::Response &res)
{
    switch (req.userinp) // request is evaluated.
    {
    case 'x':
    case 'X':
        /* increase command */
        vel_now = vel_now + inc_dec;
        break;
    case 'z':
    case 'Z':
        /* decrease command */
        if (vel_now > vel_min)
            vel_now = vel_now - inc_dec;
        else
            printf("Sorry you are already too slow, honey.\n");
        break;
    default:
        vel_now = vel_now;
        break;
    }
    res.uservel = vel_now;
    return true;
}

int main(int argc, char **argv)
{
    /* classic entrance. init and node handler. */
    ros::init(argc, argv, "controller");
    ros::NodeHandle nh;

    /* /base_scan topic is subscribed. */
    ros::Subscriber sub = nh.subscribe("/base_scan", 1000, baseCallback);

    /* service is initiated with callback function. */
    vel_service = nh.advertiseService("/service", serviceCallback);

    /* publishing to the robot's /cmd_vel topic */
    pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

    ros::spin();
    return 0;
}