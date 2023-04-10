# Building

## Linux Terminal

```bash
mkdir build
cmake -S . -B build
cmake --build build
```

You can then execute the binary with `./build/EverythingNMN`.

If you need Language Server Protocol support for autocomplete (It needs to have support for `compile_commands.json`),
you can use the following.

```
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
ln -s /path/to/myproject/build/compile_commands.json /path/to/myproject/
```

Using the `-DCMAKE_EXPORT_COMPILE_COMMANDS` creates a `compile_commands.json` file. The second command creates a symlink
to the root of the project, as your IDE or setup probably requires it to be in the root. Otherwise, you can setup your
IDE/setup to use the file from the build directory.

## Windows (Visual Studio)

You can select `File -> Open -> Local Folder` and open the folder containing `CMakeLists.txt` (the root of this repository).
You can see [Microsoft's docomentation](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio) 
on the matter for more details on using Visual Studio with CMake.

Click the fourth button from the left on the properties panel (Switch between solutions and available views),
select the "CMake Targets View" and hit Enter.Wait for a while, and after it parses it, you will have the project.
After it parses, it will bring you back to Project View and you can see the "EveryhingNMM" project and you can 
right click the executable and hit Build/Debug. 

You will need to copy the DLLs from the `out/build/<BUILD_TYPE>/_deps/sfml-build/lib` to the `out/build/<BUILD_TYPE>` directory.
`BUILD_TYPE` will be something like `x64-Debug` or `x86-Debug` or `x64-Release` (for Release mode).
Optionally, you can just add the directory containing the DLLs to your PATH environment variable.

# Building Documentation
We use [Doxygen](https://www.doxygen.nl/index.html) for our documentation. To use it, `cd` into
the docs directory, run `doxygen Doxyfile`, and in the `docs/html` directory there should be an `index.html`
file you can open in your preferred web browser.
