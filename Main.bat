IF EXIST Main.o DEL /F Main.o
IF EXIST Main.exe DEL /F Main.exe
g++ -c Main.cpp -I./Library/SFML-2.5.1/include -DSFML_STATIC
g++ -Wall Main.o -o Main -L./Library/SFML-2.5.1/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lsfml-main -lsfml-audio
IF EXIST Main.exe cls
IF EXIST Main.exe CALL Main.exe