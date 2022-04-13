#include "raylib.h"

#include <vector>
#include <memory>
#include <iostream>

#include <glm/glm.hpp>

#include "raymath.h"

#include "kaliatech-pather-lib/Map.h"
#include "kaliatech-pather-lib/Obstacle.h"
#include "kaliatech-pather-lib/Path.h"
#include "kaliatech-pather-lib/PathFinder.h"
#include "kaliatech-pather-lib/Seeker.h"
#include "kaliatech-pather-lib/MapFileUtils.h"

using namespace kpath;

class Scenario {
public:
    Seeker seeker;
    Target target;
    std::unique_ptr<Map> map;
};

Scenario* setup_senario2(int argc, char *argv[]) {

    if (argc < 2) {
        std::cout << "Usage: KaliatechPatherAppGui <map-file>" << std::endl;
        std::cerr << "Missing map-file argument" << std::endl;
        throw std::exception("Missing arguments.");
    }

    std::string mapFilePath = argv[1];
    std::unique_ptr<kpath::Map> map;
    try {
        map = kpath::MapFileUtils::load(mapFilePath);
    }
    catch (const std::exception &e) {
        std::cerr << "Error loading map. Message: " << e.what();
        throw std::exception("Unable to load map.");
    }

    return new Scenario{
            .seeker = Seeker(300, 300, 10),
            .target = Target(450, 450, 10),
            .map = std::move(map)
    };
}

Scenario* setup_senario1() {
    Scenario*  s = new Scenario{
            .seeker = Seeker(0, 0, 1),
            .target = Target(500, 500, 1)
    };

    std::vector<Obstacle> obstacles;
//    obstacles.emplace_back(Obstacle(100, 100, 50));
//    obstacles.emplace_back(Obstacle(120, 222, 50));
//    obstacles.emplace_back(Obstacle(400, 250, 15));
//    obstacles.emplace_back(Obstacle(404, 300, 15));
//    obstacles.emplace_back(Obstacle(460, 460, 50));
//    obstacles.emplace_back(Obstacle(420, 440, 50));
//    obstacles.emplace_back(Obstacle(670, 200, 80));

//    obstacles.emplace_back(Obstacle("o1", 100, 100, 50));
//    obstacles.emplace_back(Obstacle("o2", 225, 200, 10));
//    obstacles.emplace_back(Obstacle("o3", 300, 300, 40));


    obstacles.emplace_back(Obstacle("o1", 150, 150, 50));
//    obstacles.emplace_back(Obstacle("o2", 250, 270, 79));
//    obstacles.emplace_back(Obstacle("o3", 400, 100, 79));
    //obstacles.emplace_back(Obstacle("o4", 50, 500, 50));
    obstacles.emplace_back(Obstacle("o4", 200, 300, 50));
    obstacles.emplace_back(Obstacle("o5", 340, 300, 50));

    s->map = std::make_unique<Map>(500, 500, obstacles);
    return s;
}

