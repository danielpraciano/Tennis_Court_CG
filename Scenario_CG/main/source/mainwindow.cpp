#include "main/include/mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <scenario/include/object/transformation.h>
#include <scenario/include/scenario.h>
#include <scenario/include/object/vertex.h>
#include <scenario/include/object/face.h>
#include <scenario/include/object/object.h>
#include <scenario/include/light/light.h>
#include <scenario/include/light/punctual_light.h>
#include <scenario/include/light/spot_light.h>
#include <scenario/include/object/material.h>
#include <render/include/raycasting/camera.h>
#include <render/include/raycasting/color.h>
#include <render/include/raycasting/ray.h>
#include <render/include/raycasting/ray_casting.h>
#include <render/include/raycasting/projection_type.h>

#include <scenario/include/object/texture.h>

#include <core/include/io_module.h>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
}

MainWindow::~MainWindow() {
    delete ui;
    delete scene;
}

//std::shared_ptr<scenario::object::Object> get_cube(std::shared_ptr<scenario::object::Material> mat, double x, double y, double z) {
//    std::shared_ptr<scenario::object::Object> cube { new scenario::object::Object { mat } };

//    cube->add_vertex(scenario::object::Vertex { 0.0, 0.0, 0.0 }); //0
//    cube->add_vertex(scenario::object::Vertex { 1.0, 0.0, 0.0 }); //1
//    cube->add_vertex(scenario::object::Vertex { 0.0, 1.0, 0.0 }); //2
//    cube->add_vertex(scenario::object::Vertex { 1.0, 1.0, 0.0 }); //3
//    cube->add_vertex(scenario::object::Vertex { 0.0, 0.0, 1.0 }); //4
//    cube->add_vertex(scenario::object::Vertex { 1.0, 0.0, 1.0 }); //5
//    cube->add_vertex(scenario::object::Vertex { 0.0, 1.0, 1.0 }); //6
//    cube->add_vertex(scenario::object::Vertex { 1.0, 1.0, 1.0 }); //7

//    //trás
//    cube->add_face(0, 3, 1);
//    cube->add_face(0, 2, 3);

//    //direita
//    cube->add_face(1, 7, 5);
//    cube->add_face(1, 3, 7);

//    //frente
//    cube->add_face(4, 5, 7);
//    cube->add_face(4, 7, 6);

//    //esquerda
//    cube->add_face(0, 4, 6);
//    cube->add_face(0, 6, 2);

//    //baixo
//    cube->add_face(0, 1, 5);
//    cube->add_face(0, 5, 4);

//    //cima
//    cube->add_face(2, 6, 7);
//    cube->add_face(2, 7, 3);

//    scenario::object::Transformation t_resize;

//    t_resize.add_translation(core::util::Vector3 {-0.5, -0.5, -0.5});
//    t_resize.add_scale(core::util::Vector3 { x, y, z });
//    t_resize.add_to_apply(cube);
//    t_resize.make_apply();

//    return cube;
//}

uint64_t count_cube = 0;

