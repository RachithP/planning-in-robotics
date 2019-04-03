import numpy as np
import sys, cv2
import obstacleSpace, argparse

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
	if x<0 or x>250 or y<0 or y>150:
		flag = False

	#	Checking if coord is valid w.r.t obstacle space
	if flag:
		if obstacleSpace[int(x/res), int(y/res)] == 0:
			flag = False
			key = 1
	return flag, key

# for checking if a locations is valid or not
def isCoordValid(x, y, xmax, ymax):
	#	Checking bounds on the workspace
	flag = True
	if x<0 or x>xmax-1 or y<0 or y>ymax-1:
		flag = False

	#	Checking if coord is valid w.r.t obstacle space
	if flag:
		if obstacleSpace[x, y] == 0:
			flag = False
	return flag

# for calculating the distance of goal w.r.t present node
def cost2go(point1, point2):
	#	Using Eucliean distance for this purpose
	# return np.sqrt((point1[0] - point2[0])**2 + (point1[1] - point2[1])**2)
	#	Using Manhattan distance for this purpose. This works better than euclidean.
	return abs(point1[1] - point2[1]) + abs(point1[0] - point2[0])

# for showing the image
def showImg(waitKey):

	imgrot = np.rot90(displayImg,1)
	dispImg = cv2.resize(imgrot,(1000,600), interpolation = cv2.INTER_AREA)
	cv2.namedWindow('image')
	cv2.moveWindow('image', 40,30)
	cv2.imshow('image',dispImg)
	cv2.waitKey(waitKey)
	# out.write(dispImg.astype(np.uint8))	# uncomment to make a video

# for marking the pixels based on ID provided
def markImg(point, iD):
	'''
		Function to plot the image with appropriate color values
		iD = 0 : obstacle
		iD = 1 : start point
		iD = 2 : end point
		iD = 3 : explored nodes
		iD = 4 : path from goal node from start node
	'''
	if iD == 0:
		displayImg[point[0], point[1], :] = 0
		if showObstacleFormation == 1:
			showImg(1)
	if iD == 1:
		displayImg[point[0], point[1], 0] = 255
		displayImg[point[0], point[1], 1] = 0
		displayImg[point[0], point[1], 2] = 0
		showImg(1)
	if iD == 2:
		displayImg[point[0], point[1], 0] = 0
		displayImg[point[0], point[1], 1] = 0
		displayImg[point[0], point[1], 2] = 255
		showImg(1)
	if iD == 3:
		displayImg[point[0], point[1], 0] = 0
		displayImg[point[0], point[1], 1] = 255
		displayImg[point[0], point[1], 2] = 255
		showImg(1)
	if iD == 4:
		displayImg[point[0], point[1], 0] = 255
		displayImg[point[0], point[1], 1] = 255
		displayImg[point[0], point[1], 2] = 0
		showImg(1)

# for plotting the obstacle
def plotObstacle():
	'''
		Function to plot obstacle space
	'''
	for x in range(obstacleSpace.shape[0]):
		for y in range(obstacleSpace.shape[1]):
			if obstacleSpace[x, y] == 0:
				markImg([x, y], 0)

