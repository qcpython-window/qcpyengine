module;
#include <qcpyengine/qpytypedefs.h>
module qpytype.qpyunicode;
namespace QPy
{
    namespace Type
    {
        const int Unicode = qRegisterMetaType<QPyUnicode>();
    }
}

QDebug operator<<(QDebug dbg, const QPyUnicode& value)
{
    QString n = value;
    QPyAbstractObject* nptr = value;
    dbg.nospace() << "QPyUnicode(" << n << "," << nptr << ")";
    return dbg;
}
QDataStream& operator>>(QDataStream& stream, QPyUnicode& value)
{
    QString n;
    stream >> n;
    value = n;
    return stream;
}
QDataStream& operator<<(QDataStream& stream, const QPyUnicode& value)
{
    QString n = value;
    stream << n;
    return stream;
}
QPyUnicode::QPyUnicode(const QString& value):QPyObject()
{
    setObject(PyUnicode_FromString(value.toUtf8()));
}
QPyUnicode::QPyUnicode(PyObject* value)
{
    Q_ASSERT_X(PyUnicode_Check(value) == 1, "QPyUnicode", "not type");
    setObject(value);
}
QPyUnicode& QPyUnicode::operator=(const QString& value)
{
    if (object() != nullptr)
        Py_DecRef(object());
    setObject(PyUnicode_FromString(value.toUtf8()));
    return *this;

}
QPyUnicode& QPyUnicode::operator=(PyObject* value)
{
    Q_ASSERT_X(PyUnicode_Check(value) == 1, "QPyUnicode", "not type");
    if (object() != nullptr)
        Py_DecRef(object());
    setObject(value);
    return *this;
}
QPyUnicode::operator QString()
{
    return PyUnicode_AsUTF8(object());
}
QPyUnicode::operator QString() const
{
    return PyUnicode_AsUTF8(object());
}
