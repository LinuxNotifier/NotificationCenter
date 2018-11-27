# to use clang++: export CXX=/usr/bin/clang++ && ../x.sh
# to switch between DEBUG/RELEASE: cmake -DCMAKE_BUILD_TYPE=Release ..
cd build
# make clean
# rm * -rf && cmake .. && make -j3
cmake -DCMAKE_BUILD_TYPE=Debug .. -DCMAKE_INSTALL_PREFIX=/tmp/NotificationCenter
# cmake -DCMAKE_BUILD_TYPE=Release .. -DCMAKE_INSTALL_PREFIX=/tmp/NotificationCenter
make -j3 && ./NotificationCenter/NotificationCenter
# make translations
# make PyNc
