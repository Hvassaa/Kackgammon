#ifndef ID_PUSH_BUTTON
#define ID_PUSH_BUTTON

#include <QPushButton>

class IdPushButton : public QPushButton
{
	Q_OBJECT

	private:
		int id;
	public:
		IdPushButton(const QString &text, int newId, QWidget *parent = nullptr);
	private slots:
		void emitIdProxy();
	signals:
		void emitId(int id);	
};

#endif
