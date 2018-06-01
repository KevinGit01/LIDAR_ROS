#! /usr/bin/env python
import rospy
from visualization_msgs.msg import Marker
from geometry_msgs.msg import TwistStamped, Pose, Point, Vector3, Quaternion
from std_msgs.msg import Header, ColorRGBA, String,Float32MultiArray
import random

counter = 0
marker_publisher = rospy.Publisher('cloud', Marker, queue_size=100)

def cloud_plot(coordinate):
    global counter
    x = coordinate.data[0]
    y = coordinate.data[1]
    z = coordinate.data[2]
    marker = Marker(
                type=Marker.SPHERE,
                id=0,
                lifetime=rospy.Duration(2.5),
                pose=Pose(Point(x,y,z), Quaternion(0, 0, 0, 1)),
                scale=Vector3(0.3, 0.3, 0.3),
                header=Header(frame_id='map'),
                color=ColorRGBA(0, 67, 255, 0.8))

    marker.id = counter
    counter = counter +1
    marker_publisher.publish(marker)
    rospy.loginfo('%f  %f  %f',x,y,z)

def acquire_data():
    rospy.init_node('cloud_point',anonymous=True)
    rospy.Subscriber('coordinates', Float32MultiArray,cloud_plot)
    rospy.spin()



if __name__ == '__main__':
    try:
        acquire_data()
    except rospy.ROSInterruptException:
        pass
