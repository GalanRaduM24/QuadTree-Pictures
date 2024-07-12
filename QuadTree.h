#include <iostream>
#include <string>
#include <vector>

using namespace std;
int max_height = 0;

class QuadTree {
public:
    char value; // 'p' for parent, 'b' for black, 'w' for white
    QuadTree* topLeft;
    QuadTree* topRight;
    QuadTree* bottomLeft;
    QuadTree* bottomRight;

    QuadTree(char val) {
        value = val;
        topLeft = topRight = bottomLeft = bottomRight = nullptr;
    }

    // Recursive function to insert nodes in the quad tree from a pre-order representation
    static QuadTree* inserare_rec(const string& representation, int& index) {
        if (index >= representation.length())
            return nullptr;

        char val = representation[index++];
        QuadTree* node = new QuadTree(val);

        if (val == 'p') {
            node->topRight = inserare_rec(representation, index);
            node->topLeft = inserare_rec(representation, index);
            node->bottomLeft = inserare_rec(representation, index);
            node->bottomRight = inserare_rec(representation, index);
        }

        return node;
    }

    // Create a matrix representation of the image from the quad tree
    vector<vector<char>> createMatrix(int size) {
        vector<vector<char>> matrix(size, vector<char>(size, ' '));
        createMatrixRecursive(this, matrix, 0, 0, size);
        return matrix;
    }

    // Calculate the number of black pixels in a matrix
    int calculateBlackPixelCount(const vector<vector<char>>& matrix) {
        int count = 0;
        for (const auto& row : matrix) {
            for (char pixel : row) {
                if (pixel == 'b') {
                    count++;
                }
            }
        }
        return count;
    }

    // Equalize the heights of the quad tree
    QuadTree* equalizeTree(QuadTree* tree, int currentHeight, int maxHeight) {
        if (tree == nullptr)
            return nullptr;

        // If the current node is not a parent and we need to add children to reach the max height
        if (currentHeight < maxHeight && tree->value != 'p') {
            char color;
            if (tree->value == 'b') {
                color = 'b';
            }
            else {
                color = 'w';
            }
            QuadTree* equalizedNode = new QuadTree('p');
            equalizedNode->topRight = new QuadTree(color);
            equalizedNode->topLeft = new QuadTree(color);
            equalizedNode->bottomLeft = new QuadTree(color);
            equalizedNode->bottomRight = new QuadTree(color);
            return equalizedNode;
        }

        // Recursively equalize the children
        QuadTree* equalizedNode = new QuadTree(tree->value);
        equalizedNode->topRight = equalizeTree(tree->topRight, currentHeight + 1, maxHeight);
        equalizedNode->topLeft = equalizeTree(tree->topLeft, currentHeight + 1, maxHeight);
        equalizedNode->bottomLeft = equalizeTree(tree->bottomLeft, currentHeight + 1, maxHeight);
        equalizedNode->bottomRight = equalizeTree(tree->bottomRight, currentHeight + 1, maxHeight);

        return equalizedNode;
    }
   
    // Merge two quad trees
    QuadTree* mergeTrees(QuadTree* tree1, QuadTree* tree2) {
        if (tree1 == nullptr)
            return tree2;
        if (tree2 == nullptr)
            return tree1;

        if (tree1->value != 'p' && tree2->value != 'p') {
            if (tree1->value == 'b' || tree2 -> value == 'b')
                return new QuadTree('b');
            else
                return new QuadTree('w');
        }

        // Merge the children
        QuadTree* mergedNode = new QuadTree('p');
        mergedNode->topRight = mergeTrees(tree1->topRight, tree2->topRight);
        mergedNode->topLeft = mergeTrees(tree1->topLeft, tree2->topLeft);
        mergedNode->bottomLeft = mergeTrees(tree1->bottomLeft, tree2->bottomLeft);
        mergedNode->bottomRight = mergeTrees(tree1->bottomRight, tree2->bottomRight);

        // If all children are leaves of the same color, collapse the node
        if (mergedNode->topRight != nullptr && mergedNode->topLeft->value == mergedNode->topRight->value &&
            mergedNode->topLeft->value == mergedNode->bottomLeft->value && mergedNode->topLeft->value == mergedNode->bottomRight->value &&
            mergedNode->topRight->value != 'p') {
            char value = mergedNode->topLeft->value;
            delete mergedNode->topLeft;
            delete mergedNode->topRight;
            delete mergedNode->bottomLeft;
            delete mergedNode->bottomRight;
            mergedNode->topLeft = nullptr;
            mergedNode->topRight = nullptr;
            mergedNode->bottomLeft = nullptr;
            mergedNode->bottomRight = nullptr;
            mergedNode->value = value;
        }

        return mergedNode;
    }

    // Pre-order traversal of the quad tree
    void preOrderTraversal() {
        cout << value;

        if (value == 'p') {
            if (topRight != nullptr)
                topRight->preOrderTraversal();
            if (topLeft != nullptr)
                topLeft->preOrderTraversal();
            if (bottomLeft != nullptr)
                bottomLeft->preOrderTraversal();
            if (bottomRight != nullptr)
                bottomRight->preOrderTraversal();
        }
    }

    // Calculate the maximum height of the quad tree
    int maximumHeight(int level)
    {
        if (topLeft != NULL)
        {
            int leftHeight = topLeft->maximumHeight(level + 1);
            max_height = max(max_height, leftHeight);
        }
        if (topRight != NULL)
        {
            int rightHeight = topRight->maximumHeight(level + 1);
            max_height = max(max_height, rightHeight);
        }
        if (bottomLeft != NULL)
        {
            int bottomLeftHeight = bottomLeft->maximumHeight(level + 1);
            max_height = max(max_height, bottomLeftHeight);
        }
        if (bottomRight != NULL)
        {
            int bottomRightHeight = bottomRight->maximumHeight(level + 1);
            max_height = max(max_height, bottomRightHeight);
        }
        if (max_height < level)
            max_height = level;
        return max_height;
    }

    // Display the quad tree values at a specific level
    void Display(int level)
    {
        if (level == 0)
            cout << value << " ";
        else {
            if (topRight != NULL)
                topRight->Display(level - 1);
            if (topLeft != NULL)
                topLeft->Display(level - 1);
            if (bottomLeft != NULL)
                bottomLeft->Display(level - 1);
            if (bottomRight != NULL)
                bottomRight->Display(level - 1);
        }
    }

    // Recursive function to fill the matrix from the quad tree
    void createMatrixRecursive(QuadTree* node, vector<vector<char>>& matrix, int row, int col, int size) {
        if (node->value == 'b' || node->value == 'w') {
            // Fill the corresponding region in the matrix with the pixel value
            for (int i = row; i < row + size; i++) {
                for (int j = col; j < col + size; j++) {
                    matrix[i][j] = node->value;
                }
            }
        }
        else if (node->value == 'p') {
            // Recursively fill the four quadrants
            createMatrixRecursive(node->topLeft, matrix, row, col, size / 2);
            createMatrixRecursive(node->topRight, matrix, row, col + size / 2, size / 2);
            createMatrixRecursive(node->bottomLeft, matrix, row + size / 2, col, size / 2);
            createMatrixRecursive(node->bottomRight, matrix, row + size / 2, col + size / 2, size / 2);
        }
    }

};
