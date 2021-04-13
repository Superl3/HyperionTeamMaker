#include "Team.h"

QList<Member*> Team::getMembers()
{
	QList<Member*> team;
	team.append(Dealers);
	team.append(Tankers);
	team.append(Supporters);
	return team;
}

int Team::getRanks()
{
	int sum = 0;
	for (const auto player : Tankers)
		sum += player->getTankRank();
	for (const auto player : Dealers)
		sum += player->getDamageRank();
	for (const auto player : Supporters)
		sum += player->getSupportRank();
	return sum;
}
