emcc base.cpp fullscreen.cpp \
    -o index.html \
    -I/path/to/raylib/src \
    ./libraylib_web.a \
    -s USE_GLFW=3 \
    -s ASYNCIFY \
    -s ALLOW_MEMORY_GROWTH=1 \
    -DPLATFORM_WEB \
    -O2