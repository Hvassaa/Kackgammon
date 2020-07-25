#include "IdPushButton.h"
#include <iostream>

IdPushButton::IdPushButton(const QString &text, int newId) : QPushButton(text)
{
	id = newId;
	QObject::connect(this, SIGNAL(released()), this, SLOT(emitIdProxy()));
}

void IdPushButton::emitIdProxy() 
{
	emit emitId(id);
}
