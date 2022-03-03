#include "HeaderWidget.h"
#include "ui_HeaderWidget.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QString>

#ifndef __unix__
QString GetString(utfstring str) { return QString::fromStdWString(str); }
#else
QString GetString(utfstring str) { return QString::fromStdString(str); }
#endif

HeaderWidget::HeaderWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::HeaderWidget) {
  ui->setupUi(this);

  path = QFileDialog::getOpenFileName(this, "PMX", "/", "PMX(*.pmx)");

  std::filebuf fb;
  if (fb.open(path.toLocal8Bit().data(), std::ios::binary | std::ios::in)) {
    std::istream is(&fb);

    model = new pmx::PmxModel();
    model->Read(&is);

    ui->lineEdit_version->setText(QString("%1").arg(model->version));
    ui->lineEdit_text_encoding->setText(
        QString("%1").arg(model->setting.encoding));
    ui->lineEdit_additional_vec4_count->setText(
        QString("%1").arg(model->setting.uv));
    ui->lineEdit_vertex_index_size->setText(
        QString("%1").arg(model->setting.vertex_index_size));
    ui->lineEdit_texture_index_size->setText(
        QString("%1").arg(model->setting.texture_index_size));
    ui->lineEdit_material_index_size->setText(
        QString("%1").arg(model->setting.material_index_size));
    ui->lineEdit_bone_index_size->setText(
        QString("%1").arg(model->setting.bone_index_size));
    ui->lineEdit_morph_index_size->setText(
        QString("%1").arg(model->setting.morph_index_size));
    ui->lineEdit_rigidbody_index_size->setText(
        QString("%1").arg(model->setting.rigidbody_index_size));

    ui->lineEdit_model_name_local->setText(GetString(model->model_name));
    ui->lineEdit_model_name_universal->setText(
        GetString(model->model_english_name));
    ui->textEdit_comments_local->setText(GetString(model->model_comment));
    ui->textEdit_comments_unisersal->setText(
        GetString(model->model_english_comment));

    QStandardItemModel *ItemModel = new QStandardItemModel(this);

    for (int i = 0; i < model->texture_count; i++) {
      QStandardItem *item =
          new QStandardItem(GetString(model->textures.get()[i]));
      ItemModel->appendRow(item);
    }

    ui->listView_textures->setModel(ItemModel);

    connect(ui->listView_textures, SIGNAL(clicked(QModelIndex)), this,
            SLOT(OnTexturesClicked(QModelIndex)));

    for (int i = 0; i < model->material_count; i++) {
      ui->comboBox_material_name->addItem(
          GetString(model->materials.get()[i].material_name));
    }

    connect(ui->comboBox_material_name,
            SIGNAL(currentIndexChanged(const QString &)), this,
            SLOT(OnMaterialComboBoxCurrentIndexChanged(const QString &)));

    OnMaterialComboBoxCurrentIndexChanged(ui->comboBox_material_name->currentText());

    connect(ui->pushButton_diffuse_texture_view,SIGNAL(clicked()),this,SLOT(OnDiffuseViewClicked()));
    connect(ui->pushButton_sphere_texture_view,SIGNAL(clicked()),this,SLOT(OnSphereViewClicked()));
    connect(ui->pushButton_toon_texture_view,SIGNAL(clicked()),this,SLOT(OnToonViewClicked()));
  }
}
HeaderWidget::~HeaderWidget() { delete ui; }

void HeaderWidget::OnTexturesClicked(QModelIndex index) {
  QString real_path =
      path.mid(0, path.lastIndexOf('/')) + '/' + index.data().toString();
  // QMessageBox::information(this, "获取贴图路径", real_path);

  ShowWidget *showWidget = new ShowWidget(nullptr, real_path);
  connect(showWidget, SIGNAL(WindowClosing(QWidget *)), this,
          SLOT(ShowWidgetClosing(QWidget *)));
  showWidget->show();
}

void HeaderWidget::OnMaterialComboBoxCurrentIndexChanged(const QString &str) {

  pmx::PmxMaterial *pMaterial = model->materials.get();
  for (int i = 0; i < model->material_count; i++) {
    if (pMaterial[i].material_name == str) {
      ui->lineEdit_diffuse_color->setText(QString("(%1,%2,%3,%4)RGBA")
                                              .arg(pMaterial[i].diffuse[0])
                                              .arg(pMaterial[i].diffuse[1])
                                              .arg(pMaterial[i].diffuse[2])
                                              .arg(pMaterial[i].diffuse[3]));
      ui->lineEdit_specular_color->setText(QString("(%1,%2,%3)RGB")
                                               .arg(pMaterial[i].specular[0])
                                               .arg(pMaterial[i].specular[1])
                                               .arg(pMaterial[i].specular[2]));

      ui->lineEdit_specular_strength->setText(
          QString("%1").arg(pMaterial[i].specularlity));

      ui->lineEdit_ambient_color->setText(QString("(%1,%2,%3)RGB")
                                              .arg(pMaterial[i].ambient[0])
                                              .arg(pMaterial[i].ambient[1])
                                              .arg(pMaterial[i].ambient[1]));

      ui->lineEdit_edge_color->setText(QString("(%1,%2,%3,%4)RGBA")
                                           .arg(pMaterial[i].edge_color[0])
                                           .arg(pMaterial[i].edge_color[1])
                                           .arg(pMaterial[i].edge_color[2])
                                           .arg(pMaterial[i].edge_color[3]));

      ui->lineEdit_diffuse_texture->setText(
          GetString(model->textures.get()[pMaterial[i].diffuse_texture_index]));
      ui->lineEdit_sphere_texture->setText(GetString(model->textures.get()[pMaterial[i].sphere_texture_index]));
      ui->lineEdit_toon_texture->setText(GetString(model->textures.get()[pMaterial[i].toon_texture_index]));
      ui->lineEdit_memo->setText(GetString(pMaterial[i].memo));
      ui->lineEdit_index_count->setText(QString("%1").arg(pMaterial[i].index_count));

    }
  }
}

void HeaderWidget::ShowWidgetClosing(QWidget *widget) { delete widget; }

void HeaderWidget::OnDiffuseViewClicked()
{
  QString real_path =
      path.mid(0, path.lastIndexOf('/')) + '/' + ui->lineEdit_diffuse_texture->text();

  ShowWidget *showWidget = new ShowWidget(nullptr, real_path);
  connect(showWidget, SIGNAL(WindowClosing(QWidget *)), this,
          SLOT(ShowWidgetClosing(QWidget *)));
  showWidget->show();
}

void HeaderWidget::OnSphereViewClicked()
{
  QString real_path =
      path.mid(0, path.lastIndexOf('/')) + '/' + ui->lineEdit_sphere_texture->text();

  ShowWidget *showWidget = new ShowWidget(nullptr, real_path);
  connect(showWidget, SIGNAL(WindowClosing(QWidget *)), this,
          SLOT(ShowWidgetClosing(QWidget *)));
  showWidget->show();
}

void HeaderWidget::OnToonViewClicked()
{
  QString real_path =
      path.mid(0, path.lastIndexOf('/')) + '/' + ui->lineEdit_toon_texture->text();

  ShowWidget *showWidget = new ShowWidget(nullptr, real_path);
  connect(showWidget, SIGNAL(WindowClosing(QWidget *)), this,
          SLOT(ShowWidgetClosing(QWidget *)));
  showWidget->show();
}