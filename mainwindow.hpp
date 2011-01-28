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
	QImage mk_new_file(QString file);
	void show_image(QImage img);
	void set_mode(QString mode);

private:
	Ui::MainWindow *ui;
	QString ui_mode;
	QString mk_new_file_name(QString file);
	QImage scale(QImage img, QString mode);
	QImage embed(QImage img, int w, int h, QRgb colour);
	QString get_parm(QStringList list,QString str);
};

#endif // MAINWINDOW_HPP
