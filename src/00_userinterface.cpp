#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "std_srvs/Empty.h"
#include "second_assignment/UserInput.h"

ros::Publisher pub;
ros::ServiceClient client_reset;
ros::ServiceClient client_userinp;

char c;

int main(int argc, char **argv)
{
    /* classic entrance. init and node handler. */
    ros::init(argc, argv, "userinterface");
    ros::NodeHandle nh;

    /* reset and command clients are initiated */
    client_reset = nh.serviceClient<std_srvs::Empty>("/reset_positions");
    client_userinp = nh.serviceClient<second_assignment::UserInput>("/service");

    /* some more necessary declarations */
    std_srvs::Empty res_ser;
    second_assignment::UserInput user_ser;

    while (ros::ok())
    {
        printf("Enter z to decrease, x to increase speead, r to reset: ");
        system ("/bin/stty raw");
        while (c = getchar())
        {
            //getchar(); // this extra getchar is to get rid of '\n' at the end. User hits 'enter' after the input command and creates is non-deliberately.
            switch (c) // source: https://stackoverflow.com/questions/25374573/c-problems-with-using-getchar-and-switch-case-to-get-user-input-for-a-main-menu
            {
            case 'z':
            case 'Z':
            case 'x':
            case 'X':
                /* increase or decrease command */
                system("clear");
                printf("Enter z to decrease, x to increase speead, r to reset: ");
                user_ser.request.userinp = c; // request is set
                client_userinp.waitForExistence();
                client_userinp.call(user_ser);          // request is sent
                break;
            case 'r':
            case 'R':
                /* reset command */
                system("clear");
                printf("Enter z to decrease, x to increase speead, r to reset: ");
                client_reset.waitForExistence();
                client_reset.call(res_ser);
                break;

            default:
                /* other inputs are ignored */
                system("clear");
                printf("Enter z to decrease, x to increase speead, r to reset: ");
                break;
            }
        }
    }
    system ("/bin/stty cooked");
    return 0;
}
