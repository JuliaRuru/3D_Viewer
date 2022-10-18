#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settings = new QSettings("Drodolfo + Ssister + Mrorscha", "3DViewer", this);
    this->setFixedSize(this->geometry().width(),this->geometry().height());
    ui->scale_slider->setMinimum(1);
    ui->scale_slider->setMaximum(1000);
    ui->scale_box->setMinimum(0.01);
    ui->scale_box->setMaximum(10.00);
    connect(ui->load_file,SIGNAL(clicked()),this,SLOT(open_file()));
    connect(ui->standart_apply_button,SIGNAL(clicked()),this,SLOT(reset_settings()));
    ui->count_facets->setEnabled(false);
    ui->count_vertex->setEnabled(false);
    ui->file_location->setEnabled(false);
    connect(ui->export_bmp,SIGNAL(clicked()),this,SLOT(export_bmp()));
    connect(ui->export_jpeg,SIGNAL(clicked()),this,SLOT(export_jpeg()));
    connect(ui->export_gif,SIGNAL(clicked()),this,SLOT(export_gif()));
}

MainWindow::~MainWindow()
{
    save_settings();
    delete ui;
}

void MainWindow::open_file()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "../../../../src/obj/.", "*.obj");
    if (filename != "") {

        reset_settings();

        ui->openGLWidget->picture->filepath = filename;
        ui->openGLWidget->picture->initPicture();

        ui->file_location->setText(filename);
        QString text_vertexes = QString::number(ui->openGLWidget->picture->data.count_of_vertexes);
        ui->count_vertex->setText(text_vertexes);
        QString text_facets = QString::number(ui->openGLWidget->picture->data.count_of_facets);
        ui->count_facets->setText(text_facets);
    }
}

void MainWindow::reset_settings()
{
    ui->scale_box->setValue(1.0);
    ui->scale_slider->setValue(100);
    scale_new = 1;

    ui->move_x_box->setValue(0);
    ui->move_x_slider->setValue(0);
    x_new_move = 0;

    ui->move_y_box->setValue(0);
    ui->move_y_slider->setValue(0);
    y_new_move = 0;

    ui->move_z_box->setValue(0);
    ui->move_z_slider->setValue(0);
    y_new_move = 0;

    ui->rotate_x_box->setValue(0);
    ui->rotate_x_slider->setValue(0);
    x_new_rotate = 0;

    ui->rotate_y_box->setValue(0);
    ui->rotate_y_slider->setValue(0);
    y_new_rotate = 0;

    ui->rotate_z_box->setValue(0);
    ui->rotate_z_slider->setValue(0);
    z_new_rotate = 0;

    ui->openGLWidget->update();
}

void MainWindow::on_move_x_slider_valueChanged(int value)
{
    double new_val = (double)value/100;
    ui->move_x_box->setValue(new_val);
    model_move(&ui->openGLWidget->picture->vertexes, 'x', new_val - x_new_move);
    x_new_move = new_val;
    ui->openGLWidget->update();
}

void MainWindow::on_move_x_box_valueChanged(double arg1)
{
    ui->move_x_slider->setValue(arg1*100);
    model_move(&ui->openGLWidget->picture->vertexes, 'x', arg1 - x_new_move);
    x_new_move = arg1;
    ui->openGLWidget->update();
}

void MainWindow::on_move_y_slider_valueChanged(int value)
{
    double new_val = (double)value/100;
    ui->move_y_box->setValue(new_val);
    model_move(&ui->openGLWidget->picture->vertexes, 'y', new_val - y_new_move);
    y_new_move = new_val;
    ui->openGLWidget->update();
}

void MainWindow::on_move_y_box_valueChanged(double arg1)
{
    ui->move_y_slider->setValue(arg1*100);
    model_move(&ui->openGLWidget->picture->vertexes, 'y', arg1 - y_new_move);
    y_new_move = arg1;
    ui->openGLWidget->update();
}

void MainWindow::on_move_z_slider_valueChanged(int value)
{
    double new_val = (double)value/100;
    ui->move_z_box->setValue(new_val);
    model_move(&ui->openGLWidget->picture->vertexes, 'z', new_val - z_new_move);
    z_new_move = new_val;
    ui->openGLWidget->update();
}

void MainWindow::on_move_z_box_valueChanged(double arg1)
{
    ui->move_z_slider->setValue(arg1*100);
    model_move(&ui->openGLWidget->picture->vertexes, 'z', arg1 - z_new_move);
    z_new_move = arg1;
    ui->openGLWidget->update();
}

void MainWindow::on_rotate_x_slider_valueChanged(int value)
{
    double new_val = (double)value/100;
    ui->rotate_x_box->setValue(new_val);
    model_rotate(&ui->openGLWidget->picture->vertexes, 'x', new_val - x_new_rotate);
    x_new_rotate = new_val;
    ui->openGLWidget->update();
}

void MainWindow::on_rotate_x_box_valueChanged(double arg1)
{
    ui->rotate_x_slider->setValue(arg1*100);
    model_rotate(&ui->openGLWidget->picture->vertexes, 'x', arg1 - x_new_rotate);
    x_new_rotate = arg1;
    ui->openGLWidget->update();
}

