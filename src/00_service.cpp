#include "ros/ros.h"
#include "second_assignment/UserInput.h"

ros::Publisher pub;
ros::ServiceServer vel_service;

float vel_min = 0.0; // without declaring min, robot can turn back after some decrements :D

float vel_now = 1.0; // initial velocity change value
float inc_dec = 0.1; // increment-decrement value

bool serviceCallback(second_assignment::UserInput::Request &req, second_assignment::UserInput::Response &res)
{
    switch (req.userinp) // request is evaluated.
    {
    case 'a':
    case 'A':
        /* increase command */
        if (vel_now > vel_min)
            vel_now = vel_now - inc_dec;
        else
            printf("Sorry you are already too slow, honey.\n");
        break;
    case 'd':
    case 'D':
        /* decrease command */
        vel_now = vel_now + inc_dec;
        break;
    default:
        printf("An undefined service message received. That's weird tbh.\n");
        break;
    }
    res.uservel = vel_now;
    return true;
}

int main(int argc, char **argv)
{
    /* classic entrance. init and node handler. */
    ros::init(argc, argv, "service");
    ros::NodeHandle nh;

    /* service is initiated with callback function. */
    vel_service = nh.advertiseService("/service", serviceCallback);

    ros::spin();
    return 0;
}