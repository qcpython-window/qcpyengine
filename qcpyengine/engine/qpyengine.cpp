#include "qpyengine.h"
QPyEngine* QPyEngine::global()
{
	static QPyEngine p_qpyengine;
	return &p_qpyengine;
}
QPyEngine::QPyEngine(QObject *parent)
	: QObject(parent)
{}

QPyEngine::~QPyEngine()
{

}

void QPyEngine::begin()
{
	
    Q_ASSERT_X(Py_IsInitialized() == 0, "QPyCore::QPyEngine", "is initialized");
    Py_Initialize();
	PyGILState_STATE state = PyGILState_Ensure();
	m_globals = PyModule_GetDict(PyImport_AddModule("__main__"));
	m_sys = PyImport_ImportModule("sys");
	m_sysdict = PyModule_GetDict(m_sys);
	PyGILState_Release(state);
	
}
void QPyEngine::end()
{
    Q_ASSERT_X(Py_IsInitialized() > 0, "QPyCore::QPyEngine", "is finalize");
	PyGILState_STATE state = PyGILState_Ensure();
    PyGILState_Release(state);
    Py_Finalize();
	
}
void QPyEngine::configDirs()
{
    PyStatus status;
    PyConfig config;
    PyConfig_InitPythonConfig(&config);
    config.module_search_paths_set = 1;

    for (const QDir& dir : m_dirs) {
        wchar_t* wdir = Py_DecodeLocale(dir.path().toUtf8(), NULL);
        status = PyWideStringList_Append(&config.module_search_paths, wdir);
        if (PyStatus_Exception(status)) {
            PyConfig_Clear(&config);
            Py_ExitStatusException(status);
            break;
        }
    }
    if (m_dirs.isEmpty() == true)
    {
        wchar_t* wdir = Py_DecodeLocale("", NULL);
        status = PyWideStringList_Append(&config.module_search_paths, wdir);
        if (PyStatus_Exception(status)) {
            PyConfig_Clear(&config);
            Py_ExitStatusException(status);
        }
    }
    status = Py_InitializeFromConfig(&config);
    if (PyStatus_Exception(status)) {
        PyConfig_Clear(&config);
        Py_ExitStatusException(status);
    }
}
void QPyEngine::addDir(const QDir& dir)
{
    Q_ASSERT_X(Py_IsInitialized() > 0, "QPyCore::QPyEngine", "not initialized");
    if (dir.exists() == true) {
        m_dirs << dir;
        configDirs();
    }
}
QPyObject QPyEngine::eval(const QString& code, const QString& filename)
{
    Q_ASSERT_X(Py_IsInitialized() > 0, "QPyCore::QPyEngine", "not initialized");
    PyGILState_STATE state = PyGILState_Ensure();
    PyObject* result = nullptr;
    PyObject* compile = Py_CompileString(code.toUtf8(), filename.toUtf8(), Py_eval_input);
    if (compile != nullptr) {
        result = PyEval_EvalCode(compile, m_globals, nullptr);
    } else {
        if (PyErr_Occurred() != nullptr) {
            PyErr_Clear();
        }
    }
    PyGILState_Release(state);
    return result;
}
QPyObject QPyEngine::exec(const QString& code, const QString& filename)
{
    Q_ASSERT_X(Py_IsInitialized() > 0, "QPyCore::QPyEngine", "not initialized");
    PyGILState_STATE state = PyGILState_Ensure();
    PyObject* compile = Py_CompileString(code.toUtf8(), filename.toUtf8(), Py_file_input);
    PyObject* result = nullptr;
    if (compile != nullptr) {
        result = PyEval_EvalCode(compile, m_globals, nullptr);
    } else {
        if (PyErr_Occurred() != nullptr) {
            PyErr_Print();
            PyErr_Clear();
        }
    }
    PyGILState_Release(state);
    return result;
}
QPyObject QPyEngine::evaluate(const QString& code, const QString& filename)
{
    Q_ASSERT_X(Py_IsInitialized() > 0, "QPyCore::QPyEngine", "not initialized");
    PyObject* evalvalue = eval(code, filename);
    if (evalvalue != nullptr) {
        return evalvalue;
    } else {
        PyObject* execvalue = exec(code, filename);
        return execvalue;
    }
    return QPyObject();
}
void QPyEngine::run(const QString& code)
{
    Q_ASSERT_X(Py_IsInitialized() > 0, "QPyCore::QPyEngine", "not initialized");
    PyGILState_STATE state = PyGILState_Ensure();
    if (PyRun_String(code.toUtf8(), Py_file_input, m_globals, nullptr) == nullptr) {
        PyObject* given = PyErr_Occurred();
        if (given != nullptr) {
            PyErr_Print();
            PyErr_Clear();
        }
    }
    PyGILState_Release(state);
}