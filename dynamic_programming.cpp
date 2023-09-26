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
 * m = 3, n = 7�� result =28
 * m = 3, n = 2�� result =3
 * m = 3, n = 3�� result =6
 * m = 7, n = 3�� result =28
 */
static int uniquePaths(int m, int n) {  //m row, n col
	if (m <= 0 || n <= 0) {
		return 0;
	}
	std::vector<std::vector<int> > dp(m, std::vector<int>(n)); // m row, n col  ��������> >�м�Ŀո���ʡ��

	// ��ʼ��
	for (int i = 0; i < m; i++) {
		dp[i][0] = 1;
	}
	for (int i = 0; i < n; i++) {
		dp[0][i] = 1;
	}
	// �Ƶ��� dp[m-1][n-1]
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}
	}
	return dp[m - 1][n - 1];
}


/**
 * @input A : 2D integer array  �涨���������ά������Ϊ�������ݸ���������ô�ں����Ĳ��������б���ָ����������������������û��̫���ϵ������ָ��Ҳ���Բ�ָ����
 *                              ������Ѷ�ά����ת��Ϊһά������в������ݣ� ��������ʱ A[row*COL+col]
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
	std::vector<std::vector<int> > dp(m, std::vector<int>(n)); // m row, n col  ��������> >�м�Ŀո���ʡ��

	// ��ʼ��
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
	// �Ƶ��� dp[m-1][n-1]
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

	//����ָ�����������
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
