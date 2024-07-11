#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "QuadTree.h"
using namespace std;

ifstream fin("index.in.txt");



int main() {
    string representation1;
    string representation2;
    fin >> representation1;
    fin >> representation2;

    //creere tree
    int index = 0;
    QuadTree* tree1 = QuadTree::inserare_rec(representation1, index);
    index = 0;
    QuadTree* tree2 = QuadTree::inserare_rec(representation2, index);

    // Afisare pre-order
    cout << "QuadTree 1: ";
    tree1->preOrderTraversal();
    cout << endl;

    cout << "QuadTree 2: ";
    tree2->preOrderTraversal();
    cout << endl;

    //Egalare crengi
    int maxHeight = max(tree1->maximumHeight(0), tree2->maximumHeight(0));
    QuadTree* equalizedTree1 = tree1->equalizeTree(tree1, 0, maxHeight);
    QuadTree* equalizedTree2 = tree2->equalizeTree(tree2, 0, maxHeight);
    cout << "Equalized Tree1:" << endl;
    equalizedTree1->preOrderTraversal();
    cout << endl;
    cout << "Equalized Tree2:" << endl;
    equalizedTree2->preOrderTraversal();
    cout << endl;

    // Merge la cele 2 tree egalate
    QuadTree* mergedTree = equalizedTree1->mergeTrees(equalizedTree1, equalizedTree2);
    cout << "Merged QuadTree: ";
    mergedTree->preOrderTraversal();
    cout << endl;

    //afisare nivele
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
    
    cout << endl;
    // Display the matrix representation of the picture
    for (int i = 0; i < imageSize; i++) {
        for (int j = 0; j < imageSize; j++) {
            cout << matrix1[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    // Display the matrix representation of the picture
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

    int blackPixelCount1 = tree1->calculateBlackPixelCount(matrix1);
    cout << "Number of black pixels: " << blackPixelCount1 << endl;
    int blackPixelCount2 = tree2->calculateBlackPixelCount(matrix2);
    cout << "Number of black pixels: " << blackPixelCount2 << endl;
    int blackPixelCountMerged = mergedTree->calculateBlackPixelCount(matrixMerged);
    cout << "Number of black pixels: " << blackPixelCountMerged << endl;

    // sterge Tree
    delete tree1;
    delete tree2;
    delete equalizedTree1;
    delete equalizedTree2;
    delete mergedTree;

    return 0;
}
