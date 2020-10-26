sudo apt install clang libsdl2-2.0-0 libsdl2-dev libsdl2-mixer-dev libsdl2-net-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-gfx-dev curl gnupg
export PATH_TO_2DBOXING_RESOURCES=`pwd`
export PATH=$PATH:$PATH_TO_2DBOXING_RESOURCES/bin
export PATH="$HOME/bin:$PATH" 
curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor > bazel.gpg
sudo mv bazel.gpg /etc/apt/trusted.gpg.d/
echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list
sudo apt update && sudo apt install bazel-3.7.0