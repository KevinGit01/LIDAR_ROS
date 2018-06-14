# LIDAR_ROS
______
This repo is a lite 3D lidar controled by a raspberry pi using ROS. Recently, lidar has been a heated topic in the field  of autonomous driving; however, the commercial lidar products on the market are expensive. The goal of this project is to build a lite lidar system using budget parts. The core parts used in this project is a TOF(time of flight) sensor, stepper motor and servo. ROS is used as the operating system to pipe data through sensors programmed in C++ and python. Python, matplotlib and rviz are used for point cloud visulization.

## Demo for 2D lidar scan ##
______
[![lidar_2d](https://github.com/KevinGit01/LIDAR_ROS/blob/master/pics/lidar_2d.png)](https://youtu.be/_R8Wh5mv8cQ)

## Lidar Structure ##
_____
![ROS_Pi](https://github.com/KevinGit01/LIDAR_ROS/blob/master/pics/pi-ros-pc.png)

The TOF sensor returns the distance of the first obstacle it sees. The stepper motor returns the horizontal angle of the TOF sensor, and the servo returns the angle of the TOF sensor deviated from the vertical line. After the TOF sensor finished one sampling, the data is send to raspberry pi. Then ros on the raspberry pi publishes the coordinates of the obstacle onto the topic "coordinates". The ros node visulization on the ubuntu PC subscribes the coordinates topic and visulize the point cloud in the real time.

