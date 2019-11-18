

#include "world.h"


#include "object.h"
#include "colour.h"
#include "ray.h"
#include "light.h"
#include "Geometry/geometry.h"
#include <assert.h>
#include <Windows.h>


const Colour ambient_lighting(0.5f, 0.5f, 0.5f);

World::World()
{
	m_traceNum=5;
}

World::~World()
{
	for(unsigned int i=0; i<m_objects.size(); ++i)
	{
		delete m_objects[i];
	}

	for(unsigned int z=0; z<m_lights.size(); ++z)
	{
		delete m_lights[z];
	}
}


void World::insertObject(Object* ob)
{
	m_objects.push_back(ob);
}



void World::insertLight(Light* light)
{
	m_lights.push_back(light);
}



//返回与ray相交的最近的Object,并将ray起点与交点的距离存入dist；若没有Object与ray相交，返回NULL,dist为负数
Object* World::closestObject(const Ray& ray,float& dist)
{
	Object* obj=NULL;
	float smallest_dist = 1e9f; 

	for(unsigned int i=0; i<m_objects.size(); i++)
	{
		const float tracedist = m_objects[i]->getGeometry().getDistanceUntilHit(ray);
	
		if(tracedist >= 0.0f && tracedist < smallest_dist)
		{
			smallest_dist = tracedist;
			obj = m_objects[i];
		}
	}
	if(obj==NULL)dist=-666;
	else dist=smallest_dist * 0.999f;
	return obj;
}

//获取射线ray的颜色，存入colour_out，最多跟踪traceNum次
void World::getColourForRay(const Ray& ray, Colour& colour_out,int traceNum)
{
	//向量：见(maths/vec3.h)
		//Vec3 v(x,y,z)：定义Vec3对象(可表示点或方向等),float x/y/z分别是其分量(值域[-∞,+∞])
		//若有 Vec3 v,v1,v2,常用计算:v=v1,v=v1*float_number,v=v1+v2,v=v1-v2,v=v1*v2,v=normalise(v1),float dot_product=v1.dot(v2)

	//射线：见(raytracer/ray.h)
		//Ray xray(point,dir)：定义Ray对象,Vec3 point,Vec3 dir分别是起点,方向


	//颜色：见(raytracer/colour.h)
		//Colour colour(r,g,b); 定义Colour对象,float r/g/b分别是红/绿/蓝分量(值域[0.0f,1.0f]);
		//若有Colour c,c1,c2,常用计算:c=c1,c=c1*float_number,c+=c1,c-=c1,c=c1+c2,c=c1-c2,c=c1*c2


	//材质：见(raytracer/material/material.h)

	//形状：见(raytracer/geometry/geometry.h),平面(raytracer/geometry/rayplane.h),球面(raytracer/geometry/raysphere.h)

	//物体：见(raytracer/object.h).
		//Object* object=NULL; 定义Object指针


	//光源：见(raytracer/light.h)

	//---------------------------------------------------------------------

	//可能用到的函数:
	//closestObject,world.h
	//normalise,length,dot,addMult,vec3.h
	//getMaterial,object.h
	//光源存储在m_lights里.m_lights.size(),返回光源个数.m_lights[i],第i个光源 ,0<=i<m_lights.size()
	//pow(x,y),x的y次方

	//---------------------------------------------------------------------

	//本程序不考虑折射

	//---------------------------------------------------------------------

	if(traceNum<1){
		colour_out=Colour::black();
		return;
	}
	//添加代码
	Colour kd, ks, ka;
	float ns;
	Vec3 IntersectionPoint, ReflectedDirection,L,N,S,R;
	Colour LocalColor, ReflectedColor;
	Object* currrentObject = NULL;
	float dist = 0.0f;
	currrentObject = closestObject(ray,dist);
	if (currrentObject == NULL) {
		colour_out = Colour::black();
	}
	else {
		LocalColor =  currrentObject->getMaterial().m_ambient;
		//求交点坐标
		IntersectionPoint = ray.m_startPos;
		IntersectionPoint.addMult(ray.m_unitDir,dist/ray.m_unitDir.length());

		//求交点处的单位法向量
		N = currrentObject->getGeometry().getNormalForPos(IntersectionPoint);
		N = N.normalise();


		ka = currrentObject->getMaterial().m_ambient;//环境光反射系数
		kd = currrentObject->getMaterial().m_diffuse;//漫反射系数
		ks = currrentObject->getMaterial().m_specular;//镜面反射系数
		ns = currrentObject->getMaterial().m_ns;//镜面反射参数

		//射线的反方向
		S.x = -ray.m_unitDir.x;
		S.y = -ray.m_unitDir.y;
		S.z = -ray.m_unitDir.z;
		S = S.normalise();
        
		for (int i = 0; i < m_lights.size(); i++) {
		    //计算入射光单位向量
			L = m_lights[i]->getPos();
			L.sub(IntersectionPoint);
			L = L.normalise();

			//计算反射光的单位向量
			R = 2 * N*(dot(N, L)) - L;
			R = R.normalise();

			const Ray Lray(IntersectionPoint,L);
			float Ldist;
			if (closestObject(Lray,Ldist) == NULL) {
				LocalColor += m_lights[i]->getColour()*(kd*dot(N, L) + ks*pow(max(dot(R, S), 0.0), ns));
			}
		}

		colour_out = LocalColor + ks * ReflectedColor;

	}
}

void World::setTraceNum(int traceNum)
{
	m_traceNum=traceNum;
}

void World::clear()
{
	int i=m_objects.size();
	for(int j=0;j<i;j++)
		delete m_objects[j];
	m_objects.clear();

	i=m_lights.size();
	for(int j=0;j<i;j++)
		delete m_lights[j];
	m_lights.clear();
}
