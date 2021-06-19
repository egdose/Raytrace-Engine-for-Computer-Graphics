#!/bin/sh

./a5soln -input scene06_bunny_1k.txt  -size 300 300 -output 6soln.bmp\
   -shadows -bounces 3 -jitter -filter
./a5soln -input scene10_sphere.txt  -size 300 300 -output 10soln.bmp\
   -shadows -bounces 3 -jitter -filter
./a5soln -input scene11_cube.txt  -size 300 300 -output 11soln.bmp\
 -shadows -bounces 3 -jitter -filter
./a5soln -input scene12_vase.txt  -size 300 300 -output 12soln.bmp\
 -shadows -bounces 3 -jitter -filter
./a5soln -input scene13_diamond.txt  -size 300 300 -output 13soln.bmp\
 -shadows -bounces 3 -jitter -filter

