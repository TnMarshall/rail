#include "ros/ros.h"
#include "std_msgs/Float64.h"

std_msgs::Float64 pitchval;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "keyboard_teleop");

    ros::NodeHandle n;

    ros::Publisher pitch = n.advertise<std_msgs::Float64>("pitch_val", 1000);

    ros::Rate loop_rate(10);


    while (ros::ok())
    {
        pitchval.data = 10;
        pitch.publish(pitchval);

        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}