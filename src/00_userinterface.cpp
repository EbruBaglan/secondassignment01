#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "std_srvs/Empty.h"
#include "second_assignment/vel.h"
#include "second_assignment/UserInput.h"

ros::Publisher pub;
ros::ServiceClient client_reset;
ros::ServiceClient client_userinp;

char c;

second_assignment::vel vel;

int main(int argc, char **argv)
{
    /* classic entrance. init and node handler. */
    ros::init(argc, argv, "userinterface");
    ros::NodeHandle nh;

    /* reset and command clients are initiated, /vel topic is initiated to send to controller */
    client_reset = nh.serviceClient<std_srvs::Empty>("/reset_positions");
    client_userinp = nh.serviceClient<second_assignment::UserInput>("/service");
    pub = nh.advertise<second_assignment::vel>("/vel", 1);

    /* some more necessary declarations */
    std_srvs::Empty res_ser;
    second_assignment::UserInput user_ser;

    while (ros::ok())
    {
        printf("Enter a for decrease speed, d for speed increase and r for reset position:");
        while ((c = getchar()) != '\n' && c != EOF)
        {
            getchar(); // this extra getchar is to get rid of '\n' at the end. User hits 'enter' after the input command and creates is non-deliberately.
            switch (c) // source: https://stackoverflow.com/questions/25374573/c-problems-with-using-getchar-and-switch-case-to-get-user-input-for-a-main-menu
            {
            case 'a':
            case 'd':
            case 'A':
            case 'D':
                /* increase or decrease command */
                system("clear");
                printf("Enter a for decrease speed, d for speed increase and r for reset position:\n");
                user_ser.request.userinp = c; // request is set
                client_userinp.waitForExistence();
                client_userinp.call(user_ser);          // request is sent
                vel.velnow = user_ser.response.uservel; // response is taken and assigned to topic messages field
                pub.publish(vel);                       // response is published to /vel to controller
                break;
            case 'r':
                /* reset command */
                system("clear");
                printf("Enter a for decrease speed, d for speed increase and r for reset position:\n");
                client_reset.waitForExistence();
                client_reset.call(res_ser);
                break;

            default:
                /* other inputs are ignored */
                system("clear");
                printf("Please enter a for decrease speed, d for speed increase and r for reset position:\n");
                break;
            }
        }
    }

    ros::spin();
    return 0;
}
