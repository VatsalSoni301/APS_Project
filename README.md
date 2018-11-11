# Splay Tree and its comparison with AVL Tree
## Requirements
**Platform:** Linux <br/>
**Software Requirement**
1. Python version 2.7
   * **To install python :** ```sudo apt-get install python2.7 python-pip```
2. G++ compiler
   * **To install G++ :** ```sudo apt-get install g++```
3. Matplotlib library for graph
   * **To install Matplot library :** ```pip install matplotlib```
   
## How to run project
1. To compile splay tree and AVL tree
   * ```g++ splay.cpp –o splay```
   * ```g++ avl.cpp –o avl```
2. To Run splay tree and AVL tree
   * ```./splay```
   * ```./avl```

## How to run test cases
1. Go to test folder
2. Run test file
   * ```python test.py```
3. If you want to test splay tree implementation, there are some test case for it. For
that you have to run test.py.

## How to get graphical analysis
1. Go to graph folder
2. Run script file
   * ```python script.py```
3. If you want depth graphical analysis of splay tree and AVL tree, then run
script.py .It will generate graph for each operation. Graph shows time taken for
each operation.

## Abstract definition of splay tree operations
1. **Insert :** <br/>
**Function Definition:** ```void insertnode(long long key)``` <br/>
**Description:** Insert function takes one integer argument and insert it into the
tree. If key is already present then it will show appropriate message.
2. **Delete :**<br/>
**Function Definition:** ```bool deletenode(long long key)```<br/>
**Description:** Delete function takes one integer argument and delete if from tree
if it exists. Otherwise it shows error message.
If element deleted successfully then it will return true, else return false.
3. **Search :**<br/>
**Function Definition:** ```bool search(long long key)```<br/>
**Description:** Search function takes one integer argument and search that key in
the tree and show appropriate message.
If key found in the tree then it will return true, else return false.
3. **Tree Traversal :**<br/>
**Function Definition:** ```void inorder(struct node *root)```<br/>
**Description:** Inorder function takes root of the tree as argument and print
inorder traversal of the tree.
