#ifndef MDIAOLOG_H
#define MDIAOLOG_H

#include <QDialog>

class MDiaolog : public QDialog
{
    Q_OBJECT
public:
    MDiaolog(QString showText = "game over", QString buttonText = "try again",int width = 300, int height = 150);

public slots:
    void accept();

signals:
    void diaologClose();

};

#endif // MDIAOLOG_H