std::shared_ptr<scenario::object::Object> get_cube(std::shared_ptr<scenario::object::Material> mat, double x, double y, double z, scenario::object::Texture *tex = nullptr) {
    count_cube++;

    auto cube = std::make_shared<scenario::object::Object>(mat);

    cube->add_vertex(scenario::object::Vertex { 0.0, 0.0, 0.0 }); //0
    cube->add_vertex(scenario::object::Vertex { 1.0, 0.0, 0.0 }); //1
    cube->add_vertex(scenario::object::Vertex { 0.0, 1.0, 0.0 }); //2
    cube->add_vertex(scenario::object::Vertex { 1.0, 1.0, 0.0 }); //3
    cube->add_vertex(scenario::object::Vertex { 0.0, 0.0, 1.0 }); //4
    cube->add_vertex(scenario::object::Vertex { 1.0, 0.0, 1.0 }); //5
    cube->add_vertex(scenario::object::Vertex { 0.0, 1.0, 1.0 }); //6
    cube->add_vertex(scenario::object::Vertex { 1.0, 1.0, 1.0 }); //7

//    if (tex != nullptr) {
//        //trás
//        cube->add_face(0, 3, 1, mat, 2, 0, 3, tex);
//        cube->add_face(0, 2, 3, mat, 2, 0, 3, tex);

//        //direita
//        cube->add_face(1, 7, 5, mat, 0, 1, 7, tex);
//        cube->add_face(1, 3, 7, mat, 0, 1, 7, tex);

//        //frente
//        cube->add_face(4, 5, 7, mat, 2, 4, 7, tex);
//        cube->add_face(4, 7, 6, mat, 2, 4, 7, tex);

//        //esquerda
//        cube->add_face(0, 4, 6, mat, 0, 0, 6, tex);
//        cube->add_face(0, 6, 2, mat, 0, 0, 6, tex);

//        //baixo
//        cube->add_face(0, 1, 5, mat, 1, 0, 5, tex);
//        cube->add_face(0, 5, 4, mat, 1, 0, 5, tex);

//        //cima
//        cube->add_face(2, 6, 7, mat, 1, 2, 7, tex);
//        cube->add_face(2, 7, 3, mat, 1, 2, 7, tex);
    if (tex != nullptr) {
        //trás
        cube->add_face(0, 3, 1, mat, 2, 1, 3, tex);
        cube->add_face(0, 2, 3, mat, 2, 1, 3, tex);

        //direita
        cube->add_face(1, 7, 5, mat, 0, 5, 7, tex);
        cube->add_face(1, 3, 7, mat, 0, 5, 7, tex);

        //frente
        cube->add_face(4, 5, 7, mat, 2, 4, 7, tex);
        cube->add_face(4, 7, 6, mat, 2, 4, 7, tex);

        //esquerda
        cube->add_face(0, 4, 6, mat, 0, 0, 6, tex);
        cube->add_face(0, 6, 2, mat, 0, 0, 6, tex);

        //baixo
        cube->add_face(0, 1, 5, mat, 1, 4, 5, tex);
        cube->add_face(0, 5, 4, mat, 1, 4, 5, tex);

        //cima
        cube->add_face(2, 6, 7, mat, 1, 3, 7, tex);
        cube->add_face(2, 7, 3, mat, 1, 3, 7, tex);
    } else {
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
    }

    scenario::object::Transformation t_resize;

    t_resize.add_translation(core::util::Vector3 {-0.5, -0.5, -0.5});
    t_resize.add_scale(core::util::Vector3 { x, y, z });
    t_resize.add_to_apply(cube);
    t_resize.make_apply();

    return cube;
}

void add_umpire_chair(scenario::Scenario &sc, std::shared_ptr<scenario::object::Material> mat, core::util::Vector3 position, double scale = 1.0) {
    scenario::object::Transformation t_translate;
    t_translate.add_translation(position);

    std::shared_ptr<scenario::object::Object> back = get_cube(mat, scale*0.1, scale*0.46, scale*0.90);
    scenario::object::Transformation t_back;

    t_back.add_translation(-back->get_vertice(0)->get_coordinates());
    t_back.add_to_apply(back);
    t_back.make_apply();

    t_translate.add_to_apply(back);

    sc.add_object(*back);

    auto mat2 = mat;

    render::raycasting::Color color_red { 1.0, 0.0, 0.0 };
    render::raycasting::Color color_blue { 0.0, 0.0, 1.0 };
    render::raycasting::Color color_green { 0.0, 1.0, 0.0 };

    std::shared_ptr<scenario::object::Material> material_red {
    new scenario::object::Material { 100.0, color_red, color_red, color_red } };

    std::shared_ptr<scenario::object::Material> material_blue {
    new scenario::object::Material { 100.0, color_blue, color_blue, color_blue } };

    std::shared_ptr<scenario::object::Material> material_green {
    new scenario::object::Material { 100.0, color_green, color_green, color_green } };


    for (int i = 0; i < 3; ++i) {

        if ( i == 1)
            mat = material_red;
        if( i == 2)
            mat = material_blue;

        std::shared_ptr<scenario::object::Object> seat = get_cube(mat, scale*0.50 - i*0.4, scale*0.46, scale*0.2);
        scenario::object::Transformation t_seat;

        t_seat.add_translation(-seat->get_vertice(0)->get_coordinates());
        t_seat.add_translation(core::util::Vector3 { 0.0, 0.0, scale*i*0.2 });
        t_seat.add_to_apply(seat);
        t_seat.make_apply();

        t_translate.add_to_apply(seat);

        sc.add_object(*seat);
    }

        mat = material_green;

    std::shared_ptr<scenario::object::Object> seat = get_cube(mat, scale*0.23, scale*0.46, scale*0.01);
    scenario::object::Transformation t_seat;

    t_seat.add_translation(-seat->get_vertice(0)->get_coordinates());
    t_seat.add_translation(core::util::Vector3 { 0.0, 0.0, scale*0.65 });
    t_seat.add_to_apply(seat);
    t_seat.make_apply();

    t_translate.add_to_apply(seat);

    sc.add_object(*seat);
 mat = mat2;
    std::shared_ptr<scenario::object::Object> left_side = get_cube(mat, scale*0.51, scale*0.1, scale*0.90);
    scenario::object::Transformation t_left_side;

    t_left_side.add_translation(-left_side->get_vertice(0)->get_coordinates());
    t_left_side.add_translation(core::util::Vector3 { 0.0, scale*0.46, 0.0 });
    t_left_side.add_to_apply(left_side);
    t_left_side.make_apply();

    t_translate.add_to_apply(left_side);

    sc.add_object(*left_side);

    std::shared_ptr<scenario::object::Object> right_side = get_cube(mat, scale*0.51, scale*0.1, scale*0.90);
    scenario::object::Transformation t_right_side;

    t_right_side.add_translation(-right_side->get_vertice(0)->get_coordinates());
    t_right_side.add_to_apply(right_side);
    t_right_side.make_apply();

    t_translate.add_to_apply(right_side);

    sc.add_object(*right_side);

    t_translate.make_apply();

}

