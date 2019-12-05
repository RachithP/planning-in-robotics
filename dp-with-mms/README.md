## Let's find a path!!
Here, I've implemented BFS, DFS, Dijkstra in C++ 14 environment interfacing with [mms](https://github.com/mackorone/mms). Do have a look at the animation and then read-on if you find this interesting! :) 

### Requirements to run this repository
- This implementation uses mms simulator to interact and visualize the robot/mouse movement. To learn more about the mms simulator used, please refer [mms](https://github.com/mackorone/mms).
- The code base was developed using [codelite](https://codelite.org/). It's opensource, so it won't take much of your time to install it ;)
- Make sure to compile and test the [mms-simulator](https://github.com/mackorone/mms) with sample maps present in resources section of the simulator repo. Also familiarize with instructions on how to compile your own code with the simulator.

### Doxygen enabled 
- You can install [doxygen](http://www.doxygen.nl/download.html) and generate the Doxy files required to view the documentation enabled in this code.


### Sample runs
- Dijkstra Algorithm in action!
![Dijkstra](https://github.com/RachithP/planning-in-robotics/blob/master/dp-with-mms/output/gifs/dijkstra.gif)

- BFS in action!
![BFS](https://github.com/RachithP/planning-in-robotics/blob/master/dp-with-mms/output/gifs/bfs.gif)

- DFS in action! This is certainly bad performance! -- *To-Do [iterative deepening]*
![DFS](https://github.com/RachithP/planning-in-robotics/blob/master/dp-with-mms/output/gifs/dfs.gif)
