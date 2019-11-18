

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



//������ray�ཻ�������Object,����ray����뽻��ľ������dist����û��Object��ray�ཻ������NULL,distΪ����
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

//��ȡ����ray����ɫ������colour_out��������traceNum��
void World::getColourForRay(const Ray& ray, Colour& colour_out,int traceNum)
{
	//��������(maths/vec3.h)
		//Vec3 v(x,y,z)������Vec3����(�ɱ�ʾ������),float x/y/z�ֱ��������(ֵ��[-��,+��])
		//���� Vec3 v,v1,v2,���ü���:v=v1,v=v1*float_number,v=v1+v2,v=v1-v2,v=v1*v2,v=normalise(v1),float dot_product=v1.dot(v2)

	//���ߣ���(raytracer/ray.h)
		//Ray xray(point,dir)������Ray����,Vec3 point,Vec3 dir�ֱ������,����


	//��ɫ����(raytracer/colour.h)
		//Colour colour(r,g,b); ����Colour����,float r/g/b�ֱ��Ǻ�/��/������(ֵ��[0.0f,1.0f]);
		//����Colour c,c1,c2,���ü���:c=c1,c=c1*float_number,c+=c1,c-=c1,c=c1+c2,c=c1-c2,c=c1*c2


	//���ʣ���(raytracer/material/material.h)

	//��״����(raytracer/geometry/geometry.h),ƽ��(raytracer/geometry/rayplane.h),����(raytracer/geometry/raysphere.h)

	//���壺��(raytracer/object.h).
		//Object* object=NULL; ����Objectָ��


	//��Դ����(raytracer/light.h)

	//---------------------------------------------------------------------

	//�����õ��ĺ���:
	//closestObject,world.h
	//normalise,length,dot,addMult,vec3.h
	//getMaterial,object.h
	//��Դ�洢��m_lights��.m_lights.size(),���ع�Դ����.m_lights[i],��i����Դ ,0<=i<m_lights.size()
	//pow(x,y),x��y�η�

	//---------------------------------------------------------------------

	//�����򲻿�������

	//---------------------------------------------------------------------

	if(traceNum<1){
		colour_out=Colour::black();
		return;
	}
	//��Ӵ���
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
		//�󽻵�����
		IntersectionPoint = ray.m_startPos;
		IntersectionPoint.addMult(ray.m_unitDir,dist/ray.m_unitDir.length());

		//�󽻵㴦�ĵ�λ������
		N = currrentObject->getGeometry().getNormalForPos(IntersectionPoint);
		N = N.normalise();


		ka = currrentObject->getMaterial().m_ambient;//�����ⷴ��ϵ��
		kd = currrentObject->getMaterial().m_diffuse;//������ϵ��
		ks = currrentObject->getMaterial().m_specular;//���淴��ϵ��
		ns = currrentObject->getMaterial().m_ns;//���淴�����

		//���ߵķ�����
		S.x = -ray.m_unitDir.x;
		S.y = -ray.m_unitDir.y;
		S.z = -ray.m_unitDir.z;
		S = S.normalise();
        
		for (int i = 0; i < m_lights.size(); i++) {
		    //��������ⵥλ����
			L = m_lights[i]->getPos();
			L.sub(IntersectionPoint);
			L = L.normalise();

			//���㷴���ĵ�λ����
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
