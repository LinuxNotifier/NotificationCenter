import Py
from .secret import client_id, client_secret, scope
from Py import NotificationCenter as NC
import time
import json
from urllib import parse as urlparse
import requests
import threading
from http.server import BaseHTTPRequestHandler, HTTPServer
from PyQt5.QtCore import QObject, pyqtSignal, pyqtSlot, QThread, QCoreApplication
from PyQt5.QtGui import QDesktopServices
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QVBoxLayout
import webbrowser
import random
import string
import todoist


class OThread(QThread):
    def __init__(self, target):
        super().__init__()
        self.target = target

    def run(self):
        print('starting thread')
        self.target()


class OAuthServer(HTTPServer):
    def __init__(self, authencator, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self._OAuthHandler__authencator = authencator


class OAuthHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path.startswith("/oauth/authorize"):
            self.send_response(200)
            self.end_headers()
            self.wfile.write('ok'.encode('utf-8'))
            query_params = dict(urlparse.parse_qsl(urlparse.urlparse(self.path).query))
            code = query_params['code']
            access_token_url = "https://todoist.com/oauth/access_token?client_id={}&client_secret={}&code={}".format(client_id, client_secret, code)
            access_token = json.loads(requests.post(access_token_url).text)['access_token']

            self.server.__authencator.authenticated[str].emit(access_token)
        else:
            self.send_error(404, 'unknown error')

    def do_POST(self):
            self.send_error(404, 'unknown error')


class Authencator(QObject):
    authenticated = pyqtSignal(str)
    finished = pyqtSignal(todoist.TodoistAPI)
    hostname = 'localhost'
    port = 9001
    httpd = None

    def __init__(self):
        super().__init__()
        self.authenticated[str].connect(self.on_authenticated)

    @pyqtSlot()
    def start(self):
        state = ''.join(random.sample(string.ascii_letters + string.digits, 10))
        authorization_url = "https://todoist.com/oauth/authorize?client_id={}&scope={}&state={}".format(client_id, scope, state)

        webbrowser.open(authorization_url)
        QCoreApplication.processEvents()

        if self.httpd is None:
            self.httpd = OAuthServer(self, (self.hostname, self.port), OAuthHandler)
            print(time.asctime(), "server starts - %s:%s" % (self.hostname, self.port))
            self.httpd.serve_forever()
            print('server stoped')
            time.sleep(0.2)
            api = todoist.TodoistAPI(self.access_token)
            api.sync()
            self.finished[todoist.TodoistAPI].emit(api)
        else:
            print('server already started')

    def stop(self):
        pass

    @pyqtSlot(str)
    def on_authenticated(self, access_token):
        self.httpd.shutdown()
        self.httpd = None
        self.access_token = access_token


class PluginWidget(QWidget):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        layout = QVBoxLayout(self)
        pb = QPushButton(self)
        pb.clicked.connect(self.start_authenticate)
        layout.addWidget(pb)
        pb.setText("authorize")
        self.setWindowTitle("todoist")

        self.pb = pb
        self.layout = layout
        self.thread = None
        self.auth = None

    @pyqtSlot()
    def start_authenticate(self):
        if self.thread is None:
            self.thread = QThread()
            self.auth = Authencator()
        self.auth.finished[todoist.TodoistAPI].connect(self.auth_finished)
        # NOTE: we have to use QThread: https://stackoverflow.com/questions/1595649/threading-in-a-pyqt-application-use-qt-threads-or-python-threads and http://blog.qt.io/blog/2010/06/17/youre-doing-it-wrong/
        # the right way to use QThread: https://wiki.qt.io/QThreads_general_usage
        # also set self.thread = thread to prevent python garbage collection
        self.auth.moveToThread(self.thread)
        self.thread.started.connect(self.auth.start)
        self.thread.start()

    @pyqtSlot(todoist.TodoistAPI)
    def auth_finished(self, api):
        if api is None:
            print('auth failed')
        else:
            print('auth finished', api)
            self.api = api
            for project in self.api.state['projects']:
                print(project['name'])
            self.auth.stop()


# WARNING: DO NOT sub-class QObject
class Plugin(Py.ExtensionInterface):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def initialize(self, nc):
        # test use
        # msg = Py.Notification()
        # msg.setTitle("hello from python")
        # NC.notify(msg)
        return True

    def metadata(self):
        return {"name": "todoist"}

    def centralWidget(self):
        self.widget = PluginWidget()
        return self.widget

    def settingsWidget(self):
        return QWidget()


def main():
    app = QApplication([])
    plugin = Plugin()
    plugin.initialize(None)
    w = plugin.centralWidget()
    w.show()
    return app.exec()


if __name__ == '__main__':
    main()
