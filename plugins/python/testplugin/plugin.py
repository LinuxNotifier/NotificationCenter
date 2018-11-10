import sip
import PyNc
from PyNc import NotificationCenter as NC
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QVBoxLayout


class Plugin(PyNc.ExtensionInterface):
    def initialize(self, nc):
        return True

    def metadata(self):
        # return PyQt5.QtCore.QJsonObject()
        # return QJsonObject()
        return {}

    def centralWidget(self):
        widget = QWidget()
        layout = QVBoxLayout(widget)
        pb = QPushButton(widget)
        layout.addWidget(pb)
        pb.setText("haha")
        pb.setParent(widget)
        widget.setWindowTitle("plugin from Python")
        # widget.show()
        self.widget = widget
        return self.widget

    def settingsWidget(self):
        return QWidget()


def run():
    print("*********************** welcome to python world **********************")
    msg = PyNc.NcMessage()
    print(msg.messageId())
    nc = NC.instance()
    # mainwin = PyNc.MainWindow()
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
    run()
