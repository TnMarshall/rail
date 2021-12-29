# rail
INCOMPLETE: This readme will eventually contain full setup instructions. The below instructions are only part of the process.

1. On an Ubuntu 18.04 system, install ROS Melodic, catkin, etc (see ROS's install tutorial/instructions)

2. clone this repository into the directory you wish to keep it in
3. from that directory, "cd rail"
4. run "catkin_make"


5. To run the various functionalities, use roslaunch subdirectory_name launch_file_name.

6. To launch gazebo with controllers and be able to control the positions. First launch the gazebo launch file. Then the control launch file. Then rqt with a message publisher and add the pitch and yaw command topics

Again, this setup description is not complete yet.
