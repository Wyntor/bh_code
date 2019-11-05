#include "common.h"
#include "math.h"
#include "scan.h"
#include <algorithm>

//��ɨ����Y=y���AB�Ľ����x���꣬����޽��㣬����-99999
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

//�����õ��ĺ���
void SetPixel(int x,int y);
float GetDepth(int x,int y);
void SetDepth(int x,int y,float depth);

//���������㷨,Zbuffer�㷨
//coord ��������
//depth ���ض�Ӧ�����
//n ���ظ���

void linefill(int coord[][2],float depth[],int n){

	int miny,maxy;
	int X[10];
	float A[3],B[3],C[3],D[3],E[3],R[3];

	//ƽ�淽��P(u,w)=A+uB+wC
	for(int i=0;i<2;i++) {
		A[i]=coord[0][i];
		B[i]=coord[1][i]-coord[0][i];
		C[i]=coord[2][i]-coord[0][i];
	}
	A[2]=depth[0];
	B[2]=depth[1]-depth[0];
	C[2]=depth[2]-depth[0];

	//ֱ�߷���Q(t)=(x0,y0,0)+(0,0,1)t 
	D[0] = D[1] =0;//���ø�ֱ��ʱ,D[0],D[1]��Ҫ���¸�ֵ
	D[2]=0;
	E[0] = E[1] =0;
	E[2]=1;

	// �ҳ�y����������С�Ķ��� 
	miny=coord[0][1];maxy=coord[0][1];
	for (int i=0;i<n;i++){
		if (coord[i][1]<miny)
			miny=coord[i][1];
		if (coord[i][1]>maxy)
			maxy=coord[i][1];
	}

	// ʹɨ���ߴ�y������С�ĵ���1��y���Ķ��� 
	for (int y=miny;y<=maxy;y++){
		int index = 0;
		//��Ӵ���
		//���ж��ܷ����ĳ������(x,y)ʱ,Ҫ��������ص����ֵ�������ṩһ�ַ������ο���
		//��coor,depth��ѡ3���㽨��һ��ƽ��,�ٽ���һ��ֱ��(������(x,y,0),����(0,0,1))
		//���ú���facejoin(�ο�common.h),����ƽ����ֱ�ߵĽ���,�����z�����������ص����
		/*i��ʾɨ���ߣ�ɨ���ߴӶ���ε���׶˿�ʼ������ɨ��*/
		for (int j = 0; j < n; j++) {
			if (coord[j][1] <= y) {
				//���ǰһ��������ɨ�����Ϸ������ж��н��㣬����������x����X;
				if (coord[(j-1+n)%n][1] > y) {
					X[index] = linejoin(coord[j],coord[(j-1+n)%n],y);
					index++;
				}
				//�����һ��������ɨ�����Ϸ������ж��н��㣬����������x����X;
				if (coord[(j+1+n)%n][1] > y) {
					X[index] = linejoin(coord[j],coord[(j+1+n)%n],y);
					index++;
				}
			}
		}
		//��X�е�����x��������,����1,2Ϊһ�飬3,4Ϊһ�飬�Դ�����
		sort(X,index);
		//������ǰɨ�����е����أ���ȡ����Ȳ��Ƚ���ɫ
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
