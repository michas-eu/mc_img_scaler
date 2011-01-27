#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	this->ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete this->ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
	e->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *e)
{
	QString tmp;
	if (!e->mimeData()->hasUrls()) return;
	tmp = e->mimeData()->urls().first().toLocalFile();
	this->mk_new_file(tmp);
	e->accept();
}

QString MainWindow::mk_new_file(QString file)
{
	QPixmap pix;
	QImage img;
	QString new_file;
	this->ui->file_url->setText(file);
	img.load(file);
	img = this->scale(img,this->ui->mode_box->currentText());
	new_file = file.append(".new.jpeg");
	img.save(new_file,0,80);
	pix = QPixmap::fromImage(img);
	this->ui->image_tester->setPixmap(pix);
	return(file);
}

QImage MainWindow::scale(QImage img,QString mode)
{
	int w;
	int h;
	float wa;
	float ha;
	enum Qt::TransformationMode smooth;
	w = this->ui->w_box->value();
	h = this->ui->h_box->value();
	wa = (float)w/img.width();
	ha = (float)h/img.height();
//qDebug() << wa << ":" << ha << "\n";
qDebug() << mode << "\n";
	smooth = Qt::SmoothTransformation;
	if (mode == mode.fromUtf8("Szerokość")) {
		img = img.scaledToWidth(w,smooth);
	} else if (mode == mode.fromUtf8("Wysokość")) {
		img = img.scaledToHeight(h,smooth);
	} else if (mode == "Wymuszenie") {
		img = img.scaled(w,h,Qt::IgnoreAspectRatio,smooth);
	} else if (mode == "Minimum") {
		if (wa < ha) img = img.scaledToWidth(w,smooth);
		else img = img.scaledToHeight(h,smooth);
	} else if (mode == "Maksimum") {
		if (wa > ha) img = img.scaledToWidth(w,smooth);
		else img = img.scaledToHeight(h,smooth);
	} else if (mode == mode.fromUtf8("Białe dopełnienie")) {
		img = this->embed(img,w,h,qRgb(255,255,255));
	} else if (mode == mode.fromUtf8("Czarne dopełnienie")) {
		img = this->embed(img,w,h,qRgb(0,0,0));
	}

	return img;
}

QImage MainWindow::embed(QImage img, int w, int h, QRgb colour)
{
	QPainter ptr;
	QImage new_img(w,h,QImage::Format_RGB32);
	img = this->scale(img,"Minimum");
	new_img.fill(colour);
	w = (w - img.width())/2;
	h = (h - img.height())/2;
	ptr.begin(&new_img);
	ptr.drawImage(w,h,img);
	return new_img;
}

void MainWindow::set_mode(QString mode)
{
	QString tmp;
	int idx;
	if (mode == "min") tmp = "Minimum";
	else if (mode == "max") tmp = "Maksimum";
	else if (mode == "width") tmp = tmp.fromUtf8("Szerokość");
	else if (mode == "height") tmp = tmp.fromUtf8("Wysokość");
	else if (mode == "white") tmp = tmp.fromUtf8("Białe dopełnienie");
	else if (mode == "black") tmp = tmp.fromUtf8("Czarne dopełnienie");
	else if (mode == "force") tmp = "Wymuszenie";
	idx = this->ui->mode_box->findText(tmp);
	if (idx<0) idx = 0;
	this->ui->mode_box->setCurrentIndex(idx);
}

void MainWindow::set_args(QStringList list)
{
	QString tmp;
	tmp = this->get_parm(list,"-w");
	if (tmp != "") this->ui->w_box->setValue(tmp.toInt());
	tmp = this->get_parm(list,"-h");
	if (tmp != "") this->ui->h_box->setValue(tmp.toInt());
	tmp = this->get_parm(list,"-m");
	if (tmp != "") this->set_mode(tmp);
	tmp = this->get_parm(list,"-f");
	if (tmp != "") this->mk_new_file(tmp);
	tmp = this->get_parm(list,"-g");
	this->ui_mode = tmp;
}

QString MainWindow::get_parm(QStringList list, QString str)
{
	int idx;
	idx = list.lastIndexOf(str);
	if (idx < 0) return "";
	idx++;
	if (idx >= list.length()) return "";
	return list.at(idx);
}

int MainWindow::cond_show()
{
	if (this->ui_mode == "") this->ui_mode = "full";
	if (this->ui_mode == "no") return 0;
	else if (this->ui_mode == "simple") {
		this->show();
		this->ui->mode_box->setVisible(false);
		this->ui->w_box->setVisible(false);
		this->ui->h_box->setVisible(false);
	}
	else {
		this->show();
	}
	return 1;
}
