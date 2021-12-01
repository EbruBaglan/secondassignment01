#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"

ros::Publisher pub;
ros::Publisher pub2;
ros::ServiceClient client2;
int count = 10;

void ass2Callback(const turtlesim::Pose::ConstPtr& msg) // constant pointer for the callback
{
	msg->ranges
	
	my_srv::Velocity vel_srv;

	if (count ==10){
		count = 0;

		vel_srv.request.min = 0.0;
		vel_srv.request.max = 1.0;
		client2.waitForExistence();
		client2.call(vel_srv);

		geometry_msgs::Twist my_vel;
	    my_vel.linear.x = vel_srv.response.x;
	    my_vel.angular.z = vel_srv.response.z;

	    pub.publish(my_vel);
	    turtlebot_controller::Vel new_vel;
	    new_vel.name = "linear";
	    new_vel.vel = my_vel.linear.x;
	    pub2.publish(new_vel);



	}
	count = count + 1;


    
}

int main (int argc, char **argv)
{
	// Initialize the node, setup the NodeHandle for handling the communication with the ROS
	//system
	ros::init(argc, argv, "turtlebot_subscriber");
	ros::NodeHandle nh;

	ros::Subscriber sub = nh.subscribe("/basescan", 1,ass2Callback);
	pub = nh.advertise<geometry_msgs::Twist>("rt1_turtle/cmd_vel",1);
	pub2 = nh.advertise<turtlebot_controller::Vel>("/my_vel",1);

	ros::ServiceClient client1 = nh.serviceClient<turtlesim::Spawn>("/spawn");
	client2 = nh.serviceClient<my_srv::Velocity>("/velocity");

	turtlesim::Spawn srv1;

	srv1.request.x = 1.0;
	srv1.request.y = 5.0;
	srv1.request.theta = 0.0;
	srv1.request.name = "rt1_turtle";

	client1.waitForExistence(); // to be sure that service is active
	client1.call(srv1);

    ros::spin();
	return 0;
}
