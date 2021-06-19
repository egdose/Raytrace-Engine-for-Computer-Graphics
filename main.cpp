#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <omp.h>

#include "SceneParser.h"
#include "Image.h"
#include "Camera.h"
#include "ArgParser.h"
#include "RayTracer.h"
#include <string.h>
#include <chrono>

using namespace std;

using namespace std::chrono;

#define SUPERSAMPLE_X 3
#define NUM_THREADS 12

float clampedDepth ( float depthInput, float depthMin , float depthMax);

#include "bitmap_image.hpp"
int main( int argc, char* argv[] )
{
	// Fill in your implementation here.
	ArgParser args(argc, argv);

	//Initializing Output Image
	Image outputImage(args.width, args.height);

	//Initializing Depth Map Image
	Image depthImage(args.width, args.height);

	//Initializing Normal Image
	Image normalImage(args.width, args.height);

	//Multithreading
	omp_set_num_threads(NUM_THREADS);
	if(NUM_THREADS > 1)
		printf("Multithreading Enabled: %d Threads\n", NUM_THREADS);

	//Performance Benchmarking
	auto start_time = high_resolution_clock::now();
	
		
	// First, parse the scene using SceneParser.
	SceneParser scene(args.input_file);
	// Then loop over each pixel in the image, shooting a ray
	// through that pixel and finding its intersection with
	// the scene.  Write the color at the intersection to that
	// pixel in your output image.
	std::cout << "-----------------------------------\n";
	std::cout << "Preparing: " << args.input_file << endl;
	RayTracer engine(&scene, &args);
	if(args.jitter == 0)
	{
		//int i, j;
		#pragma omp parallel for schedule(dynamic)
		for(register int i = 0 ; i < args.width ; ++i)
		{
			//printf("Iteration: %d\n", i);
			#pragma omp parallel for schedule(dynamic)
			for(register int j = 0 ; j < args.height ; ++j)
			{
				//printf("Iteration: %d, %d\n", i, j);
				float x_point = 2.0f * float(j)/args.width -1.0f;
				float y_point = 2.0f * float(i)/args.height -1.0f;
				Vector2f point = Vector2f(x_point, y_point);

				//printf("check1 %d, %d\n", i, j);
				Ray currentRay = scene.getCamera()->generateRay(point);
				Hit h;
				h = Hit( FLT_MAX, NULL, Vector3f( 0, 0, 0 ) );


				//printf("check2 %d, %d\n", i, j);
				//cout << "Casting Ray!\n";
				Matrix3f colors;

				
				colors = engine.traceRay(currentRay, 
						scene.getCamera()->getTMin(), 0
						, 1.0, h);
				

				//cout << "Color returned\n";
				// outputImage.SetPixel(j, i, colors);
				// depthImage.SetPixel(j, i, colors);
				// normalImage.SetPixel(j, i, colors);

				//printf("check3 %d, %d\n", i, j);
				outputImage.SetPixel(j, i, colors.getCol(0));
				depthImage.SetPixel(j, i, colors.getCol(1));
				normalImage.SetPixel(j, i, colors.getCol(2));

				//printf("Done: %d, %d\n", i, j);

				//cout << "Color Set!\n";
			}
		}
	}
	else
	{
		int superWidth = args.width*SUPERSAMPLE_X;
		int superHeight = args.height*SUPERSAMPLE_X;

		Image superOutput(superWidth, superHeight);
		Image superDepth(superWidth, superHeight);
		Image superNormal(superWidth, superHeight);

		//Supersampling
		//int i, j;
		#pragma omp parallel for schedule(dynamic)
		for(register int i = 0 ; i < superWidth ; ++i)
		{
			#pragma omp parallel for schedule(dynamic)
			for(register int j = 0 ; j < superHeight ; ++j)
			{
				float r_i = (float)rand()/(float)RAND_MAX - 0.5f;
				float r_j = (float)rand()/(float)RAND_MAX - 0.5f;

				float x_point = 2.0f * float(j+r_j)/superWidth -1.0f;
				float y_point = 2.0f * float(i+r_i)/superHeight -1.0f;
				Vector2f point = Vector2f(x_point, y_point);

				Ray currentRay = scene.getCamera()->generateRay(point);
				Hit h;
				h = Hit( FLT_MAX, NULL, Vector3f( 0, 0, 0 ) );


				//cout << "Casting Ray!\n";

				Matrix3f colors = engine.traceRay(currentRay, 
							scene.getCamera()->getTMin(), 0
							, 1.0, h);

				//cout << "Color returned\n";
				// outputImage.SetPixel(j, i, colors);
				// depthImage.SetPixel(j, i, colors);
				// normalImage.SetPixel(j, i, colors);

				superOutput.SetPixel(j, i, colors.getCol(0));
				superDepth.SetPixel(j, i, colors.getCol(1));
				superNormal.SetPixel(j, i, colors.getCol(2));

				//cout << "Color Set!\n";
			}
		}

		//Gaussian Blur
		Image blur1(superWidth, superHeight);
		Image blur2(superWidth, superHeight);
		if(args.filter == 1)
		{
			float K[5] = {0.1201f, 0.2339f, 0.2931f, 0.2339f, 0.1201f};
			//Horizontal
			#pragma omp parallel for schedule(dynamic)
			for(register int i = 0 ; i < superWidth ; ++i)
			{
				if(i == 0 || i == 1 || i == superWidth-2 || i == superHeight-1)
				{
					continue;
				}
				#pragma omp parallel for schedule(dynamic)
				for(register int j = 0 ; j < superHeight ; ++j)
				{
					if(j == 0 || j == 1 || j == superHeight-2 || j == superHeight-1)
					{
						continue;
					}
					Vector3f next(0.0f);

					next += superOutput.GetPixel(j, i-2)*K[0];
					next += superOutput.GetPixel(j, i-1)*K[1];
					next += superOutput.GetPixel(j, i)*K[2];
					next += superOutput.GetPixel(j, i+1)*K[3];
					next += superOutput.GetPixel(j, i+2)*K[4];
					
					blur1.SetPixel(j, i, next);
				}
			}
			//Vertical
			#pragma omp parallel for schedule(dynamic)
			for(register int i = 0 ; i < superWidth ; ++i)
			{
				if(i == 0 || i == 1 || i == superWidth-2 || i == superHeight-1)
				{
					continue;
				}
				#pragma omp parallel for schedule(dynamic)
				for(register int j = 0 ; j < superHeight ; ++j)
				{
					if(j == 0 || j == 1 || j == superHeight-2 || j == superHeight-1)
					{
						continue;
					}
					Vector3f next(0.0f);

					next += blur1.GetPixel(j, i-2)*K[0];
					next += blur1.GetPixel(j, i-1)*K[1];
					next += blur1.GetPixel(j, i)*K[2];
					next += blur1.GetPixel(j, i+1)*K[3];
					next += blur1.GetPixel(j, i+2)*K[4];
					
					blur2.SetPixel(j, i, next);
				}
			}
		}
		


		//Downsampling
		#pragma omp parallel for schedule(dynamic)
		for(register int i = 0 ; i < args.width ; ++i)
		{
			#pragma omp parallel for schedule(dynamic)
			for(register int j = 0 ; j < args.height ; ++j)
			{
				Vector3f tempColor(0.0f);
				Vector3f tempColor2(0.0f);
				Vector3f tempColor3(0.0f);
				int i_t = i*SUPERSAMPLE_X;
				int j_t = j*SUPERSAMPLE_X;

				for(register int i_tt = i_t ; i_tt < i_t+3 ; ++i_tt)
				{
					if(i_tt >= superWidth)
					{
						break;
					}
					for(register int j_tt = j_t ; j_tt < j_t+3 ; ++j_tt)
					{
						if(j_tt >= superHeight)
						{
							break;
						}
						if(args.filter && (j_tt>2 && j_tt<superHeight-2) && (i_tt>2 && i_tt<superWidth-2))
							tempColor += blur2.GetPixel(j_tt, i_tt);
						else
							tempColor += superOutput.GetPixel(j_tt, i_tt);
						tempColor2 += superDepth.GetPixel(j_tt, i_tt);
						tempColor3 += superNormal.GetPixel(j_tt, i_tt);
					}
				}

				outputImage.SetPixel(j, i, tempColor/9.0f);
				depthImage.SetPixel(j, i, tempColor2/9.0f);
				normalImage.SetPixel(j, i, tempColor3/9.0f);
			}
		}
	}

	//Performance Benchmarking
	auto stop_time = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop_time - start_time);

	cout << "Render Time: " << (duration.count()/1000.0f) << " seconds" << endl;

	//Saving Output Image
	if(args.output_file != nullptr)
	{
		printf("Exporting the Output BMP File: %s\n", args.output_file);
		outputImage.SaveBMP(args.output_file);
	}
	//Saving Depth Map
	if(args.depth_file != nullptr)
	{
		printf("Exporting the Depth Map File: %s\n", args.depth_file);
		depthImage.SaveBMP(args.depth_file);
	}
	//Saving Normal Image
	if(args.normals_file != nullptr)
	{
		printf("Exporting the Normal BMP File: %s\n", args.normals_file);
		normalImage.SaveBMP(args.normals_file);
	}
	std::cout << "-----------------------------------\n";

	return 0;
}