def dijkstra(startPoint, endPoint, resolution, xUnits, yUnits):

	#	Intitializations
	gcost = np.full((xUnits,yUnits), np.inf)
	parent = [[[None,None] for j in range(yUnits)] for i in range(xUnits)]
	visitedFlag = np.zeros((xUnits,yUnits))
	exploredNodes = []
	priorityQ = []

	#	Values for starting point
	gcost[startPoint[0] ,startPoint[1]] = 0					#	Setting distance of starting point as zero
	visitedFlag[startPoint[0], startPoint[1]] = 1			#	Marking starting node as visited
	push(priorityQ, 0, startPoint)							#	Pushing starting point to the priority queue
	exploredNodes.append(startPoint)						#	Making a note of explore nodes in order of exploration
	goalFlag = False

	while not isEmpty(priorityQ):
		#	Pop element and set it as current node
		currentNode = pop(priorityQ)

		if currentNode == endPoint:
			goalFlag = True
			break

		#	Check all its neighbours and update their distances
		for i in [-1, 0, 1]:
			for j in [-1, 0, 1]:

				if not isCoordValid(currentNode[0]+i, currentNode[1]+j, xUnits, yUnits):
					continue

				if i == 0 and j == 0:
					continue

				#	Get the new distance
				if i==0 or j==0:
					dist = gcost[currentNode[0], currentNode[1]] + 1
				else:
					dist = gcost[currentNode[0], currentNode[1]] + 1.414

				if not visitedFlag[currentNode[0]+i, currentNode[1]+j]:
					#	Mark this node as visited
					visitedFlag[currentNode[0]+i, currentNode[1]+j] = 1
					#	Update gcost
					gcost[currentNode[0]+i, currentNode[1]+j] = dist
					#	Push this to the Queue
					push(priorityQ, dist, [currentNode[0]+i, currentNode[1]+j])
					#	Mark the parent as current Node
					parent[currentNode[0]+i][currentNode[1]+j] = [currentNode[0],currentNode[1]]
					#	Add this to explored nodes for visualization
					exploredNodes.append([currentNode[0]+i,currentNode[1]+j])
					#	For plotting purpose only
					markImg([currentNode[0]+i,currentNode[1]+j], 3)
				else:
					#	check if this new distance is less than previously stored distance
					#	if dist is less, update the existing value and the new parent
					if dist < gcost[currentNode[0]+i, currentNode[1]+j]:
						#	Update the queue with latest distance information
						update(priorityQ, dist, [currentNode[0]+i, currentNode[1]+j])
						#	Update the new parent based on lower gcost
						parent[currentNode[0]+i][currentNode[1]+j] = [currentNode[0],currentNode[1]]
						#	Update the new lower gcost
						gcost[currentNode[0]+i, currentNode[1]+j] = dist

	#	Trace back using the parent node
	finalPath = [[None,None]]
	finalPath[0] = [endPoint[0], endPoint[1]]
	t = []

	# for getting the path from start to end
	try:	
		while t != startPoint:
			t = parent[finalPath[-1][0]][finalPath[-1][1]]
			finalPath.append([t[0],t[1]])
	except TypeError:
		print "Press any key to close the image\n"
		showImg(0)	#	For the user to see the final image
		print "Path to goal node does not exist. Try another goal node"
		quit()

	# for plotting the path
	for node in reversed(finalPath):
		markImg(node, 4)

	print 'Number of explored nodes in configuration space: ', len(exploredNodes)
	print 'Cost to reach destination in configuration space: ', resolution * gcost[endPoint[0], endPoint[1]], 'mm'

def main(args):

	# Parse Command Line arguments
	Parser = argparse.ArgumentParser()
	Parser.add_argument('--radius', default=5.0, help='radius of the circular robot, Default: 5.0mm')
	Parser.add_argument('--res', default=1.0, help='resolution of the map, Default: 1')
	Parser.add_argument('--clc', default=0.0, help='clearance of the map, Default: 0')
	Parser.add_argument('--startx', default=0.0, help='x coordinate of start point, Default: 0')
	Parser.add_argument('--starty', default=0.0, help='y coordinate of start point, Default: 250')
	Parser.add_argument('--endx', default=250.0, help='x coordinate of end point, Default: 0')
	Parser.add_argument('--endy', default=150.0, help='y coordinate of end point, Default: 150')
	
	Args = Parser.parse_args()
	
	radius = float(Args.radius)
	resolution = float(Args.res)
	clc = float(Args.clc)
	startPoint = (int(Args.startx), int(Args.starty))
	endPoint = (int(Args.endx), int(Args.endy))
	redStartPoint = [int(startPoint[0]/resolution), int(startPoint[1]/resolution)]
	redEndPoint = [int(endPoint[0]/resolution), int(endPoint[1]/resolution)]

	global obstacleSpace 
	obstacleSpace = obstacleSpace.main([resolution, radius, clc])

	xUnits = obstacleSpace.shape[0]
	yUnits = obstacleSpace.shape[1]

	ret, val = isCoordValidInWorkSpace(startPoint[0], startPoint[1], resolution)
	if not ret:
		if val:
			print 'Start point is not a valid point. It is in obstacle space. Please enter another point.\n'			
		else:
			print 'Start point is not a valid point. It is outside the workspace. Please enter another point.\n'
		quit()

	ret, val = isCoordValidInWorkSpace(endPoint[0], endPoint[1], resolution)
	if not ret:
		if val:
			print 'End point is not a valid point. It is in obstacle space. Please enter another point.\n'			
		else:
			print 'End point is not a valid point. It is outside the workspace. Please enter another point.\n'
		quit()

	## Uncomment to record video
	## Define the codec and create VideoWriter object
	# global out
	# fourcc = cv2.VideoWriter_fourcc(*'XVID')
	# out = cv2.VideoWriter('dijkstra.avi',fourcc, 30.0, (1000,600))

	global displayImg
	displayImg = np.full((xUnits, yUnits, 3), 255.0)

	global showObstacleFormation
	showObstacleFormation = 0

	plotObstacle()
	markImg(redStartPoint, 1)
	markImg(redEndPoint, 2)
	
	#	A-Star algorithm in the configuration space
	# aStar(redStartPoint, redEndPoint, resolution, xUnits, yUnits)
	dijkstra(redStartPoint, redEndPoint, resolution, xUnits, yUnits)

	markImg(redStartPoint, 1)
	markImg(redEndPoint, 2)
	print "Press any key to close the image\n"
	showImg(0)	#	For the user to see the final image

if __name__ == "__main__":
	main(sys.argv)