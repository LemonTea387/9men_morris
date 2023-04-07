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

You can select `Open -> Local Folder` and open the folder containing `CMakeLists.txt` (the root of this repository).
You can see [Microsoft's docomentation](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio) 
on the matter for more details on using Visual Studio with CMake.
