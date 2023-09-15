# clear
pushd build > /dev/null

# -Wno-compare-distinct-pointer-types // doesn't work
gcc ../main.c -o output.exe -g -Wno-incompatible-pointer-types

result=$?

popd > /dev/null

if [ $result -eq 0 ]; then
	./build/output.exe
fi
exit $result