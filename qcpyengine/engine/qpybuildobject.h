#pragma once
#include <qcpyengine/qpytypedefs.h>
import qpytype.qpyobject;

class QPyBuildObject  : public QObject
{
	Q_OBJECT
public:
	explicit QPyBuildObject(const QMetaObject* qmetaobject, const QMetaObject* qmetamodule,QObject *parent);
	~QPyBuildObject();
private:
	QPyAbstractTypeObject m_qpytypeobject = {
	   .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
	};
	QObject* m_factory = nullptr;
	const QMetaObject* m_qmetaobject = nullptr;
	QList<const QMetaObject*> m_propertys;
};
