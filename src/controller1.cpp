#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"

int i;


// int get_min_of(int array[], int size){
//     int min = array[0];
//     for (i = 0; i = size; i++){
//         if (array[i] < min){
//             min = array[i];
//         }
//     }
//     return min;
// }

// int * arr_split(int array[], int sz, int n, int m){
//     int divided[m-n+1] = {0};
//     for (i = n; i <= m; i++){
//         divided[i] = array[i];
//     }
//     return divided;
// }


void baseCallback(const sensor_msgs::LaserScan::ConstPtr& msg) // constant pointer for the callback
{
    int size = msg->ranges.size();
    int dist[size], min1;
    int left_bottom[91];
    //int left_mid[180] = {0};
    //int front[180] = {0};
    //int right_mid[180] = {0};
    //int right_bottom[90] = {0};
    //int min1 = left_bottom[0];

    for ( i = 0 ; i < size ; i++ ){
        dist[i] = ceil(msg->ranges[i]);
    }

    for (i = 0; i =  90; i++){  left_bottom[i] = dist[i];   }
    //for (i = 0; i = 179; i++){  left_mid[i] = dist[i+91];   }
    //for (i = 0; i = 179; i++){  front[i] = dist[i+271];     }
    //for (i = 0; i = 179; i++){  right_mid[i] = dist[i+451]; }
    //for (i = 0; i =  89; i++){  right_bottom[i] = dist[i+631];}

    
    for (i = 0; i = 90; i++){ if (left_bottom[i] < min1)    min1 = left_bottom[i];}
    ROS_INFO("left_bottom minimum is    %d  ", min1);


    // int left_bottom =   get_min_of(arr_split(dist, size, 0, 90), 91);
    // int left_mid    =   get_min_of(arr_split(dist, size, 91, 270), 180);
    // int front       =   get_min_of(arr_split(dist, size, 271, 450), 180);
    // int right_mid   =   get_min_of(arr_split(dist, size, 451, 630), 180);
    // int right_bottom=   get_min_of(arr_split(dist, size, 631, 721), 91);

    //ROS_INFO("left_bottom     %d  ", min1);
    

   
    // for ( i = 0 ; i < msg->ranges.size() ; i++ ){
    //     if (msg->ranges[i] >= 5.0){
    //         ROS_INFO("Bu %d nci eleman ve degeri de sudur [%f]", i ,msg->ranges[i]);
    //     }
    // }

    // ROS_INFO("\n \n \n");
    //int length = sizeof(msg->ranges) / sizeof(msg->ranges[0]);
    //int rere = sizeof(msg->ranges);
    // for ( i = 0 ; i < msg->ranges.size() ; i++ )
    //  {
    //      ROS_INFO("Bu %d nci eleman ve degeri de sudur [%f]", i ,msg->ranges[i]);
    //  }  
    // ROS_INFO("Bu 0 %f",msg->ranges[0]);
    // ROS_INFO("Bu 1 %f",msg->ranges[1]);
    // ROS_INFO("Bu 2 %f",msg->ranges[2]);
    //
    //ROS_INFO("%lu",msg->ranges.size()); //cevap 721
    //
    // for ( i = 0 ; i < (sizeof(msg->ranges)/sizeof(msg->ranges[0])) ; i++ )
    // {
    //     ROS_INFO("[%f]",msg->ranges[i]);
    // }
}

int main (int argc, char **argv)
{
	ros::init(argc, argv, "ebru_reader");
	ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("base_scan",1000,baseCallback);

    ros::spin();
	return 0;
}