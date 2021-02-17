/*
������Ϊ16��һά���鰴��zig-zag˳�򣬷�16�β��뵽16��16�����У�
*/
#include <stdio.h>

int coeff[16][16] = { 0 };

const int SNGL_SCAN[16][2] =
{
	{ 0, 0 }, { 1, 0 }, { 0, 1 }, { 0, 2 },
	{ 1, 1 }, { 2, 0 }, { 3, 0 }, { 2, 1 },
	{ 1, 2 }, { 0, 3 }, { 1, 3 }, { 2, 2 },
	{ 3, 1 }, { 3, 2 }, { 2, 3 }, { 3, 3 }
};

/*
��������insert_matrix
������
	(in/out)int (*matrix)[16]��������ʼ��ַ
	(in)int *block������������
	(in)int start���ھ����в������ʼλ��
	(in)int maxCoeffNum��ϵ����������
	(in)int x��4x4����ˮƽ����
	(in)int y��4x4����ֱ����
*/
void insert_matrix(int(*matrix)[16], int *block, int start, int maxCoeffNum, int x, int y)
{
	int row = 0, column = 0, startX = 4 * x, startY = 4 * y;
	for (int idx = 0, pos0 = start; idx < maxCoeffNum && pos0 < 16; idx++)
	{
		row = SNGL_SCAN[pos0][0] + startY;
		column = SNGL_SCAN[pos0][1] + startX;
		matrix[row][column] = block[idx];
		pos0++;
	}
}

int main()
{
	int block[16] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5 };

	insert_matrix(coeff, block, 0, 16, 1, 0);

	return 0;
}