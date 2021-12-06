# About

Here is project of data structure and algorithm course in NEU.

# Test 1

## topic

Storing students' score and performing simple statistics using a linked list.

## tutorial

The students' Chinese and mathematics scores are stored,  the statistics of the maximum, minimum, and average values are realized.

The new information is inserted at the front. The complexity is $O(1)$.

The linked list is traversed form front to end for displaying. The complexity is $O(n)$.

# Test 2

## topic

Infix expression parsing using stacks.

## tutorial

My stack is realized by array.

For the processing of infix expressions, two stacks are used, one of which is a number stack and the other is an operator stack.

Implement the ```eval()``` function to perform an operation, such that two numbers on the top of the number stack are popped sequentially, the operator on the top of the operator stack is popped, and the two numbers are subjected to the operation represented by the operator and pushed into the number stack.

Traverse expression:

- When a number is read, push the number into the number stack.
- When the opening parenthesis is read, it is pushed onto the operator stack.
- When the right parenthesis is read, the ```eval()``` operation is continued until the top of the operator stack is the left parenthesis, and the left parenthesis is popped. The priority of parentheses is handled in this way.
- When the four arithmetic operators are read, continue to perform the ```eval()``` operation until the top of the operator stack is the left parenthesis or the priority of the top operator is less than the four arithmetic operations corresponding to the four arithmetic operators. In this way, the precedence of the four arithmetic operators is processed.

When the traversal is over, continue to perform the ```eval()``` operation until the operator stack is empty, at this time the top of the number stack is the value of the infix expression.

Let the length of the infix expression string be $$n$$, then the complexity is $$O(n)$$.

# Test 3

## topic

Building a given a tree. Querying all sons of a given node.

## tutorial

Adopt adjacency list for storage.

In this test, for the node ```u``` is composed of ```k``` nodes ```v```, the additional information ```k``` can be stored in the node```v``` for querying easily.

It is worth noting that the node in this question is uniquely restricted by the name which is is string, so we need to map the string to a number. Because the language is restricted to C, it is difficult to implement the common mapping algorithm. The methods that can be considered for this question are string hash, balanced binary tree, red-black tree, trie, etc.

Let the length of the string be $$s$$ and the number of nodes be $$n$$, so the complexity of mapping by trie is $$O(s)$$, which is the most efficient. This project uses a trie to realize the mapping from strings to numbers.

# Test 4

## topic

Calculating the BST weight for a given connected graph.

## tutorial

Use the adjacency list for storage. Same as above, the node in this question is uniquely constrained by the name of the string type, and a trie is used for mapping.

Use the prim algorithm.





# 关于

本项目为东北大学数据结构与算法实验课代码。

# 实验一

## 题意

使用链表存储学生成绩信息，并进行简单统计。

## 实现

本项目存储学生的语文成绩和数学成绩，并实现最大值、最小值、平均值的统计。

新增学生信息使用链表的头插法，复杂度为 $O(1)$。

每次展示统计信息遍历一次链表，复杂度为 $O(n)$。

# 实验二

## 题意

使用栈解析中缀表达式。

## 实现

采用数组的方式实现栈结构。

对于中缀表达式的处理，使用了两个栈，其中一为数字栈，一为运算符栈。

实现```eval()```函数，进行一次运算操作。逻辑为，依次弹出数字栈顶的两个数字，弹出运算符栈顶的运算符，将两个数字进行该运算符所代表的运算操作，并压入数字栈中。

遍历表达式：

- 读取到数字时，将该数字压入数字栈中。
- 读取到左括号时，将其压入运算符栈中。
- 读取到右括号时，不断进行```eval()```操作，直到运算符栈顶为左括号，并弹出左括号。通过此种办法处理括号的优先级。
- 读取到四则运算符时，不断进行```eval()```操作，直到运算符栈顶为左括号或栈顶运算符的优先级小于该四则运算符对应的四则运算。通过此种办法处理四则运算符的优先级。

当遍历结束后，不断进行```eval()```操作直到运算符栈为空，此时数字栈顶即为中缀表达式的值。

令中缀表达式字符串的长度为 $$n$$，则算法复杂度为 $$O(n)$$。

# 实验三

## 题意

给定树形结构进行存储。实现查询某一结点的子结点。

## 实现

采用邻接表进行存储。

对于题目中的结点```u```由```k```个结点```v```组成，可以将```k```这个附加信息储存到结点```v```中便于查找。

值得注意的是，本题中的结点以字符串类型的名称为唯一约束，所以我们需要将字符串映射成为数字。由于语言限制为C语言，所以常见的字符串映射为数字的算法实现困难。本题可以考虑的做法有字符串哈希、平衡二叉树、红黑树、字典树等。

令字符串的长度为 $$s$$，节点个数为$$n$$，使用字典树的时间复杂度为 $$O(s)$$，效率最高。本项目使用字典树实现字符串到数字的映射。

# 实验四

## 题意

给定连通图求BST权。

## 实现

使用邻接表进行存储。同上，本题中的结点以字符串类型的名称为唯一约束，使用字典树进行映射。

使用prim算法。