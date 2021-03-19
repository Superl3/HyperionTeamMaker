#pragma once

#include <QDialog>
#include <QMap>
#include <QString>

#include "Team.h"

class Member;
class QListWidget;
class QComboBox;
class QTimer;
class QLineEdit;

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
	void initUI();

	void start();

	QMap<QString, Member*> totalMembers;
	QMap<QString, Member*> gameMembers;

	QListWidget *totalMemberList = nullptr;
	QListWidget *gameMemberList = nullptr;

	QLineEdit *searchEdit = nullptr;

	QComboBox *roundComboBox = nullptr;
	QTimer *searchTimer = nullptr;

	Team A, B;
};