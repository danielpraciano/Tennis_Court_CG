#include "main/include/mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <scenario/include/object/transformation.h>
#include <scenario/include/scenario.h>
#include <scenario/include/object/vertex.h>
#include <scenario/include/object/face.h>
#include <scenario/include/object/object.h>
#include <scenario/include/light/light.h>
#include <scenario/include/object/material.h>
#include <scenario/include/light/punctual_light.h>
#include <render/include/raycasting/camera.h>
#include <render/include/raycasting/color.h>
#include <render/include/raycasting/ray.h>
#include <render/include/raycasting/ray_casting.h>

#include <core/include/io_module.h>
#include <scenario/include/object/chair_meuOBJ.h>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

std::shared_ptr<scenario::object::Object> get_cube(std::shared_ptr<scenario::object::Material> mat, double x, double y, double z) {
    std::shared_ptr<scenario::object::Object> cube { new scenario::object::Object { mat } };

    cube->add_vertex(scenario::object::Vertex { 0.0, 0.0, 0.0 }); //0
    cube->add_vertex(scenario::object::Vertex { 1.0, 0.0, 0.0 }); //1
    cube->add_vertex(scenario::object::Vertex { 0.0, 1.0, 0.0 }); //2
    cube->add_vertex(scenario::object::Vertex { 1.0, 1.0, 0.0 }); //3
    cube->add_vertex(scenario::object::Vertex { 0.0, 0.0, 1.0 }); //4
    cube->add_vertex(scenario::object::Vertex { 1.0, 0.0, 1.0 }); //5
    cube->add_vertex(scenario::object::Vertex { 0.0, 1.0, 1.0 }); //6
    cube->add_vertex(scenario::object::Vertex { 1.0, 1.0, 1.0 }); //7

    //trás
    cube->add_face(0, 3, 1);
    cube->add_face(0, 2, 3);

    //direita
    cube->add_face(1, 7, 5);
    cube->add_face(1, 3, 7);

    //frente
    cube->add_face(4, 5, 7);
    cube->add_face(4, 7, 6);

    //esquerda
    cube->add_face(0, 4, 6);
    cube->add_face(0, 6, 2);

    //baixo
    cube->add_face(0, 1, 5);
    cube->add_face(0, 5, 4);

    //cima
    cube->add_face(2, 6, 7);
    cube->add_face(2, 7, 3);

    scenario::object::Transformation t_resize;

    t_resize.add_translation(core::util::Vector3 {-0.5, -0.5, -0.5});
    t_resize.add_scale(core::util::Vector3 { x, y, z });
    t_resize.add_to_apply(cube);
    t_resize.make_apply();

    return cube;
}

std::shared_ptr<scenario::object::Object> get_chair(std::shared_ptr<scenario::object::Material> mat) {
//    double m = 96.078;
//    render::raycasting::Color k_a { 0.00, 0.00, 0.00 };
//    render::raycasting::Color k_d { 0.640, 0.640, 0.640 };
//    render::raycasting::Color k_s { 0.500, 0.500, 0.500 };

//    std::shared_ptr<scenario::object::Material> material {
//    new scenario::object::Material { m, k_a, k_d, k_s } };

    std::shared_ptr<scenario::object::Object> chair { new scenario::object::Object { mat } };

    for (unsigned int i = 0; i < 3*chair_meuOBJNumVerts; i += 3)
        chair->add_vertex(scenario::object::Vertex { chair_meuOBJVerts[i], chair_meuOBJVerts[i + 1], chair_meuOBJVerts[i + 2] });

    for (unsigned int i = 0; i < chair_meuOBJNumVerts; i += 3)
        chair->add_face(i, i + 1, i + 2);

//    core::io_module::ObjReader reader;

//    const std::string path = "/home/daniel/chair_novo.obj";

//    auto chair = reader.read(path, mat);

    return chair;
}

