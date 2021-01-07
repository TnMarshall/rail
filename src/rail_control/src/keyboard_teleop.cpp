//Used for reference
//https://github.com/methylDragon/teleop_twist_keyboard_cpp/blob/master/src/teleop_twist_keyboard.cpp

#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "geometry_msgs/Twist.h"

#include <stdio.h>
#include <unistd.h>
#include <termios.h>


std_msgs::Float64 pitchval;


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
    ros::init(argc, argv, "keyboard_teleop");

    ros::NodeHandle n;

    ros::Publisher pitch = n.advertise<std_msgs::Float64>("pitch_val", 1000);

    ros::Rate loop_rate(10);
    printf("Press q to exit");

    while (ros::ok())
    {
        key = getch();
        printf("%c\n", key);
        if (key == 'q'){
            break;
        }
        pitchval.data = 10;
        pitch.publish(pitchval);

        ros::spinOnce();

        loop_rate.sleep();
    }

    return 0;
}