
module;
#include <qcpyengine/qpytypedefs.h>
module qpytype.qpybytearray;

namespace QPy 
{
    namespace Type
    {
        const int ByteArray = qRegisterMetaType<QPyByteArray>();
    }
}

QDebug operator<<(QDebug dbg, const QPyByteArray& value)
{
    QByteArray n = value;
    QPyAbstractObject* nptr = value;
    dbg.nospace() << "QPyByteArray(" << n << "," << nptr << ")";
    return dbg;
}
QDataStream& operator>>(QDataStream& stream, QPyByteArray& value)
{
    QByteArray n;
    stream >> n;
    value = n;
    return stream;
}
QDataStream& operator<<(QDataStream& stream, const QPyByteArray& value)
{
    QByteArray n = value;
    stream << n;
    return stream;
}
QPyByteArray::QPyByteArray(const QByteArray& value) :QPyObject()
{
    setObject(PyByteArray_FromStringAndSize(value, value.size()));
}
QPyByteArray::QPyByteArray(PyObject* value) :QPyObject()
{
    Q_ASSERT_X(PyByteArray_Check(value) == 1, "QPyByteArray", "not type");
    setObject(value);
}
QPyByteArray& QPyByteArray::operator=(const QByteArray& value)
{
    if (object() != nullptr)
        Py_DecRef(object());
    setObject(PyByteArray_FromStringAndSize(value, value.size()));
    return *this;
}
QPyByteArray& QPyByteArray::operator=(PyObject* value)
{
    Q_ASSERT_X(PyByteArray_Check(value) == 1, "QPyByteArray", "not type");
    if (object() != nullptr)
        Py_DecRef(object());
    setObject(value);
    return *this;
}
QPyByteArray::operator QByteArray()
{
    return PyByteArray_AsString(object());
}
QPyByteArray::operator QByteArray() const
{
    return PyByteArray_AsString(object());
}