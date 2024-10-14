module;
#include <qcpyengine/qpytypedefs.h>
module qpytype.qpytuple;

namespace QPy
{
    namespace Type
    {
        const int Tuple = qRegisterMetaType<QPyTuple>();
    }
}

QDebug operator<<(QDebug dbg, const QPyTuple& tuple)
{
    QPyAbstractObject* nptr = tuple;
    int size = tuple.size();
    dbg.nospace() << "QPyTuple({";
    for (int i = 0; i < size; i++) {
        if (i < size - 1)
            dbg.nospace() << tuple[i] << ",";
        else if (i == size - 1)
            dbg.nospace() << tuple[i];
    }
    dbg.nospace() << "}," << nptr << ")";
    return dbg;
}
QPyTuple::QPyTuple(const std::initializer_list<QPyObject>& values) :QPyObject()
{
    setObject(PyTuple_New(values.size()));
    int step = 0;
    for (const QPyObject& value : values) {

        PyTuple_SetItem(object(), step, value);
        step++;
    }
}
QPyTuple::QPyTuple(PyObject* values) :QPyObject()
{
    Q_ASSERT_X(PyTuple_Check(object()) == 1, "QPyTuple", "not type");
    setObject(values);

}
int QPyTuple::size()
{
    return PyTuple_Size(object());
}
int QPyTuple::size() const
{
    return PyTuple_Size(object());
}
QPyObject QPyTuple::operator[](int i)
{
    Q_ASSERT_X(PyTuple_Size(object()) > i, "QPyTuple", "out range");
    return PyTuple_GetItem(object(), i);
}
QPyObject QPyTuple::operator[](int i) const
{
    Q_ASSERT_X(PyTuple_Size(object()) > i, "QPyTuple", "out range");
    return PyTuple_GetItem(object(), i);
}