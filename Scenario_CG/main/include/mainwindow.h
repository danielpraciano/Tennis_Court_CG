#pragma once

#include <QWidget>
#include <QSlider>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_rc_button_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
};
