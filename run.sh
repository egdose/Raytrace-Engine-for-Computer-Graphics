clear

echo "Deleting previous executable------------------------"
make clean

echo "Compiling-------------------------------------------"
make
echo "Executing-------------------------------------------"
#./a5 -input scene04_axes.txt  -size 400 400 -output 4.bmp -depth 0 10 4_depth.bmp -normals 4_normal.bmp -bounces 0
./a5 -input scene10_sphere.txt  -size 400 400 -output 10.bmp -shadows -bounces 3 -jitter -filter -depth 0 10 10z_depth.bmp -normals 10z_normal.bmp
# ./a5 -input scene06_bunny_1k.txt  -size 800 800 -output 6.bmp\
#    -shadows -bounces 3 -jitter -filter -depth 0 10 6z_depth.bmp -normals 6z_normal.bmp
# ./test_cases.sh