# Collision Detection (SDL3 / C)

**Demo in the browser:** https://8observer8.github.io/examples/sdl3/collision-detection-box2d-3.1.1-sdl-3.3.6-c

**EXE for Windows 10, 64-bit:** [english-text-sdl-3.3.6-c-exe.zip](https://www.dropbox.com/scl/fi/ix3eesrf2q5j6zxqtaxij/collision-detection-box2d-3.1.1-sdl-3.3.6-c-exe.zip?rlkey=hk4b5cgomcts1rvif8asma42r&st=5rsr6vx9&raw=1)
- Zip size: 2.43 MB
- Unzipped: 5.56 MB

---

Version in Python: [GitHub repository](https://github.com/8Observer8/collision-detection-pybox2d-2.3.1-pysdl-3.3.2-python)

---

## File Sizes

**WASM ( built with Emscripten 4.0.15):**

- `index.html` — 3.27 KB
- `app.js` — 186 KB
- `app.wasm` — 2.17 MB
- **Total:** 2.35 MB

**EXE (built with MinGW GCC 11.2):**

- EXE — 607 KB
- `SDL3.dll` (v3.3.6) — 2.65 MB
- `SDL3_ttf.dll`(v3.2.2) — 1.92 MB
- Assets ([LiberationSans-Regular.ttf](https://github.com/liberationfonts/liberation-fonts/releases/tag/2.1.5)) — 402 KB
- **Total:** 5.56 MB

---

## Tools to Build the EXE

- [MinGW GCC 11.2](https://github.com/brechtsanders/winlibs_mingw/releases/download/11.2.0-14.0.0-9.0.0-ucrt-r7/winlibs-x86_64-posix-seh-gcc-11.2.0-mingw-w64ucrt-9.0.0-r7.zip) (zip - 178 MB, unzipped - 671 MB)
- [box2d-3.1.1-mingw.zip](https://www.dropbox.com/scl/fi/4rnfxs7zzfzghmax008va/box2d-3.1.1-mingw.zip?rlkey=drmv2k5s8erhjv0e7o728ybib&st=ltavrgj7&raw=1) (zip - 239 KB, unzipped - 827 KB)
- [SDL3-3.3.6-win32-x64.zip](https://www.dropbox.com/scl/fi/8zjwbr9xddx4v2lyt1wcz/SDL3-3.3.6-win32-x64.zip?rlkey=25j235cj7omg6209rzyrhsq2r&st=dmrm7nwo&raw=1) (zip - 1.09 MB, unzipped - 2.65 MB)
- [SDL3-devel-3.3.6-mingw.zip](https://www.dropbox.com/scl/fi/vzml2n9l2pz5ti5foq531/SDL3-devel-3.3.6-mingw.zip?rlkey=euh4qomybr19r4lz9rkda27s3&st=kebihweu&raw=1) (zip - 2.64 MB, unzipped - 9.43 MB)
- [SDL3_ttf-3.2.2-win32-x64.zip](https://www.dropbox.com/scl/fi/p33ll3ugh6iclm26ihmg9/SDL3_ttf-3.2.2-win32-x64.zip?rlkey=7cwafwymlfmhawo9c1cofemdk&st=3fhfm8vt&raw=1) (zip - 980 KB, unzipped - 1.57 MB)
- [SDL3_ttf-devel-3.2.2-mingw.zip](https://www.dropbox.com/scl/fi/5mvpyk9rentyea4315wfi/SDL3_ttf-devel-3.2.2-mingw.zip?rlkey=41rf5qvlel3ejdmycacewv9x3&st=0z7oen81&raw=1) (zip - 1.33 MB, unzipped - 3.15 MB)
- [freetype-2.13.3-mingw.zip](https://www.dropbox.com/scl/fi/wo7zns5jo75bqo1c0bbuq/freetype-2.13.3-mingw.zip?rlkey=o3lulbob9cwd73tw43y9o0ra0&st=5fculia5&raw=1) (zip - 572 KB, unzipped - 1.54 MB)

---

## Tools to Build WebAssembly

- [Emscripten 4.0.15](https://emscripten.org/docs/getting_started/downloads.html) (1.82 GB)
- [box2d-3.1.1-wasm.zip](https://www.dropbox.com/scl/fi/lqssynczgrn91v6t62nuz/box2d-3.1.1-wasm.zip?rlkey=oruvl6ti3heq9df7jdwyow2ns&st=e3gt9l5a&raw=1) (zip - 555 KB, unzipped - 1.37 MB)
- [SDL3-devel-3.3.6-wasm.zip](https://www.dropbox.com/scl/fi/3sleht6wezn2yrb8bppgq/SDL3-devel-3.3.6-wasm.zip?rlkey=xi5t3spmpqd0vutc2o7205sqw&st=5in1umrq&raw=1) (zip - 1.21 MB, unzipped - 5.21 MB)
- [SDL3_ttf-devel-3.2.2-wasm.zip](https://www.dropbox.com/scl/fi/y5i1ijt2go41nu2l8o1nh/SDL3_ttf-devel-3.2.2-wasm.zip?rlkey=ab0y09j0o5755bc81ur79rlg1&st=r2306dkl&raw=1) (zip - 62 KB, unzipped - 213 KB)
- [freetype-2.13.3-wasm.zip](https://www.dropbox.com/scl/fi/wxxswsratpyq9rv88a9y3/freetype-2.13.3-wasm.zip?rlkey=z7xrjepcngwjb749656dhidph&st=1tnm9mg0&raw=1) (zip - 1.2 MB, unzipped - 2.89 MB)

---

## How to Build EXE (Windows)

- Add [MinGW GCC 11.2](https://github.com/brechtsanders/winlibs_mingw/releases/download/11.2.0-14.0.0-9.0.0-ucrt-r7/winlibs-x86_64-posix-seh-gcc-11.2.0-mingw-w64ucrt-9.0.0-r7.zip) `bin` folder to your `PATH`.
- Add [SDL3-3.3.6-win32-x64.zip](https://www.dropbox.com/scl/fi/8zjwbr9xddx4v2lyt1wcz/SDL3-3.3.6-win32-x64.zip?rlkey=25j235cj7omg6209rzyrhsq2r&st=dmrm7nwo&raw=1) folder to your `PATH`.
- Add [SDL3_ttf-3.2.2-win32-x64.zip](https://www.dropbox.com/scl/fi/p33ll3ugh6iclm26ihmg9/SDL3_ttf-3.2.2-win32-x64.zip?rlkey=7cwafwymlfmhawo9c1cofemdk&st=3fhfm8vt&raw=1) folder to your `PATH`.
- Configure paths in `config-web.bat` for your SDL3 libraries.
- From the project root, run:

```bat
config-exe
build-exe
run-exe
```

## How to Build WebAssembly

1. Set up [Emscripten 4.0.15](https://emscripten.org/docs/getting_started/downloads.html) and Node.js
2. Install http-server globally:

```bat
npm i http-server -g
```

3. Configure paths in `config-web.bat` for your SDL3 libraries.
4. From the project root, run:

```bat
config-web
build-web
http-server -c-1
```

5. Open your browser and go to http://localhost:8080 to run the app locally.

> Note: You can also run the WASM app on Android via Wi-Fi using http-server. After starting the server, it will show local URL addresses — just type one into your mobile browser.

This example uses a free font file: https://github.com/liberationfonts/liberation-fonts/releases/tag/2.1.5
