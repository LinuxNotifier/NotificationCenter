# to use clang++: export CXX=/usr/bin/clang++ && ../x.sh
# to switch between DEBUG/RELEASE: cmake -DCMAKE_BUILD_TYPE=Release ..
cd build
# make clean
# rm * -rf && cmake .. && make -j3
cmake -DCMAKE_BUILD_TYPE=Debug .. -DCMAKE_INSTALL_PREFIX=/tmp/NotificationCenter
# cmake -DCMAKE_BUILD_TYPE=Release .. -DCMAKE_INSTALL_PREFIX=/tmp/NotificationCenter
mkdir NotificationCenter/languages -p
cp *.qm NotificationCenter/languages
# make -j3 && cp plugins/*/*.so NotificationCenter/plugins/ && cp modules/python3/libpython.so NotificationCenter/plugins && ./NotificationCenter/NotificationCenter
make -j3 && cp plugins/*/*.so NotificationCenter/plugins/ && cp modules/python3/libpymodule.so NotificationCenter/plugins && ./NotificationCenter/NotificationCenter
# make translations
# make PyNc
