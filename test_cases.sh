#!/bin/sh
./a5 -input scene01_plane.txt  -size 300 300 -output renders/1.bmp\
   -shadows -bounces 3 -jitter -filter -depth 0 10 renders/1z_depth.bmp -normals renders/1z_normal.bmp

./a5 -input scene02_cube.txt  -size 300 300 -output renders/2.bmp\
   -shadows -bounces 3 -jitter -filter -depth 0 10 renders/2z_depth.bmp -normals renders/2z_normal.bmp

./a5 -input scene03_sphere.txt  -size 300 300 -output renders/3.bmp\
   -shadows -bounces 3 -jitter -filter -depth 0 10 renders/3z_depth.bmp -normals renders/3z_normal.bmp

./a5 -input scene04_axes.txt  -size 300 300 -output renders/4.bmp\
   -shadows -bounces 3 -jitter -filter -depth 0 10 renders/4z_depth.bmp -normals renders/4z_normal.bmp

./a5 -input scene05_bunny_200.txt  -size 300 300 -output renders/5.bmp\
   -shadows -bounces 3 -jitter -filter -depth 0 10 renders/5z_depth.bmp -normals renders/5z_normal.bmp

./a5 -input scene06_bunny_1k.txt  -size 300 300 -output renders/6.bmp\
   -shadows -bounces 3 -jitter -filter -depth 0 10 renders/6z_depth.bmp -normals renders/6z_normal.bmp

./a5 -input scene07_shine.txt  -size 300 300 -output renders/7.bmp\
   -shadows -bounces 3 -jitter -filter -depth 0 10 renders/7z_depth.bmp -normals renders/7z_normal.bmp

./a5 -input scene08_c.txt  -size 300 300 -output renders/8.bmp\
   -shadows -bounces 3 -jitter -filter -depth 0 10 renders/8z_depth.bmp -normals renders/8z_normal.bmp

./a5 -input scene09_s.txt  -size 300 300 -output renders/9.bmp\
   -shadows -bounces 3 -jitter -filter -depth 0 10 renders/9z_depth.bmp -normals renders/9z_normal.bmp

./a5 -input scene10_sphere.txt  -size 300 300 -output renders/10.bmp\
   -shadows -bounces 3 -jitter -filter -depth 0 10 renders/10z_depth.bmp -normals renders/10z_normal.bmp

./a5 -input scene11_cube.txt  -size 300 300 -output renders/11.bmp\
 -shadows -bounces 3 -jitter -filter -depth 0 10 renders/11z_depth.bmp -normals renders/11z_normal.bmp

./a5 -input scene12_vase.txt  -size 300 300 -output renders/12.bmp\
 -shadows -bounces 3 -jitter -filter -depth 0 10 renders/12z_depth.bmp -normals renders/12z_normal.bmp

./a5 -input scene13_diamond.txt  -size 300 300 -output renders/13.bmp\
 -shadows -bounces 3 -jitter -filter -depth 0 10 renders/13z_depth.bmp -normals renders/13z_normal.bmp
