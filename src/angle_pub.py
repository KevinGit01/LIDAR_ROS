#! /usr/bin/env python
import rospy
from visualization_msgs.msg import Marker
from lidar_3d.msg import angle
import random
import RPi.GPIO as GPIO
import time

def angle_pub():
	STP = 37;
	DIR = 35;
	MS1 = 33;
	MS2 = 31;
	EN  = 29;
	GPIO.setmode(GPIO.BOARD)
	GPIO.setup(STP,GPIO.OUT);
	GPIO.setup(DIR,GPIO.OUT);
	GPIO.setup(MS1,GPIO.OUT);
	GPIO.setup(MS2,GPIO.OUT);
	GPIO.setup(EN,GPIO.OUT);

	GPIO.output(DIR,GPIO.LOW);
	counter = 6000;
	GPIO.output(MS1,GPIO.LOW);
	GPIO.output(MS2,GPIO.LOW);
	step = 200;
	sleep = 0.0025;
	pitch = 0;
	yaw = 0;
	resolution = 1.8
	pub = rospy.Publisher('angle', angle, queue_size=50)
	rospy.init_node('angle_pub', anonymous=True)
	rate = rospy.Rate(50)
	angles = angle()
	angles.angle_h = 0
	angles.angle_v = 0

	while not rospy.is_shutdown():
		GPIO.output(STP,GPIO.HIGH);
		time.sleep(0.001);
		GPIO.output(STP,GPIO.LOW);
		time.sleep(0.001);
		pub.publish(angles)

		yaw = yaw + 1;
		angles.angle_h = yaw*resolution
		angles.angle_v = pitch;
		if yaw == step:
			yaw = 0
			pitch = pitch +1                
	#	rospy.loginfo("angle_published")
		rate.sleep()
		if pitch >= 1:
			rospy.signal_shutdown("finished")
	GPIO.cleanup();

if __name__ == '__main__':
    try:
		angle_pub()
    except rospy.ROSInterruptException:
        pass









