#include <Python.h>
#include "python.h"
#include <dlfcn.h>
#include "debug.h"
#include <QCoreApplication>
#include <QStringList>

Python::Python(QObject *parent) :
    QObject(parent)
{
    
}

Python::~Python()
{
    Py_Finalize();
}

bool Python::initialize(NotificationCenter *nc)
{
    QStringList argv = QCoreApplication::arguments();
    int argc = argv.length();

    // FIXME: don't use specific version
    // fix undefined symbol: https://bugs.python.org/issue4434
    if (!dlopen("libpython3.5m.so", RTLD_LAZY | RTLD_GLOBAL)) {
		qWarning() << "failed to load libpython3.5m.so";
        return false;
    }

    Py_Initialize();
    PyEval_InitThreads();
    wchar_t *python_argv[argc];
    for (int i = 0; i < argc; i++) {
        python_argv[i] = Py_DecodeLocale(argv[i].toLatin1().data(), NULL);
    }
    PySys_SetArgv(argc, python_argv);

    wchar_t *path = Py_DecodeLocale((qApp->applicationDirPath() + "/plugins/python").toLatin1().data(), NULL);
    Py_SetPath(path);
    wchar_t *program_name = Py_DecodeLocale("NotificationCenter", NULL);
    Py_SetProgramName(program_name);
    for (int i = 0; i < argc; i++) {
        PyMem_RawFree(python_argv[i]);
    }
    PyMem_RawFree(path);
    PyMem_RawFree(program_name);

    // loadPythonPlugins();
    // to make sure all other preparation work all done,
    // because loadPythonPlugins() will call app.exec(),
    // which will block the code after that.
    QTimer::singleShot(3000, this, &Python::loadPythonPlugins);

    return true;
}

QJsonObject Python::metadata() const
{
    return QJsonObject();
}

void Python::loadPythonPlugins()
{
    // Py_BEGIN_ALLOW_THREADS
    // Py_END_ALLOW_THREADS
    //
    // PyGILState_STATE gstate;
    // gstate = PyGILState_Ensure();
    PyRun_SimpleString("import os\n"
                       "import sys\n"
                       "import importlib\n"
                       "from PyQt5.QtWidgets import qApp\n"
                       "plugins_path = os.path.join(qApp.applicationDirPath(), 'plugins', 'python')\n"
                       "sys.path.insert(0, plugins_path)\n"
                       "modules_path = os.path.join(qApp.applicationDirPath(), 'modules')\n"
                       "sys.path.insert(0, modules_path)\n"
                       "from Py import NotificationCenter as NC\n"
                       "plugins = []\n"
                       "for package in os.listdir(plugins_path):\n"
                       "    plugin = os.path.join(plugins_path, package)\n"
                       "    if os.path.isdir(plugin):\n"
                       "        try:\n"
                       "            module = importlib.import_module(package)\n"
                       "            plugin = module.Plugin()\n"
                       "            plugins.append(plugin)\n"
                       "            NC.instance().registerExtension(plugin)\n"
                       // "            NC.instance().newExtension.emit(plugin)\n"
                       "        except Exception as e:\n"
                       "            print(e)\n"
                       "print('all python plugins loaded')\n"
                       "qApp.exec()\n"
                       "print('qApp.exec()')\n"
                       "del os\n"
                       "del sys\n"
                       "del importlib\n"
                       "del plugins_path\n"
                       "del modules_path\n"
                       "del NC\n"
                       "del package\n"
                       "del plugin_file\n"
                       "del module\n"
                       );
    // PyGILState_Release(gstate);
    qDebug() << "loaded python plugins";
}
