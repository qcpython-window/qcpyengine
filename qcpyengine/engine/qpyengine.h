#pragma once
#include <qcpyengine/engine/qpybuildobject.h>
import qpytype.qpyobject;

using QPyDirs = QList<QDir>;
class QPyEngine  : public QObject
{
	Q_OBJECT

public:
	static QPyEngine* global();
	~QPyEngine();
	void begin();
	void end();
	void addDir(const QDir& dir);
	QPyObject evaluate(const QString& code, const QString& filename);
public slots:
	void run(const QString& code);
protected:
	QPyObject eval(const QString& code, const QString& filename = QString());
	QPyObject exec(const QString& code, const QString& filename = QString());
private:
	QPyEngine(QObject* parent = nullptr);
	QPyObject m_globals;
	QPyObject m_sys;
	QPyObject m_sysdict;
	QPyDirs m_dirs;
	void configDirs();
};
