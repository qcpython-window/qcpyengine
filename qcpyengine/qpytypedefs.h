

#ifndef Q_MOC_RUN
#define InitMethod
#define StdMethod
#define RichCompare
#define NumberMethod_Add
#define NumberMethod_Substract
#define NumberMethod_Multiply
#define NumberMethod_Divide
#define NumberMethod_Remainder
#define NumberMethod_InplaceAdd
#define NumberMethod_InplaceSubstract
#define NumberMethod_InplaceMultiply
#define NumberMethod_InplaceDivide
#define NumberMethod_InplaceRemainder
#define SequenceMethod_GetItem
#define SequenceMethod_SetItem
#define SequenceMethod_GetSlice
#define SequenceMethod_SetSlice
#define SequenceMethod_Size
#define SequenceMethod_Concat
#define SequenceMethod_InplaceConcat
#define StrMethod
#endif

#define QP_INITCALL  Q_INVOKABLE
#define QP_STDCALL StdMethod Q_INVOKABLE
#define QP_RICHCOMPARECALL RichCompare Q_INVOKABLE
#define QP_NUM_ADDCALL NumberMethod_Add Q_INVOKABLE
#define QP_NUM_SUBSTRACTCALL NumberMethod_Substract Q_INVOKABLE
#define QP_NUM_MULTIPLYCALL NumberMethod_Multiply Q_INVOKABLE
#define QP_NUM_DIVIDECALL NumberMethod_Divide Q_INVOKABLE
#define QP_NUM_REMAINDERCALL  NumberMethod_Remainder Q_INVOKABLE
#define QP_NUM_INPLACEADDCALL NumberMethod_InplaceAdd Q_INVOKABLE
#define QP_NUM_INPLACESUBSTRACTCALL NumberMethod_InplaceSubstract Q_INVOKABLE
#define QP_NUM_INPLACEMULTIPLYCALL NumberMethod_InplaceMultiply Q_INVOKABLE
#define QP_NUM_INPLACEDIVIDECALL NumberMethod_InplaceDivide Q_INVOKABLE
#define QP_NUM_INPLACEREMAINDERCALL  NumberMethod_InpalceRemainder Q_INVOKABLE
#define QP_SEQ_GETITEMCALL SequenceMethod_GetItem Q_INVOKABLE
#define QP_SEQ_SETITEMCALL  SequenceMethod_SetItem Q_INVOKABLE
#define QP_SEQ_GETSLICECALL SequenceMethod_GetSlice Q_INVOKABLE
#define QP_SEQ_SETSLICECALL  SequenceMethod_SetSlice  Q_INVOKABLE
#define QP_SEQ_SIZECALL SequenceMethod_Size Q_INVOKABLE
#define QP_SEQ_CONCATCALL SequenceMethod_Concat  Q_INVOKABLE
#define QP_SEQ_INPLACECONCATCALL SequenceMethod_InplaceConcat Q_INVOKABLE
#define QP_STRCALL StrMethod Q_INVOKABLE
//-------------------------------------------------------------------------------------------------------------------------------

#include <QObject>
#include <QMetaObject>
#include <QMetaMethod>
#include <QMetaProperty>
#include <QMetaType>
#include <QVariant>
#include <QDataStream>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
//--------------------------------------------------------------------------------
#include <qcpyengine/cpython/Python.h>
#include <qcpyengine/cpython/structmember.h>
#include <qcpyengine/cpython/compile.h>
#include <qcpyengine/cpython/ceval.h>
#include <qcpyengine/cpython/pytypedefs.h>
#include <qcpyengine/cpython/frameobject.h>
#include <qcpyengine/cpython/traceback.h>
//---------------------------------------------------------------------------------
#include <complex>
#include <numbers>
//---------------------------------------------------------------------------------

//-------------------------------------------------------------
#define object_method    0xAA
#define object_property  0xAB
#define stderr_run       0xBA
#define stderr_comp      0xBB
#define meth_noargs      METH_NOARGS
#define meth_args        METH_VARARGS
#define meth_static      METH_STATIC
//-------------------------------------------------------------------------
#define op_lt Py_LT  //<
#define op_le Py_LE  //<=
#define op_eq Py_EQ  //==
#define op_ne Py_NE  //!=
#define op_gt Py_GT  //>
#define op_ge Py_GE  //>=
//-----------------------------------------------------------------------
using TNewMethod=PyObject *(*)(PyTypeObject *, PyObject *, PyObject *);
using TAllocMethod=PyObject* (*)(PyTypeObject *,Py_ssize_t);
using TFreeMethod=void (*)(void *);
using TDeallocMethod=void (*)(PyObject*);
using TInitMethod=int (*)(PyObject *,PyObject *, PyObject *);
using TStdMethod=PyObject *(*)(PyObject *, PyObject *);
using TSequenceGetItemMethod=PyObject* (*)(PyObject *,Py_ssize_t);
using TSequenceSetItemMethod=int (*)(PyObject *,Py_ssize_t,PyObject *);
using TSequenceGetSliceMethod=PyObject*(*)(PyObject*,Py_ssize_t ,Py_ssize_t );
using TSequenceSetSliceMethod=int(*)(PyObject*,Py_ssize_t ,Py_ssize_t ,PyObject *);
using TSequenceSizeMethod=Py_ssize_t (*)(PyObject *);
using TRichCompareMethod=PyObject *(*)(PyObject *, PyObject *, int op);
using TStrMethod=PyObject* (*)(PyObject*);
using TCallMethod=PyObject *(*)(PyObject *, PyObject *, PyObject *);
using TGetMethod=PyObject*(*)(PyObject*,void*);
using TSetMethod=int(*)(PyObject*,PyObject*,void*);
using TRegisterInitMethod=PyObject*(*)();
//-----------------------------------------------------------------------------------------------------------------------------

using qcomplex=std::complex<double>;



struct QPyAbstractObject:PyObject{ 
    PyObject_HEAD
    QObject *ob_qobject=nullptr;
    QObject *ob_qmodule=nullptr;
    QObject *ob_qerrors=nullptr;
    QObject *ob_qcontext=nullptr;
};
struct QPyAbstractTypeObject :PyTypeObject {
    PyObject_VAR_HEAD
    const QMetaObject* tp_qmetaobject = nullptr;
    QObject* tp_qmodule = nullptr;
    QObject* tp_qerrors = nullptr;
};

struct QPyAbstractModule:PyModuleDef{
    QObject *m_qmodule=nullptr;
    QObject *m_qcontext=nullptr;
};



