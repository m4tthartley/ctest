# clear
# pushd build > /dev/null

# -Wno-compare-distinct-pointer-types // doesn't work
gcc main.c -o build/output.exe -I ../core -g -Wno-incompatible-pointer-types -lopengl32 -lgdi32

result=$?

# popd > /dev/null

# if [ $result -eq 0 ]; then
# 	./build/output.exe
# fi
exit $result