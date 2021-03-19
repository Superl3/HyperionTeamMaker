#pragma once

#include "Member.h"
#include <QList>


class Team {
	Team() {}
	~Team() {}

	QList<Member*> getMembers();

	QList<Member*> Tankers;
	QList<Member*> Dealers;
	QList<Member*> Supporters;
};