void add_chair(scenario::Scenario &sc, std::shared_ptr<scenario::object::Material> mat, core::util::Vector3 position, double scale = 1.0) {
    scenario::object::Transformation t_translate;
    t_translate.add_translation(position);

    std::shared_ptr<scenario::object::Object> back = get_cube(mat, scale*0.1, scale*0.46, scale*0.81);
    scenario::object::Transformation t_back;

    t_back.add_translation(-back->get_vertice(0)->get_coordinates());
    t_back.add_to_apply(back);
    t_back.make_apply();

    t_translate.add_to_apply(back);

    sc.add_object(*back);

    std::shared_ptr<scenario::object::Object> seat = get_cube(mat, scale*0.50, scale*0.46, scale*0.1);
    scenario::object::Transformation t_seat;

    t_seat.add_translation(-seat->get_vertice(0)->get_coordinates());
    t_seat.add_translation(core::util::Vector3 { 0.0, 0.0, scale*0.25 });
    t_seat.add_to_apply(seat);
    t_seat.make_apply();

    t_translate.add_to_apply(seat);

    sc.add_object(*seat);

    std::shared_ptr<scenario::object::Object> left_side = get_cube(mat, scale*0.51, scale*0.1, scale*0.81);
    scenario::object::Transformation t_left_side;

    t_left_side.add_translation(-left_side->get_vertice(0)->get_coordinates());
    t_left_side.add_translation(core::util::Vector3 { 0.0, scale*0.46, 0.0 });
    t_left_side.add_to_apply(left_side);
    t_left_side.make_apply();

    t_translate.add_to_apply(left_side);

    sc.add_object(*left_side);

    std::shared_ptr<scenario::object::Object> right_side = get_cube(mat, scale*0.51, scale*0.1, scale*0.81);
    scenario::object::Transformation t_right_side;

    t_right_side.add_translation(-right_side->get_vertice(0)->get_coordinates());
    t_right_side.add_to_apply(right_side);
    t_right_side.make_apply();

    t_translate.add_to_apply(right_side);

    sc.add_object(*right_side);

    t_translate.make_apply();

}

