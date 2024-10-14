#include "qpybuildobject.h"
import qpytype.qpytuple;
//-------------------------------------------------------------------
static int  __qpinit__(PyObject* self, PyObject* args, PyObject* kwd)
{
    Q_UNUSED(kwd)
    QPyObject qpyself = self; 
    QPyTuple  qpyargs = args;

    if (qpyargs.size() > 0) {    
        static_cast<QPyAbstractObject*>(qpyself)->ob_qobject = static_cast<QPyAbstractTypeObject*>(qpyself)->tp_qmetaobject->newInstance(Q_ARG(QPyObject, qpyself), Q_ARG(QPyTuple, qpyargs));
        //qpyself->m_qerrors = qpytypeobject->m_qerrors;
        //qpyself->m_qcontext = new QPyContext(qpyself->m_qobject);
    } else if (qpyargs.size() == 0) {
        static_cast<QPyAbstractObject*>(qpyself)->ob_qobject = static_cast<QPyAbstractTypeObject*>(qpyself)->tp_qmetaobject->newInstance(Q_ARG(QPyObject, qpyself));
        //qpyself->m_qerrors = qpytypeobject->m_qerrors;
        //qpyself->m_qcontext = new QPyContext(qpyself->m_qobject);
    }
    qDebug() << "_init_";
    return 1;

}
static PyObject* __qpalloc__(PyTypeObject* type, Py_ssize_t size)
{
    QPyObject qpyobject = reinterpret_cast<QPyAbstractObject*>(malloc(size));
    QPyObject qpytypeobject = type;
    static_cast<QPyAbstractObject*>(qpyobject)->ob_qmodule = static_cast<QPyAbstractTypeObject*>(qpytypeobject)->tp_qmodule;
    qDebug() << "_alloc_";
    return PyObject_Init(qpyobject, qpytypeobject);
}
static PyObject* __qpnew__(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
    Q_UNUSED(args)
    Q_UNUSED(kwds)
    qDebug() << "_new_";
    return type->tp_alloc(type, sizeof(QPyAbstractObject));
}
static void  __qpdealloc__(PyObject* self)
{
    QPyAbstractObject* qpyobj = static_cast<QPyAbstractObject*>(self);
    QObject* qobject = qpyobj->ob_qobject;
   
    if (qobject != nullptr) {
        delete qobject;
        qobject = nullptr;
    }
    qDebug() << "_dealloc_";
    Py_TYPE(self)->tp_free(self);

}
static void  __qpfree__(void* self)
{
    QPyAbstractObject* obj =  reinterpret_cast<QPyAbstractObject*>(self);
    free(obj);
    qDebug() << "_free_";
    self = nullptr;
}
//----------------------------------------------------------------------------------------
struct PyObjectMethods {
    QList<QPair<QMetaMethod*, TStdMethod>> m_stdmethods;
    QList<QPair<QMetaProperty*, QPair<TSetMethod, TGetMethod>>> m_getsetmethods;
    PyNumberMethods* m_numbermethods = nullptr;
    TStrMethod m_strmethod = nullptr;
};
static PyObject* __qpymethodstd__(PyObject* self, PyObject* args, int n)
{

    QPyObject qpyself = self;
    QPyTuple qpyargs = args;
    QPyObject qpyresult = Py_None;
    QMetaMethod method = static_cast<QPyAbstractObject*>(qpyself)->ob_qobject->metaObject()->method(n);
    if (method.access() == QMetaMethod::Public && (method.methodType() == QMetaMethod::Method || method.methodType() == QMetaMethod::Slot)) {
        if (method.returnType() == QPy::Type::Void) {
            if (method.parameterCount() == 0) {
                method.invoke(static_cast<QPyAbstractObject*>(qpyself)->ob_qobject, Qt::DirectConnection);
            }
            else if (method.parameterCount() == 1) {
                 if (method.parameterType(0) == QPy::Type::Tuple) {
                    method.invoke(static_cast<QPyAbstractObject*>(qpyself)->ob_qobject, Qt::DirectConnection, Q_ARG(QPyTuple, qpyargs));
                 }
            }
        }
        else if (method.returnType() == QPy::Type::Object) {
             if (method.parameterCount() == 0) {
                 method.invoke(static_cast<QPyAbstractObject*>(qpyself)->ob_qobject, Qt::DirectConnection, Q_RETURN_ARG(QPyObject, qpyresult));
             }
             else if (method.parameterCount() == 1){
                  if (method.parameterType(0) == QPy::Type::Tuple) {
                      method.invoke(static_cast<QPyAbstractObject*>(qpyself)->ob_object, Qt::DirectConnection, Q_RETURN_ARG(QPyObject, qpyresult), Q_ARG(QPyTuple, qpyargs));
                  }
             }
        }
    }
    return qpyresult;
}
static PyObject* __qpynumbermethod__(PyObject* obj1, PyObject* obj2, int n)
{
    QPyObject* qpyobj1 = static_cast<QPyObject*>(obj1);
    QPyObject* qpyobj2 = static_cast<QPyObject*>(obj2);


    QPyValue qpyresult = Py_None;
    QMetaMethod* method = new QMetaMethod(qpyobj1->m_qobject->metaObject()->method(n));
    if (method->access() == QMetaMethod::Public && (method->methodType() == QMetaMethod::Method || method->methodType() == QMetaMethod::Slot))
    {
        if (method->returnType() == PyType::QPyValueDef)
        {
            if (method->parameterCount() == 1)
            {
                if (method->parameterType(0) == PyType::QPyValueDef)
                {
                    method->invoke(qpyobj1->m_qobject, Qt::DirectConnection, Q_RETURN_ARG(QPyValue, qpyresult), Q_ARG(QPyValue, QPyValue(qpyobj2)));
                }
            }
        }
    }
    return qpyresult;
}
static PyObject* __qpystrmethod__(PyObject* self, int n)
{
    QPyValue qpyres = Py_None;
    QPyObject* qpyself = static_cast<QPyObject*>(self);
    QMetaMethod* method = new QMetaMethod(qpyself->m_qobject->metaObject()->method(n));
    method->invoke(qpyself->m_qobject, Qt::DirectConnection, Q_RETURN_ARG(QPyValue, qpyres));
    return qpyres;
}
static PyObject* __qpgetmethod__(PyObject* self, void* closure, int n)
{
    Q_UNUSED(closure)
        QPyObject* qpyself = static_cast<QPyObject*>(self);
    QMetaProperty property = qpyself->m_qobject->metaObject()->property(n);
    return qvariant_cast<QPyValue>(property.read(qpyself->m_qobject));
}
static int  __qpsetmethod__(PyObject* self, PyObject* value, void* closure, int n)
{
    Q_UNUSED(closure)
        QPyObject* qpyself = static_cast<QPyObject*>(self);
    QPyValue qpyvalue = value;
    QMetaProperty property = qpyself->m_qobject->metaObject()->property(n);
    return property.write(qpyself->m_qobject, QVariant::fromValue(qpyvalue)) - 1;
}
template<int n>
class qpyobjectfactorymethods {
private:
    static PyObject* __qpymethodstdprivate__(PyObject* self, PyObject* args)
    {
        return __qpymethodstd__(self, args, n - 1);
    }
    static PyObject* __qpynumbermethodprivate__(PyObject* obj1, PyObject* obj2)
    {
        return __qpynumbermethod__(obj1, obj2, n - 1);
    }
    static int  __qpsetmethodprivate__(PyObject* self, PyObject* value, void* closure)
    {
        return __qpsetmethod__(self, value, closure, n - 1);
    }
    static PyObject* __qpgetmethodprivate__(PyObject* self, void* closure)
    {
        return __qpgetmethod__(self, closure, n - 1);
    }
    static PyObject* __qpystrmethodprivate__(PyObject* self)
    {
        return __qpystrmethod__(self, n - 1);
    }
public:
    qpyobjectfactorymethods(const QMetaObject* metaobject, PyObjectMethods* methods)
    {
        qpyobjectfactorymethods<n - 1>(metaobject, methods);
        if (n <= metaobject->methodCount())
        {
            QMetaMethod* method = new QMetaMethod(metaobject->method(n - 1));

            if (method->access() == QMetaMethod::Public && (method->methodType() == QMetaMethod::Method || method->methodType() == QMetaMethod::Slot))
            {
                if (qstrcmp(method->tag(), "StdMethod") == 0)
                {
                    methods->m_stdmethods << QPair<QMetaMethod*, TStdMethod>(method, __qpymethodstdprivate__);
                }
                else if (qstrcmp(method->tag(), "NumberMethod_Add") == 0)
                {
                    methods->m_numbermethods->nb_add = __qpynumbermethodprivate__;
                }
                else if (qstrcmp(method->tag(), "NumberMethod_Substract") == 0)
                {
                    methods->m_numbermethods->nb_subtract = __qpynumbermethodprivate__;
                }
                else if (qstrcmp(method->tag(), "NumberMethod_Multiply") == 0)
                {
                    methods->m_numbermethods->nb_multiply = __qpynumbermethodprivate__;
                }
                else if (qstrcmp(method->tag(), "NumberMethod_Divide") == 0)
                {
                    methods->m_numbermethods->nb_true_divide = __qpynumbermethodprivate__;
                }
                else if (qstrcmp(method->tag(), "NumberMethod_Remainder") == 0)
                {
                    methods->m_numbermethods->nb_remainder = __qpynumbermethodprivate__;
                }
                else if (qstrcmp(method->tag(), "NumberMethod_InplaceAdd") == 0)
                {
                    methods->m_numbermethods->nb_inplace_add = __qpynumbermethodprivate__;
                }
                else if (qstrcmp(method->tag(), "NumberMethod_InplaceSubstract") == 0)
                {
                    methods->m_numbermethods->nb_inplace_subtract = __qpynumbermethodprivate__;
                }
                else if (qstrcmp(method->tag(), "NumberMethod_InplaceMultiply") == 0)
                {
                    methods->m_numbermethods->nb_inplace_multiply = __qpynumbermethodprivate__;
                }
                else if (qstrcmp(method->tag(), "NumberMethod_InplaceDivide") == 0)
                {
                    methods->m_numbermethods->nb_inplace_true_divide = __qpynumbermethodprivate__;
                }
                else if (qstrcmp(method->tag(), "NumberMethod_InplaceRemainder") == 0)
                {
                    methods->m_numbermethods->nb_inplace_remainder = __qpynumbermethodprivate__;
                }
                else if (qstrcmp(method->tag(), "StrMethod") == 0)
                {
                    methods->m_strmethod = __qpystrmethodprivate__;
                }
                else if (method->methodType() == QMetaMethod::Slot)
                {
                    if (method->parameterCount() == 0 && method->returnType() == PyType::CVoid)
                    {
                        methods->m_stdmethods << QPair<QMetaMethod*, TStdMethod>(method, __qpymethodstdprivate__);
                    }
                    else if (method->parameterCount() == 1 && method->returnType() == PyType::QPyValueDef)
                    {
                        if (method->parameterType(0) == PyType::QPyValueTupleDef)
                        {
                            methods->m_stdmethods << QPair<QMetaMethod*, TStdMethod>(method, __qpymethodstdprivate__);
                        }
                    }
                }

            }
        }
        if (n > metaobject->propertyOffset() && n <= metaobject->propertyCount())
        {

            QMetaProperty* property = new QMetaProperty(metaobject->property(n - 1));
            if (property->typeId() == PyType::QPyValueDef)
                methods->m_getsetmethods << QPair<QMetaProperty*, QPair<TSetMethod, TGetMethod>>(property, QPair<TSetMethod, TGetMethod>(__qpsetmethodprivate__, __qpgetmethodprivate__));
        }
    }
};
template<>
class qpyobjectfactorymethods<0> {
public:
    qpyobjectfactorymethods(const QMetaObject* metaobject, PyObjectMethods* methods)
    {
        Q_UNUSED(metaobject)
            Q_UNUSED(methods)
    }
};




//----------------------------------------------------------------------------------------
QPyBuildObject::QPyBuildObject(const QMetaObject* qmetaobject, const QMetaObject* qmetamodule,QObject *parent) : QObject(parent)
{
    m_qmetaobject = qmetaobject;
    m_qpytypeobject.tp_name = QByteArray(qmetamodule->className()) + "." + QByteArray(m_qmetaobject->className());
    m_qpytypeobject.tp_doc = QByteArray();
    m_qpytypeobject.tp_qmetaobject = qmetaobject;
    m_qpytypeobject.tp_new = __qpnew__;
    m_qpytypeobject.tp_alloc = __qpalloc__;
    m_qpytypeobject.tp_init = (initproc)(__qpinit__);
    m_qpytypeobject.tp_free = __qpfree__;
    m_qpytypeobject.tp_dealloc = (destructor)(__qpdealloc__);

}
QPyBuildObject::~QPyBuildObject()
{}
