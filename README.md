# Memory-Management-Simulator

A fully page internal memory management simlulator that runs different heap algorithms and compares the results!

## Disclaimer

This application was designed with certain specifications.

## Requirements

This application requires the use of cmake 3.0 and C++98 to build.

## Installation Instructions:

First, cd into the directory you would like to install this application in

Then git clone this repository
```bash
git clone https://github.com/zwimer/Memory-Management-Simulator
```

Create your build directory as follows
```bash
mkdir Memory-Management-Simulator/build && cd Memory-Management-Simulator/build/
```

After that run qmake and make with the command below
```bash
cmake .. && make
```

## Usage
This application takes two arguments. The first is the input file, the file to be read. And the second is the file to which the simulations statics must be written.
