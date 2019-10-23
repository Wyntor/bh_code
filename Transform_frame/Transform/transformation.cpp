#include <math.h>
#include <float.H>
#include <stdio.h>
#include "transformation.h"
#include "line.h"
#define PI 3.1415926
// ƽ��(tx,ty,tz)�ľ���Txyz 
void matTxyz(float Txyz[4][4],float tx,float ty,float tz)
{
	////��Ӵ���
	Txyz[0][3] = tx;
	Txyz[1][3] = ty;
	Txyz[2][3] = tz;

}

// ��x����תtheta�ǵľ���Rx 
void matRx(float Rx[4][4],float theta)
{
	////��Ӵ���
	Rx[1][1] = (float)cos(theta);
	Rx[1][2] = -(float)sin(theta);
	Rx[2][1] = (float)sin(theta);
	Rx[2][2] = (float)cos(theta);
}

// ��y����תtheta�ǵľ���Ry 
void matRy(float Ry[4][4],float theta)
{
	////��Ӵ���
	Ry[0][0] = (float)cos(theta);
	Ry[0][2] = (float)sin(theta);
	Ry[2][0] = -(float)sin(theta);
	Ry[2][2] = (float)cos(theta);
}

// ��z����תtheta�ǵľ���Rz 
void matRz(float Rz[4][4],float theta)
{
	////��Ӵ���
	Rz[0][0] = (float)cos(theta);
	Rz[0][1] = -(float)sin(theta);
	Rz[1][0] = (float)sin(theta);
	Rz[1][1] = (float)cos(theta);
}


//��ָ����(���(0,0,0),�յ�(x,y,z))��תtheta�ǵľ���R
void matR(float R[4][4],float theta,float x,float y,float z)
{
	////��Ӵ���
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


// ���ž���Sxyz
void matSxyz(float Sxyz[4][4],float sx,float sy,float sz)
{
	////��Ӵ���
	Sxyz[0][0] = sx;
	Sxyz[1][1] = sy;
	Sxyz[2][2] = sz;

}

// 4�׷������ R=A*B 
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

// 4�׷�����4ά������� PV=Mat*Vector 
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
