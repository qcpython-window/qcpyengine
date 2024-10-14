module;
#include <qcpyengine/qpytypedefs.h>
module qpytype.qpycomplex;

namespace QPy
{
    namespace Type
    {
        const int Complex = qRegisterMetaType<QPyComplex>();
    }
}

QDebug operator<<(QDebug dbg, const QPyComplex& value)
{
    qcomplex n = value;
    QPyAbstractObject* nptr = value;
    dbg.nospace() << "QPyComplex(" << "[" << n.real() << "," << n.imag() << "]" << "," << nptr << ")";
    return dbg;
}
QDataStream& operator>>(QDataStream& stream, QPyComplex& value)
{
    double nr = 0.0;
    double ni = 0.0;
    stream >> nr >> ni;
    value = qcomplex(nr, ni);
    return stream;
    
}
QDataStream& operator<<(QDataStream& stream, const QPyComplex& value)
{
    qcomplex n = value;
    stream << n.real() << n.imag();
    return stream;
}
QPyComplex::QPyComplex(double real, double imag) :QPyObject()
{
    Py_complex  cpx{ real,imag};
    setObject(PyComplex_FromCComplex(cpx));
}
QPyComplex::QPyComplex(const qcomplex& value) :QPyObject()
{
    Py_complex  cpx{ value.real(),value.imag() };
    setObject(PyComplex_FromCComplex(cpx));
}

QPyComplex::QPyComplex(PyObject* value) :QPyObject()
{
    Q_ASSERT_X(PyComplex_Check(value) == 1, "QPyComplex", "not type");
    setObject(value);
}
QPyComplex& QPyComplex::operator=(const qcomplex& value)
{
    if (object() != nullptr)
        Py_DecRef(object());
    Py_complex  cpx{ value.real(),value.imag() };
    setObject(PyComplex_FromCComplex(cpx));
    return *this;

}
QPyComplex& QPyComplex::operator=(PyObject* value)
{
    Q_ASSERT_X(PyComplex_Check(value) == 1, "QPyComplex", "not type");
    if (object() != nullptr)
        Py_DecRef(object());
    setObject(value);
    return *this;
}
QPyComplex::operator qcomplex()
{
    Py_complex pycpx = PyComplex_AsCComplex(object());
    return qcomplex(pycpx.real, pycpx.imag);
}
QPyComplex::operator qcomplex() const
{
    Py_complex pycpx = PyComplex_AsCComplex(object());
    return qcomplex(pycpx.real, pycpx.imag);
}
