#ifndef SRC_VIEW_MAINWINDOW_H
#define SRC_VIEW_MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>

#include "../Controller/controller.h"
#include "qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  Controller *my_controller_;
  QSettings *settings;
  QString path;
  QColor *line_color = new QColor(0, 0, 0, 255);
  QColor *back_color = new QColor(214, 214, 214, 255);
  QColor *ver_color = new QColor(0, 0, 255, 255);
  double x_new_move = 0, y_new_move = 0, z_new_move = 0;
  double x_new_rotate = 0, y_new_rotate = 0, z_new_rotate = 0;
  double scale_new = 1;
  int time = 0;
  bool load_file = false;
  QGifImage *gif;
  QImage *photo;
  QTimer *timer;

private slots:
  void open_file();
  void on_move_x_slider_valueChanged(int value);
  void on_move_x_box_valueChanged(double arg1);
  void on_move_y_slider_valueChanged(int value);
  void on_move_y_box_valueChanged(double arg1);
  void on_move_z_slider_valueChanged(int value);
  void on_move_z_box_valueChanged(double arg1);
  void on_rotate_x_slider_valueChanged(int value);
  void on_rotate_x_box_valueChanged(double arg1);
  void on_rotate_y_slider_valueChanged(int value);
  void on_rotate_y_box_valueChanged(double arg1);
  void on_rotate_z_slider_valueChanged(int value);
  void on_rotate_z_box_valueChanged(double arg1);
  void on_scale_slider_valueChanged(int value);
  void on_scale_box_valueChanged(double arg1);
  void reset_settings();
  void export_bmp();
  void export_jpeg();
  void export_gif();
  void timer_for_gif();

  void on_parallel_projection_clicked();
  void on_central_projection_clicked();
  void on_background_color_button_clicked();
  void on_facets_color_button_clicked();
  void on_vertexes_color_button_clicked();
  void on_dotted_facets_clicked();
  void on_solid_facets_clicked();
  void on_facets_width_box_valueChanged(double linesize);
  void on_vertexes_size_box_valueChanged(double dotsize);
  void on_none_vertexes_clicked();
  void on_round_vertexes_clicked();
  void on_square_vertexes_clicked();
  void save_settings();
  void load_settings();
  void on_reset_settings_clicked();
  void default_settings();
  void on_load_settings_clicked();
};

} //  namespace s21

#endif // SRC_VIEW_MAINWINDOW_H
