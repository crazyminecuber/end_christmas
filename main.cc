#include <iomanip>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "json.hpp" // to parse data from json file. See json.hpp for source.

#include "Game.h"
#include "Resource_manager.h"
#include "Entity.h"
#include "Tile.h"
#include "Tile_nothing.h"
#include "Tile_tower.h"
#include "Tile_enemy.h"
#include "Tile_enemy_start.h"
#include "Tile_enemy_end.h"

// #include "Tower_shop.h"
// #include "Wallet.h"
// #include "Tower.h"
// #include <vector>

using namespace std;

// using namespace sf;
//
// int const width  { 1000 };
// int const height { 800 };


void throttle(double fps, sf::Clock & clock);


int main ()
{
    std::string map_file{"map.csv"};
    sf::Vector2u window_size{1400, 800};
    int health{100};
    Game game(window_size, map_file, health);
    sf::Clock clock;

    game.load_entities("entity.json");

    while ( game.is_running() )
    {
        game.handle_input();
        game.update_logic();
        game.render();

        throttle(game.get_fps(), clock);
    }

    return 0;
}

void throttle(double fps, sf::Clock & clock)
{
    auto const target{sf::milliseconds(1000.0/fps)};
    auto wait_time{target - clock.getElapsedTime()};
    sleep(wait_time);
    clock.restart();
}

