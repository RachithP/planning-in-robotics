#!/usr/bin/env python2
import argparse
import obstacleSpace
import numpy as np
import cv2
import math
import sys
from sets import Set
import rospy
# import turtlebot3_controller

# for checking if the queue is empty


def isEmpty(queue):
	return len(queue) == 0

# for pushing an element in the queue


def push(queue, dist, node):
	queue.append([dist, node])

# for popping an element based on Priority. It is here where the lowest element is searched and popped.


def pop(queue):
	try:
		min = 0
		for i in range(len(queue)):
			if queue[i] < queue[min]:
				min = i
		item = queue[min]
		del queue[min]
		return item[1]
	except IndexError:
		print()
		exit()

# for updating a queue with latest dist corresponding to a node


def update(queue, dist, node):
	for val in queue:
		if node == val[1]:
			val[0] = dist
			break
	return queue

# for checking validity of start, end points in workspace


def isCoordValidInWorkSpace(x, y, res):
	#	Checking bounds on the workspace
	flag = True
	key = 0
	if x < 0 or x > 1110 or y < 0 or y > 1010:
		flag = False

	#	Checking if coord is valid w.r.t obstacle space
	if flag:
		if obstacleSpace[int(x/res), int(y/res)] == 0.0:
			flag = False
			key = 1
	return flag, key

# for checking if a locations is valid or not


def isCoordValid(x, y, xmax, ymax):
	#	Checking bounds on the workspace
	flag = True
	if x < 0 or x > xmax-1 or y < 0 or y > ymax-1:
		flag = False

	#	Checking if coord is valid w.r.t obstacle space
	if flag:
		if obstacleSpace[x, y] == 0.0:
			flag = False
	return flag

# for calculating the distance of goal w.r.t present node


def cost2go(point1, point2):
	#	Using Eucliean distance for this purpose
	return np.sqrt((point1[0] - point2[0])**2 + (point1[1] - point2[1])**2)
	#	Using Manhattan distance for this purpose. This works better than euclidean.
	# return abs(point1[1] - point2[1]) + abs(point1[0] - point2[0])


# for showing the image
def showImg(waitKey):
	'''
		This function is to show the environment with updated details each time the function is called.
	'''
	imgrot = np.rot90(displayImg, 1)
	dispImg = cv2.resize(imgrot, (1110, 1010), interpolation=cv2.INTER_AREA)
	cv2.namedWindow('image')
	cv2.moveWindow('image', 50, 50)
	cv2.imshow('image', dispImg.astype(np.uint8))
	cv2.waitKey(waitKey)
	# out.write(dispImg.astype(np.uint8))	# uncomment to make a video


# for marking the pixels based on ID provided
def markImg(point, point2, iD):
	'''
		Function to plot the image with appropriate color values
		iD = 0 : obstacle
		iD = 1 : start point
		iD = 2 : end point
		iD = 3 : explored nodes
		iD = 4 : path from goal node from start node
	'''
	if iD == 0:
		displayImg[point[0], point[1], 0] = 100
		displayImg[point[0], point[1], 1] = 100
		displayImg[point[0], point[1], 2] = 50
		# if showObstacleFormation == 1:
			# showImg(1)
	if iD == 1:
		displayImg[point[0], point[1], 0] = 255
		displayImg[point[0], point[1], 1] = 0
		displayImg[point[0], point[1], 2] = 0
		# showImg(1)
	if iD == 2:
		displayImg[point[0], point[1], 0] = 0
		displayImg[point[0], point[1], 1] = 0
		displayImg[point[0], point[1], 2] = 255
		# showImg(1)
	if iD == 3:
		cv2.line(displayImg, (point[1], point[0]),
		         (point2[1], point2[0]), (0, 255, 255), 1)
		# showImg(1)
	if iD == 4:
		cv2.line(displayImg, (point[1], point[0]),
		         (point2[1], point2[0]), (0, 255, 0), 1)
		# showImg(1)


# for plotting the obstacle
def plotObstacle():
	'''
		Function to plot obstacle space
	'''
	for x in range(obstacleSpace.shape[0]):
		for y in range(obstacleSpace.shape[1]):
			if obstacleSpace[x, y] == 0:
				markImg([x, y], [0, 0], 0)


