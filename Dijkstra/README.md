## Dijkstra and A-star for motion planning along with GUI for visualization.

Assuming the map is of size [250,150] and cannot be changed.

# Dijkstra:

To see how Dijkstra algorithm works, run the python file as 'python2 Dijkstra.py'

Default values are taken if none provided. They can be seen using help. If you type 'python Dijkstra.py --help', you will see the following:

usage: Dijkstra.py [-h] [--radius RADIUS] [--res RES] [--clc CLC]
                   [--startx STARTX] [--starty STARTY] [--endx ENDX]
                   [--endy ENDY]

optional arguments:
  -h, --help       show this help message and exit
  --radius RADIUS  radius of the circular robot, Default: 5.0mm
  --res RES        resolution of the map, Default: 1
  --clc CLC        clearance of the map, Default: 0
  --startx STARTX  x coordinate of start point, Default: 0
  --starty STARTY  y coordinate of start point, Default: 250
  --endx ENDX      x coordinate of end point, Default: 0
  --endy ENDY      y coordinate of end point, Default: 150


# A-star:

To see how A-star algorithm works, run the python file as 'python2 Astar.py'

Default values are taken if none provided. They can be seen using help. If you type 'python Astar.py --help', you will see the following:

usage: Astar.py [-h] [--radius RADIUS] [--res RES] [--clc CLC]
                [--startx STARTX] [--starty STARTY] [--endx ENDX]
                [--endy ENDY]

optional arguments:
  -h, --help       show this help message and exit
  --radius RADIUS  radius of the circular robot, Default: 5.0mm
  --res RES        resolution of the map, Default: 1
  --clc CLC        clearance of the map, Default: 0
  --startx STARTX  x coordinate of start point, Default: 0
  --starty STARTY  y coordinate of start point, Default: 250
  --endx ENDX      x coordinate of end point, Default: 0
  --endy ENDY      y coordinate of end point, Default: 150


# NOTE
When radius > 0 is given, the boundaries of the obstacles and the walls of the map will increase by 'radius' amount, but this isn't the final expansion that must be made. Resolution also needs to be considered. Resolution is the amount of steps the robot can take at a time. So, if resolution != 1, then boundaries might not increase just by radius. This also depends on the map size, if the max width/height is not an exact multiple of resolution, boundary increment might not be equal for all edges. This is taken care in the program.
