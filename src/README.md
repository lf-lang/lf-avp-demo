Notes:

- Please change AUTOWARE_HOME in include/CMakeListsExtension.txt to reflect your top-level AutowareAuto folder. You can do this by changing the follwoing line:
  
      set(AUTOWARE_HOME /home/$ENV{USER}/adehome/AutowareAuto)
      
- Make sure the terminal is properly sourced for _both_ ROS and Autoware. See
      
      https://docs.ros.org/en/foxy/Tutorials/Configuring-ROS2-Environment.html
      
  For example, if ROS is installed in /opt/ros/foxy and Autoware is built in /home/${USER}/adehome/AutowareAuto/opt/AutowareAuto you can source the terminal via:
  
      source /opt/ros/foxy/setup.bash
      source /home/${USER}/adehome/AutowareAuto/opt/AutowareAuto/setup.bash
      
