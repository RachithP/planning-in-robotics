import numpy as np
import cv2
import math
import sys

def circle(x, y, circleXcenter, circleYcenter, circleRadius):
	# 	Circular obstacle
	if (x - circleXcenter)**2 + (y - circleYcenter)**2 - circleRadius**2 <= 0:
		workSpace[x, y] = 0

def minkowski(xUnits, yUnits, resolution, rad, clc):
	'''
		This function calculates the minkowski sum for the obstacles with the robot (circular 'rad' radius in cm). Assuming the map is also in cm.
		Input:
				xUnits - x axis length of the workspace
				yUnits - y axis length of the workspace
				resolution - grid size for configuration space
				rad - radius of the robot
				clc - clearance for the robot
		Output:
				configspace with obstaclespace, resolution update
	'''
	global workSpace
	workSpace = np.ones((xUnits+1, yUnits+1))*255

	configSpace = np.ones((int(round(xUnits/resolution))+1, (int(round(yUnits/resolution))+1)))*255

	clc = rad + clc
	# print 'Size of new workspace space: ', configSpace.shape

	for x in range(xUnits+1):
		for y in range(yUnits+1):

			#	Square obstacle. Since edges are parallel to x & y axes, equation of lines are direct.
			# 1
			if x >= int(983-clc) and x <= math.ceil(1026+clc) and y >= int(919-clc) and y <= math.ceil(1010):
				workSpace[x, y] = 0
			# 2
			if x >= int(832-clc) and x <= math.ceil(918+clc) and y >= int(827-clc) and y <= math.ceil(1010):
				workSpace[x, y] = 0
			# 3
			if x >= int(744-clc) and x <= math.ceil(1110) and y >= int(621-clc) and y <= math.ceil(697+clc):
				workSpace[x, y] = 0
			# 4
			if x >= int(1052-clc) and x <= math.ceil(1110) and y <= math.ceil(565.5+clc) and y >= int(448.5-clc):
				workSpace[x, y] = 0
			# 5
			if x >= int(1019-clc) and x <= math.ceil(1110) and y >= int(362.5-clc) and y <= int(448.5-clc):
				workSpace[x, y] = 0
			# 6
			if x >= int(1052-clc) and x <= math.ceil(1110) and y >= int(178.25-clc) and y <= math.ceil(295.25+clc):
				workSpace[x, y] = 0
			# 7
			if x >= int(927-clc) and x <= math.ceil(1110) and y >= int(35-clc) and y <= math.ceil(111+clc):
				workSpace[x, y] = 0
			# 8
			if x >= int(779-clc) and x <= math.ceil(896+clc) and y >= int(35-clc) and y <= math.ceil(93+clc):
				workSpace[x, y] = 0
			# 9
			if x >= int(474-clc) and x <= math.ceil(748+clc) and y >= int(35-clc) and y <= math.ceil(187+clc):
				workSpace[x, y] = 0
			# 10
			if x >= int(438-clc) and x <= math.ceil(529+clc) and y >= int(315-clc) and y <= math.ceil(498+clc):
				workSpace[x, y] = 0
			# 11
			if x >= int(529-clc) and x <= math.ceil(712+clc) and y >= int(265-clc) and y <= math.ceil(341+clc):
				workSpace[x, y] = 0
			# 12
			if x >= int(784.5-clc) and x <= math.ceil(936.5+clc) and y >= int(267-clc) and y <= math.ceil(384+clc):
				workSpace[x, y] = 0
			# 13 - obstacle at the bottom most part
			if x >= int(685-clc) and x <= math.ceil(1110) and y >= 0 and y <= math.ceil(35+clc):
				workSpace[x, y] = 0


			# Semi-circles + rectangle obstacle
			# circle(x, y, 149.95, 830.05, 79.95+clc)
			# circle(x, y, 309.73, 830.05, 79.95+clc)
			rad = 0.5*math.ceil(910+clc) - 0.5*int(750.10-clc)
			ycenter = 0.5*math.ceil(910+clc) + 0.5*int(750.10-clc)
			circle(x, y, 149.95, ycenter, rad)
			circle(x, y, 309.73, ycenter, rad)
			if x >= int(149.95-clc) and x <= math.ceil(309.73+clc) and y >= int(750.10-clc) and y <= math.ceil(910+clc):
				workSpace[x, y] = 0

			# Circular obstacles
			circle(x, y, 390, 45, 40.5+clc)
			circle(x, y, 438, 274, 40.5+clc)
			circle(x, y, 390, 965, 40.5+clc)
			circle(x, y, 438, 736, 40.5+clc)

	#	creating a new workspace based on resolution input
	for x in range(0, xUnits+1-int(resolution), int(resolution)):
		for y in range(0, yUnits+1-int(resolution), int(resolution)):
			configSpace[int(x/resolution), int(y/resolution)] = workSpace[x:x+int(resolution), y:y+int(resolution)].min()

	if clc != 0:
		configSpace[int(xUnits/resolution)-int(clc/resolution):xUnits+1, :] = 0
		configSpace[:, int(yUnits/resolution)-int(clc/resolution):yUnits+1] = 0
		configSpace[0:int(clc/resolution), :] = 0
		configSpace[:, 0:int(clc/resolution)] = 0

	# imgrot = np.rot90(configSpace,1)
	# cv2.namedWindow('workSpace')        # Create a named window
	# cv2.moveWindow('workSpace', 50,50)
	# cv2.imshow('workSpace', imgrot)
	# cv2.waitKey(0)
	return workSpace, configSpace
 
def main(args):
	'''
		This function will be called by the planning algorithm
		Input in order:
				resolution
				radius of the robot
				clearance
		Output:
				updated map with minkowski sum along with clearance for the robot
	'''
	xUnits = 1110
	yUnits = 1010

	workSpace, configSpace = minkowski(xUnits, yUnits, float(args[0]), float(args[1]), float(args[2]))
	# workSpace, configSpace = minkowski(xUnits, yUnits, 1, 22.0, 10.0)

	return configSpace

if __name__ == "__main__":
	main(sys.argv)