int main(int argc, char *argv[]) {

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 500;
    const int screenHeight = 500;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "KPath Tester");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------



    std::unique_ptr<Scenario> s;
    try {
        //s = std::unique_ptr<Scenario>(setup_senario1());
        s = std::unique_ptr<Scenario>(setup_senario2(argc, argv));
    }
    catch (std::exception e) {
        return EXIT_FAILURE;
    }


    //std::vector<Circle> obstacleCircles(obstacles.begin(), obstacles.end());
    //std::vector<Path> paths = buildPaths(seeker, target, obstacles);

    kpath::PathFinder pathFinder;
    PathSequence pSequence = pathFinder.find(*s->map, s->seeker, s->target);
    if (pSequence.getPaths().empty()) {
        std::cout << "NO PATH FOUND" << std::endl;
    } else {
        std::cout << "PATH SEGMENTS:" << pSequence.getPaths().size() << std::endl;
    }

    Image deathStarImg = LoadImage("assets/deathstar.png");
    Texture2D deathStarTexture = LoadTextureFromImage(
            deathStarImg);      // Image converted to texture, uploaded to GPU memory (VRAM)
    UnloadImage(deathStarImg);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        int winW = GetScreenWidth();
        int winH = GetScreenHeight();

        int mapW = s->map->getWidth();
        int mapH = s->map->getHeight();
        float scaleW = (float) winW / s->map->getWidth();
        float scaleH = (float) winH / s->map->getHeight();
        float scale = scaleW < scaleH ? scaleW : scaleH;

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        for (auto ob: s->map->getObstacles()) {
            Vector2 l = {ob.x, ob.y};
            l = Vector2Scale(l, scale);

            DrawTexturePro(deathStarTexture,
                           Rectangle{0, 0, (float) deathStarTexture.width, (float) deathStarTexture.height},
                           Rectangle{l.x - ob.r * scale,
                                     l.y - ob.r * scale,
                                     ob.r * 2 * scale,
                                     ob.r * 2 * scale},
                           Vector2{0, 0},
                           0,
                           WHITE);
        }

        bool DRAW_OBSTACLE_BITTANGENTS = true;
        bool DRAW_SEEKER_PATHS = true;
        bool DRAW_OBSTACLE_PATHS = true;
        bool DRAW_ARC_PATHS = true;
        bool DRAW_PATH = true;

        // Draw seeker paths
        if (DRAW_SEEKER_PATHS) {
            std::vector<std::shared_ptr<Path>> paths = pathFinder.getSeekerPaths();
            for (auto p: paths) {
                glm::mat2x4 AB = p->AB() * scale;
                DrawLineEx(Vector2{AB[0].x, AB[0].y}, Vector2{AB[1].x, AB[1].y}, 2, RED);
            }
        }

        // Draw obstacle paths
        if (DRAW_OBSTACLE_PATHS) {
            for (auto const&[key, val]: pathFinder.getStartObjPaths()) {
                for (const auto &path: val) {
                    glm::mat2x4 AB = path->AB() * scale;
                    DrawLineEx(Vector2{AB[0].x, AB[0].y}, Vector2{AB[1].x, AB[1].y}, 2, RED);
                }

            }
        }

        // Draw arc paths
        if (DRAW_ARC_PATHS) {
            std::vector<std::shared_ptr<Path>> paths = pathFinder.getArcPaths();
            for (auto p: paths) {
                glm::mat2x4 AB = p->AB() * scale;
                DrawLineEx(Vector2{AB[0].x, AB[0].y}, Vector2{AB[1].x, AB[1].y}, 2, GREEN);
//                DrawLineBezier(Vector2{AB[0].x, AB[0].y}, Vector2{AB[1].x, AB[1].y}, 2, RED );
//
                vec2 center = p->center * scale;
                float radius = p->arcRadius * scale;
                int segments = (int) p->length() / 2;
                DrawCircle((int) center.x, (int) center.y, radius / 10, RED);
                //DrawCircleSectorLines(Vector2{center.x,center.y}, radius, RAD2DEG*p->AngleB(), RAD2DEG*p->AngleA(), segments, GREEN);
                //DrawCircleSector(Vector2{center.x,center.y}, radius, 180 - RAD2DEG*p->AngleA(), 180 - RAD2DEG*p->AngleB() , segments, RED);
                //DrawCircleSector(Vector2{center.x,center.y}, radius, 180 - 0, 180 - 45 , segments, RED);
                //DrawCircleSector(Vector2{center.x,center.y}, radius, 180 - RAD2DEG*p->AngleA(), 180 - RAD2DEG*p->AngleB() , segments, RED);
//                DrawCircleSector(Vector2{center.x,center.y}, radius, RAD2DEG*p->AngleA(), RAD2DEG*p->AngleB(), segments, RED);
//                std::cout << RAD2DEG*p->AngleA() << std::endl;
//                std::cout << RAD2DEG*p->AngleB() << std::endl;

//                std::cout << p->AngleA() << std::endl;
//                std::cout << p->AngleB() << std::endl;

            }
//            vec2 A(10.0,10.0);
//            vec2 B(200.0,200.0);
//            vec2 center(0.0,0.0);
//            float radius = 10.0;
//            Path testP("id", A, B, center, radius);
//            std::cout << "P:" << testP.toString() << std::endl;
//            std::cout << "A:" << RAD2DEG*testP.AngleA() << std::endl;
//            std::cout << "B:" << RAD2DEG*testP.AngleB() << std::endl;
        }

        if (DRAW_PATH) {
            for (auto p: pSequence.getPaths()) {
                glm::mat2x4 AB = p->AB() * scale;
                DrawLineEx(Vector2{AB[0].x, AB[0].y}, Vector2{AB[1].x, AB[1].y}, 2, BLUE);
            }
        }

        DrawCircle((int) (s->seeker.x * scale), (int) (s->seeker.y * scale), s->seeker.r * scale, RED);
        DrawCircle((int) (s->target.x * scale), (int) (s->target.y * scale), s->target.r * scale, GREEN);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return EXIT_SUCCESS;
}
