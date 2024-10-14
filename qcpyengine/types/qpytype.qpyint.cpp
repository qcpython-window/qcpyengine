module;
#include <qcpyengine/qpytypedefs.h>
module qpytype.qpyint;

namespace QPy
{
    namespace Type
    {
        const int Int = qRegisterMetaType<QPyInt>();
    }
}

QDebug operator<<(QDebug dbg, const QPyInt& value)
{
    int n = value;
    QPyAbstractObject* nptr = value;
    dbg.nospace() << "QPyInt(" << n << "," << nptr << ")";
    return dbg;
}
QDataStream& operator>>(QDataStream& stream, QPyInt& value)
{
    int n;
    stream >> n;
    value = n;
    return stream;
}
QDataStream& operator<<(QDataStream& stream, const QPyInt& value)
{
    int n = value;
    stream << n;
    return stream;
}

QPyInt::QPyInt(int value) :QPyObject()
{
    setObject(PyLong_FromLong(value));
}
QPyInt::QPyInt(PyObject* value) :QPyObject()
{
    Q_ASSERT_X(PyLong_Check(value) == 1, "QPyInt", "not  types");
    setObject(value);
}
QPyInt& QPyInt::operator=(int value)
{
    if (object() != nullptr)
        Py_DecRef(object());
    setObject(PyLong_FromLong(value));
    return *this;
}
QPyInt& QPyInt::operator=(PyObject* value)
{
    Q_ASSERT_X(PyLong_Check(value) == 1, "QPyInt", "not  types");
    if (object() != nullptr)
        Py_DecRef(object());
    setObject(value);
    return *this;
}
QPyInt::operator int()
{
    return PyLong_AsLong(object());
}
QPyInt::operator int() const
{
    return PyLong_AsLong(object());
}
