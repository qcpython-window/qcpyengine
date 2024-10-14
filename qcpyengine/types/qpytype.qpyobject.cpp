module;
#include <qcpyengine/qpytypedefs.h>
module qpytype.qpyobject;


namespace QPy
{
    namespace Type
    {
        const int Object = qRegisterMetaType<QPyObject>();
        const int ObjectStar = qRegisterMetaType<QPyAbstractObject*>();
        const int TypeObjectStar = qRegisterMetaType<QPyAbstractTypeObject*>();
        const int ModuleStar = qRegisterMetaType<QPyAbstractModule*>();
        const int QtObjectStar = QMetaType::QObjectStar;
        const int Void = QMetaType::Void;
    }
}
static QMetaType fromQPyAbstractObject(QPyAbstractObject* qpyobject)
{
    if (PyLong_Check(qpyobject) == 1) {
        return QMetaType(QPy::Type::Int);
    } else if (PyFloat_Check(qpyobject) == 1) {
        return QMetaType(QPy::Type::Float);
    } else if (PyComplex_Check(qpyobject) == 1) {
        return QMetaType(QPy::Type::Complex);
    } else if (PyByteArray_Check(qpyobject) == 1) {
        return QMetaType(QPy::Type::ByteArray);
    } else if (PyUnicode_Check(qpyobject) == 1) {
        return QMetaType(QPy::Type::Unicode);
    } else if (PyTuple_Check(qpyobject) == 1) {
        return QMetaType(QPy::Type::Tuple);
    }
    return QMetaType(QPy::Type::Object);
}
QDebug operator<<(QDebug dbg, const QPyObject& value)
{
    QPyAbstractObject* nptr = value;
    QMetaType metatype = value.metaType();
    if (metatype.isValid() == true)
        metatype.debugStream(dbg, reinterpret_cast<const void*>(&value));
    else
        dbg.nospace() << "QPyObject(" << nptr << ")";
    return dbg;
}
QPyObject::QPyObject(PyObject* pyobject)
{
    m_qpyobject = static_cast<QPyAbstractObject*>(pyobject);
}
QPyObject::QPyObject(PyTypeObject* pytypeobject)
{
    PyObject* pyobject = reinterpret_cast<PyObject*>(pytypeobject);
    m_qpyobject = static_cast<QPyAbstractObject*>(pyobject);
}
QPyObject::QPyObject(PyModuleDef* pymodule)
{
    m_qpyobject = static_cast<QPyAbstractObject*>(PyState_FindModule(pymodule));
}
QMetaType QPyObject::metaType()
{
    return fromQPyAbstractObject(m_qpyobject);
}
QMetaType QPyObject::metaType() const
{
    return fromQPyAbstractObject(m_qpyobject);
}
void QPyObject::setObject(PyObject* pyobject)
{
    m_qpyobject = static_cast<QPyAbstractObject*>(pyobject);
}
QPyAbstractObject* QPyObject::object()
{
    return m_qpyobject;
}
QPyAbstractObject* QPyObject::object() const
{
    return m_qpyobject;
}
QPyObject::operator QPyAbstractObject* ()
{
    return m_qpyobject;
}
QPyObject::operator QPyAbstractObject* () const
{
    return m_qpyobject;
}
QPyObject::operator QPyAbstractTypeObject* ()
{
    return static_cast<QPyAbstractTypeObject*>(Py_TYPE(m_qpyobject));
}
QPyObject::operator QPyAbstractTypeObject* () const
{
    return static_cast<QPyAbstractTypeObject*>(Py_TYPE(m_qpyobject));
}
QPyObject::operator QVariant()
{
    QMetaType metatype = fromQPyAbstractObject(m_qpyobject);
    return QVariant(metatype, reinterpret_cast<const void*>(this));
}
QPyObject::operator QVariant() const
{
    QMetaType metatype = fromQPyAbstractObject(m_qpyobject);
    return QVariant(metatype, reinterpret_cast<const void*>(this));
}