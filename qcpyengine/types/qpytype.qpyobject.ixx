module;
#include <qcpyengine/qpytypedefs.h>
export module qpytype.qpyobject;


export namespace QPy
{
    namespace Type
    {
        extern const int Object;
        extern const int ObjectStar;
        extern const int TypeObjectStar;
        extern const int ModuleStar;
        extern const int QtObjectStar;
        extern const int Void;
        extern const int Int;
        extern const int Float;
        extern const int Complex;
        extern const int ByteArray;
        extern const int Unicode;
        extern const int Tuple;
    }
}

export class QPyObject {
    friend QDebug operator<<(QDebug dbg, const QPyObject& value);
 public:
    QPyObject() = default;
    QPyObject(PyObject* pyobject);
    QPyObject(PyTypeObject* pytypeobject);
    QPyObject(PyModuleDef* pymodule);
    QMetaType metaType();
    QMetaType metaType() const;
    operator QPyAbstractObject* ();
    operator QPyAbstractObject* () const;
    operator QPyAbstractTypeObject* ();
    operator QPyAbstractTypeObject* () const;
    operator QVariant();
    operator QVariant() const;
protected:
    void setObject(PyObject* pyobject);
    QPyAbstractObject* object();
    QPyAbstractObject* object() const;
private:
    QPyAbstractObject* m_qpyobject = nullptr;
};

