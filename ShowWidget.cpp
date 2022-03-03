#include "ShowWidget.h"
#include <QPainter>

ShowWidget::ShowWidget(QWidget * parent,QPixmap * texture) : QWidget(parent)
{
  pTexture = texture;
  resize(800,600);
}

ShowWidget::ShowWidget(QWidget * parent,QString path) : QWidget(parent)
{
  pTexture = new QPixmap(path);
  resize(800,600);
}

void ShowWidget::paintEvent(QPaintEvent*)
{
  QPainter painter(this);
  if(pTexture!=nullptr)
  {
    //resize(pTexture->width(),pTexture->height());

    painter.drawPixmap(0, 0, width(), height(), *pTexture);
  }
}

void ShowWidget::closeEvent(QCloseEvent*)
{
  emit WindowClosing(this);
}