export ROS_IP=10.105.48.40
sleep 3
roscore | rosrun lidar_3d dataPub | rosrun lidar_3d angle_pub.py
