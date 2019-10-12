
#include "curve.h"
#include <math.h>
#include <glut.h>

//计算n!/(k!(n-k)!),存储到c[k],其中k=0,1,...,n
void BezierCurve::binomiaCoeffs(int n,float *c){

	int k,i;

	for(k=0;k<=n;k++){
		//计算n!/(k!(n-k)!)
		c[k]=1;
		for(i=n;i>=k+1;i--)
			c[k]*=i;
		for(i=n-k;i>=2;i--)
			c[k]/=i;
	}

}


//Bezier曲线中,起点为B(0),终点为B(1),该函数计算点B(u)的坐标，其中0<=u<=1;
//bezPt 指向B(u)的指针,
//nCtrlPts 控制点个数
//ctrlPts 控制点内存起始地址
void BezierCurve::computeBezPt(float u,wcPt3D *bezPt,int nCtrlPts,wcPt3D *ctrlPts,float *C){

	//powf(x,k) x的k次方
	//添加代码
	int k, n = nCtrlPts - 1;
	float frac_sum;
	bezPt->x = bezPt->y = bezPt->z = 0.0;
	for (k = 0; k < nCtrlPts; k++) {
		frac_sum = C[k] * pow(u, k) * pow(1 - u, n - k);
		bezPt->x += ctrlPts[k].x * frac_sum;
		bezPt->y += ctrlPts[k].y * frac_sum;
		bezPt->z += ctrlPts[k].z * frac_sum;
	}
}


//计算bezier曲线
//ctrlPts 控制点数组内存起始地址
//nCtrlPts 控制点个数
//bezCurvePts 曲线点数组内存起始地址
//nBezCurvePts 曲线点个数
void BezierCurve::bezier(wcPt3D *ctrlPts,int nCtrlPts,wcPt3D *bezCurvePts,int nBezCurvePts){

	//添加代码
	//计算所有曲线点并存入数组bezCurvePts中
	float *C;
	float u;
	wcPt3D bezpt;
	C = new float[nCtrlPts];
	binomiaCoeffs(nCtrlPts - 1, C);
	for (int i = 0; i < nBezCurvePts; i++) {
		u = float(i) / float(nBezCurvePts-1);
		computeBezPt(u, &bezpt, nCtrlPts, ctrlPts, C);
		bezCurvePts[i].x = bezpt.x;
		bezCurvePts[i].y = bezpt.y;
		bezCurvePts[i].z = bezpt.z;
	}
}
