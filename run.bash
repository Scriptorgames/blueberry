clear
cd ../..
echo "building..."
colcon build --packages-select blueberry
source ~/.bashrc
cd src/blueberry
echo "running..."
ros2 run blueberry blueberry_node
