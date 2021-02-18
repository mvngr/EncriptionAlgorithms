#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum Algorithms {
        TranspositionCipherFlag = 0,
        MagicsquareCipherFlag
    };
    Q_ENUM(Algorithms)

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_base_message_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
