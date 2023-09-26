// Dynamic Programming

#include <algorithm>  /// for std::is_sorted
#include <cassert>    /// for std::assert
#include <ctime>      /// for std::time
#include <vector>
#include <iostream>   /// for IO operations


/**
 * @input m : Integer array's ( A ) rows
 * @input n : Integer array's ( A ) columns
 *
 * @Output Integer
 * https://leetcode.cn/problems/unique-paths/
 * m = 3, n = 7， result =28
 * m = 3, n = 2， result =3
 * m = 3, n = 3， result =6
 * m = 7, n = 3， result =28
 */
static int uniquePaths(int m, int n) {  //m row, n col
	if (m <= 0 || n <= 0) {
		return 0;
	}
	std::vector<std::vector<int> > dp(m, std::vector<int>(n)); // m row, n col  后面两个> >中间的空格不能省略

	// 初始化
	for (int i = 0; i < m; i++) {
		dp[i][0] = 1;
	}
	for (int i = 0; i < n; i++) {
		dp[0][i] = 1;
	}
	// 推导出 dp[m-1][n-1]
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}
	}
	return dp[m - 1][n - 1];
}


/**
 * @input A : 2D integer array  规定：如果将二维数组作为参数传递给函数，那么在函数的参数声明中必须指明数组的列数，数组的行数没有太大关系，可以指定也可以不指定。
 *                              本程序把二维数组转化为一维数组进行参数传递， 并在引用时 A[row*COL+col]
 * @input m : Integer array's ( A ) rows
 * @input n : Integer array's ( A ) columns
 *
 * @Output Integer
 * https://www.interviewbit.com/problems/unique-paths-in-a-grid/
 * https://www.interviewbit.com/facebook-interview-questions/
 * https://www.interviewbit.com/search/?q=Facebook
 */
int uniquePathsWithObstacles(int* A, int m, int n) {
	if (m <= 0 || n <= 0) {
		return 0;
	}
	std::vector<std::vector<int> > dp(m, std::vector<int>(n)); // m row, n col  后面两个> >中间的空格不能省略

	// 初始化
	for (int i = 0; i < m; i++) {
		if (A[i*n+0] == 1){
			for( ; i < m; i++) dp[i][0] = 0;
		}
		else {
			dp[i][0] = 1;
		}
	}
	for (int i = 0; i < n; i++) {
		if (A[0*n+i] == 1) {
			for (; i < m; i++) dp[0][i] = 0;
		}
		else {
			dp[0][i] = 1;
		}
	}
	// 推导出 dp[m-1][n-1]
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			if (A[i*n+j] == 1) {
				dp[i][j] = 0;
			}
			else {
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}
	}
	return dp[m - 1][n - 1];
}

/*
* Asked In: facebook
Given a grid of size m * n, lets assume you are starting at (1,1) and your goal is to reach (m,n). At any instance, if you are on (x,y), you can either go to (x, y + 1) or (x + 1, y).
Now consider if some obstacles are added to the grids. How many unique paths would there be?
An obstacle and empty space is marked as 1 and 0 respectively in the grid.
Example :
There is one obstacle in the middle of a 3x3 grid as illustrated below.
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
The total number of unique paths is 2.

[ [0,1,0],
  [0,0,0],
  [0,0,0] ] number of unique paths is 3.

  [ [0,1,0],
    [0,0,0],
    [1,0,0] ] number of unique paths is 2.
Note: m and n will be at most 100.
*/


void testDynamicProgramming() {
	int m = 3, n = 7;
	
	int path;
	
	path = uniquePaths(m, n);

	std::cout << "\n The paths(m=" << m << ", n=" << n << ")  number is : " << path;

	//必须指明数组的列数
	int obs[][3] = { {0,1,0},
					 {0,0,0},
					 {1,0,0} };

	m = 3;
	n = 3;

	std::cout << "\n the obstacle array is: \n";

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)std::cout << obs[i][j] << " ";
		std::cout << "\n";
	}

	path = uniquePathsWithObstacles(reinterpret_cast<int*>(obs), m, n);

	std::cout << "\n The paths(m=" << m << ", n=" << n << ")  number with obstacles is : " << path;
	
}


/*
* Starting point is m[0][0], need to find a path go to m[9][9]. 
* 0 means OK, 1 means cannot go there, boundary is 0 and 9, cannot go beyond boundary.
* Each step can be made horizontally or vertically for one more grid (diagonal jump is not allowed).
* Your program should print a series of grid coordinates that start from m[0][0] and go to m[9][9]
* Hint: No need to find the shortest path, only need to find one path that gets you to desitination
*/