void add_floodlight(scenario::Scenario &sc, std::shared_ptr<scenario::object::Material> mat, core::util::Vector3 position, bool in_right, double scale = 1.0) {
    scenario::object::Transformation t_translate;
    t_translate.add_translation(position);

    std::shared_ptr<scenario::object::Object> rod = get_cube(mat, scale*0.1, scale*0.1, scale*5.0);
    scenario::object::Transformation t_rod;

    if (in_right)
        t_rod.add_translation(-rod->get_vertice(0)->get_coordinates());
    else
        t_rod.add_translation(-rod->get_vertice(1)->get_coordinates());

    t_rod.add_to_apply(rod);
    t_rod.make_apply();

    t_translate.add_to_apply(rod);

    sc.add_object(*rod);

    std::shared_ptr<scenario::object::Object> light = get_cube(mat, scale*0.3, scale*0.1, scale*0.1);
    scenario::object::Transformation t_light;

    if (in_right)
        t_light.add_translation(-light->get_vertice(0)->get_coordinates());
    else
        t_light.add_translation(-light->get_vertice(1)->get_coordinates());

    t_light.add_translation(core::util::Vector3 { 0.0, 0.0, scale*5.0 });
    t_light.add_to_apply(light);
    t_light.make_apply();

    t_translate.add_to_apply(light);

    sc.add_object(*light);

    t_translate.make_apply();

}

