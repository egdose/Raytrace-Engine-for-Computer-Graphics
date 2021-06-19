#!/bin/sh

./a5 -input scene01_plane.txt  -size 300 300 -output 1.bmp\
   -shadows -bounces 1 -jitter -filter -depth 0 10 1z_depth.bmp -normals 1z_normal.bmp
./a5 -input scene02_cube.txt  -size 300 300 -output 2.bmp\
   -shadows -bounces 1 -jitter -filter -depth 0 10 2z_depth.bmp -normals 2z_normal.bmp
./a5 -input scene03_sphere.txt  -size 300 300 -output 3.bmp\
   -shadows -bounces 1 -jitter -filter -depth 0 10 3z_depth.bmp -normals 3z_normal.bmp
./a5 -input scene04_axes.txt  -size 300 300 -output 4.bmp\
   -shadows -bounces 1 -jitter -filter -depth 0 10 4z_depth.bmp -normals 4z_normal.bmp
./a5 -input scene05_bunny_200.txt  -size 300 300 -output 5.bmp\
   -shadows -bounces 1 -jitter -filter -depth 0 10 5z_depth.bmp -normals 5z_normal.bmp
./a5 -input scene07_shine.txt  -size 300 300 -output 7.bmp\
   -shadows -bounces 1 -jitter -filter -depth 0 10 7z_depth.bmp -normals 7z_normal.bmp
./a5 -input scene08_c.txt -size 300 300 -output 8.bmp\
   -shadows -bounces 1 -jitter -filter -depth 0 10 8z_depth.bmp -normals 8z_normal.bmp
./a5 -input scene09_s.txt -size 300 300 -output 9.bmp\
   -shadows -bounces 1 -jitter -filter -depth 0 10 9z_depth.bmp -normals 9z_normal.bmp
