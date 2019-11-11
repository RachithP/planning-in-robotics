# This is a TSP 2-approx method using Minimal Spanning Tree (MST). The resultant graph is fine-tuned to reduce the cost through Heuristics - Crossed edges are unravelled.

## Sample output is as shown below;
### Graph with 51 nodes.
![51 nodes](https://github.com/RachithP/planning-in-robotics/blob/master/tsp/sample_gifs/eil51_1.gif)

### Graph with 76 nodes.
### Sample Terminal output
```
Number of vertices are 76
Sum of the MST edges is 472.331
Initial TSP Tour cost is 742.751
TSP Tour length after applying heuristic is 657.766
Time taken to complete is 1.448680 seconds 
------------------------------------------
```

![76 nodes](https://github.com/RachithP/planning-in-robotics/blob/master/tsp/sample_gifs/eil76_1.gif)

### Graph with 101 nodes.
![101 nodes](https://github.com/RachithP/planning-in-robotics/blob/master/tsp/sample_gifs/eil101.gif)

Required:
1. c++11 standard followed.
2. g++ 5.4.0 compiler
3. opencv3.3
4. Cmake version 3.5.

Input:
1. Input the absolute path to the .tsp file as input to the program.
2. The input .tsp file shoud contain 3 alphabets and then the dimension in its filename. Eg: abc10000.tsp has 10000 nodes in the graph. "abc" can be any alphabets.

Opencv
1. opencv is used for visualization purpose only
2. You are given an option to visualize the graph. (I cannot guarantee it will look good as it needs more tuning).

How to RUN program:
1. This code is run using cmake version 3.5.1. Min required version is 3.5
2. In the zip file you can see a folder named code_cpp. This contains the code for this program.
3. A binary/executable has alread been generated, just needs to be run.
4. executable is called "hw1_executable" and is placed under code_cpp/build/hw1_executable
5. To run this code, your current directory has to be 'code_cpp/build'. Then execute the command `./hw1_executable`. If that does not work, run `chmod a+x hw1_executable` and retry `./hw1_executable`.
6. If you want to recompile the code, you will need to build it through cmake.
7. execute the following commands in same order with current directory being 'code_cpp'.
`rm -rf build`
`mkdir build`
`cd build`
`cmake ..`
`make`
8. Then follow step 5.

While running program:
1. You will be promted to enter the input file and asked if you want to visualize a graph when you execute the binary.
2. Make sure you enter the absolute path to the input file.
3. enter 0 to "Do you want to visualize graph?" if you do not want to visualize. Either way you will have to have opencv.

OUTPUT file:
1. The current code does not write output to any folder. output being file of required format (Eg: eil51.out.tour). Uncomment writeTourOutput() function under main() in main.cpp to write output into a file. Please follow the direction on console to find where the output file is written to.
2. Before you write output file, make sure to create a folder named "output" in the directory where you have the input .tsp file.
3. If your input folder is input_dir and input file is input_dir/abc10000.tsp, then output will be written to input_dir/output/abc10000.tour.out


Output of 3 standard instances eli51.tsp, eli76.tsp, eli101.tsp are placed in in_out_files folder.
