CFLAGS = ${BASEFLAGS} `sdl-config --cflags`
LDFLAGS = ${BASEFLAGS} `sdl-config --libs` -lSDL_ttf
