#include "mainwindow.h"
#include <QApplication>
#include <Catch2/catch.hpp>

TEST_CASE("test MainWindow", "[mainwindow], [widget]") {

    qSetMessagePattern("[%{type}] " __FILENAME__ ":%{line} <%{function}> %{message}");
    int argc = 1;
    char *argv[] = {(char *)"./test_main"};
    QApplication app(argc, argv);
    MainWindow w;
    w.loadTheme("dark");
}
