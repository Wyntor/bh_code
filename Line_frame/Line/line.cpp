
#include <math.h>
#include "common.h"
#include "line.h"

//DDA�㷨����ֱ��
//(xa,ya),�����������
//(xb,yb),�յ���������
//setPixel,���ش�����
void DDA(int xa,int ya,int xb,int yb,void (*setPixel)(int x,int y)){

	//��Ӵ���
	int dx, dy, steps, k;
	float delta_x, delta_y,x,y;
	x = xa;
	y = ya;
	dx = xb - xa;
	dy = yb - ya;
	if (abs(dx) >= abs(dy)) {
		steps = abs(dx);//б��С�ڵ���1
	}
	else {
		steps = abs(dy);
	}
	delta_x = (float)dx / (float)steps;
	delta_y = (float)dy / (float)steps;
	for (k = 0; k <= steps; k++) {
		setPixel(int(x+0.5),int(y+0.5));
		x += delta_x;
		y += delta_y;
	}
}

//Bresenham�㷨����ֱ��
//����ͬDDA
void Bres(int xa,int ya,int xb,int yb,void (*setPixel)(int x,int y)){

	bool u=false,v=false,w=false;
	int tx,ty;
	int dsx=xb-xa;
	int dsy=yb-ya;

	if(dsx<0){
		dsx=-dsx;//dsxȡ��
		u=true;
	}
	if(dsy<0){
		dsy=-dsy;//dsyȡ��
		v=true;
	}
	if(dsx<dsy){
		swap(dsx,dsy);//dsx,dsy����
		w=true;
	}

	int dx=dsx,dy=dsy;
	int p=2*dy-dx;
	int twoDy=2*dy,twoDyDx=2*(dy-dx);
	int x,y,xEnd;

	x=0;
	y=0;
	xEnd=dsx;
	setPixel(xa,ya);

	while(x<xEnd){
		x++;

		if(p<0)
			p+=twoDy;
		else{
			y++;
			p+=twoDyDx;
		}
		tx=ROUND(x);
		ty=ROUND(y);

		if(w)swap(tx,ty);
		if(v)ty=-ty;
		if(u)tx=-tx;

		tx+=xa;
		ty+=ya;
		setPixel(tx,ty);
	}
}