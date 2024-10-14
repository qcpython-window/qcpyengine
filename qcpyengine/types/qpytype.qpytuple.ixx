module;
#include <qcpyengine/qpytypedefs.h>
export module qpytype.qpytuple;
import qpytype.qpyobject;

export class QPyTuple : public QPyObject
{
    friend QDebug operator<<(QDebug dbg, const QPyTuple& tuple);
public:
    QPyTuple() = default;
    QPyTuple(const std::initializer_list<QPyObject>& values);
    QPyTuple(PyObject* values);
    int size();
    int size() const;
    QPyObject operator[](int i);
    QPyObject operator[](int i) const;

};

