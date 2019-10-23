#include <math.h>
#include <float.H>
#include <stdio.h>
#include "transformation.h"
#include "line.h"

// ƽ��(tx,ty,tz)�ľ���Txyz 
void matTxyz(float Txyz[4][4],float tx,float ty,float tz)
{
	////��Ӵ���
}

// ��x����תtheta�ǵľ���Rx 
void matRx(float Rx[4][4],float theta)
{
	////��Ӵ���
}

// ��y����תtheta�ǵľ���Ry 
void matRy(float Ry[4][4],float theta)
{
	////��Ӵ���
}

// ��z����תtheta�ǵľ���Rz 
void matRz(float Rz[4][4],float theta)
{
	////��Ӵ���
}


//��ָ����(���(0,0,0),�յ�(x,y,z))��תtheta�ǵľ���R
void matR(float R[4][4],float theta,float x,float y,float z)
{
	////��Ӵ���
}


// ���ž���Sxyz
void matSxyz(float Sxyz[4][4],float sx,float sy,float sz)
{
	////��Ӵ���
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
