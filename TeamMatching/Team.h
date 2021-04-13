#pragma once

#include "Member.h"
#include <QList>


class Team {
public:
	Team() {}
	~Team() {}

	void setPosition(QList<Member*> Players, Position::Types type) {
		switch (type) {
		case Position::TANKER:
			Tankers = Players;
			break;
		case Position::DEALER:
			Dealers = Players;
			break;
		case Position::SUPPORTER:
			Supporters = Players;
			break;
		default:
			assert(false);
		}
	}
	QList<Member*> getMembers();
	int getRanks();

	QList<Member*> Tankers;
	QList<Member*> Dealers;
	QList<Member*> Supporters;
};
