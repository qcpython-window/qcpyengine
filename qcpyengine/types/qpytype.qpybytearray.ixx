module;
#include <qcpyengine/qpytypedefs.h>
export module qpytype.qpybytearray;
import qpytype.qpyobject;

export class QPyByteArray : public QPyObject
{
    friend QDebug operator<<(QDebug dbg, const QPyByteArray& value);
    friend QDataStream& operator>>(QDataStream& stream, QPyByteArray& value);
    friend QDataStream& operator<<(QDataStream& stream, const QPyByteArray& value);
public:
    QPyByteArray() = default;
    QPyByteArray(const QByteArray& value);
    QPyByteArray(PyObject* value);
    QPyByteArray& operator=(const QByteArray& value);
    QPyByteArray& operator=(PyObject* value);
    operator QByteArray();
    operator QByteArray() const;
};


