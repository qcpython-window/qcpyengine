module;
#include <qcpyengine/qpytypedefs.h>
export module qpytype.qpyint;
import qpytype.qpyobject;


export class QPyInt :public QPyObject
{
    friend QDebug operator<<(QDebug dbg, const QPyInt& value);
    friend QDataStream& operator>>(QDataStream& stream, QPyInt& value);
    friend QDataStream& operator<<(QDataStream& stream, const QPyInt& value);
public:
    QPyInt() = default;
    QPyInt(int value);
    QPyInt(PyObject* value);
    QPyInt& operator=(int value);
    QPyInt& operator=(PyObject* value);
    operator int();
    operator int() const;
};
