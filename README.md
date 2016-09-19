# Optical-Security-Threat-Detection
Project for DT228 Computer Science.

Optical-Security-Threat-Detection system features:

  1. Gaussian Blur
  2. Canny Edge Detection
  3. Feature detection using Hough, Harris, etc.
  4. Colour Threshold
  5. Image classification

Usage:

To use this software, run the executable and follow the prompts to have a directory of included images analysed.
It can also be ran by placing an image in the directory with the executable and using its filename as an argument.

In the Test_Eval directory are Python scripts. To run an evaluation of the system, run the following command from inside the directory

  "python OSTD_Test.py" (followed by "-Threat" or "-Non_Threat" as the argument, to evaluate against appropriate image set)

About:

The C++ application was developed using the MinGW 32 bit GCC 4.8 compilers, OpenCV 3.0 library and Netbeans 8.1 IDE.

The Python scripts were developed using Python 3.5 with standard libraries
