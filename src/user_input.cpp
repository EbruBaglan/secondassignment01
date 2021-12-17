#include "ros/ros.h"
#include "std_msgs/String.h"
#include "second_assignment/UserInput.h"

ros::Publisher pub;
std::string inputString;

bool ere(second_assignment::UserInput::Request &req, second_assignment::UserInput::Response &res){
    req.req = inputString;
    std::cout << "2.req.req assigned as\n" << req.req;
    if (req.req.compare("a")==0 || req.req.compare("s")==0 || req.req.compare("d")==0 )
        res.resp = req.req;
    else
        std::cout << "Else e geldin bebos\n";
    return true;
}


int main(int argc, char** argv){
    while(true){
    ros::init(argc, argv, "UserInput");
	ros::NodeHandle nh;   
    
    std::cout << "Please enter a for decrease speed, d for speed increase and s for reset position:";
    std::getline(std::cin, inputString);
    
    std::cout << "1.You entered  " << inputString <<"\n";
    
    ros::ServiceServer service = nh.advertiseService("/UserInput", ere);
    
    std::cout << "5.funccalled\n";

    ros::spinOnce();}
    return 0;
}


/*
The important point to keep in mind is that your subscriber will receive nothing
until you call spin or spinOnce. In your code, you block waiting for user input before calling spinOnce,
so you receive nothing. Place the spinOnce before the std::getline.
https://answers.ros.org/question/190877/getting-messages-after-an-user-input/


A code here:
cout << "Type a number: "; // Type a number and press enter
    cin >> x; // Get user input from the keyboard
    cout << "Your number is: " << x; // Display the input value 

    pub = nh.advertise<geometry_msgs::Twist>("cmd_vel",1);

    ros::Spin();

    return 0;


    Another code
    #include <ros/ros.h>
    #include <std_msgs/String.h>

    int main(int argc, char** argv)
    {
  ros::init(argc, argv, "test");

  ros::NodeHandle nh("~");
  ros::Publisher p = nh.advertise<std_msgs::String> ("msg", 1);
  while(true)
  {
    std::string inputString;
    std::cout << "Give input";
    std::getline(std::cin, inputString);
    std_msgs::String msg;

    if(inputString.compare("something") == 0)
    {
      //send a request to the node serving out the messages
      //print out recieved messages.
      msg.data = inputString;
      p.publish(msg);
    }

    ros::spinOnce();
  }

  return 0;
}
*/

/*
#include "ros/ros.h"
#include <std_msgs/String.h>
#include <second_assignment/UserInput.h>

ros::Publisher pub;

int main(int argc, char** argv){
    ros::init(argc, argv, "user_input");
	ros::NodeHandle nh;
    ros::Publisher p = nh.advertise<std_msgs::String> ("msg", 1);       // msg is the topic
    ros::ServiceClient client = nh.serviceClient<second_assignment/UserInput>
    second_assignment::UserInput srv1
    
    // while loop
    while(true)
    {   
    std::string inputString;
    std::cout << "Please enter a for decrease speed, d for speed increase and s for reset position:";
    std::getline(std::cin, inputString);
    //std_msgs::String msg;

    //msg.data = inputString;     //msg to publish
    //p.publish(msg);             //publishing here

    srv1.request.req = inputString;
    client.waitForExistence();
    client.call(srv1);

    ros::spinOnce();
    } //end of while

}


/*
The important point to keep in mind is that your subscriber will receive nothing
until you call spin or spinOnce. In your code, you block waiting for user input before calling spinOnce,
so you receive nothing. Place the spinOnce before the std::getline.
https://answers.ros.org/question/190877/getting-messages-after-an-user-input/


A code here:
cout << "Type a number: "; // Type a number and press enter
    cin >> x; // Get user input from the keyboard
    cout << "Your number is: " << x; // Display the input value 

    pub = nh.advertise<geometry_msgs::Twist>("cmd_vel",1);

    ros::Spin();

    return 0;


    Another code
    #include <ros/ros.h>
    #include <std_msgs/String.h>

    int main(int argc, char** argv)
    {
  ros::init(argc, argv, "test");

  ros::NodeHandle nh("~");
  ros::Publisher p = nh.advertise<std_msgs::String> ("msg", 1);
  while(true)
  {
    std::string inputString;
    std::cout << "Give input";
    std::getline(std::cin, inputString);
    std_msgs::String msg;

    if(inputString.compare("something") == 0)
    {
      //send a request to the node serving out the messages
      //print out recieved messages.
      msg.data = inputString;
      p.publish(msg);
    }

    ros::spinOnce();
  }

  return 0;
}
*/
