#ifndef HEADERWIDGET_HEADER
#define HEADERWIDGET_HEADER

#include <QWidget>
#include <QModelIndex>
#include "ShowWidget.h"
#include "Pmx.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class HeaderWidget;
}
QT_END_NAMESPACE

class HeaderWidget : public QWidget {
  Q_OBJECT
public:
  explicit HeaderWidget(QWidget *parent = nullptr);
  ~HeaderWidget();

private slots:
  void OnTexturesClicked(QModelIndex index);
  void OnMaterialComboBoxCurrentIndexChanged(const QString& str);
  void ShowWidgetClosing(QWidget*);

  void OnDiffuseViewClicked();
  void OnSphereViewClicked();
  void OnToonViewClicked();
private:
  Ui::HeaderWidget *ui;
  QString path;
  pmx::PmxModel *model;
};

#endif