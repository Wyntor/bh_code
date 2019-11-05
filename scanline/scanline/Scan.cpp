#include "common.h"
#include "math.h"
#include "scan.h"
#include <algorithm>

//求扫描线Y=y与边AB的交点的x坐标，如果无交点，返回-99999
int linejoin(int A[2],int B[2],int y)
{
	float t;
	if (B[1]==A[1])
		return -99999;

	t = (y-A[1]) / float(B[1]-A[1]);
	if (t>=0.0 && t<=1.0){
		return ROUND(A[0] + (B[0]-A[0])*t);
	}else
		return -99999;
}

//可能用到的函数
void SetPixel(int x,int y);
float GetDepth(int x,int y);
void SetDepth(int x,int y,float depth);

//多边形填充算法,Zbuffer算法
//coord 像素坐标
//depth 像素对应的深度
//n 像素个数

void linefill(int coord[][2],float depth[],int n){

	int miny,maxy;
	int X[10];
	float A[3],B[3],C[3],D[3],E[3],R[3];

	//平面方程P(u,w)=A+uB+wC
	for(int i=0;i<2;i++) {
		A[i]=coord[0][i];
		B[i]=coord[1][i]-coord[0][i];
		C[i]=coord[2][i]-coord[0][i];
	}
	A[2]=depth[0];
	B[2]=depth[1]-depth[0];
	C[2]=depth[2]-depth[0];

	//直线方程Q(t)=(x0,y0,0)+(0,0,1)t 
	D[0] = D[1] =0;//在用该直线时,D[0],D[1]需要重新赋值
	D[2]=0;
	E[0] = E[1] =0;
	E[2]=1;

	// 找出y坐标最大和最小的顶点 
	miny=coord[0][1];maxy=coord[0][1];
	for (int i=0;i<n;i++){
		if (coord[i][1]<miny)
			miny=coord[i][1];
		if (coord[i][1]>maxy)
			maxy=coord[i][1];
	}

	// 使扫描线从y坐标最小的递增1到y最大的顶点 
	for (int y=miny;y<=maxy;y++){
		int index = 0;
		//添加代码
		//在判断能否绘制某个像素(x,y)时,要计算该像素的深度值。这里提供一种方法供参考：
		//从coor,depth中选3个点建立一个平面,再建立一条直线(经过点(x,y,0),方向(0,0,1))
		//调用函数facejoin(参考common.h),计算平面与直线的交点,交点的z分量即是像素的深度
		/*i表示扫描线，扫描线从多边形的最底端开始，向上扫描*/
		for (int j = 0; j < n; j++) {
			if (coord[j][1] <= y) {
				//如果前一个顶点在扫描线上方，则判断有交点，将交点坐标x放入X;
				if (coord[(j-1+n)%n][1] > y) {
					X[index] = linejoin(coord[j],coord[(j-1+n)%n],y);
					index++;
				}
				//如果后一个顶点在扫描线上方，则判断有交点，将交点坐标x放入X;
				if (coord[(j+1+n)%n][1] > y) {
					X[index] = linejoin(coord[j],coord[(j+1+n)%n],y);
					index++;
				}
			}
		}
		//对X中的坐标x进行排序,其中1,2为一组，3,4为一组，以此类推
		sort(X,index);
		//遍历当前扫描线中的像素，获取到深度并比较着色
		for (int k = 0; k <= index/2 -1; k++) {
			for (int x = X[2 * k]; x <= X[2 * k + 1]; x++) {
				D[0] = x;
				D[1] = y;
				if (facejoin(R,A,B,C,D,E) == 1) {
					if (R[2] >= 0.0 && R[2] <= 1.0 && R[2] < GetDepth(x,y) ) {
						SetPixel(x,y);
						SetDepth(x,y,R[2]);
					}
				}
			}
		}

	}

}
