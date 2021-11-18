#define _CRT_SECURE_NO_WARNINGS
#include <bangtal>
#include <cstdlib>
#include <ctime>
using namespace bangtal;

ObjectPtr rule[6], start[6];
int choose_index(ObjectPtr o) {
    for (int i = 0;i < 6;i++) {
        if (rule[i] == o) return i;
        else if (start[i] == o) return i;
    }
    return -1;
}

int main()
{
    //게임 화면, 게임 선택장면 미리 생성
    auto  practice_scene = Scene::create("", "Images/prac_back.png");
    ScenePtr prac[6], challege[6];
    for (int i = 0;i < 6;i++) {
        if (i == 3) prac[i]= Scene::create("", "Images/배경1.png");
        else if(i==5) prac[i]= Scene::create("", "Images/배경.png");
        else prac[i] = Scene::create("", "Images/임시 배경.png");
    }

    //처음화면 생성
    auto main_scene = Scene::create("", "Images/main_background.png");
    auto challenge_button = Object::create("Images/challenge.png",main_scene,250,150);
    auto practice_button = Object::create("Images/practice.png", main_scene, 750, 150);
    practice_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        practice_scene->enter();
        return true;
        });    
    auto off= Object::create("Images/on-off.png", main_scene,1150, 600);
    off->setScale(0.2f);
    off->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        endGame();
        return true;
        });
    auto info = Object::create("Images/info.png", main_scene, 1150, 50);
    //연습모드 화면
    auto back = Object::create("Images/left-arrow.png", practice_scene, 50, 650);
    back->setScale(0.1f);
    back->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        main_scene->enter();
        return true;
        });
    for (int i = 0;i < 6;i++) {
        rule[i] = Object::create("Images/game_rule.png", practice_scene, 150+355*(i%3), 400-260*(i/3));
        start[i]= Object::create("Images/game_start.png", practice_scene, 250+ 355 * (i % 3), 400 - 260 * (i / 3));
        rule[i]->setScale(0.8f), start[i]->setScale(0.8f);
        rule[i]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
            int num = choose_index(object);
            printf("%d\n", num);
            return true;
            });
        start[i]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
            int num = choose_index(object);
            prac[num]->enter();
            return true;
            });
    }

    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
    startGame(main_scene);
}

