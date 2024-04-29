@echo off
gcc\bin\gcc.exe main.c -o main -I ./SDL2/include -L ./SDL2/lib -lSDL2
main.exe
@REM timeout 3 /nobreak
pause