/// Author: Nicolas Martens
/// Name: Environment.h
/// Description: The header file containing function signatures to be exported to the DLL

#define _CRT_SECURE_NO_WARNINGS 1
#define _USE_MATH_DEFINES 1

#include <random>
#include <vector>
#include <cmath>

#define DLL_FUNCTION __declspec(dllexport)

#pragma execution_character_set("utf-8")

extern "C" {
	DLL_FUNCTION double** createPolygon(double x, double y, double r, double i, double s, int n);
	DLL_FUNCTION int deletePolygon(double** polygon, int n);
}