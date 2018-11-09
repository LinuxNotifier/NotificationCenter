import sip
import PyNc
from PyNc import NotificationCenter as NC
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QVBoxLayout
# from PyQt5.QtCore import QJsonObject
# from PyQt5.QtGui import *
import sys


print(sys.argv)
widget = QWidget()
layout = QVBoxLayout(widget)
pb = QPushButton(widget)
layout.addWidget(pb)
pb.setText("haha")
pb.setParent(widget)
widget.setWindowTitle("plugin from Python")
# widget.show()


class Plugin(PyNc.PluginInterface):
    def initialize(self, nc):
        pass

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

    def interfaceVersion(self):
        return "v0.2.1"


def run():
    print("*********************** welcome to python world **********************")
    msg = PyNc.NcMessage()
    print(msg.messageId())
    nc = NC.instance()
    # nc.setView(mainwin)
    print(sip.unwrapinstance(nc.view()))
    print('notifying message')
    # nc.notify(msg)
    print('instanize Plugin')
    plugin = Plugin()
    print('adding plugin Plugin')
    NC.instance().addPlugin(plugin)
    print('plugin Plugin added')
    print("*********************** end of journey **********************")


if __name__ == '__main__':
    app = QApplication([])
    # mainwin = PyNc.MainWindow()
    run()
