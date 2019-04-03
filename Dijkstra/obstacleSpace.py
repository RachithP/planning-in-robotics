import numpy as np
import cv2, math, sys

# for calculating the equation of a line given 2 points
def calculateLineEquation(point1, point2):
	return point2[1]-point1[1], point1[0]-point2[0], point2[0]*point1[1]-point1[0]*point2[1]

# for calculating intersecting point of 2 lines
def lineIntersection(line1, line2):

	a1 = line1[0]; b1 = line1[1]; c1 = line1[2]
	a2 = line2[0]; b2 = line2[1]; c2 = line2[2]
	div = float(a1 * b2 - a2 * b1)

	if int(div) == 0:
		raise Exception('lines do not intersect')

	x = (c2 * b1 - c1 * b2)/ div
	y = (c1 * a2 - c2 * a1) / div

	return x, y

def minkowski(xUnits, yUnits, resolution, rad, clc):
	'''
		This function calculates the minkowski sum for the obstacles with the robot (circular radmm radius). Assuming the map is also in mm.
		Input:
				xUnits - x axis length of the workspace
				yUnits - y axis length of the workspace
				resolution - grid size for configuration space
				rad - radius of the obstacle
				clc - clearance of the robot
		Output:
				workspace with obstaclespace updated
	'''
	workSpace = np.ones((xUnits+1, yUnits+1))*255

	configSpace = np.ones((int(round(xUnits/resolution))+1, (int(round(yUnits/resolution))+1)))*255
	# print 'Size of new workspace space: ', configSpace.shape
	
	radius = rad + clc
	ellipseXcenter = 140
	ellipseYcenter = 120
	ellipseMajorAxis = 15 + radius
	ellipseMinorAxis = 6 + radius
	circleXcenter = 190
	circleYcenter = 130
	circleRadius = 15 + radius

	#	Equation of a line is given by x(y2-y1) + y(x1-x2) + x2y1-x1y2 = 0
	#	First line (150,15) & (173,15)
	a1, b1, c1 = calculateLineEquation([150.0,15.0], [173.0, 15.0])
	#	Second line (125,56) & (150,15)
	a2, b2, c2 = calculateLineEquation([125.0,56.0], [150.0, 15.0])
	#	Third line (163,52) & (125,56)
	a3, b3, c3 = calculateLineEquation([163.0,52.0], [125.0, 56.0])
	#	Fourth line (170,90) & (163,52)
	a4, b4, c4 = calculateLineEquation([170.0,90.0], [163.0, 52.0])
	#	Fifth line (193,52) & (170,90)
	a5, b5, c5 = calculateLineEquation([193.0,52.0], [170.0, 90.0])
	#	Sixth line (173,15) & (193,52)
	a6, b6, c6 = calculateLineEquation([173.0,15.0], [193.0, 52.0])
	#	Seventh line (163, 52) & (173, 15).
	a7, b7, c7 = calculateLineEquation([163.0,52.0], [173.0, 15.0])


	#	Calculate new line equations based on the above equations. This is after applying minkowski sum
	#	This is done separately for each line
	#	First line (150,15) & (173,15)
	A1 = a1; B1 = b1; C1 = c1 + radius*b1
	#	Second line (125,56) & (150,15)
	A2 = a2; B2 = b2; C2 = c2 + (radius/math.cos(math.atan(A2/B2)))*b2
	#	Third line (163,52) & (125,56)
	A3 = a3; B3 = b3; C3 = c3 - (radius/math.cos(math.atan(A3/B3)))*b3
	#	Fourth line (170,90) & (163,52)
	A4 = a4; B4 = b4; C4 = c4 - (radius/math.cos(math.atan(A4/B4)))*b4
	#	Fifth line (193,52) & (170,90)
	A5 = a5; B5 = b5; C5 = c5 - (radius/math.cos(math.atan(A5/B5)))*b5
	#	Sixth line (173,15) & (193,52)
	A6 = a6; B6 = b6; C6 = c6 + (radius/math.cos(math.atan(A6/B6)))*b6
	#	Now find the intersection of line 3,4 and 1,6
	x1, y1 = lineIntersection([A3,B3,C3], [A4,B4,C4])
	x2, y2 = lineIntersection([A1,B1,C1], [A6,B6,C6])
	A7, B7, C7 = calculateLineEquation([x1, y1], [x2, y2])

	for x in range(xUnits+1):
		for y in range(yUnits+1):

			#	Square obstacle. Since edges are parallel to x & y axes, equation of lines are direct.
			if x >= int(50+radius) and x <= math.ceil(100+radius) and y>=int(67.5+radius) and y <= math.ceil(112.5+radius):
				workSpace[x, y] = 0

			#	Ellipsoid obstacle
			if ((x - ellipseXcenter)**2)/ellipseMajorAxis**2 + ((y - ellipseYcenter)**2/ellipseMinorAxis**2) - 1 <= 0:
				workSpace[x, y] = 0

			# 	Circular obstacle
			if (x - circleXcenter)**2 + (y - circleYcenter)**2 - circleRadius**2 <= 0:
				workSpace[x, y] = 0

			#	Define half-planes for getting the boundary of the polygon
			if (x*A1+y*B1+C1 <= 0) and (x*A2+y*B2+C2 <= 0) and (x*A3+y*B3+C3 <= 0) and (x*A7+y*B7+C7 >= 0):
				workSpace[x, y] = 0
			if (x*A4+y*B4+C4 <= 0) and (x*A5+y*B5+C5 <= 0) and (x*A6+y*B6+C6 <= 0) and (x*A7+y*B7+C7 <= 0):
				workSpace[x, y] = 0

			#	considering map boundaries as obstacles
			if radius != 0:
				if (x>xUnits-radius) or (x<radius) or (y>yUnits-radius) or (y<radius):
					workSpace[x, y] = 0

	#	creating a new workspace based on resolution input
	for x in range(0, xUnits+1-int(resolution), int(resolution)):
		for y in range(0, yUnits+1-int(resolution), int(resolution)):
			configSpace[int(x/resolution), int(y/resolution)] = workSpace[x:x+int(resolution), y:y+int(resolution)].min()
	
	if radius != 0:
		configSpace[int(xUnits/resolution)-int(radius/resolution), :] = 0
		configSpace[:, int(yUnits/resolution)-int(radius/resolution)] = 0

	# cv2.imshow('workSpace', configSpace)
	# cv2.waitKey(0)
	return configSpace

def main(args):
	'''
		This function will be called by the planning algorithm
		Input in order:
				resolution
				radius of the robot
				clearance
		Output:
				updated map with minkowski sum
	'''
	xUnits = 250
	yUnits = 150
	
	configSpace = minkowski(xUnits, yUnits, float(args[0]), float(args[1]), float(args[2]))
	# workSpace, configSpace = minkowski(xUnits, yUnits, float(args[1]), float(args[2]), float(args[3]))

	return configSpace

if __name__ == "__main__":
	main(sys.argv)