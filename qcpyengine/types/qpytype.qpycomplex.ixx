module;
#include <qcpyengine/qpytypedefs.h>
export module qpytype.qpycomplex;
import qpytype.qpyobject;

export class QPyComplex : public QPyObject
{
    friend QDebug operator<<(QDebug dbg, const QPyComplex& value);
    friend QDataStream& operator>>(QDataStream& stream, QPyComplex& value);
    friend QDataStream& operator<<(QDataStream& stream, const QPyComplex& value);
public:
    QPyComplex() = default;
    QPyComplex(double real, double imag);
    QPyComplex(const qcomplex& value);
    QPyComplex(PyObject* value);
    QPyComplex& operator=(const qcomplex& value);
    QPyComplex& operator=(PyObject* value);
    operator qcomplex();
    operator qcomplex() const;
};

