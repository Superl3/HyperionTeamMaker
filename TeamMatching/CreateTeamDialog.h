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

class CreateTeamDialog : public QDialog {
	Q_OBJECT
public:
	CreateTeamDialog();
	~CreateTeamDialog();
	
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
	void createTwoTeam(QList<Member *> teamA, QList<Member *> teamB);
	void pickFromTeamA(QList<Member *> teamA, QList<Member *> teamB);
	void pickFromTeamB(QList<Member *> teamA, QList<Member *> teamB);
	void pickPositionFromBothTeam(QList<Member *> teamA, QList<Member *> teamB, Position::Types type);

	bool checkTeamBalance();
	bool checkPositionBalance(QList<Member *> teamAPlayers, QList<Member *> teamBPlayers, Position::Types type);
	bool doesTeamMakingDone(QList<Member *> teamA, QList<Member *> teamB, Position::Types type);
	bool checkTwoTeamsCreated(QList<Member *> teamA, QList<Member *> teamB);
};