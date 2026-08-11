cd build
make -j$(nproc)
ctest --output-on-failure