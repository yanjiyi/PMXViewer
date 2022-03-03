#ifndef SHOWWDIGET_HEADER
#define SHOWWDIGET_HEADER

#include <QWidget>
#include <QPixmap>
#include <QString>

class ShowWidget : public QWidget
{
  Q_OBJECT
  public:
    explicit ShowWidget(QWidget * parent = nullptr,QPixmap * texture = nullptr);
    explicit ShowWidget(QWidget * parent = nullptr,QString path = "");

  signals:
    void WindowClosing(QWidget*);

  protected:
    void paintEvent(QPaintEvent*);
    void closeEvent(QCloseEvent*);
    
    QPixmap * pTexture;
};

#endif