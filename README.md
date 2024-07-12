# QuadTree Image Processor

## Overview
This project implements a QuadTree data structure for image processing. It reads two QuadTree representations from an input file, constructs the QuadTrees, equalizes their heights, merges them, and performs various operations to visualize and analyze the resulting images.

## Features
- Construct QuadTrees from string representations.
- Pre-order traversal of QuadTrees.
- Equalize the height of two QuadTrees.
- Merge two QuadTrees.
- Convert QuadTrees to matrix representations.
- Calculate the number of black pixels in the resulting image.
- Display QuadTree nodes at specific levels for debugging.

## Code Overview
``main.cpp``
The main file contains the core logic for:

- Reading QuadTree representations from an input file.
- Constructing QuadTrees.
- Equalizing the heights of the QuadTrees.
- Merging the QuadTrees.
- Displaying QuadTrees in pre-order traversal and matrix representation.
- Calculating the number of black pixels.

``QuadTree.h``
This header file defines the QuadTree class and its associated methods:

`inserare_rec`: Constructs a QuadTree from a string representation.
`createMatrix`: Creates a matrix representation of the image from the QuadTree.
`calculateBlackPixelCount`: Calculates the number of black pixels in the matrix.
`equalizeTree`: Equalizes the height of the QuadTree.
`mergeTrees`: Merges two QuadTrees.
`preOrderTraversal`: Performs a pre-order traversal of the QuadTree.
`maximumHeight`: Calculates the maximum height of the QuadTree.
`Display`: Displays the QuadTree nodes at a specific level.
`createMatrixRecursive`: Fills the matrix from the QuadTree.