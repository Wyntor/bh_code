
#include "curve.h"
#include <math.h>
#include <glut.h>

//����n!/(k!(n-k)!),�洢��c[k],����k=0,1,...,n
void BezierCurve::binomiaCoeffs(int n,float *c){

	int k,i;

	for(k=0;k<=n;k++){
		//����n!/(k!(n-k)!)
		c[k]=1;
		for(i=n;i>=k+1;i--)
			c[k]*=i;
		for(i=n-k;i>=2;i--)
			c[k]/=i;
	}

}


//Bezier������,���ΪB(0),�յ�ΪB(1),�ú��������B(u)�����꣬����0<=u<=1;
//bezPt ָ��B(u)��ָ��,
//nCtrlPts ���Ƶ����
//ctrlPts ���Ƶ��ڴ���ʼ��ַ
void BezierCurve::computeBezPt(float u,wcPt3D *bezPt,int nCtrlPts,wcPt3D *ctrlPts,float *C){

	//powf(x,k) x��k�η�
	//��Ӵ���
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


//����bezier����
//ctrlPts ���Ƶ������ڴ���ʼ��ַ
//nCtrlPts ���Ƶ����
//bezCurvePts ���ߵ������ڴ���ʼ��ַ
//nBezCurvePts ���ߵ����
void BezierCurve::bezier(wcPt3D *ctrlPts,int nCtrlPts,wcPt3D *bezCurvePts,int nBezCurvePts){

	//��Ӵ���
	//�����������ߵ㲢��������bezCurvePts��
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
