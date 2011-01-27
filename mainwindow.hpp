#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QDragEnterEvent>
#include <QUrl>
#include <QDebug>
#include <QPixmap>
#include <QImage>
#include <QStringList>
#include <QString>
#include <QPainter>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void set_args(QStringList list);
	int cond_show();

protected:
	void dragEnterEvent(QDragEnterEvent *e);
	void dropEvent(QDropEvent *e);

private slots:
	QString mk_new_file(QString file);

private:
	QString ui_mode;
	void set_mode(QString mode);
	QImage scale(QImage img, QString mode);
	QImage embed(QImage img, int w, int h, QRgb colour);
	Ui::MainWindow *ui;
	QString get_parm(QStringList list,QString str);
};

#endif // MAINWINDOW_HPP