void MainWindow::on_rotate_y_box_valueChanged(double arg1)
{
    ui->rotate_y_slider->setValue(arg1*100);
    model_rotate(&ui->openGLWidget->picture->vertexes, 'y', arg1 - y_new_rotate);
    y_new_rotate = arg1;
    ui->openGLWidget->update();
}

void MainWindow::on_rotate_y_slider_valueChanged(int value)
{
    double new_val = (double)value/100;
    ui->rotate_y_box->setValue(new_val);
    model_rotate(&ui->openGLWidget->picture->vertexes, 'y', new_val - y_new_rotate);
    y_new_rotate = new_val;
    ui->openGLWidget->update();
}

void MainWindow::on_rotate_z_box_valueChanged(double arg1)
{
    ui->rotate_z_slider->setValue(arg1*100);
    model_rotate(&ui->openGLWidget->picture->vertexes, 'z', arg1 - z_new_rotate);
    z_new_rotate = arg1;
    ui->openGLWidget->update();
}

void MainWindow::on_rotate_z_slider_valueChanged(int value)
{
    double new_val = (double)value/100;
    ui->rotate_z_box->setValue(new_val);
    model_rotate(&ui->openGLWidget->picture->vertexes, 'z', new_val - z_new_rotate);
    z_new_rotate = new_val;
    ui->openGLWidget->update();
}

void MainWindow::on_scale_slider_valueChanged(int value)
{
    double new_val = (double)value/100;
    ui->scale_box->setValue(new_val);
    if (value != 0) {
        model_scale(&ui->openGLWidget->picture->vertexes, new_val / scale_new);
        scale_new = new_val;
    }
    ui->openGLWidget->update();
}

void MainWindow::on_scale_box_valueChanged(double arg1)
{
    ui->scale_slider->setValue(arg1*100);
    if (arg1 != 0.0) {
        model_scale(&ui->openGLWidget->picture->vertexes, arg1 / scale_new);
        scale_new = arg1;
    }
    ui->openGLWidget->update();
}

void MainWindow::export_bmp()
{
    QDate date;
    QTime time;
    QString curtime = time.currentTime().toString();
    QString curdate = date.currentDate().toString();
    QString filepath = QFileDialog::getExistingDirectory();
    ui->openGLWidget->grabFramebuffer().save(filepath + "/" + curdate + curtime + ".BMP", NULL, 100);
}

void MainWindow::export_jpeg()
{
    QDate date;
    QTime time;
    QString curtime = time.currentTime().toString();
    QString curdate = date.currentDate().toString();
    QString filepath = QFileDialog::getExistingDirectory();
    ui->openGLWidget->grabFramebuffer().save(filepath + "/" + curdate + curtime + ".JPG", NULL, 100);

}

void MainWindow::export_gif()
{
    gif = new QGifImage;
    photo = new QImage;
    time = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_for_gif()));
    timer->start(100);
}

void MainWindow::timer_for_gif()
{
    QDate date;
    QTime currtime;
    QString curtime = currtime.currentTime().toString();
    QString curdate = date.currentDate().toString();
    time++;
    *photo = ui->openGLWidget->grabFramebuffer();
    gif->addFrame(*photo);
    if (time == 50) {
        timer->stop();
        gif->save(QFileDialog::getExistingDirectory() + "/" + curdate + " " + curtime + ".GIF");
        delete timer;
        delete gif;
        delete photo;
    }
}

void MainWindow::on_parallel_projection_clicked()
{
    ui->openGLWidget->check_projection = true;
    ui->openGLWidget->resizeGL(4, 3);
    ui->openGLWidget->update();
}

void MainWindow::on_central_projection_clicked()
{
    ui->openGLWidget->check_projection = false;
    ui->openGLWidget->resizeGL(4, 3);
    ui->openGLWidget->update();
}

void MainWindow::on_background_color_button_clicked()
{
    QColor tmp = QColorDialog::getColor();
        if (tmp.isValid()) {
            *back_color = tmp;
            ui->openGLWidget->color_back = back_color;
            ui->openGLWidget->update();
        }
}

void MainWindow::on_facets_color_button_clicked()
{
    QColor tmp = QColorDialog::getColor();
        if (tmp.isValid()) {
            *line_color = tmp;
            ui->openGLWidget->color_line = line_color;
            ui->openGLWidget->update();
        }
}


void MainWindow::on_vertexes_color_button_clicked()
{
    QColor tmp = QColorDialog::getColor();
        if (tmp.isValid()) {
            *ver_color = tmp;
            ui->openGLWidget->color_ver = ver_color;
            ui->openGLWidget->update();
        }
}


void MainWindow::on_dotted_facets_clicked()
{
    ui->openGLWidget->line_dot = true;
}


void MainWindow::on_solid_facets_clicked()
{
    ui->openGLWidget->line_dot = false;
}

void MainWindow::on_facets_width_box_valueChanged(double linesize)
{
    ui->openGLWidget->picture->line_width = linesize;
    ui->openGLWidget->update();
}

