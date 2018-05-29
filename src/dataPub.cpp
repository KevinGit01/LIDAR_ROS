#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "SparkFun_VL53L1X_Arduino_Library.h"
#include <unistd.h>
#include <ctime>
#include "ros/ros.h"
#include <fstream>

#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"

#include "std_msgs/Float32MultiArray.h"

using namespace std;



int main(int argc, char **argv)
{

	    
    VL53L1X distanceSensor;
    distanceSensor.begin();
    ofstream myfile;
    myfile.open("lidar_point.txt");
	ros::init(argc, argv, "coordinatePublisher");

	ros::NodeHandle n;

	ros::Publisher pub = n.advertise<std_msgs::Float32MultiArray>("coordinates", 100);
	ros::Rate loop_rate(51);
    
    int sensor_result;
    float x=0,y=0,z=0;
	while (ros::ok())
	{
		std_msgs::Float32MultiArray coordinate;
		//Clear array
		coordinate.data.clear();
		//for loop, pushing data in the size of the array

		//assign array a random number between 0 and 255.
	    distanceSensor.startMeasurement();
        
        usleep(5000);

        sensor_result = distanceSensor.getDistance(); //Get the result of the measurement from the sensor
		x = sensor_result/1000.0;
		coordinate.data.push_back(x);
      	coordinate.data.push_back(0);
		coordinate.data.push_back(0);

		//Publish array
		pub.publish(coordinate);
        myfile << x <<" "<< y <<" "<< z << endl;
		//Let the world know
		ROS_INFO("published");
		//Do this.
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;

}
