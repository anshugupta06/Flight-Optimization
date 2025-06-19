#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>  // For background image

class Backend;
class QStringListModel;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void findPathButtonClicked();

private:
    QString extractIataCode(const QString& airportText) const;

    Ui::MainWindow *ui;
    Backend *backend = nullptr;
    QStringListModel *airportListModel = nullptr;
    QPixmap backgroundPixmap;
};

#endif // MAINWINDOW_H