def diffDriveCalc(action, dt, wheelRad, wheelSep, theta, x, y, xUnits, yUnits, resolution, compareSet):
	'''
		This function is for calculation of differential drive robot constrained movement giving x and y displacements along with heading (theta).
	'''
	x = x * resolution  						# convert back to workspace
	y = y * resolution							# convert back to workspace
	flag = True 								# To keep track of whether the new point is in obstacle space or within a region of threshold w.r.t another visitednode
	rpmLeft = action[0]							# rpm of left wheel
	rpmRight = action[1]						# rpm of right wheel
	angVelLeft = rpmLeft * 2 * math.pi / 60.0					# angular velocity of left wheel
	angVelRight = rpmRight * 2 * math.pi / 60.0					# angular velocity of right wheel
	# value to calculate the sampling frequency of dt
	n = math.ceil(dt/0.01)
	freq = n / dt												# this is the sampling frequency of dt
	w = (wheelRad / wheelSep) * (angVelRight - angVelLeft)

	# Integration using sampling frequency calculated above
	# this is the cost of moving along a curve (approximated) from x,y for dt duration with rpmLeft and rpmRight wheel velocities
	euclDist = 0
	dx = 0				# infitesimal movement along x-axis
	dy = 0				# infitesimal movement along y-axis
	dtheta = 0			# infitesimal movement of theta w.r.t x-axis
	for _ in range(int(freq)):
		dvx = wheelRad * 0.5 * (angVelLeft + angVelRight) * math.cos(theta)		# instantaneous linear x-velocity
		dvy = wheelRad * 0.5 * (angVelLeft + angVelRight) * math.sin(theta)		# instantaneous linear y-velocity
		dx = dvx * dt / freq
		dy = dvy * dt / freq
		dtheta = w * dt / freq
		x += dx																		# update x with new change dx
		y += dy																		# update y with new change dy
		theta += dtheta																# update theta with new change dtheta
		# get curvature distance as the cost
		euclDist += math.sqrt(dx**2 + dy**2)

		# Check if any of the curvature paths being taken are in obstacle space or not
		if not isCoordValid(x, y, xUnits, yUnits):
			flag = False

	# Check if the new x,y are within a certain region of any other previous x,y. This is done to eliminate redundancy
	if inThresholdRegion(x, y, compareSet):
		flag = False

	return int(x/resolution), int(y/resolution), theta, euclDist, dvx, dvy, w, flag


def inThresholdRegion(x, y, compareSet):
	'''
		This function is to check if the visiting location is already within a reasonable (pruneResolution) distance - square box with values going to bottom left corner
	'''
	if int(x/pruneResolution) * 10000 + int(y/pruneResolution) in compareSet:
		return True
	else:
		return False


