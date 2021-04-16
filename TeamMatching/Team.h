#pragma once

#include "Member.h"
#include <QList>


class Team {
public:
	Team() {}
	~Team() {}

	void setPosition(QList<Member*> Players, Position::Types type);
	QList<Member*> getPosition(Position::Types type);
	QList<Member*> getMembers();
	int getRanks();

	QList<Member*> Tankers;
	QList<Member*> Dealers;
	QList<Member*> Supporters;

	QString getTeam();
};
