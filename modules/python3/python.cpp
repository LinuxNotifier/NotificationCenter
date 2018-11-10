#include <Python.h>
#include "python.h"
#include <dlfcn.h>
#include "ncdebug.h"
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

    // fix undefined symbol: https://bugs.python.org/issue4434
    if (!dlopen("libpython3.5m.so", RTLD_LAZY | RTLD_GLOBAL))
		qCritical() << "failed to load libpython3.5m.so";

    Py_Initialize();
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

    loadPythonPlugins();

    return true;
}

QJsonObject Python::metadata() const
{
    return QJsonObject();
}

void Python::loadPythonPlugins()
{
    // return;
    // PyRun_SimpleString("import os\n"
    //                    "import sys\n"
    //                    "import importlib\n"
    //                    "plugins_path = os.path.join(os.getcwd(), 'NotificationCenter', 'plugins', 'python')\n"
    //                    "sys.path.insert(0, plugins_path)\n"
    //                    "modules_path = os.path.join(os.getcwd(), 'NotificationCenter', 'modules')\n"
    //                    "sys.path.insert(0, modules_path)\n"
    //                    "from PyNc import NotificationCenter as NC\n"
    //
    //                    "for package in os.listdir(plugins_path):\n"
    //                    "    plugin_file = os.path.join(plugins_path, package, 'plugin.py')\n"
    //                    "    if os.path.isfile(plugin_file):\n"
    //                    "        module = importlib.import_module(package + '.plugin')\n"
    //                    "        plugin = module.Plugin()\n"
    //                    "        NC.instance().addPlugin(plugin)\n"
    //                    "del os\n"
    //                    "del sys\n"
    //                    "del importlib\n"
    //                    // "del qApp\n"
    //                    "del plugins_path\n"
    //                    "del modules_path\n"
    //                    "del NC\n"
    //                    "del package\n"
    //                    "del plugin_file\n"
    //                    "del module\n"
    //                    );
    // return;
    PyRun_SimpleString("import os\n"
                       "import sys\n"
                       "import importlib\n"
                       "from PyQt5.QtWidgets import qApp\n"
                       "plugins_path = os.path.join(qApp.applicationDirPath(), 'plugins', 'python')\n"
                       "sys.path.insert(0, plugins_path)\n"
                       "modules_path = os.path.join(qApp.applicationDirPath(), 'modules')\n"
                       "sys.path.insert(0, modules_path)\n"
                       "from PyNc import NotificationCenter as NC\n"

                       "for package in os.listdir(plugins_path):\n"
                       "    plugin_file = os.path.join(plugins_path, package, 'plugin.py')\n"
                       "    if os.path.isfile(plugin_file):\n"
                       "        module = importlib.import_module(package + '.plugin')\n"
                       "        plugin = module.Plugin()\n"
                       "        NC.instance().addPlugin(plugin)\n"
                       "del os\n"
                       "del sys\n"
                       "del importlib\n"
                       "del qApp\n"
                       "del plugins_path\n"
                       "del modules_path\n"
                       "del NC\n"
                       "del package\n"
                       "del plugin_file\n"
                       "del module\n"
                       );
}
