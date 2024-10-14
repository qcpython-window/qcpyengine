module;
#include <qcpyengine/qpytypedefs.h>
module qpytype.qpyfloat;

namespace QPy
{
    namespace Type
    {
        const int Float = qRegisterMetaType<QPyFloat>();
    }
}

QDebug operator<<(QDebug dbg, const QPyFloat& value)
{
    double n = value;
    QPyAbstractObject* nptr = value;
    dbg.nospace() << "QPyFloat(" << n << "," << nptr << ")";
    return dbg;
}
QDataStream& operator>>(QDataStream& stream, QPyFloat& value)
{
    double n;
    stream >> n;
    value = n;
    return stream;
}
QDataStream& operator<<(QDataStream& stream, const QPyFloat& value)
{
    double n = value;
    stream << n;
    return stream;
}
QPyFloat::QPyFloat(double value) :QPyObject()
{
    setObject(PyFloat_FromDouble(value));
}
QPyFloat::QPyFloat(PyObject* value) :QPyObject()
{
    Q_ASSERT_X(PyFloat_Check(value) == 1, "PyFloat", "no types");
    setObject(value);
}
QPyFloat& QPyFloat::operator=(double value)
{
    if (object() != nullptr)
        Py_DecRef(object());
    setObject(PyFloat_FromDouble(value));
    return *this;
}
QPyFloat& QPyFloat::operator=(PyObject* value)
{
    Q_ASSERT_X(PyFloat_Check(value) == 1, "PyFloat", "no types");
    if (object() != nullptr)
        Py_DecRef(object());
    setObject(value);
    return *this;
}
QPyFloat::operator double()
{
    return PyFloat_AsDouble(object());
}
QPyFloat::operator double() const
{
    return PyFloat_AsDouble(object());
}
