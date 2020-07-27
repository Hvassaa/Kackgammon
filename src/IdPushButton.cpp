#include "IdPushButton.h"

IdPushButton::IdPushButton(const QString &text, int newId, QWidget *parent) : QPushButton(text, parent)
{
	id = newId;
	QObject::connect(this, SIGNAL(released()), this, SLOT(emitIdProxy()));
}

void IdPushButton::emitIdProxy() 
{
	emit emitId(id);
}
