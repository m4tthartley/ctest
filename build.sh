# clear
# pushd build > /dev/null

# -Wno-compare-distinct-pointer-types // doesn't work
files="main.c ../core/audio.cpp"
gcc $files -o build/output.exe -I ../core -g -Wno-incompatible-pointer-types -lopengl32 -lgdi32 -lOle32

result=$?

# popd > /dev/null

# if [ $result -eq 0 ]; then
# 	./build/output.exe
# fi
exit $result
