build:
	mkdir -p bin/
	g++ \
		-o bin/my_app main.cpp \
		src/graphics/window.cpp -lglfw3 -lGLEW \
		-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -framework Carbon
