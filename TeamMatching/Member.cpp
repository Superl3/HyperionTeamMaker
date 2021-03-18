#include "Member.h"

Member::Member(QString _name, int dps, int tank, int support) : QListWidgetItem(""),
name(_name), Damage(Position(dps)), Tank(Position(tank)), Support(Position(support))
{
	setText();
};

void Member::changeData(QString _name, int dps, int tank, int support)
{
	name = _name;
	Damage.setRank(dps);
	Tank.setRank(tank);
	Support.setRank(support);
}

Member* Member::fromString(QString raw)
{
	auto splitedRaw = raw.split('\t');
	QString name = splitedRaw[0];
	int dealer = splitedRaw[1].toInt();
	int tanker = splitedRaw[2].toInt();
	int support = splitedRaw[3].toInt();

	return new Member(name, dealer, tanker, support);
}

QString Member::toString()
{
	return name + '\t' +
		QString::number(Damage.getRank()) + '\t' +
		QString::number(Tank.getRank()) + '\t' +
		QString::number(Support.getRank());
}

void Member::setText()
{
	QString syntax = name + QString::number(Damage.getRank()) + '/' +
		QString::number(Tank.getRank()) + '/' +
		QString::number(Support.getRank());

	QListWidgetItem::setText(syntax);
}
