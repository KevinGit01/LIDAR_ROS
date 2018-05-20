#include <stdio.h>
#include <stdlib.h>

#include "ros/ros.h"

#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"

#include "std_msgs/Float32MultiArray.h"

int main(int argc, char **argv)
{
    

	ros::init(argc, argv, "coordinatePublisher");

	ros::NodeHandle n;

	ros::Publisher pub = n.advertise<std_msgs::Float32MultiArray>("coordinates", 100);
	ros::Rate loop_rate(100);

	while (ros::ok())
	{
		std_msgs::Float32MultiArray coordinate;
		//Clear array
		coordinate.data.clear();
		//for loop, pushing data in the size of the array
		
		//assign array a random number between 0 and 255.
		
		
	
		coordinate.data.push_back(100.9);
        coordinate.data.push_back(1.1);
		coordinate.data.push_back(200.1);
		
		//Publish array
		pub.publish(coordinate);
		//Let the world know
		ROS_INFO("published");
		//Do this.
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;

}
