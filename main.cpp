#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "QuadTree.h"
using namespace std;

ifstream fin("index.in.txt");

int main() {
    // Read the quad tree representations from the input file
    string representation1;
    string representation2;
    fin >> representation1;
    fin >> representation2;

    // Create the quad trees from the representations
    int index = 0;
    QuadTree* tree1 = QuadTree::inserare_rec(representation1, index);
    index = 0;
    QuadTree* tree2 = QuadTree::inserare_rec(representation2, index);

    // Display the quad trees in pre-order traversal
    cout << "QuadTree 1: ";
    tree1->preOrderTraversal();
    cout << endl;

    cout << "QuadTree 2: ";
    tree2->preOrderTraversal();
    cout << endl;

    // Equalize the heights of the two quad trees
    int maxHeight = max(tree1->maximumHeight(0), tree2->maximumHeight(0));
    QuadTree* equalizedTree1 = tree1->equalizeTree(tree1, 0, maxHeight);
    QuadTree* equalizedTree2 = tree2->equalizeTree(tree2, 0, maxHeight);

    // Display the equalized quad trees in pre-order traversal
    cout << "Equalized Tree1:" << endl;
    equalizedTree1->preOrderTraversal();
    cout << endl;

    cout << "Equalized Tree2:" << endl;
    equalizedTree2->preOrderTraversal();
    cout << endl;

    // Merge the two equalized quad trees
    QuadTree* mergedTree = equalizedTree1->mergeTrees(equalizedTree1, equalizedTree2);
    cout << "Merged QuadTree: ";
    mergedTree->preOrderTraversal();
    cout << endl;

    // Display the quad trees at each level for debugging purposes
    tree1->Display(0);
    cout << endl;
    tree1->Display(1);
    cout << endl;
    tree1->Display(2);
    cout << endl;

    tree2->Display(0);
    cout << endl;
    tree2->Display(1);
    cout << endl;
    tree2->Display(2);
    cout << endl;

    equalizedTree1->Display(0);
    cout << endl;
    equalizedTree1->Display(1);
    cout << endl;
    equalizedTree1->Display(2);
    cout << endl;

    equalizedTree2->Display(0);
    cout << endl;
    equalizedTree2->Display(1);
    cout << endl;
    equalizedTree2->Display(2);
    cout << endl;

    mergedTree->Display(0);
    cout << endl;
    mergedTree->Display(1);
    cout << endl;
    mergedTree->Display(2);
    cout << endl;
    
    cout << endl;

    int imageSize = 32; // Size of the image (32x32)
    vector<vector<char>> matrix1 = tree1->createMatrix(imageSize);
    vector<vector<char>> matrix2 = tree2->createMatrix(imageSize);
    vector<vector<char>> matrixEqual1 = equalizedTree1->createMatrix(imageSize);
    vector<vector<char>> matrixEqual2 = equalizedTree2->createMatrix(imageSize);
    vector<vector<char>> matrixMerged = mergedTree->createMatrix(imageSize);
    
    // Display the matrix representation of the images for debugging purposes
    cout << endl;
    for (int i = 0; i < imageSize; i++) {
        for (int j = 0; j < imageSize; j++) {
            cout << matrix1[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    for (int i = 0; i < imageSize; i++) {
        for (int j = 0; j < imageSize; j++) {
            cout << matrix2[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    for (int i = 0; i < imageSize; i++) {
        for (int j = 0; j < imageSize; j++) {
            cout << matrixMerged[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    for (int i = 0; i < imageSize; i++) {
        for (int j = 0; j < imageSize; j++) {
            cout << matrixEqual1[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    for (int i = 0; i < imageSize; i++) {
        for (int j = 0; j < imageSize; j++) {
            cout << matrixEqual2[i][j] << " ";
        }
        cout << endl;
    }

    // Calculate the number of black pixels in the images
    int blackPixelCount1 = tree1->calculateBlackPixelCount(matrix1);
    cout << "Number of black pixels: " << blackPixelCount1 << endl;
    int blackPixelCount2 = tree2->calculateBlackPixelCount(matrix2);
    cout << "Number of black pixels: " << blackPixelCount2 << endl;
    int blackPixelCountMerged = mergedTree->calculateBlackPixelCount(matrixMerged);
    cout << "Number of black pixels: " << blackPixelCountMerged << endl;

    // Clean up dynamically allocated memory
    delete tree1;
    delete tree2;
    delete equalizedTree1;
    delete equalizedTree2;
    delete mergedTree;

    return 0;
}
