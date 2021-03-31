<!-- @format -->

Requires SDL-2 can be installed from https://www.libsdl.org/download-2.0.php or `sudo apt install libsdl2-dev` `sudo pacman -S boost-libs sdl2`, Project also requires, for linux clang (`sudo apt install clang` [type in root password when prompted] ), and for windows you will need visual studio 2019.

Alternatively, just type in (Debian based distro's only) `chmod +x install_dep.sh && ./install_dep.sh`


Contributers: 
    No one just me (Mikhail Chalakov).


> Only works on Linux for now
`bazel build //main:game`
`cp bazel-bin/main/game .`
`./game`
