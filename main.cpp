#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

#define M_PI 3.14159265358979323846

const double ROLL_DEGREES = 100.0;
const double PITCH_DEGREES = 0.0;
const double YAW_DEGREES = 90.0;

int main() {
    // Camera parameters
    double cx = 636.0;
    double cy = 548.0;
    double fx = 241.0;
    double fy = 238.0;

    // Camera Pos (meters)
    double x_pos = 0.5;
    double y_pos = 0.16;
    double z_pos = 1.14;

    // Pixel coordinates of the object
    double u = 795.0;
    double v = 467.0;

    double d = 2.7;
    double x_normalized = (u - cx) / fx;
    double y_normalized = (v - cy) / fy;

    // Calculate 3D coordinates in camera frame
    double x_camera = d * x_normalized;
    double y_camera = d * y_normalized;
    double z_camera = d;

    // Convert to radians
    double roll = ROLL_DEGREES * M_PI / 180.0;
    double pitch = PITCH_DEGREES * M_PI / 180.0;
    double yaw = YAW_DEGREES * M_PI / 180.0;

    double x_vehicle = (x_camera * cos(yaw) - y_camera * sin(yaw) * sin(roll) - z_camera * sin(yaw) * cos(roll)) + x_pos;
    double y_vehicle = (x_camera * sin(yaw) + y_camera * cos(yaw) * sin(roll) + z_camera * cos(yaw) * cos(roll)) + y_pos;
    double z_vehicle = (y_camera * cos(roll) - z_camera * sin(roll)) + z_pos;

    // Rounded the coordinates to three decimal places
    x_vehicle = round(x_vehicle * 1000.0) / 1000.0;
    y_vehicle = round(y_vehicle * 1000.0) / 1000.0;
    z_vehicle = round(z_vehicle * 1000.0) / 1000.0;

    // Output the 3D coordinates in the vehicle frame
    std::ofstream outputFile("coordinates.txt");
    if (outputFile.is_open()) {
        outputFile << std::fixed << std::setprecision(3);
        outputFile << x_vehicle << ", " << y_vehicle << ", " << z_vehicle << std::endl;
        outputFile.close();
    } else {
        std::cerr << "Unable to open the file for writing." << std::endl;
    }


    return 0;
}