#define N 10

int isSafe(int(*maze)[N], int x, int y)
{
	if (x >= 0 && x < N && y >= 0 && y < N && !(maze[x][y]) )
		return 1;
	return 0;
}

void Maze(int(*maze)[N], int x, int y, int(*sol)[N])
{
	int i, j;
	if (x == N - 1 && y == N - 1)
	{
		std::cout << "\n\nSolution\n\n";
		sol[x][y] = 2;
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				std::cout << sol[i][j];
			}
			std::cout << std::endl;
		}
	}
	else
	{
		if (isSafe(maze, x, y) && sol[N - 1][N - 1] != 2) // 
		{
			std::cout << " (" << x << "," << y << ")";

			sol[x][y] = 2;

			/*int direct[4] = {0};
			int tmpDir, dirNum=0;
			while (dirNum < 4) {
				tmpDir = std::rand() % 4;
				std::cout << "(n-" << dirNum << ",d-" << tmpDir << ")";

				if (tmpDir == 0 && direct[0] == 0){
					direct[0]++;
					dirNum++;
					if (isSafe(maze, x + 1, y))Maze(maze, x + 1, y, sol);
				}

				if (tmpDir == 1 && direct[1] == 0) {
					direct[1]++;
					dirNum++;
					if (isSafe(maze, x, y + 1))Maze(maze, x, y + 1, sol);
				}

				if (tmpDir == 2 && direct[2] == 0) {
					direct[2]++;
					dirNum++;
					if (isSafe(maze, x - 1, y))Maze(maze, x - 1, y, sol);
				}

				if (tmpDir == 3 && direct[3] == 0) {
					direct[3]++;
					dirNum++;
					if (isSafe(maze, x, y - 1))Maze(maze, x, y - 1, sol);
				}
			} */
			if (isSafe(maze, x + 1, y))Maze(maze, x + 1, y, sol);
			if (isSafe(maze, x, y + 1))Maze(maze, x, y + 1, sol);
			if (isSafe(maze, x - 1, y))Maze(maze, x - 1, y, sol);
			if (isSafe(maze, x, y - 1))Maze(maze, x, y - 1, sol);

			sol[x][y] = 0;
			// if noexist （&& sol[N - 1][N - 1] != 2） and setting sol[x][y] = 0;, the program will deadlooped, because the different moving-branch will go an go
		}
	}
}


void Maze2(int(*maze)[N], int x, int y, int(*sol)[N])
{
	static int i, j;
	if (x == N - 1 && y == N - 1)
	{
		std::cout << "\n\nSolution 2:\n\n";
		sol[x][y] = 1;
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
				std::cout << sol[i][j];

			std::cout << std::endl;
		}
	}
	else
	{
		if (isSafe(maze, x, y))
		{
			sol[x][y] = 1;

			Maze2(maze, x + 1, y, sol);
			Maze2(maze, x, y + 1, sol);

			// only move forward, in some case it need to backward

			sol[x][y] = 0;
		}
	}
}


void testFindWay() {

	//必须指明数组的列数
	int maze[N][N]= { {0,0,1,0,0,0,0,0,0,0},
					  {0,0,1,0,0,0,0,0,0,0},
					  {0,1,0,0,0,0,0,0,0,0},
					  {0,1,0,0,1,0,0,0,0,0},
					  {0,0,0,0,1,0,0,0,0,0},
					  {0,1,1,0,1,1,0,0,0,0},
					  {0,1,0,0,0,0,0,0,0,0},
					  {0,1,0,0,0,0,1,0,0,0},
					  {0,1,0,0,0,0,0,0,0,0},
					  {0,1,0,0,0,0,0,1,0,0} };

	int solu[N][N] = { 0 };

	std::srand(std::time(nullptr));

	std::cout << "\n The paths is : " << std::endl;

	Maze(maze, 0, 0, maze);
	//Maze2(maze, 0, 0, maze);
	//Maze(maze, 0, 0, solu);  //0xC00000FD: Stack overflow 

	std::cout << "\n\nFinal:\n\n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			std::cout << maze[i][j];
		}
		std::cout << std::endl;
	}

	std::cout << "\n\nFinal solution:\n\n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			std::cout << solu[i][j];
		}
		std::cout << std::endl;
	}
}
