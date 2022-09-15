#ifndef MAINPROJECT_H
#define MAINPROJECT_H

#include <QWidget>

namespace Ui {
class MainProject;
}

class MainProject : public QWidget
{
    Q_OBJECT

public:
    explicit MainProject(QWidget *parent = nullptr);
    ~MainProject();

signals:
    void mainProjectShow();


private:
    Ui::MainProject *ui;
};

#endif // MAINPROJECT_H
