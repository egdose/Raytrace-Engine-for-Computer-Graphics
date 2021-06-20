#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>


class ArgParser {

public:

  ArgParser() { DefaultValues(); }

  ArgParser(int argc, char *argv[]) {
    DefaultValues();

    for (int i = 1; i < argc; i++) {

	// rendering output
	if (!strcmp(argv[i],"-input")) {
		//cout << "Input\n";
	i++; assert (i < argc); 
	input_file = argv[i];
	} else if (!strcmp(argv[i],"-output")) {
		//cout << "Output\n";
	i++; assert (i < argc); 
	output_file = argv[i];
	} else if (!strcmp(argv[i],"-normals")) {
		//cout << "Normal\n";
	i++; assert (i < argc); 
	normals_file = argv[i];
	} else if (!strcmp(argv[i],"-size")) {
		//cout << "Size\n";
	i++; assert (i < argc); 
	width = atoi(argv[i]);
	i++; assert (i < argc); 
	height = atoi(argv[i]);
	} 

	// rendering options
	else if (!strcmp(argv[i],"-depth")) {
		//cout << "Depth\n";
	i++; assert (i < argc); 
	depth_min = (float)atof(argv[i]);
	i++; assert (i < argc); 
	depth_max = (float)atof(argv[i]);
	i++; assert (i < argc); 
	depth_file = argv[i];
	} else if (!strcmp(argv[i],"-bounces")) {
		//cout << "Bounces\n";
	i++; assert (i < argc); 
	bounces = atoi(argv[i]);
	} else if (!strcmp(argv[i],"-shadows")) {
		//cout << "Shadows\n";
	shadows = 1;
	}

	//Depth of Field
	else if (strcmp(argv[i], "-dof") == 0) {
		depth_of_field = 1;
	}
	
	// supersampling
	else if (strcmp(argv[i],"-jitter")==0) {
		//cout << "Jitter\n";
	jitter = 1;
	}else if(strcmp(argv[i],"-filter")==0){
		//cout << "Filter\n";
	  filter =1;
	} 
	else {
	  printf ("Unknown command line argument %d: '%s'\n",i,argv[i]);
	  assert(0);
	}
    }
  }

  void DefaultValues() {
    // rendering output
    input_file = NULL;
    output_file = NULL;
    depth_file = NULL;
    normals_file = NULL;
    width = 100;
    height = 100;
    stats = 0;

    // rendering options
    depth_min = 0;
    depth_max = 1;
    bounces = 4;
    shadows = 0;
	depth_of_field = 0;

    // sampling
    jitter = 0;
    filter = 0;
  }

  // ==============
  // REPRESENTATION
  // all public! (no accessors)

  // rendering output
  char *input_file;
  char *output_file;
  char *depth_file;
  char *normals_file;
  int width;
  int height;
  int stats;

  // rendering options
  float depth_min;
  float depth_max;
  int bounces;
  int shadows;
  int depth_of_field;

  // supersampling
  int jitter;
  int filter;
};

#endif // ARG_PARSER_H
