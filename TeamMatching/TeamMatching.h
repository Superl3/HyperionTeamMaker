#pragma once

#include <QMainWindow>
#include "ui_TeamMatching.h"

class TeamMatching : public QMainWindow
{
    Q_OBJECT

public:
    TeamMatching(QWidget *parent = Q_NULLPTR);

public slots:
	void slotOpenConfigureDialog();
	void slotOpenCreateTeamDialog();

private:
    Ui::TeamMatchingClass ui;
};
