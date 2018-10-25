# to use clang++: export CXX=/usr/bin/clang++ && ../x.sh
# to switch between DEBUG/RELEASE: cmake -DCMAKE_BUILD_TYPE=Release ..
cd build
# make clean
# rm * -rf && cmake .. && make -j3
cmake -DCMAKE_BUILD_TYPE=Debug .. -DCMAKE_INSTALL_PREFIX=/tmp/NotificationCenter -DCMAKE_PREFIX_PATH=/home/zhiping/Applications/Qt/5.10.1/gcc_64/
# cmake -DCMAKE_BUILD_TYPE=Release .. -DCMAKE_INSTALL_PREFIX=/tmp/NotificationCenter -DCMAKE_PREFIX_PATH=/home/zhiping/Applications/Qt/5.10.1/gcc_64/
mkdir NotificationCenter/languages -p
cp *.qm NotificationCenter/languages
export LD_LIBRARY_PATH="/home/zhiping/Applications/Qt/5.10.1/gcc_64/lib/l;/home/zhiping/Projects/QtProjects/Notifier/modules/dbus;$LD_LIBRARY_PATH"
make -j3 && cp plugins/*/*.so NotificationCenter/plugins/ && ./NotificationCenter/NotificationCenter
# make translations
