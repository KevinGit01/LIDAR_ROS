#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "SparkFun_VL53L1X_Arduino_Library.h"
#include <unistd.h>
#include <ctime>
#include "ros/ros.h"
#include <fstream>
#include <math.h>

#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Float32MultiArray.h"
#include "lidar_3d/angle.h"


using namespace std;
VL53L1X distanceSensor;
float x=0,y=0,z=0,angle_h=0,angle_v=0,angle_horizontal = 0,angle_vertical = 0;
std_msgs::Float32MultiArray coordinate;
int sensor_result;



void coord_pub(const lidar_3d::angle& angle){
	angle_horizontal = angle.angle_h;
	angle_vertical = angle.angle_v;
  }


int main(int argc, char **argv)
{

	    
    VL53L1X distanceSensor;
    distanceSensor.begin();
    ofstream myfile;
    myfile.open("lidar_point.txt");
	ros::init(argc, argv, "coordinatePublisher");

	ros::NodeHandle n;

	ros::Publisher pub = n.advertise<std_msgs::Float32MultiArray>("coordinates", 100);
	ros::Subscriber sub = n.subscribe("angle",50,coord_pub);
	ros::Rate loop_rate(50);

    while (ros::ok())
	 {


		coordinate.data.clear();
		//for loop, pushing data in the size of the array

	    distanceSensor.startMeasurement();
        usleep(5000);
        sensor_result = distanceSensor.getDistance(); //Get the result of the measurement from the sensor
        sensor_result = sensor_result/100.0;
//		sensor_result = 3;		
		x = sensor_result*cos(angle_vertical*M_PI/180.0)*cos(angle_horizontal*M_PI/180);
        y = sensor_result*cos(angle_vertical*M_PI/180.0)*sin(angle_horizontal*M_PI/180);
        z = sensor_result*sin(angle_vertical*M_PI/180.0);
		coordinate.data.push_back(x);
      	coordinate.data.push_back(y);
		coordinate.data.push_back(z);

		//Publish array
		pub.publish(coordinate);
        myfile << x <<" "<< y <<" "<< z << endl;
		//Let the world know
		ROS_INFO("coordinate published");
		//Do this.
		ros::spinOnce();
		loop_rate.sleep();
	}

    ros::spin();
	return 0;

}


/*

class coordinate_pub
{


public:


  void subAndPub(){
				ROS_INFO("published 3");
    pub = n.advertise<std_msgs::Float32MultiArray>("coordinates", 50);
    sub = n.subscribe("angle",50,&coordinate_pub::coord_pub,this);

}
  
  void coord_pub(const lidar_3d::angle& angle)
  {
     	distanceSensor.startMeasurement();
        usleep(5000);
        sensor_result = distanceSensor.getDistance(); //Get the result of the measurement from the sensor
        sensor_result = sensor_result/1000.0;
		x = sensor_result*cos(angle.angle_v)*cos(angle.angle_h);
        x = sensor_result*cos(angle.angle_v)*sin(angle.angle_h);
        z = sensor_result*sin(angle.angle_v);
		coordinate.data.push_back(x);
      	coordinate.data.push_back(y);
		coordinate.data.push_back(z);

		//Publish array
		pub.publish(coordinate);

  }

private:
    ros::NodeHandle n;
	ros::Publisher pub;
	ros::Subscriber sub; 

};


*/





