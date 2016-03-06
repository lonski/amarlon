del /S /Q src\*.h
del /S /Q src\*.cc
protoc\protoc.exe -I=def --cpp_out=src def\*.proto

echo.&pause