def aStar(startPoint, endPoint, resolution, xUnits, yUnits, rpmLeft, rpmRight, wheelRad, wheelSep, initialTheta):
	'''
		A-STAR ALGORITHM FOR DIFFERENTIAL DRIVE ROBOTS!!!
	'''
	#	Intitializations
	global pruneResolution
	# this is used for creating a region for visited node selection
	pruneResolution = 10
	# this is the cost to come that location x,y
	gcost = np.full((xUnits, yUnits), np.inf, dtype=np.float64)
	# keeping track of parent for ecah x,y
	parent = [[[None, None] for j in range(yUnits)] for i in range(xUnits)]
	# used to publish values into gazebo environment
	global params
	params = np.zeros((xUnits, yUnits, 3), dtype=np.float64)
	# keeping a track of visited nodes
	visitedFlag = np.zeros((xUnits, yUnits))
	# used for storing values that represent bottom left corner of the pruing region
	compareSet = Set([])
	heading = np.zeros((xUnits, yUnits), dtype=np.float64)										# stores heading at each x, y
	exploredNodes = []															# keeping track of order of explored nodes
	# data structure used to pop, store locations and their distances
	priorityQ = []

	#--------------Values for starting point----------#
	# adding starting point to the compare set
	compareSet.add(startPoint[0]*10000+startPoint[1])
	# Setting distance of starting point as zero
	gcost[startPoint[0], startPoint[1]] = 0
	# Marking starting node as visited
	visitedFlag[startPoint[0], startPoint[1]] = 1
	# Pushing starting point to the priority queue
	push(priorityQ, 0, startPoint)
	# Making a note of explore nodes in the order of exploration
	exploredNodes.append(startPoint)
	# Taking starting node heading to be initial angle
	heading[startPoint[0], startPoint[1]] = initialTheta
	#-------------------------------------------------#

	# Taking ending node heading to be initial angle
	heading[endPoint[0], endPoint[1]] = initialTheta
	goalFlag = False												# Keeping a flag when goal node is reached
	# Making a list of all possible actions
	actions = [(0, rpmRight), (rpmLeft, 0), (rpmLeft, rpmRight), (rpmLeft, rpmLeft), (rpmRight, rpmRight), (0, rpmLeft), (rpmRight, 0), (rpmRight, rpmLeft)]

	lastNode = endPoint												# keeping track of last node

	while not isEmpty(priorityQ):

		#	Pop element and set it as current node
		currentNode = pop(priorityQ)

		#	Check all possible actions and update their distances
		for action in actions:

			x, y, theta, cost, dvx, dvy, dw, flag = diffDriveCalc(
				action, 1, wheelRad, wheelSep, heading[currentNode[0], currentNode[1]], currentNode[0], currentNode[1], xUnits, yUnits, resolution, compareSet)

			#	do not take output x,y if flag is false
			if not flag:
				continue
			#	check if x, y is valid
			if not isCoordValid(x, y, xUnits, yUnits):
				continue

			#	Update the new values
			compareSet.add(int(x/pruneResolution) * 10000 + int(y/pruneResolution))		# used for pruning
			heading[x, y] = theta														# update heading
			params[x, y, 0] = math.sqrt(dvx**2 + dvy**2)								# update the publishing params
			params[x, y, 1] = dvy
			params[x, y, 2] = dw

			#	Get the cost2go from new location
			# specifically wrote 1 to highlight that it can be changed to get weighted A-star algorithm
			c2g = 1*cost2go([x, y], endPoint)
			#	Calculate the total cost for the new node
			dist = gcost[currentNode[0], currentNode[1]] + cost + c2g

			if not visitedFlag[x, y]:
				#	Mark this node as visited
				visitedFlag[x, y] = 1
				#	Update gcost
				gcost[x, y] = dist - c2g
				#	Push this to the Queue
				push(priorityQ, dist, [x, y])
				#	Mark the parent as current Node
				parent[x][y] = [currentNode[0], currentNode[1]]
				#	Add this to explored nodes for visualization
				exploredNodes.append([x, y])
				#	For plotting purpose only
				markImg([x, y], [currentNode[0], currentNode[1]], 3)
				showImg(1)
			else:
				#	check if this new distance is less than previously stored distance, if dist is less, update the existing value and the new parent
				if dist < gcost[x, y] + c2g:
					#	Update the queue with latest distance information
					update(priorityQ, dist, [x, y])
					#	Update the new parent based on lower gcost
					parent[x][y] = [currentNode[0], currentNode[1]]
					#	Update the new lower gcost
					gcost[x, y] = dist - c2g

		#	End the loop if end point is reached within a radius of certain number
		if math.sqrt((currentNode[0]-endPoint[0])**2 + (currentNode[1]-endPoint[1])**2) <= pruneResolution+10:
			goalFlag = True
			print("Your end goal is within a circle of certain threshold from the start point. Hence, reached!!\n")
			print("Either you are too close to obstacle space wherein robot cannot turn or there is no path that can be traversed successfully by the robot\n")
			lastNode = currentNode  # making a note of last visited node
			break

	#	Trace back using the parent node
	# this is for final path from start node to end node
	finalPath = [[None, None]]
	temp = [[None, None, None]]		# this is for publishing velocities in order
	# initialy it will have values in reverse order
	finalPath[0] = [lastNode[0], lastNode[1]]
	temp[0] = [[0, 0, 0]]			# this is for start node with all values taken as zero
	t = []

	# for getting the path from start to end
	try:
		while t != startPoint:
			t = parent[finalPath[-1][0]][finalPath[-1][1]]
			finalPath.append([t[0], t[1]])
			temp.append([params[t[0], t[1], :]])
	except TypeError:
		print("Press any key to close the image\n")
		markImg(startPoint, [0, 0], 1)
		markImg(endPoint, [0, 0], 2)
		# showImg(1)  # For the user to see the final image
		print("Path to goal node does not exist. Try another goal node")
		quit()

	# for plotting the path
	# for node in reversed(finalPath):
	# 	markImg(node, [0, 0], 4)
	finalPath.reverse()			# getting the path from start to end
	for i in range(len(finalPath)-1):
		markImg(finalPath[i], finalPath[i+1], 4)

	finalParams = []
	for param in reversed(temp):
		finalParams.append(param)

	print('Number of explored nodes in configuration space: ', len(exploredNodes))

	return finalParams, finalPath

