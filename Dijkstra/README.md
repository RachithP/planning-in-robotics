# Dijkstra algorithm implementation for motion planning along with GUI for visualization.

## Dijkstra:

To see how Dijkstra algorithm works, run the python file as ```python2 Dijkstra.py```

Default values are taken if none provided. They can be seen using help. If you type ```python Dijkstra.py --help```, you will see the following:


```python
usage: Dijkstra.py [-h] [--radius RADIUS] [--res RES] [--clc CLC]
                [--startx STARTX] [--starty STARTY] [--endx ENDX]
                [--endy ENDY]

optional arguments:
  -h, --help       show this help message and exit
  --radius RADIUS  radius of the circular robot, Default: 5.0
  --res RES        resolution of the map, Default: 1
  --clc CLC        clearance of the map, Default: 0
  --startx STARTX  x coordinate of start point, Default: 0
  --starty STARTY  y coordinate of start point, Default: 250
  --endx ENDX      x coordinate of end point, Default: 0
  --endy ENDY      y coordinate of end point, Default: 150
```

For a map size of 250x150, this algorithm has an obstacle space with res = 1, clc = 0, radius = 0 as follows:
![Obstacle Space](https://github.com/RachithP/motion-planning/blob/master/Dijkstra/obstacleSpace.png)

Sample run:
```python Dijkstra.py --radius 5 --res 1 --startx 50 --starty 139 --endx 200 --endy 30 --clc 5```
produces an output as shown below:
![simulation](https://github.com/RachithP/motion-planning/blob/master/Dijkstra/dijkstra.gif)

Output Image:
![Sample output](https://github.com/RachithP/motion-planning/blob/master/Dijkstra/sample_output.png)


## NOTE
When radius > 0, the boundaries of the obstacles and the walls will increase by 'radius' amount, but this isn't the final expansion. Resolution also needs to be considered. Resolution is the amount of steps the robot can take at a time. So, if resolution != 1, then boundaries might not increase just by radius. This also depends on the map size, if the max width/height is not an exact multiple of resolution, boundary increment might not be equal for all edges.
