
#include <math.h>
#include "common.h"
#include "line.h"

//DDA算法绘制直线
//(xa,ya),起点像素坐标
//(xb,yb),终点像素坐标
//setPixel,像素处理函数
void DDA(int xa,int ya,int xb,int yb,void (*setPixel)(int x,int y)){

	//添加代码
	int dx, dy, steps, k;
	float delta_x, delta_y, x, y;
	x = xa;
	y = ya;
	dx = xb - xa;
	dy = yb - ya;
	if (abs(dx) >= abs(dy)) {
		steps = abs(dx);//斜率小于等于1
	}
	else {
		steps = abs(dy);
	}
	delta_x = (float)dx / (float)steps;
	delta_y = (float)dy / (float)steps;
	for (k = 0; k <= steps; k++) {
		setPixel(int(x + 0.5), int(y + 0.5));
		x += delta_x;
		y += delta_y;
	}

}

//Bresenham算法绘制直线
//参数同DDA
void Bres(int xa,int ya,int xb,int yb,void (*setPixel)(int x,int y)){

	bool u=false,v=false,w=false;
	int tx,ty;
	int dsx=xb-xa;
	int dsy=yb-ya;

	if(dsx<0){
		dsx=-dsx;//dsx取反
		u=true;
	}
	if(dsy<0){
		dsy=-dsy;//dsy取反
		v=true;
	}
	if(dsx<dsy){
		swap(dsx,dsy);//dsx,dsy互换
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