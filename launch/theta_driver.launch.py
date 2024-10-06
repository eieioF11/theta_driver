import os
import sys
from glob import glob
from launch_ros.descriptions import ComposableNode
from launch_ros.actions import Node
from launch_ros.actions import ComposableNodeContainer
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument
from launch.actions import IncludeLaunchDescription
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
import launch_ros.actions


def generate_launch_description():
    pkg_dir = get_package_share_directory('theta_driver')
    list = [
        Node(
            package="tf2_ros",
            executable="static_transform_publisher",
            arguments=[
                "--x",
                "0.0",
                "--y",
                "0.0",
                "--z",
                "0.0",
                "--yaw",
                "-1.5707",
                "--pitch",
                "0.0",
                "--roll",
                "-1.5707",
                "--frame-id",
                "camera_link",
                "--child-frame-id",
                "camera_rgb_optical_frame",
            ],
            # parameters=[{'use_sim_time': True}]
        ),
        Node(
            package='theta_driver',
            executable='theta_driver_node',
            namespace='',
            output="screen",
            parameters=[os.path.join(pkg_dir, "config", "theta_param.yaml")],
            # prefix=['valgrind --tool=callgrind'],
            # prefix=['xterm -e valgrind --tool=callgrind'],
            # prefix=['valgrind --tool=callgrind --dump-instr=yes -v --instr-atstart=no --verbose'],
            respawn=True,
        ),
    ]

    return LaunchDescription(list)