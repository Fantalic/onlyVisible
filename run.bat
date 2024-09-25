cd build
g++ ../src/*.cpp -o Game.exe -O2 -Wall -Wno-missing-braces -I ../include/ -L ../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
IF %ERRORLEVEL% NEQ 0 pause /B %ERRORLEVEL%
Game.exe
cd..