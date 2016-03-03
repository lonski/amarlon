rmdir /S /Q src/*.cc
rmdir /S /Q src/*.h
mkdir src
protoc\protoc.exe -I=def --cpp_out=src def\*.proto

echo.&pause