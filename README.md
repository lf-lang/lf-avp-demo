# Autonomous Vehicle Parking (AVP) Demo
This is a Lingua Franca port of the Autoware AVP demo featured in:

    Bateni, Soroush and Lohstroh, Marten and Wong, Hou Seng and Kim, Hokeun and Lin, Shaokai and
    Menard, Christian and Lee, Edward A.. "Risk and Mitigation of Nondeterminism in Distributed
    Cyber-Physical Systems". 21st ACM/IEEE International Symposium on Formal Methods and Models
    for System Design (MEMOCODE), Hamburg, Germany, September 21-22 2023.

The implementation uses the federated runtime and is currently only supported by the C target.
To be able to use this branch, clone the [Lingua Franca](https://github.com/lf-lang/lingua-franca) repository.

Note:

- Please change `AUTOWARE_HOME` in include/CMakeListsExtension.txt to reflect your top-level AutowareAuto folder. You can do this by changing the following line:
  
      set(AUTOWARE_HOME /home/$ENV{USER}/adehome/AutowareAuto)
  
- Make sure the terminal is properly sourced for _both_ ROS and Autoware. See
      
      https://docs.ros.org/en/foxy/Tutorials/Configuring-ROS2-Environment.html
  
  For example, if ROS is installed in /opt/ros/foxy and Autoware is built in /home/${USER}/adehome/AutowareAuto/opt/AutowareAuto you can source the terminal via:
  
      source /opt/ros/foxy/setup.bash
      source /home/${USER}/adehome/AutowareAuto/opt/AutowareAuto/setup.bash
  
 - Please use the port of Autoware located in https://github.com/lf-lang/Autoware
