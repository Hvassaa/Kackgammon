#include <QPushButton>

class IdPushButton : public QPushButton
{
	Q_OBJECT

	private:
		int id;
	public:
		IdPushButton(const QString &text, int newId);
	private slots:
		void emitIdProxy();
	signals:
		void emitId(int id);	
};
