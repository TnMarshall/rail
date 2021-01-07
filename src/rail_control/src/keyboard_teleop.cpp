//Used for reference
//https://github.com/methylDragon/teleop_twist_keyboard_cpp/blob/master/src/teleop_twist_keyboard.cpp

#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "geometry_msgs/Twist.h"

#include <stdio.h>
#include <unistd.h>
#include <termios.h>


std_msgs::Float64 pitchval;
std_msgs::Float64 yawval;
std_msgs::Float64 servoMax;  //temporary solution to keep values bound to useful servo values
std_msgs::Float64 servoMin;  //temporary solution to keep values bound to useful servo values

////////// Included directly from reference, to be replaced later //////////

char key(' ');

// For non-blocking keyboard inputs
int getch(void)
{
  int ch;
  struct termios oldt;
  struct termios newt;

  // Store old settings, and copy to new settings
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;

  // Make required changes and apply the settings
  newt.c_lflag &= ~(ICANON | ECHO);
  newt.c_iflag |= IGNBRK;
  newt.c_iflag &= ~(INLCR | ICRNL | IXON | IXOFF);
  newt.c_lflag &= ~(ICANON | ECHO | ECHOK | ECHOE | ECHONL | ISIG | IEXTEN);
  newt.c_cc[VMIN] = 1;
  newt.c_cc[VTIME] = 0;
  tcsetattr(fileno(stdin), TCSANOW, &newt);

  // Get the current character
  ch = getchar();

  // Reapply old settings
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  return ch;
}

////////// Included directly from reference, to be replaced later //////////


int main(int argc, char **argv)
{

    servoMax.data = 90;  //temporary solution to keep values bound to useful servo values
    servoMin.data = -90;  //temporary solution to keep values bound to useful servo values

    ros::init(argc, argv, "keyboard_teleop");

    ros::NodeHandle n;

    ros::Publisher pitch = n.advertise<std_msgs::Float64>("rail/pitch_position_controller/command", 1000);
    ros::Publisher yaw = n.advertise<std_msgs::Float64>("rail/yaw_position_controller/command", 1000);

    ros::Rate loop_rate(100);
    printf("Press q to exit\n____________________\nw = up\ns = down\na = left\nd = right\nc = center\n___________________\n");

    while (ros::ok())
    {
        key = getch();

        pitchval.data = pitchval.data / 3.14159265 * 180;
        yawval.data = yawval.data / 3.14159265 * 180;

        switch (key){
            case 'q':
                printf("quitting\n");
                break;
                break;
            case 'w':
                printf("up\n");
                pitchval.data = pitchval.data - 1;
                if(pitchval.data < servoMin.data) pitchval.data = servoMin.data;
                break;
            case 'a':
                printf("left\n");
                yawval.data = yawval.data + 1;
                if(yawval.data > servoMax.data) yawval.data = servoMax.data;
                break;
            case 's':
                printf("down\n");
                pitchval.data = pitchval.data + 1;
                if(pitchval.data > servoMax.data) pitchval.data = servoMax.data;
                break;
            case 'd':
                printf("right\n");
                yawval.data = yawval.data - 1;
                if(yawval.data < servoMin.data) yawval.data = servoMin.data;
                break;
            case 'c':
                printf("centering\n");
                pitchval.data = 0;
                yawval.data = 0;
        }
        if (key == 'q'){
            break;
        }
        pitchval.data = pitchval.data * 3.14159265 / 180;
        yawval.data = yawval.data * 3.14159265 / 180;
        pitch.publish(pitchval);
        yaw.publish(yawval);

        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}