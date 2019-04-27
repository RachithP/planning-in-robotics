## A-star on differential drive robot

# A-star algorithm implementation on turtlebot3-waffle for motion planning along with GUI for visualization.

For a differential drive robot like turtlebot, this implementation takes into account different wheel velocities for the 2 wheels and based on that 8 action sets are generated. The action sets are as follows:

```
actions = [(0, rpm_1), (rpm_2, 0), (rpm_2, rpm_1), (rpm_2, rpm_2), (rpm_1, rpm_1), (0, rpm_2), (rpm_1, 0), (rpm_1, rpm_2)]
```
Based on these actions, the robot follows paths as shown below:
![differential robot paths](https://github.com/RachithP/motion-planning/blob/master/A-star/non-holonomic_robot/paths.jpg)
Credits: ENPM661 - Project3

It is also important to note the heading of the bot at every location. This is required for further exploration.
 
To see how A-star algorithm works, run the python file as ```python tb3_astar.py```

Default values are taken if none provided. They can be seen using help. If you type ```python tb3_astar.py --help```, you will see the following:

```python
usage: tb3_astar.py [-h] [--res RES] [--clc CLC] [--startx STARTX]
                    [--starty STARTY] [--endx ENDX] [--endy ENDY]
                    [--rpmLeft RPMLEFT] [--rpm_1 RPMRIGHT]
                    [--initialTheta INITIALTHETA]

optional arguments:
  -h, --help            show this help message and exit
  --res RES             resolution of the map, Default: 1
  --clc CLC             clearance for safety, Default: 10
  --startx STARTX       x coordinate of start point, Default: 680
  --starty STARTY       y coordinate of start point, Default: 680
  --endx ENDX           x coordinate of end point, Default: 200
  --endy ENDY           y coordinate of end point, Default: 150
  --rpmLeft RPMLEFT     rpm of left wheel, Default: 100
  --rpmRight RPMRIGHT   rpm of right wheel, Default: 50
  --initialTheta INITIALTHETA
                        initial theta w.r.t x-axis (horizontal axis) in
                        radians, Default: 0
```
For a map size of 1110x1050, this algorithm has an obstacle space with res = 1, clc = 10, radius of the turtlebot3 = 22. All units are in cms, ie. each pixel is 1cmx1cm
![Obstacle Space](https://github.com/RachithP/motion-planning/blob/master/A-star/non-holonomic_robot/output/obstacle_space.png)

Sample run:
```python tb3_astar.py --res 1 --startx 680 --starty 680 --endx 200 --endy 150 --clc 10```
produces an output as shown below:
![simulation](https://github.com/RachithP/motion-planning/blob/master/A-star/non-holonomic_robot/output/astar.gif)


