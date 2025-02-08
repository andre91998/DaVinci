mkdir -p cmake/build
pushd cmake/build
export MY_INSTALL_DIR=$HOME/.local
mkdir -p $MY_INSTALL_DIR
export PATH="$MY_INSTALL_DIR/bin:$PATH"
cmake -DCMAKE_PREFIX_PATH=$MY_INSTALL_DIR ../..
make -j 4