all:
	gcc -Iinclude/ src/main.c src/model.c src/draw.c src/camera.c src/utils.c src/glutcallbacks.c src/modelloader.c src/scene.c -lSOIL -lglut32 -lopengl32 -lglu32 -lm -o grafbeadando.exe
linux:
	gcc -Iinclude/ src/main.c src/model.c src/draw.c src/camera.c src/utils.c src/glutcallbacks.c src/modelloader.c src/scene.c -fcommon -lSOIL -lobj -lGL -lGLU -lglut -lm -o cube -Wall -Wextra -Wpedantic
