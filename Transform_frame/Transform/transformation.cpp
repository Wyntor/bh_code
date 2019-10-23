#include <math.h>
#include <float.H>
#include <stdio.h>
#include "transformation.h"
#include "line.h"
#define PI 3.1415926
// 平移(tx,ty,tz)的矩阵Txyz 
void matTxyz(float Txyz[4][4],float tx,float ty,float tz)
{
	////添加代码
	Txyz[0][3] = tx;
	Txyz[1][3] = ty;
	Txyz[2][3] = tz;

}

// 绕x轴旋转theta角的矩阵Rx 
void matRx(float Rx[4][4],float theta)
{
	////添加代码
	Rx[1][1] = (float)cos(theta);
	Rx[1][2] = -(float)sin(theta);
	Rx[2][1] = (float)sin(theta);
	Rx[2][2] = (float)cos(theta);
}

// 绕y轴旋转theta角的矩阵Ry 
void matRy(float Ry[4][4],float theta)
{
	////添加代码
	Ry[0][0] = (float)cos(theta);
	Ry[0][2] = (float)sin(theta);
	Ry[2][0] = -(float)sin(theta);
	Ry[2][2] = (float)cos(theta);
}

// 绕z轴旋转theta角的矩阵Rz 
void matRz(float Rz[4][4],float theta)
{
	////添加代码
	Rz[0][0] = (float)cos(theta);
	Rz[0][1] = -(float)sin(theta);
	Rz[1][0] = (float)sin(theta);
	Rz[1][1] = (float)cos(theta);
}


//绕指定轴(起点(0,0,0),终点(x,y,z))旋转theta角的矩阵R
void matR(float R[4][4],float theta,float x,float y,float z)
{
	////添加代码
	float length = sqrt(x*x + y*y + z*z);
	float cosTheta = (float)cos(theta);
	float sinTheta = (float)sin(theta);
	float cos1 = 1 - cosTheta;
	float ux = x / length;
	float uy = y / length;
	float uz = z / length;

	R[0][0] = ux*ux*cos1 + cosTheta;
	R[0][1] = ux*uy*cos1 - uz*sinTheta;
	R[0][2] = ux*uz*cos1 + uy*sinTheta;
	R[1][0] = uy*ux*cos1 + uz*sinTheta;
	R[1][1] = uy*uy*cos1 + cosTheta;
	R[1][2] = uy*uz*cos1 - ux*sinTheta;
	R[2][0] = uz*ux*cos1 - uy*sinTheta;
	R[2][1] = uz*uy*cos1 + ux*sinTheta;
	R[2][2] = uz*uz*cos1 + cosTheta;
}


// 缩放矩阵Sxyz
void matSxyz(float Sxyz[4][4],float sx,float sy,float sz)
{
	////添加代码
	Sxyz[0][0] = sx;
	Sxyz[1][1] = sy;
	Sxyz[2][2] = sz;

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
