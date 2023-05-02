from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
					# x y z roll pitch yaw parent_frame_name child_frame_name 
            arguments = ['0', '0', '1', '0', '0', '0', 'world', 'mystaticturtle']
        ),
    ])