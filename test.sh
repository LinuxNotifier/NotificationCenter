cd build
export LD_LIBRARY_PATH="/home/zhiping/Applications/Qt/5.10.1/gcc_64/lib/l;/home/zhiping/Projects/QtProjects/Notifier/modules/dbus;$LD_LIBRARY_PATH"
make test_NotificationCenter -j3 && ./test/NotificationCenter/test_NotificationCenter
