# theta_driver

## Getting started

### with docker

```bash
git clone --recursive git@github.com:stella-cv/theta_driver.git
cd theta_driver
docker build -t theta_driver .
docker run --rm -it --net=host --privileged theta_driver
ros2 run theta_driver theta_driver_node
```

### without docker

You need to install the libuvc and it's dependencies before using this package.

1. Install GStreamer-1.0.
```
sudo apt-get install libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio libgstreamer-plugins-base1.0-dev
```
2. <https://github.com/ricohapi/libuvc-theta>

```bash
git clone https://github.com/ricohapi/libuvc-theta.git
cd libuvc-theta
mkdir build
cd build
cmake ..
make && sudo make install
```

You will also need the sample for the Theta-Z1

3. clone
  ```bash
git clone https://github.com/eieioF11/theta_driver.git
cd theta_driver
git submodule update --init --recursive
```
4. build
```bash
colcon build --symlink-install
```

Try it with:

```bash
ros2 run theta_driver theta_driver_node
```
or
```bash
ros2 launch theta_driver theta_driver.launch.py
```

And then you can use image_view package, rqt or rviz2 to see the published image.