void MainWindow::on_rc_button_clicked() {
    render::raycasting::Color color_red { 1.0, 0.0, 0.0 };
    render::raycasting::Color color_blue { 0.0, 0.0, 1.0 };
    render::raycasting::Color color_green { 0.0, 1.0, 0.0 };
    render::raycasting::Color color_white { 1.0, 1.0, 1.0 };
    render::raycasting::Color color_black { 0.0, 0.0, 0.0 };
    render::raycasting::Color color_yellow { 1.0, 1.0, 0.0 };
    render::raycasting::Color color_orange { 1.0, 140.0/255.0, 0.0 };

    render::raycasting::Color k_a_ground { 101.0/255, 179.0/255, 253.0/255 };
    render::raycasting::Color k_d_ground { 101.0/255, 179.0/255, 253.0/255 };
    render::raycasting::Color k_s_ground { 101.0/255, 179.0/255, 253.0/255 };

    std::shared_ptr<scenario::object::Material> material_ground {
    new scenario::object::Material { 100.0, k_a_ground, k_d_ground, k_s_ground } };

    //azulado
//    render::raycasting::Color k_a_court { 69.0/255, 114.0/255, 172.0/255 };
//    render::raycasting::Color k_d_court { 69.0/255, 114.0/255, 172.0/255 };
//    render::raycasting::Color k_s_court { 69.0/255, 114.0/255, 172.0/255 };

    render::raycasting::Color k_a_court { 196.0/255, 102.0/255, 70.0/255 };
    render::raycasting::Color k_d_court { 196.0/255, 102.0/255, 70.0/255 };
    render::raycasting::Color k_s_court { 196.0/255, 102.0/255, 70.0/255 };

    std::shared_ptr<scenario::object::Material> material_court {
    new scenario::object::Material { 100.0, k_a_court, k_d_court, k_s_court } };

    std::shared_ptr<scenario::object::Material> material_red {
    new scenario::object::Material { 100.0, color_red, color_red, color_red } };

    std::shared_ptr<scenario::object::Material> material_blue {
    new scenario::object::Material { 100.0, color_blue, color_blue, color_blue } };

    std::shared_ptr<scenario::object::Material> material_green {
    new scenario::object::Material { 100.0, color_green, color_green, color_green } };

    std::shared_ptr<scenario::object::Material> material_white {
    new scenario::object::Material { 100.0, color_white, color_white, color_white } };

    std::shared_ptr<scenario::object::Material> material_black {
    new scenario::object::Material { 100.0, color_black, color_black, color_black } };

    std::shared_ptr<scenario::object::Material> material_yellow {
    new scenario::object::Material { 100.0, color_yellow, color_yellow, color_yellow } };

    std::shared_ptr<scenario::object::Material> material_orange {
    new scenario::object::Material { 100.0, color_orange, color_orange, color_orange } };

    //

    std::shared_ptr<scenario::object::Object> ground = get_cube(material_ground, 2 * 10.974, 2 * 23.77, 0.001);
    scenario::object::Transformation t_ground;

    t_ground.add_translation(-ground->get_vertice(0)->get_coordinates());
    t_ground.add_translation(core::util::Vector3 { -10.974/2, -23.77/2, -0.002 });
    t_ground.add_to_apply(ground);
    t_ground.make_apply();

    std::shared_ptr<scenario::object::Object> court = get_cube(material_court, 10.974, 23.77, 0.001);
    scenario::object::Transformation t_court;

    t_court.add_translation(-court->get_vertice(0)->get_coordinates());
    t_court.add_translation(core::util::Vector3 { 0.0, 0.0, -0.001 });
    t_court.add_to_apply(court);
    t_court.make_apply();

    std::shared_ptr<scenario::object::Object> left_doubles_sideline = get_cube(material_white, 7.62/100, 23.77, 0.001);
    scenario::object::Transformation t_left_doubles_sideline;

    t_left_doubles_sideline.add_translation(-left_doubles_sideline->get_vertice(0)->get_coordinates());
    t_left_doubles_sideline.add_to_apply(left_doubles_sideline);
    t_left_doubles_sideline.make_apply();

    std::shared_ptr<scenario::object::Object> left_singles_sideline = get_cube(material_white, 7.62/100, 23.77, 0.001);
    scenario::object::Transformation t_left_singles_sideline;

    t_left_singles_sideline.add_translation(-left_singles_sideline->get_vertice(0)->get_coordinates());
    t_left_singles_sideline.add_translation(core::util::Vector3 { 1.372, 0.0, 0.0 });
    t_left_singles_sideline.add_to_apply(left_singles_sideline);
    t_left_singles_sideline.make_apply();

    std::shared_ptr<scenario::object::Object> before_center_mark = get_cube(material_white, 7.62/100, 0.77, 0.001);
    scenario::object::Transformation t_before_center_mark;

    t_before_center_mark.add_translation(-before_center_mark->get_vertice(0)->get_coordinates());
    t_before_center_mark.add_translation(core::util::Vector3 { 10.974/2, 0.0, 0.0 });
    t_before_center_mark.add_to_apply(before_center_mark);
    t_before_center_mark.make_apply();

    std::shared_ptr<scenario::object::Object> center_service_line = get_cube(material_white, 7.62/100, 2*6.4, 0.001);
    scenario::object::Transformation t_center_service_line;

    t_center_service_line.add_translation(-center_service_line->get_vertice(0)->get_coordinates());
    t_center_service_line.add_translation(core::util::Vector3 { 10.974/2, 23.77/2 - 6.4, 0.0 });
    t_center_service_line.add_to_apply(center_service_line);
    t_center_service_line.make_apply();

    std::shared_ptr<scenario::object::Object> after_center_mark = get_cube(material_white, 7.62/100, 0.77, 0.001);
    scenario::object::Transformation t_after_center_mark;

    t_after_center_mark.add_translation(-after_center_mark->get_vertice(2)->get_coordinates());
    t_after_center_mark.add_translation(core::util::Vector3 { 10.974/2, 23.77, 0.0 });
    t_after_center_mark.add_to_apply(after_center_mark);
    t_after_center_mark.make_apply();

    std::shared_ptr<scenario::object::Object> right_singles_sideline = get_cube(material_white, 7.62/100, 23.77, 0.001);
    scenario::object::Transformation t_right_singles_sideline;

    t_right_singles_sideline.add_translation(-right_singles_sideline->get_vertice(1)->get_coordinates());
    t_right_singles_sideline.add_translation(core::util::Vector3 { 1.372 + 8.23, 0.0, 0.0 });
    t_right_singles_sideline.add_to_apply(right_singles_sideline);
    t_right_singles_sideline.make_apply();

    std::shared_ptr<scenario::object::Object> right_doubles_sideline = get_cube(material_white, 7.62/100, 23.77, 0.001);
    scenario::object::Transformation t_right_doubles_sideline;

    t_right_doubles_sideline.add_translation(-right_doubles_sideline->get_vertice(1)->get_coordinates());
    t_right_doubles_sideline.add_translation(core::util::Vector3 { 1.372 + 8.23 + 1.372, 0.0, 0.0 });
    t_right_doubles_sideline.add_to_apply(right_doubles_sideline);
    t_right_doubles_sideline.make_apply();

    std::shared_ptr<scenario::object::Object> after_baseline = get_cube(material_white, 10.974, 7.62/100, 0.001);
    scenario::object::Transformation t_after_baseline;

    t_after_baseline.add_translation(-after_baseline->get_vertice(2)->get_coordinates());
    t_after_baseline.add_translation(core::util::Vector3 { 0.0, 23.77, 0.0 });
    t_after_baseline.add_to_apply(after_baseline);
    t_after_baseline.make_apply();

    std::shared_ptr<scenario::object::Object> after_service_line = get_cube(material_white, 8.23, 7.62/100, 0.001);
    scenario::object::Transformation t_after_service_line;

    t_after_service_line.add_translation(-after_service_line->get_vertice(2)->get_coordinates());
    t_after_service_line.add_translation(core::util::Vector3 { 1.372, 23.77/2 + 6.4, 0.0 });
    t_after_service_line.add_to_apply(after_service_line);
    t_after_service_line.make_apply();

    //NET

    std::shared_ptr<scenario::object::Object> left_support_net = get_cube(material_white, 0.114, 0.1, 0.91);
    scenario::object::Transformation t_left_support_net;

    t_left_support_net.add_translation(-left_support_net->get_vertice(0)->get_coordinates());
    t_left_support_net.add_translation(core::util::Vector3 { -0.914, 23.77/2, 0.0 });
    t_left_support_net.add_to_apply(left_support_net);
    t_left_support_net.make_apply();

    std::shared_ptr<scenario::object::Object> above_support_net = get_cube(material_white, 0.914 + 10.974 + 0.914, 0.1, 0.11);
    scenario::object::Transformation t_above_support_net;

    t_above_support_net.add_translation(-above_support_net->get_vertice(0)->get_coordinates());
    t_above_support_net.add_translation(core::util::Vector3 { -0.914, 23.77/2, 0.80 });
    t_above_support_net.add_to_apply(above_support_net);
    t_above_support_net.make_apply();

    std::shared_ptr<scenario::object::Object> net_lines[4];

    #pragma omp parallel for
    for (int i = 0; i < 4; i++) {
        std::shared_ptr<scenario::object::Object> net_line = get_cube(material_black, (0.914-0.114) + 10.974 + (0.914-0.114), 0.1, 0.1);
        scenario::object::Transformation t_net_line;

        t_net_line.add_translation(-net_line->get_vertice(0)->get_coordinates());
        t_net_line.add_translation(core::util::Vector3 { -0.914 + 0.114, 23.77/2, i*0.2 });
        t_net_line.add_to_apply(net_line);
        t_net_line.make_apply();

        net_lines[i] = net_line;
    }

    std::shared_ptr<scenario::object::Object> net_columns[62];

    #pragma omp parallel for
    for (int j = 0; j < 62; j++) {
        std::shared_ptr<scenario::object::Object> net_column = get_cube(material_black, 0.1, 0.1, 0.91 - 0.11);
        scenario::object::Transformation t_net_column;

        t_net_column.add_translation(-net_column->get_vertice(0)->get_coordinates());
        t_net_column.add_translation(core::util::Vector3 { -0.914 + 0.114 + 0.14 + j*0.2, 23.77/2, 0.01 });
        t_net_column.add_to_apply(net_column);
        t_net_column.make_apply();

        net_columns[j] = net_column;
    }

    std::shared_ptr<scenario::object::Object> right_support_net = get_cube(material_white, 0.114, 0.1, 0.91);
    scenario::object::Transformation t_right_support_net;

    t_right_support_net.add_translation(-right_support_net->get_vertice(1)->get_coordinates());
    t_right_support_net.add_translation(core::util::Vector3 { 10.974+0.914, 23.77/2, 0.0 });
    t_right_support_net.add_to_apply(right_support_net);
    t_right_support_net.make_apply();

    std::shared_ptr<scenario::object::Object> before_service_line = get_cube(material_white, 8.23, 7.62/100, 0.001);
    scenario::object::Transformation t_before_service_line;

    t_before_service_line.add_translation(-before_service_line->get_vertice(2)->get_coordinates());
    t_before_service_line.add_translation(core::util::Vector3 { 1.372, 23.77/2 - 6.4, 0.0 });
    t_before_service_line.add_to_apply(before_service_line);
    t_before_service_line.make_apply();

    std::shared_ptr<scenario::object::Object> before_baseline = get_cube(material_white, 10.974, 7.62/100, 0.001);
    scenario::object::Transformation t_before_baseline;

    t_before_baseline.add_translation(-before_baseline->get_vertice(0)->get_coordinates());
    t_before_baseline.add_to_apply(before_baseline);
    t_before_baseline.make_apply();

    core::util::Vector3 pos { 10.0, 10.0, -5.0 };

    render::raycasting::Color cor { 0.5, 0.5, 0.5 };

    std::unique_ptr<scenario::light::Light> amb_l;

    amb_l.reset(new scenario::light::PunctualLight { pos, cor });

    std::unique_ptr<scenario::light::Light> pl_left_before;
    pl_left_before.reset(new scenario::light::PunctualLight { core::util::Vector3 { -5.0, -5.0, 15.0 } , render::raycasting::Color { 0.25, 0.25, 0.25 } });

    std::unique_ptr<scenario::light::Light> pl_right_before;
    pl_right_before.reset(new scenario::light::PunctualLight { core::util::Vector3 { 10.974 + 5.0, -5.0, 15.0 } , render::raycasting::Color { 0.25, 0.25, 0.25 } });

    std::unique_ptr<scenario::light::Light> pl_left_after;
    pl_left_after.reset(new scenario::light::PunctualLight { core::util::Vector3 { -5.0, 23.77 + 5.0, 15.0 } , render::raycasting::Color { 0.25, 0.25, 0.25 } });

    std::unique_ptr<scenario::light::Light> pl_right_after;
    pl_right_after.reset(new scenario::light::PunctualLight { core::util::Vector3 { 10.974 + 5.0, 23.77 + 5.0, 15.0 } , render::raycasting::Color { 0.25, 0.25, 0.25 } });

    scenario::Scenario sc { amb_l.get() };

    auto chair = get_chair(material_black);

    scenario::object::Transformation t_chair;

    auto center = chair->get_boundary().get_center();

    t_chair.add_translation(-center);
    t_chair.add_rotation(core::util::Vector3 { 1.0, 0.0, 0.0 }, 180);
    t_chair.add_rotation(core::util::Vector3 { 0.0, 1.0, 0.0 }, 180);
    t_chair.add_translation(core::util::Vector3 { 5.0, 5.0, 0.0 });
//    t_chair.add_scale(core::util::Vector3 { 3.0, 3.0, 3.0 });
    t_chair.add_to_apply(chair);
    t_chair.make_apply();

    std::cout << chair->get_boundary().get_radius() << std::endl;

    auto cubee = get_cube(material_black, 1.0, 1.0, 1.0);

    sc.add_object(*cubee);

    sc.add_object(*chair);

//        core::util::Vector3 eye     { center(0) - 3.0, center(1), center(2) + 5.0 };
//        core::util::Vector3 look_at { center(0), center(1) +3.0, center(2) };
//        core::util::Vector3 view_up { center(0), center(1) + 5.0, center(2) };

//                core::util::Vector3 eye     { 0, 0, -2 };
//                core::util::Vector3 look_at { center(0), center(1), center(2) };
//                core::util::Vector3 view_up { center(0), center(1) + 2.0, center(2) };

//    double d = 1.4;
//    double w = 1.0;
//    double h = 1.0;

    sc.add_object(*ground);
    sc.add_object(*court);
    sc.add_object(*left_doubles_sideline);
    sc.add_object(*left_singles_sideline);
    sc.add_object(*before_center_mark);
    sc.add_object(*center_service_line);
    sc.add_object(*after_center_mark);
    sc.add_object(*right_singles_sideline);
    sc.add_object(*right_doubles_sideline);
    sc.add_object(*before_baseline);
    sc.add_object(*after_service_line);
    sc.add_object(*left_support_net);
    sc.add_object(*above_support_net);
    for (int i = 0; i < 4; i++) sc.add_object(*net_lines[i]);
    for (int j = 0; j < 62; j++) sc.add_object(*net_columns[j]);
    sc.add_object(*right_support_net);
    sc.add_object(*before_service_line);
    sc.add_object(*after_baseline);

    sc.add_light(pl_left_before.get());
    sc.add_light(pl_right_before.get());
    sc.add_light(pl_left_after.get());
    sc.add_light(pl_right_after.get());

    //COURT'S ABOVE ok
    core::util::Vector3 eye     { 0.0, 0.0, 35.0 };
    core::util::Vector3 look_at { 0.0, 0.0,  0.0 };
    core::util::Vector3 view_up { 0.0, 5.0,     0.0 };

//    core::util::Vector3 eye     { 0, 20, 0.0 };
//    core::util::Vector3 look_at { 0.0, 0.0,  0.0 };
//    core::util::Vector3 view_up { 1, 30, 1.0 };

    //COURT'S FRONT
//    core::util::Vector3 eye     { 10.974/2, -10.0, 1.0 };
//    core::util::Vector3 look_at { 10.974/2, 23.77/2,  0.0 };
//    core::util::Vector3 view_up { 10.974/2, 23.77/2,     3.0 };

    render::raycasting::Camera cam { eye, look_at, view_up };

    double d = 1.4;
    double w = 1.0;
    double h = 1.0;

//    render::raycasting::Color bg { 101.0/255, 179.0/255, 253.0/255 };
    render::raycasting::Color bg { 1.0, 0.0, 0.0 };

    render::raycasting::RayCasting rc { d, w, h, bg };

    rc.render(cam, sc);

    auto frame = rc.get_frame_buffer();

    int n = core::constants::ROWS_PIXELS;
    int m = core::constants::COLS_PIXELS;

    QImage img = QImage(n, m, QImage::Format_RGB888);

    #pragma omp parallel for
    for(int i = 0; i < n; i++) {
        #pragma omp parallel for
        for(int j = 0; j < m; j++) {
            render::raycasting::Color color = frame[i][j];
            img.setPixel(j, i, qRgb(color.get_r(), color.get_g(), color.get_b()));
        }
    }

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(QPixmap::fromImage(img));

    ui->graphics_view->setScene(scene);
    ui->graphics_view->show();
}
