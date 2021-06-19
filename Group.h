#ifndef GROUP_H
#define GROUP_H


#include "Object3D.h"
#include "Ray.h"
#include "Hit.h"
#include <iostream>
#include <omp.h>

using  namespace std;

///TODO: 
///Implement Group
///Add data structure to store a list of Object* 
class Group:public Object3D
{
public:

	Group(){
		size = 100;
		collection = new Object3D*[size];
	}
	
	Group( int num_objects ){
		size = num_objects;
		collection = new Object3D*[size];
	}

	~Group(){
		delete [] collection;
	}

	virtual bool intersect( const Ray& r , Hit& h , float tmin ) {
		bool ret = false;
		
		//#pragma omp critical
		//{
			for (register int i = 0 ; i < size ; ++ i)
			{
				if(collection[i] != nullptr)
				{
					if(collection[i]->intersect(r, h, tmin))
					{
						ret = true;
						//printf("%c\t", collection[i]->getType());
					}
				}
			}
		//}
		

		return ret;
	}

	bool intersectShadowRay( const Ray& r , Hit& h , float tmin ) {
		bool toReturn = false;
		//#pragma omp critical
		//{
			for (register int i = 0 ; i < size ; ++ i)
			{
				if(collection[i] != nullptr)
				{
					if(collection[i]->intersect(r, h, tmin))
					{
						toReturn = true;
						break;
					}
				}
			}
		//}
		

		return toReturn;
	}
	
	void addObject( int index , Object3D* obj ){
		if (index > size-1)
		{
			printf("Invalid index while adding object to group\n");
			exit(0);
		}
		collection[index] = obj;
	}

	int getGroupSize(){
		int s; 
		for(register int i = 0 ; i < size ; i ++)
		{
			if(collection[i] != nullptr)
			{
				++s;
			}
		}

		return s;
	}

 private:
	int size;
	Object3D** collection;
};

#endif
	
