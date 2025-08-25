/// Name: Environment.cpp
/// Version: 0.0.3-alpha
/// Description: The file containing function definitions for anything environment related
/// Author: Nicolas Martens


#include "Environment.h"

using namespace std;

/// <summary>
/// Generates the angles at which the points of the polygon should go on, using a uniform distribution with the irregularity value
/// </summary>
/// <param name="n">The number of points in the polygonv</param>
/// <param name="i">The irregularity value</param>
/// <returns>A list of angles representing the angle at which each point on the polygon will go on</returns>
vector<double> generateSteps(int n, double i) {
	// Initialise our variables
	vector<double> angles;
	double lowerBound = (2 * M_PI / n) - i;
	double upperBound = (2 * M_PI / n) + i;
	double angleSum = 0;
	random_device seed;
	mt19937 gen(seed());
	uniform_real_distribution<double> rand(lowerBound, upperBound);
	// For each angle, get some variance based on our irregularity value
	for (int i = 0; i < n; i++) {
		double angle = rand(gen);
		angles.push_back(angle);
		angleSum += angle;
	}
	// Summation for some tidiness
	angleSum /= 2 * M_PI;
	for (int i = 0; i < n; i++) angles[i] /= angleSum;
	return angles;
}

/// <summary>
/// Clip the value to make sure it will lie between our values
/// </summary>
/// <param name="value">The value to clip</param>
/// <param name="lower">The lower allowed bound of our value</param>
/// <param name="upper">The upper allowed bound of our value</param>
/// <returns>The clipped value</returns>
double clip(double value, double lower, double upper) {
	return min(upper, max(value, lower));
}

/// <summary>
/// Creates a polygon from some preset values, using gaussian distribution to randomly generate point locations around a focal point
/// </summary>
/// <param name="x">The X coordinate of the focal point</param>
/// <param name="y">The y coordinate of the focal point</param>
/// <param name="r">The base radius of the focal point</param>
/// <param name="i">A number between 0 and 1 inclusive representing the irregularity of point locations</param>
/// <param name="s">A number between 0 and 1 inclusive representing the spikiness of the polygon points</param>
/// <param name="n">The amount of points that the polygon should have</param>
/// <returns>A 2D list representing the points that make up the polygon</returns>
DLL_FUNCTION double** createPolygon(double x, double y, double r, double i, double s, int n) {
	// Adjust our parameters to be relative
	i *= 2 * M_PI / n;
	s *= r;
	// Generate our polygon angles
	vector<double> angles = generateSteps(n, i);
	random_device seed;
	mt19937 gen(seed());
	uniform_real_distribution<double> once(0, 2 * M_PI);
	normal_distribution<double> rand(r, s);
	double angle = once(gen);
	double** ret = new double*[n];
	// For each point, generate the location
	for (int i = 0; i < n; i++) {
		double radius = clip(rand(gen), 0, 2 * r);
		double* point = new double[2](x + r * cos(angle), y + r * sin(angle));
		ret[i] = point;
		angle += angles[i];
	}
	return ret;
}

/// <summary>
/// Deletes a polygon by releasing the memory stored by the pointers
/// </summary>
/// <param name="polygon">The pointer to the first element in the polygon</param>
/// <param name="n">The amount of points in the polygon</param>
/// <returns>The integer 0</returns>
DLL_FUNCTION int deletePolygon(double** polygon, int n) {
	for (int i = 0; i < n; i++) delete[] polygon[i];
	delete[] polygon;
	return 0;
}