void MainWindow::on_rc_button_clicked() {
//    scenario::object::Texture *tex = new scenario::object::Texture { "/home/daniel/Textura_Court/491830606.jpg" };
//    scenario::object::Texture *tex = new scenario::object::Texture { "/home/daniel/Textura_Court/179023303.jpg" };
//    scenario::object::Texture *tex = new scenario::object::Texture { "/home/daniel/Textura_Court/clay2.jpg" };

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

//    render::raycasting::Color k_a_ground { 196.0/255, 102.0/255, 70.0/255 };
//    render::raycasting::Color k_d_ground { 196.0/255, 102.0/255, 70.0/255 };
//    render::raycasting::Color k_s_ground { 196.0/255, 102.0/255, 70.0/255 };

    std::shared_ptr<scenario::object::Material> material_ground {
    new scenario::object::Material { 1.0, k_a_ground, k_d_ground, k_s_ground } };

    //azulado
    render::raycasting::Color k_a_court { 69.0/255, 114.0/255, 172.0/255 };
    render::raycasting::Color k_d_court { 69.0/255, 114.0/255, 172.0/255 };
    render::raycasting::Color k_s_court { 69.0/255, 114.0/255, 172.0/255 };

//    render::raycasting::Color k_a_court { 196.0/255, 102.0/255, 70.0/255 };
//    render::raycasting::Color k_d_court { 196.0/255, 102.0/255, 70.0/255 };
//    render::raycasting::Color k_s_court { 196.0/255, 102.0/255, 70.0/255 };

    //green
//    render::raycasting::Color k_a_court { 76.0/255, 153.0/255, 0.0/255 };
//    render::raycasting::Color k_d_court { 76.0/255, 153.0/255, 0.0/255 };
//    render::raycasting::Color k_s_court { 76.0/255, 153.0/255, 0.0/255 };

    std::shared_ptr<scenario::object::Material> material_court {
    new scenario::object::Material { 1.0, k_a_court, k_d_court, k_s_court } };

    render::raycasting::Color k_a_wood { 130.0/255, 82.0/255, 1.0/255 };
    render::raycasting::Color k_d_wood { 130.0/255, 82.0/255, 1.0/255 };
    render::raycasting::Color k_s_wood { 130.0/255, 82.0/255, 1.0/255 };

    std::shared_ptr<scenario::object::Material> material_wood {
    new scenario::object::Material { 1.0, k_a_wood, k_d_wood, k_s_wood } };

    std::shared_ptr<scenario::object::Material> material_red {
    new scenario::object::Material { 1.0, color_red, color_red, color_red } };

    std::shared_ptr<scenario::object::Material> material_blue {
    new scenario::object::Material { 1.0, color_blue, color_blue, color_blue } };

    std::shared_ptr<scenario::object::Material> material_green {
    new scenario::object::Material { 1.0, color_green, color_green, color_green } };

    std::shared_ptr<scenario::object::Material> material_white {
    new scenario::object::Material { 1.0, color_white, color_white, color_white } };

    std::shared_ptr<scenario::object::Material> material_black {
    new scenario::object::Material { 1.0, color_black, color_black, color_black } };

    std::shared_ptr<scenario::object::Material> material_yellow {
    new scenario::object::Material { 1.0, color_yellow, color_yellow, color_yellow } };

    std::shared_ptr<scenario::object::Material> material_orange {
    new scenario::object::Material { 1.0, color_orange, color_orange, color_orange } };

    //

    std::shared_ptr<scenario::object::Object> ground = get_cube(material_ground, 4 * 10.974, 2 * 23.77, 0.001);
    scenario::object::Transformation t_ground;

    t_ground.add_translation(-ground->get_vertice(0)->get_coordinates());
    t_ground.add_translation(core::util::Vector3 { -10.974*1.5, -23.77/2, -0.002 });
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
//    std::cout << -left_doubles_sideline->get_vertice(0)->get_coordinates() << std::endl;
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
    for (int i = 0; i < 4; ++i) {
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
    for (int j = 0; j < 62; ++j) {
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

//    auto cubee = get_cube(material_court, 3.0, 3.0, 3.0, tex);
//    auto cubee = get_cube(material_ground, 100.0, 0.1, 100.0);

//        scenario::object::Transformation t_cube;

//        t_cube.add_translation(-cubee->get_vertice(0)->get_coordinates());
////        t_cube.add_translation(core::util::Vector3 { 5.0, 0.0, 0.0 });
////        t_cube.add_translation(core::util::Vector3 { 10.974/2-2, 23.77/2-4, 3.0 });
//        t_cube.add_to_apply(cubee);
//        t_cube.make_apply();

//        auto cubee2 = get_cube(material_court, 1.0, 3.0, 1.0);

//            scenario::object::Transformation t_cube2;

//            t_cube2.add_translation(-cubee2->get_vertice(0)->get_coordinates());
//            t_cube2.add_translation(core::util::Vector3 { 50.0, 0.0, 50.0 });
//    //        t_cube.add_translation(core::util::Vector3 { 5.0, 0.0, 0.0 });
//    //        t_cube.add_translation(core::util::Vector3 { 10.974/2-2, 23.77/2-4, 3.0 });
//            t_cube2.add_to_apply(cubee2);
//            t_cube2.make_apply();

    std::unique_ptr<scenario::light::Light> ambient_light { new scenario::light::PunctualLight { core::util::Vector3 { 0.0, 0.0, 0.0 },
                    render::raycasting::Color { 0.5, 0.5, 0.5 } } };

//    std::unique_ptr<scenario::light::Light> pl_left_before;
////    pl_left_before.reset(new scenario::light::PunctualLight { core::util::Vector3 { 50.5, 5.0, 50.5 } , render::raycasting::Color { 1.0, 1.0, 1.0 } });
//    pl_left_before.reset(new scenario::light::PunctualLight { core::util::Vector3 { -5.0, -5.0, 15.0 } , render::raycasting::Color { 0.25, 0.25, 0.25 } });
////    pl_left_before.reset(new scenario::light::PunctualLight { core::util::Vector3 { 10.0, 0.0, 10.0 } , render::raycasting::Color { 0.7, 0.7, 0.7 } });

//    std::unique_ptr<scenario::light::Light> pl_right_before;
//    pl_right_before.reset(new scenario::light::PunctualLight { core::util::Vector3 { 10.974 + 5.0, -5.0, 15.0 } , render::raycasting::Color { 0.25, 0.25, 0.25 } });

//    std::unique_ptr<scenario::light::Light> pl_left_after;
//    pl_left_after.reset(new scenario::light::PunctualLight { core::util::Vector3 { -5.0, 23.77 + 5.0, 15.0 } , render::raycasting::Color { 0.25, 0.25, 0.25 } });

//    std::unique_ptr<scenario::light::Light> pl_right_after;
//    pl_right_after.reset(new scenario::light::PunctualLight { core::util::Vector3 { 10.974 + 5.0, 23.77 + 5.0, 15.0 } , render::raycasting::Color { 0.25, 0.25, 0.25 } });

    std::unique_ptr<scenario::light::Light> sl_left_before;
    sl_left_before.reset(new scenario::light::SpotLight { core::util::Vector3 { 0.0000 - 5.0, 0.000 - 3.0, 10.0 } ,
                                                          core::util::Vector3 {10.974/4, 23.77/4, 0.0}, 30.0,
                                                          render::raycasting::Color { 1.00, 1.00, 1.00 } });

    std::unique_ptr<scenario::light::Light> sl_right_before;
    sl_right_before.reset(new scenario::light::SpotLight { core::util::Vector3 { 10.974 + 5.0, 0.000 - 3.0, 10.0 } ,
                                                           core::util::Vector3 { 10.974/2 + 10.974/4, 23.77/4, 0.0 }, 30.0,
                                                           render::raycasting::Color { 1.00, 1.00, 1.00 } });

    std::unique_ptr<scenario::light::Light> sl_left_after;
    sl_left_after.reset(new scenario::light::SpotLight { core::util::Vector3 { 0.0000 - 5.0, 23.77 + 3.0, 10.0 } ,
                                                         core::util::Vector3 { 10.974/4, 23.77/2 + 23.77/4, 0.0 }, 30.0,
                                                         render::raycasting::Color { 1.00, 1.00, 1.00 } });

    std::unique_ptr<scenario::light::Light> sl_right_after;
    sl_right_after.reset(new scenario::light::SpotLight { core::util::Vector3 { 10.974 + 5.0, 23.77 + 3.0, 10.0 } ,
                                                          core::util::Vector3 { 10.974/2 + 10.974/4, 23.77/2 + 23.77/4, 0.0 }, 30.0,
                                                          render::raycasting::Color { 1.00, 1.00, 1.00 } });


    scenario::Scenario sc { ambient_light.get() };

    add_umpire_chair(sc, material_wood, core::util::Vector3 {-3.2, 23.77/2 - (3.5*0.46 / 2), 0.0}, 3.5);
//    add_umpire_chair(sc, material_court, core::util::Vector3 {0, 0, 0.0}, 1.0);
    add_chair(sc, material_wood, core::util::Vector3 {-3.0, 23.77/2 + 4.0, 0.0}, 2.5);
    add_chair(sc, material_wood, core::util::Vector3 {-3.0, 23.77/2 - 4.0, 0.0}, 2.5);
    add_floodlight(sc, material_wood, core::util::Vector3 {0.0000 - 5.0, 23.77 + 3.0, 0.0}, true,  2.0); // left after
    add_floodlight(sc, material_wood, core::util::Vector3 {10.974 + 5.0, 23.77 + 3.0, 0.0}, false, 2.0); // right after
    add_floodlight(sc, material_wood, core::util::Vector3 {0.0000 - 5.0, 0.000 - 3.0, 0.0}, true,  2.0); // left before
    add_floodlight(sc, material_wood, core::util::Vector3 {10.974 + 5.0, 0.000 - 3.0, 0.0}, false, 2.0); // right before

    for (int i = 0; i < 10; ++i) {
        std::shared_ptr<scenario::object::Object> seat = get_cube(material_wood, 5.0 - i*0.5, 23.77, 0.5);
        scenario::object::Transformation t_seat;

        t_seat.add_translation(-seat->get_vertice(0)->get_coordinates());
        t_seat.add_translation(core::util::Vector3 { -10.0, 0.0, i*0.5 });
        t_seat.add_to_apply(seat);
        t_seat.make_apply();

        sc.add_object(*seat);
    }

    for (int i = 0; i < 10; ++i) {
        std::shared_ptr<scenario::object::Object> seat = get_cube(material_wood, 5.0 - i*0.5, 23.77, 0.5);
        scenario::object::Transformation t_seat;

        t_seat.add_translation(-seat->get_vertice(1)->get_coordinates());
        t_seat.add_translation(core::util::Vector3 { 10.974 + 10.0, 0.0, i*0.5 });
        t_seat.add_to_apply(seat);
        t_seat.make_apply();

        sc.add_object(*seat);
    }

    for (int i = 0; i < 10; ++i) {
        std::shared_ptr<scenario::object::Object> seat = get_cube(material_wood, 10.974, 5.0 - i*0.5, 0.5);
        scenario::object::Transformation t_seat;

        t_seat.add_translation(-seat->get_vertice(0)->get_coordinates());
        t_seat.add_translation(core::util::Vector3 { 0.0, -8.0, i*0.5 });
        t_seat.add_to_apply(seat);
        t_seat.make_apply();

        sc.add_object(*seat);
    }

    for (int i = 0; i < 10; ++i) {
        std::shared_ptr<scenario::object::Object> seat = get_cube(material_wood, 10.974, 5.0 - i*0.5, 0.5);
        scenario::object::Transformation t_seat;

        t_seat.add_translation(-seat->get_vertice(2)->get_coordinates());
        t_seat.add_translation(core::util::Vector3 { 0.0, 23.77 + 8.0, i*0.5 });
        t_seat.add_to_apply(seat);
        t_seat.make_apply();

        sc.add_object(*seat);
    }

//    sc.add_object(*cubee);
//    sc.add_object(*cubee2);
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

//    sc.add_light(pl_left_before.get());
//    sc.add_light(pl_right_before.get());
//    sc.add_light(pl_left_after.get());
//    sc.add_light(pl_right_after.get());

    sc.add_light(sl_left_before.get());
//    sc.add_light(sl_right_before.get());
//    sc.add_light(sl_left_after.get());
//    sc.add_light(sl_right_after.get());

    //COURT'S ABOVE ok
    core::util::Vector3 eye     { 10.974/2, 23.77/2, 60.0 };
    core::util::Vector3 look_at { 10.974/2, 23.77/2,  0.0 };
    core::util::Vector3 view_up { 10.974/2, 20.0,     0.0 };

//        core::util::Vector3 eye     { 0.0, 0.0, 35.0 };
//    core::util::Vector3 look_at { 0.0, 0.0,  0.0 };
//    core::util::Vector3 view_up { 0.0, 5.0,     0.0 };

//    core::util::Vector3 eye     { 0, 20, 0.0 };
//    core::util::Vector3 look_at { 0.0, 0.0,  0.0 };
//    core::util::Vector3 view_up { 1, 30, 1.0 };

    //COURT'S FRONT
//    core::util::Vector3 eye     { 10.974/2, -10.0, 1.0 };
//    core::util::Vector3 look_at { 10.974/2, 23.77/2,  0.0 };
//    core::util::Vector3 view_up { 10.974/2, 23.77/2,     3.0 };

//        core::util::Vector3 eye     { 2.0, -100.0, 1.0 };
//        core::util::Vector3 look_at { 2.0, 4.0,  0.0 };
//        core::util::Vector3 view_up { 2.0, 4.0,  3.0 };

//            core::util::Vector3 eye     { 2.0, 0.23, 0.5 };
//            core::util::Vector3 look_at { 0.0, 0.23,  0.5 };
//            core::util::Vector3 view_up { 0.5, 1.0,  0.5 };

//    core::util::Vector3 eye     { 81.0, 81.0, 81.0 };

//    core::util::Vector3 eye     { 0.5, 0.5, 4.5 };
//    core::util::Vector3 look_at { 0.5, 0.5, 0.5 };
//    core::util::Vector3 view_up { 0.5, 4.5, 0.5 };


//    core::util::Vector3 eye     { 50.5, 4.0, 60.5 };
//    core::util::Vector3 look_at { 50.5, 0.0, 50.5 };
//    core::util::Vector3 view_up { 50.5, 20.0, 50.5 };

    render::raycasting::Camera cam { eye, look_at, view_up };

    double d = 1.4;
    double w = 1.0;
    double h = 1.0;

    render::raycasting::Color bg { 0.0/255, 0.0/255, 204.0/255 };
//    render::raycasting::Color bg { 1.0, 0.0, 0.0 };

    render::raycasting::RayCasting rc { d, w, h, bg };

    rc.render(cam, sc, render::raycasting::ProjectionType::PERSPECTIVE);

    auto frame = rc.get_frame_buffer();

    int n = core::constants::ROWS_PIXELS;
    int m = core::constants::COLS_PIXELS;

    QImage img = QImage(m, n, QImage::Format_RGB888);

    #pragma omp parallel for
    for(int i = 0; i < n; i++) {
        #pragma omp parallel for
        for(int j = 0; j < m; j++) {
            const render::raycasting::Color &color = frame[i][j];
            img.setPixel(j, i, qRgb(color.get_r(), color.get_g(), color.get_b()));
        }
    }

    scene->addPixmap(QPixmap::fromImage(img));

    ui->graphics_view->setScene(scene);
    ui->graphics_view->show();
    ui->widget->hide();

    std::cout << "Cubes: " << count_cube << std::endl;
    std::cout << "Faces: " << count_cube * 12 << std::endl;

}
