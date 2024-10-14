module;
#include <qcpyengine/qpytypedefs.h>
export module qpytype.qpyunicode;
import qpytype.qpyobject;


export class QPyUnicode : public QPyObject
{
    friend QDebug operator<<(QDebug dbg, const QPyUnicode& value);
    friend QDataStream& operator>>(QDataStream& stream, QPyUnicode& value);
    friend QDataStream& operator<<(QDataStream& stream, const QPyUnicode& value);
public:
    QPyUnicode() = default;
    QPyUnicode(const QString& value);
    QPyUnicode(PyObject* value);
    QPyUnicode& operator=(const QString& value);
    QPyUnicode& operator=(PyObject* value);
    operator QString();
    operator QString() const;
};