// void load_map(sf::RenderWindow const& window)
// {
//     /* prepare variables needed for reading from file */
//     std::ifstream infile{"map.csv"};
//     std::string line;
//     int num;
//     sf::Vector2i tile_index_pos(-1, -1);
//
//     /* create all tiles */
//     while ( std::getline(infile, line) )
//     {
//         tile_index_pos.x = -1;
//         std::istringstream iss{line};
//         while ( iss >> num )
//         {
//             if      ( num == -1 )
//             {
//                 ;
//             }
//             else if ( num == 0 )
//             {
//                 new Tile_nothing("resources/textures/stones.jpg", window, tile_index_pos);
//             }
//             else if ( num == 1 )
//             {
//                 new Tile_tower("resources/textures/grass.jpg", window, tile_index_pos);
//             }
//             else if ( num == 2 )
//             {
//                 new Tile_enemy("resources/textures/dirt.jpg", window, tile_index_pos);
//             }
//             else if ( num == 3 )
//             {
//                 new Tile_enemy_start("resources/textures/dirt.jpg", window, tile_index_pos);
//             }
//             else if ( num == 4 )
//             {
//                 new Tile_enemy_end("resources/textures/dirt.jpg", window, tile_index_pos);
//             }
//             else
//             {
//                 cout << "Error: tile number not specified" << endl;
//             }
//             tile_index_pos.x++;
//             iss.get();
//         }
//         tile_index_pos.y++;
//     }
//     cout << "Laddat in kartan" << endl;
//
//     /* update side_length */
//     // calculate Tile::side_length and change all tiles
//     int tiles_per_row = tile_index_pos.y  + (1 - 2);
//     int tiles_per_col = tile_index_pos.x + (1 - 2);
//     Tile::side_length = std::min(width/tiles_per_row, height/tiles_per_col);
//     for (std::map<sf::Vector2i, Tile*>::iterator it=Tile::tiles.begin(); it!=Tile::tiles.end(); ++it)
//     {
//         (*it).second->update_side_length();
//     }
//
//     /* set direction of tiles */
//     determine_tile_directions();
// }
//
// void determine_tile_directions()
// {
//     sf::Vector2i enemy_end;
//     sf::Vector2i last_tile{-100, -100}; // init so never next to enemy_end
//     sf::Vector2i current_tile;
//     sf::Vector2i next_tile;
//     sf::Vector2i direction;
//
//     /* find enemy_end tile */
//     for (std::map<sf::Vector2i, Tile*>::iterator it=Tile::tiles.begin(); it!=Tile::tiles.end(); ++it)
//     {
//         if ( is_tile_enemy_end((*it).first) )
//             enemy_end = (*it).second->get_index_position();
//     }
//     cout << "Tile_enemy_end at: (" << enemy_end.x << ", " << enemy_end.y << ")" << endl;
//     current_tile = enemy_end;
//
//     /* loop through enemy path backwards and set set direction of tile */
//     while ( !(is_tile_enemy_start(current_tile)) )
//     {
//         /* if (tile exists) and (tile is enemy) and (tile is not last tile) */
//         // look up
//         if ( Tile::tiles.find(current_tile + sf::Vector2i{0, -1})  !=
//                 Tile::tiles.end()                                  &&
//              is_tile_enemy(  (current_tile + sf::Vector2i{0, -1})) &&
//              last_tile !=    (current_tile + sf::Vector2i{0, -1})     )
//         {
//             next_tile = current_tile + sf::Vector2i{0, -1};
//         }
//         // look right
//         if ( Tile::tiles.find(current_tile + sf::Vector2i{1, 0})  !=
//                 Tile::tiles.end()                                 &&
//              is_tile_enemy(  (current_tile + sf::Vector2i{1, 0})) &&
//              last_tile !=    (current_tile + sf::Vector2i{1, 0})     )
//         {
//             next_tile = current_tile + sf::Vector2i{1, 0};
//         }
//         // look down
//         if ( Tile::tiles.find(current_tile + sf::Vector2i{0, 1})  !=
//                 Tile::tiles.end()                                 &&
//              is_tile_enemy(  (current_tile + sf::Vector2i{0, 1})) &&
//              last_tile !=    (current_tile + sf::Vector2i{0, 1})     )
//         {
//             next_tile = current_tile + sf::Vector2i{0, 1};
//         }
//         // look left
//         if ( Tile::tiles.find(current_tile + sf::Vector2i{-1, 0})  !=
//                 Tile::tiles.end()                                  &&
//              is_tile_enemy(  (current_tile + sf::Vector2i{-1, 0})) &&
//              last_tile !=    (current_tile + sf::Vector2i{-1, 0})     )
//         {
//             next_tile = current_tile + sf::Vector2i{-1, 0};
//         }
//
//         // prepare for next iteration
//         last_tile = current_tile;
//         current_tile = next_tile;
//
//         // set direction
//         direction = last_tile - current_tile;
//         Tile::get_tile_by_index(current_tile)->set_direction(direction);
//     }
// }
//
// bool is_tile_enemy(sf::Vector2i index)
// {
//     return  ( !(dynamic_cast<Tile_enemy*>
//                 (Tile::get_tile_by_index(index)) == nullptr) );
// }
//
// bool is_tile_enemy_start(sf::Vector2i index)
// {
//     return  ( !(dynamic_cast<Tile_enemy_start*>
//                 (Tile::get_tile_by_index(index)) == nullptr) );
// }
//
// bool is_tile_enemy_end(sf::Vector2i index)
// {
//     return  ( !(dynamic_cast<Tile_enemy_end*>
//                 (Tile::get_tile_by_index(index)) == nullptr) );
// }
//
// void render(sf::RenderWindow & window)
// {
//     window.clear();
//     // render tiles
//     for (auto it{begin(Tile::tiles)}; it != end(Tile::tiles); ++it)
//     {
//         window.draw(*it->second);
//     }
//     window.display();
// }
//

