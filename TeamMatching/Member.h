#pragma once

#include <QVector>
#include <QListWidgetItem>

class Position {
public:
	enum Types {
		TANKER = 0,
		DEALER,
		SUPPORTER,
		Default
	};
	static Types getNextType(Types type) {
		Types nextType;
		switch (type) {
		case Position::TANKER:
			nextType = SUPPORTER;
			break;
		case Position::DEALER:
			nextType = TANKER;
			break;
		case Position::SUPPORTER:
			nextType = Default;
			break;
		default:
			assert(false);
		}
		return nextType;
	}
	enum Heroes {
		GENJI = 0, DOOMFIST, REAPER, MCCREE, MEI, BASTION, SOLDIER76, SOMBRA, SYMMETRA, ASHE, ECHO, WIDOWMAKER, JUNKRAT, TORBJORN, TRACER, PHARAH, HANZO,
		DVA, REINHARDT, WRECKINGBALL, ROADHOG, SIGMA, ORISA, WINSTON, ZARYA,
		LUCIO, MERCY, MOIRA, BAPTISTE, BRIGITTE, ANA, ZENYATTA
	};

public:
	Position(int _current) : best(_current), current(_current) {};
	Position(int _current, QVector<Heroes> _playable) : Position(_current) {
		playable = _playable;
	}

	Position(int _best, int _current) : best(_best), current(_current) {};
	Position(int _best, int _current, QVector<Heroes> _playable) : Position(_best, _current) {
		playable = _playable;
	}

	int getRank() { return best; }
	void setRank(int _best) { best = _best; current = _best; }

	int best;
	int current;

	QVector<Heroes> playable;
};

class Member : public QListWidgetItem{
public:
	Member(QString _name, int dps, int tank, int support);

	void changeData(QString _name, int dps, int tank, int support);

	static Member* fromString(QString raw);
	QString toString();

	QString getName() { return name; }

	int getTankRank() { return Tank.getRank(); }
	int getDamageRank() { return Damage.getRank(); }
	int getSupportRank() { return Support.getRank(); }

	int getRank(Position::Types type) {
		int requestedScore;
		switch (type) {
		case Position::TANKER:
			requestedScore = getTankRank();
			break;
		case Position::DEALER:
			requestedScore = getDamageRank();
			break;
		case Position::SUPPORTER:
			requestedScore = getSupportRank();
			break;
		default:
			assert(false);
		}
		return requestedScore;
	}

	void setText();

	static struct rankCompare {
	public:
		explicit rankCompare(Position::Types _type) : type(_type) {}
		bool operator () (Member *a, Member *b) const {
			return a->getRank(type) > b->getRank(type);
		}
		Position::Types type;
	};

private:
	Position Damage, Tank, Support;
	QString name;
};