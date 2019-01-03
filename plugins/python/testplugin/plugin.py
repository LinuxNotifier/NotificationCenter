import sip
import Py
from Py import NotificationCenter as NC
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QVBoxLayout, QCalendarWidget, QSizePolicy, QTableView, QHeaderView
# from PyQt5.QtGui import QSizePolicy
# from PyQt5.QtCore import QJsonObject
# from PyQt5.QtGui import *
import sys


print(sys.argv)
widget = QWidget()
layout = QVBoxLayout(widget)
# pb = QPushButton(widget)
# layout.addWidget(pb)
# pb.setText("haha")
# pb.setParent(widget)
widget.setWindowTitle("plugin from Python")
cal = QCalendarWidget()
cal.setVerticalHeaderFormat(QCalendarWidget.NoVerticalHeader)
# cal.setMaximumWidth(140)
aux = cal.findChild(QTableView)
aux.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeMode.Fixed)
# aux.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeMode.Stretch)
# aux.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeMode.ResizeToContents)
aux.horizontalHeader().setDefaultSectionSize(48)
print(aux)
# layout.addWidget(cal)
# layout = QVBoxLayout(cal)
widget = cal
widget.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
# widget = QCalendarWidget()
# layout = QVBoxLayout(widget)
# widget.show()


class Plugin(Py.ExtensionInterface):
    def initialize(self, nc):
        return True

    def metadata(self):
        # return PyQt5.QtCore.QJsonObject()
        # return QJsonObject()
        return {}

    def centralWidget(self):
        # FIXME: the object will be garbage cycled
        # widget = QWidget()
        # widget.setWindowTitle("plugin from Python")
        return widget

    def settingsWidget(self):
        return QWidget()


def run():
    print("*********************** welcome to python world **********************")
    msg = Py.Notification()
    print(msg.notificationId())
    nc = NC.instance()
    # nc.setView(mainwin)
    print(sip.unwrapinstance(nc.view()))
    print('notifying notification')
    # nc.notify(msg)
    print('instanize Plugin')
    plugin = Plugin()
    print('adding plugin Plugin')
    NC.instance().registerExtension(plugin)
    print('plugin Plugin added')
    print("*********************** end of journey **********************")


if __name__ == '__main__':
    app = QApplication([])
    # mainwin = Py.MainWindow()
    run()
