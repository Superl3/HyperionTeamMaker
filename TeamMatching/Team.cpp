#include "Team.h"

void Team::setPosition(QList<Member*> Players, Position::Types type)
{
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

QList<Member*> Team::getPosition(Position::Types type)
{
		QList<Member*> Players;
		switch (type) {
		case Position::TANKER:
			Players = Tankers;
			break;
		case Position::DEALER:
			Players = Dealers;
			break;
		case Position::SUPPORTER:
			Players = Supporters;
			break;
		default:
			assert(false);
		}
		return Players;
}

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

QString Team::getTeam()
{
	QString res = "";

	Position::Types type = Position::DEALER;
	while (type != Position::Default) {
		for (const auto &player : getPosition(type)) {
			res += player->getName() + " ";
		}
		type = Position::getNextType(type);
	}

	return res;
}
