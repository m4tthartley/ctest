# clear
pushd build > /dev/null

gcc ../main.c -o output.exe -g -Wno-incompatible-pointer-types

result=$?
if [ $result -eq 0 ]; then
	./output.exe
fi
exit $result

# popd > /dev/null

# ./build/output.exe