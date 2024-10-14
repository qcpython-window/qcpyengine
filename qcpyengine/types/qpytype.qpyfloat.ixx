module;
#include <qcpyengine/qpytypedefs.h>
export module qpytype.qpyfloat;
import qpytype.qpyobject;



export class QPyFloat : public QPyObject
{
    friend QDebug operator<<(QDebug dbg, const QPyFloat& value);
    friend QDataStream& operator>>(QDataStream& stream, QPyFloat& value);
    friend QDataStream& operator<<(QDataStream& stream, const QPyFloat& value);
public:
    QPyFloat() = default;
    QPyFloat(double value);
    QPyFloat(PyObject* value);
    QPyFloat& operator=(double value);
    QPyFloat& operator=(PyObject* value);
    operator double();
    operator double() const;

};

