emcmake cmake -S . -B dist/web ^
-Dbox2d_DIR=H:/libs/box2d-3.1.1-wasm/lib/cmake/box2d ^
-DSDL3_DIR=H:/libs/SDL3-devel-3.3.6-wasm/lib/cmake/SDL3 ^
-DSDL3_ttf_DIR=H:/libs/SDL3_ttf-devel-3.2.2-wasm/lib/cmake/SDL3_ttf ^
-DFREETYPE_INCLUDE_DIRS=H:/libs/freetype-2.13.3-wasm/include ^
-DFREETYPE_LIBRARY=H:/libs/freetype-2.13.3-wasm/lib/libfreetype.a ^
-DCMAKE_BUILD_TYPE=Debug