void MainWindow::on_vertexes_size_box_valueChanged(double dotsize)
{
    ui->openGLWidget->picture->dot_size = dotsize;
    ui->openGLWidget->update();
}

void MainWindow::on_none_vertexes_clicked()
{
    ui->openGLWidget->picture->flag_dot_vert = false;
    ui->openGLWidget->picture->flag_dot_round = false;
}

void MainWindow::on_round_vertexes_clicked()
{
    ui->openGLWidget->picture->flag_dot_vert = true;
    ui->openGLWidget->picture->flag_dot_round = true;
}


void MainWindow::on_square_vertexes_clicked()
{
    ui->openGLWidget->picture->flag_dot_vert = true;
    ui->openGLWidget->picture->flag_dot_round = false;
}

void MainWindow::default_settings()
{
    ui->scale_box->setValue(1.0);
    ui->scale_slider->setValue(100);
    scale_new = 1;

    ui->move_x_box->setValue(0);
    ui->move_x_slider->setValue(0);
    x_new_move = 0;

    ui->move_y_box->setValue(0);
    ui->move_y_slider->setValue(0);
    y_new_move = 0;

    ui->move_z_box->setValue(0);
    ui->move_z_slider->setValue(0);
    y_new_move = 0;

    ui->rotate_x_box->setValue(0);
    ui->rotate_x_slider->setValue(0);
    x_new_rotate = 0;

    ui->rotate_y_box->setValue(0);
    ui->rotate_y_slider->setValue(0);
    y_new_rotate = 0;

    ui->rotate_z_box->setValue(0);
    ui->rotate_z_slider->setValue(0);
    z_new_rotate = 0;

    ui->openGLWidget->color_back = new QColor(0, 0, 0, 255);
    ui->openGLWidget->color_line = new QColor(214, 214, 214, 255);
    ui->openGLWidget->color_ver = new QColor(0, 0, 255, 255);

    ui->openGLWidget->line_dot = false;
    ui->solid_facets->setChecked(true);
    ui->openGLWidget->picture->line_width = 1.0;
    ui->facets_width_box->setValue(1.0);

    ui->openGLWidget->check_projection = false;
    ui->central_projection->setChecked(true);
    ui->openGLWidget->resizeGL(4, 3);

    ui->openGLWidget->picture->flag_dot_round = false;
    ui->openGLWidget->picture->flag_dot_vert = false;
    ui->vertexes_size_box->setValue(1.0);
    ui->none_vertexes->setChecked(true);

    ui->openGLWidget->update();
}

void MainWindow::save_settings()
{
    settings->setValue("filepath", ui->openGLWidget->picture->filepath);

    settings->setValue("color_back", *ui->openGLWidget->color_back);
    settings->setValue("color_line", *ui->openGLWidget->color_line);
    settings->setValue("color_ver", *ui->openGLWidget->color_ver);

    settings->setValue("flag_dot_round", ui->openGLWidget->picture->flag_dot_round);
    settings->setValue("flag_dot_vert", ui->openGLWidget->picture->flag_dot_vert);
    settings->setValue("dot_size", ui->openGLWidget->picture->dot_size);

    settings->setValue("line_width", ui->openGLWidget->picture->line_width);
    settings->setValue("flag_dotted", ui->openGLWidget->line_dot);

    settings->setValue("check_projection", ui->openGLWidget->check_projection);
}


void MainWindow::load_settings()
{
    ui->openGLWidget->check_projection = settings->value("check_projection").toBool();
    if(ui->openGLWidget->check_projection) ui->parallel_projection->setChecked(1);
    else ui->central_projection->setChecked(1);

    *back_color = settings->value("color_back").toByteArray().constData();
    ui->openGLWidget->color_back = back_color;
    *line_color = settings->value("color_line").toByteArray().constData();
    ui->openGLWidget->color_line = line_color;
    *ver_color = settings->value("color_ver").toByteArray().constData();
    ui->openGLWidget->color_ver = ver_color;

    ui->openGLWidget->picture->flag_dot_round = settings->value("flag_dot_round").toBool();
    ui->openGLWidget->picture->flag_dot_vert = settings->value("flag_dot_vert").toBool();
    if(ui->openGLWidget->picture->flag_dot_round) ui->round_vertexes->setChecked(1);
    else if(ui->openGLWidget->picture->flag_dot_vert) ui->square_vertexes->setChecked(1);
    else ui->none_vertexes->setChecked(1);
    ui->openGLWidget->picture->dot_size = settings->value("dot_size").toDouble();
    ui->vertexes_size_box->setValue(ui->openGLWidget->picture->dot_size);

    ui->openGLWidget->line_dot = settings->value("flag_dotted").toBool();
    if(ui->openGLWidget->line_dot) ui->dotted_facets->setChecked(1);
    else ui->solid_facets->setChecked(1);
    ui->openGLWidget->picture->line_width = settings->value("line_width").toDouble();
    ui->facets_width_box->setValue(ui->openGLWidget->picture->line_width);

    ui->openGLWidget->update();
}

void MainWindow::on_reset_settings_clicked()
{
    default_settings();
}


void MainWindow::on_load_settings_clicked()
{
    load_settings();
}

