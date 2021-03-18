#pragma once

#include <QDialog>
#include <QMap>
#include <QString>

class Member;
class QListWidget;
class QComboBox;
class QTimer;

class CreateTeam : public QDialog {
	Q_OBJECT
public:
	CreateTeam();
	~CreateTeam();
	
public slots:
	void slotGoUp();
	void slotGoDown();
	void slotReset();

	void slotCreateTeam();
	void slotCancel();

	void slotTextChanged();

private:
	void load();
	void filter();

	QMap<QString, Member*> members;
	QListWidget *totalMemberList;
	QListWidget *gameMemberList;

	QComboBox *roundComboBox;
	QTimer *searchTimer;
};