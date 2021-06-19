echo "Executing-------------------------------------------"
./a4 -input scene01_plane.txt -size 400 400 -output 1.bmp -depth 2 3 1_depth.bmp -normal 1_normal.bmp
./a4 -input scene02_cube.txt  -size 400 400 -output 2.bmp -depth 2 3 2_depth.bmp -normal 2_normal.bmp
./a4 -input scene03_sphere.txt  -size 400 400 -output 3.bmp -depth 2 3 3_depth.bmp -normal 3_normal.bmp
./a4 -input scene04_axes.txt  -size 400 400 -output 4.bmp -depth 2 3 4_depth.bmp -normal 4_normal.bmp
./a4 -input scene05_bunny_200.txt -size 400 400 -output 5.bmp -depth 2 3 5_depth.bmp -normal 5_normal.bmp
./a4 -input scene06_bunny_1k.txt -size 400 400 -output 6.bmp -depth 2 3 6_depth.bmp -normal 6_normal.bmp
./a4 -input scene07_shine.txt  -size 400 400 -output 7.bmp -depth 2 3 7_depth.bmp -normal 7_normal.bmp
./a4 -input scene08_c.txt -size 400 400 -output 8.bmp -depth 2 3 8_depth.bmp -normal 8_normal.bmp
./a4 -input scene09_s.txt -size 400 400 -output 9.bmp -depth 2 3 9_depth.bmp -normal 9_normal.bmp
