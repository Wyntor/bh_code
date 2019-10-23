#include <math.h>
#include <float.H>
#include <stdio.h>
#include "transformation.h"
#include "line.h"

// 平移(tx,ty,tz)的矩阵Txyz 
void matTxyz(float Txyz[4][4],float tx,float ty,float tz)
{
	////添加代码
}

// 绕x轴旋转theta角的矩阵Rx 
void matRx(float Rx[4][4],float theta)
{
	////添加代码
}

// 绕y轴旋转theta角的矩阵Ry 
void matRy(float Ry[4][4],float theta)
{
	////添加代码
}

// 绕z轴旋转theta角的矩阵Rz 
void matRz(float Rz[4][4],float theta)
{
	////添加代码
}


//绕指定轴(起点(0,0,0),终点(x,y,z))旋转theta角的矩阵R
void matR(float R[4][4],float theta,float x,float y,float z)
{
	////添加代码
}


// 缩放矩阵Sxyz
void matSxyz(float Sxyz[4][4],float sx,float sy,float sz)
{
	////添加代码
}

// 4阶方阵相乘 R=A*B 
void MatMul(float R[4][4],float A[4][4],float B[4][4])
{
	int i,j,k;
	float TR[4][4];

	for(i=0;i<4;i++) {
		for(j=0;j<4;j++) {
			TR[i][j] = 0; 
			for(k=0;k<4;k++)
				TR[i][j] = TR[i][j]+ A[i][k]*B[k][j];
		}
	}
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			R[i][j]=TR[i][j];
}

// 4阶方阵与4维向量相乘 PV=Mat*Vector 
void MVMul(float PV[],float Mat[][4],float Vector[])
{
	int i,j;
	for(i=0;i<4;i++) {
		PV[i] = 0;
		for(j=0;j<4;j++) {
			PV[i] = PV[i] + Mat[i][j]*Vector[j];
		}
	}
}