// int main ()
// {
//     RenderWindow window {
//         VideoMode { width, height },
//         "SFML DEMO"
//     };
//
//     /* skapa en cirkel */
//     float const r { 16.0 };
//     CircleShape circle { r };
//
//     // placera cirkeln på skärmen
//     circle.setPosition(width / 2, height / 2);
//
//     // sätt vilken punkt som är origo
//     // i cirkeln (det är denna punkt som
//     // cirkelns position är specificerad ifrån
//     circle.setOrigin (r, r);
//
//     // sätt en bakgrundsfärg på cirkeln
//     circle.setFillColor (Color::Green);
//
//     /* ladda in en texture (bild) */
//     Texture texture{};
//     if ( !texture.loadFromFile ("resources/textures/Santa.png") )
//     {
//         // gick inte att ladda bilden
//         return 1;
//     }
//
//     // skapa och scala sprite (Hittar inget bättre sätt att skala på :()
//
//     float sprite_x{100};
//     float sprite_y{100};
//     Vector2u old_size{texture.getSize()};
//     Sprite sprite{texture};
//     sprite.setPosition(width / 2, height / 2);
//     sprite.setScale(sprite_x / old_size.x, sprite_y / old_size.y);
//
//     // sätt origin på sprite till mitten
//     auto size { texture.getSize () };
//     sprite.setOrigin (size.x / 2, size.y / 2);
//
//     float const speed { 4.0 }; // Pixlar per frame
//
//     // skapa en klocka
//     Clock clock;
//
//     double const fps { 60.0 };
//
//     // beräkna hur lång tid vi har per frame
//     auto const target { milliseconds (1000.0 / fps) };
//
//     /* skapa text */
//     Font font;
//     if ( !font.loadFromFile ("resources/fonts/best_font.ttf") )
//     {
//         // kunde inte ladda typsnitt
//         return 2;
//     }
//
//     // skapa text objekt
//     Text text { "Demo", font };
//
//     auto bounds { text.getGlobalBounds () };
//     text.setPosition ((width - bounds.width) / 2, 0);
//
//
// //-------------Tower_shop test----------------------------------
//
//     Wallet wallet{1000};
//     sf::Vector2f position{100,100};
//     sf::Vector2f size_{100,100};
//     float hit_rad{100};
//     sf::Vector2f dir{1,0};
//     float mov_spd{10};
//     int arg_level{1};
//     int cost{100};
//
//     Tower_basic * tower = new Tower_basic{"texture", position, size_, hit_rad, dir, mov_spd, arg_level, cost}; // Memory leak, will fix someday.
//     vector<Tower *> passive_towers{};
//     passive_towers.push_back(tower);
//     Vector2f pos {100,100};
//     Vector2f siz {500,500};
//     Vector2f btnsiz {100,100};
//     Tower_shop shop{passive_towers, wallet, pos, siz, btnsiz};
//
//
//
//
//
//
//
// //-----------------------------------------------
//
//     // loopa sålänge fönstret finns
//     while ( window.isOpen () )
//     {
//         // börja tidtagning
//         clock.restart ();
//
//         /* hantera events */
//         Event event;
//         // hämta ett event i taget
//         while ( window.pollEvent (event) )
//         {
//             if ( event.type == Event::Closed )
//             {
//                 window.close ();
//             }
//             // har en mus-knapp tryckts?
//             else if ( event.type == Event::MouseButtonPressed )
//             {
//                 auto mouse { event.mouseButton };
//                 // är det vänster musknapp?
//                 if ( mouse.button == Mouse::Button::Left )
//                 {
//                     // flytta cirkeln
//                     circle.setPosition (mouse.x, mouse.y);
//                 }
//             }
//         }
//
//         /* hantera logiken */
//         auto old_position { sprite.getPosition () };
//
//         if ( Keyboard::isKeyPressed (Keyboard::Key::W) )
//         {
//             sprite.setRotation (0);
//             sprite.move (0, -speed);
//         }
//         else if ( Keyboard::isKeyPressed (Keyboard::Key::S) )
//         {
//             sprite.setRotation (180);
//             sprite.move (0, speed);
//         }
//         else if ( Keyboard::isKeyPressed (Keyboard::Key::A) )
//         {
//             sprite.setRotation (-90);
//             sprite.move (-speed, 0);
//         }
//         else if ( Keyboard::isKeyPressed (Keyboard::Key::D) )
//         {
//             sprite.setRotation (90);
//             sprite.move (speed, 0);
//         }
//
//         auto sprite_box { sprite.getGlobalBounds () };
//         auto circle_box { circle.getGlobalBounds () };
//         if ( sprite_box.intersects (circle_box) )
//         {
//             // om kollision, flytta tillbaks sprite
//             sprite.setPosition (old_position);
//         }
//
//         /* rita ut */
//         window.clear (); // rensa skärmen
//
//         window.draw (text); // rita ut texten
//         window.draw (circle); // rita ut cirkeln
//         window.draw (sprite); // rita ut bilden
//
//         window.display (); // visa ändringarna
//
//         // räkna ut hur lång tid vi har kvar tills nästa
//         // frame ska börja
//         auto wait_time { target - clock.getElapsedTime () };
//
//         // vänta tiden som blev över
//         sleep (wait_time);
//     }
// }
