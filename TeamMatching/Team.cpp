#include "Team.h"

QList<Member*> Team::getMembers()
{
	QList<Member*> team;
	team.append(Dealers);
	team.append(Tankers);
	team.append(Supporters);
	return team;
}
