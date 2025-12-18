cmake -G "MinGW Makefiles" -S . -B dist/win ^
-Dbox2d_DIR=H:/libs/box2d-3.1.1-mingw/lib/cmake/box2d ^
-DSDL3_DIR=H:/libs/SDL3-devel-3.3.6-mingw/lib/cmake/SDL3 ^
-DSDL3_ttf_DIR=H:/libs/SDL3_ttf-devel-3.2.2-mingw/lib/cmake/SDL3_ttf ^
-DCMAKE_BUILD_TYPE=Debug