def main(args):

	# Parse Command Line arguments. This is not required as of now since we are passing values from simulation launch file.
	# Uncomment below block to use it separately. But make sure to comment appropriate lines (which correspond to ROS)
	
	Parser = argparse.ArgumentParser()
	Parser.add_argument('--res', default=1.0,
	                    help='resolution of the map, Default: 1')
	Parser.add_argument('--clc', default=10.0,
	                    help='clearance for safety, Default: 10')
	Parser.add_argument('--startx', default=680.0,
	                    help='x coordinate of start point, Default: 680')
	Parser.add_argument('--starty', default=680.0,
	                    help='y coordinate of start point, Default: 680')
	Parser.add_argument('--endx', default=200.0,
	                    help='x coordinate of end point, Default: 200')
	Parser.add_argument('--endy', default=100.0,
	                    help='y coordinate of end point, Default: 150')
	Parser.add_argument('--rpmLeft', default=100.0,
                     	help='rpm of left wheel, Default: 100')
	Parser.add_argument('--rpmRight', default=50.0,
                      	help='rpm of right wheel, Default: 50')
	Parser.add_argument('--initialTheta', default=0,
	                    help='initial theta w.r.t x-axis (horizontal axis) in radians, Default: 0')

	Args = Parser.parse_args()
	resolution = float(Args.res)
	clc = float(Args.clc)
	startPoint = (int(Args.startx), int(Args.starty))
	endPoint = (int(Args.endx), int(Args.endy))
	redStartPoint = [int(startPoint[0]/resolution), int(startPoint[1]/resolution)]
	redEndPoint = [int(endPoint[0]/resolution), int(endPoint[1]/resolution)]
	rpmLeft = Args.rpmLeft
	rpmRight = Args.rpmRight
	initialTheta = float(Args.initialTheta)

	wheelRad = 3.3  		# units in centi-meters, waffle turtlebot3
	wheelSep = 29.0  		# units in centi-meters, waffle turtlebot3
	radius = 22  			# units in centi-meters, waffle turtlebot3

	print('(start point) , (end point):', startPoint, endPoint)
	print('(config space start point) , (config space end point):', redStartPoint, redEndPoint)

	global obstacleSpace
	# get obstacle space from another file
	obstacleSpace = obstacleSpace.main([resolution, radius, clc])

	xUnits = obstacleSpace.shape[0]
	yUnits = obstacleSpace.shape[1]

	ret, val = isCoordValidInWorkSpace(startPoint[0], startPoint[1], resolution)
	if not ret:
		if val:
			print('Start point is not a valid point. It is in obstacle space. Please enter another point.\n')
		else:
			print('Start point is not a valid point. It is outside the workspace. Please enter another point.\n')
		quit()

	ret, val = isCoordValidInWorkSpace(endPoint[0], endPoint[1], resolution)
	if not ret:
		if val:
			print('End point is not a valid point. It is in obstacle space. Please enter another point.\n')
		else:
			print('End point is not a valid point. It is outside the workspace. Please enter another point.\n')
		quit()

	## Uncomment to record video
	## Define the codec and create VideoWriter object
	# global out
	# fourcc = cv2.VideoWriter_fourcc(*'XVID')
	# out = cv2.VideoWriter('astar.avi',fourcc, 30.0, (1000,600))

	global displayImg
	displayImg = np.full((xUnits, yUnits, 3), 0, dtype=np.float64)

	global showObstacleFormation
	showObstacleFormation = 0

	plotObstacle()
	markImg(redStartPoint, [0, 0], 1)
	markImg(redEndPoint, [0, 0], 2)

	#	A-Star algorithm in the configuration space
	finalParams, finalPath = aStar(redStartPoint, redEndPoint, resolution, xUnits, yUnits, rpmLeft, rpmRight, wheelRad, wheelSep, initialTheta)

	markImg(redStartPoint, [0, 0], 1)
	markImg(redEndPoint, [0, 0], 2)
	print("Press any key to close the image\n")
	showImg(0)  # For the user to see the final image

	cv2.destroyAllWindows()

	# out.release

if __name__ == "__main__":
	main(sys.argv)
