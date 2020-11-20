#include <iomanip>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

using namespace sf;

int const width  { 1000 };
int const height { 800 };

int main ()
{
    RenderWindow window {
        VideoMode { width, height },
        "SFML DEMO"
    };

    /* skapa en cirkel */
    float const r { 16.0 };
    CircleShape circle { r };

    // placera cirkeln på skärmen
    circle.setPosition (width / 2, height / 2);

    // sätt vilken punkt som är origo
    // i cirkeln (det är denna punkt som
    // cirkelns position är specificerad ifrån
    circle.setOrigin (r, r);

    // sätt en bakgrundsfärg på cirkeln
    circle.setFillColor (Color::Green);

    /* ladda in en texture (bild) */
    Texture texture;
    if ( !texture.loadFromFile ("resources/textures/Santa.png") )
    {
        // gick inte att ladda bilden
        return 1;
    }

    // skapa sprite
    Sprite sprite { texture };
    sprite.setPosition (width / 2, height / 2);

    // sätt origin på sprite till mitten
    auto size { texture.getSize () };
    sprite.setOrigin (size.x / 2, size.y / 2);

    float const speed { 4.0 };

    // skapa en klocka
    Clock clock;

    double const fps { 60.0 };

    // beräkna hur lång tid vi har per frame
    auto const target { milliseconds (1000.0 / fps) };

    /* skapa text */
    Font font;
    if ( !font.loadFromFile ("resources/fonts/best_font.ttf") )
    {
        // kunde inte ladda typsnitt
        return 2;
    }

    // skapa text objekt
    Text text { "Demo", font };

    auto bounds { text.getGlobalBounds () };
    text.setPosition ((width - bounds.width) / 2, 0);

    // loopa sålänge fönstret finns
    while ( window.isOpen () )
    {
        // börja tidtagning
        clock.restart ();

        /* hantera events */
        Event event;
        // hämta ett event i taget
        while ( window.pollEvent (event) )
        {
            if ( event.type == Event::Closed )
            {
                window.close ();
            }
            // har en mus-knapp tryckts?
            else if ( event.type == Event::MouseButtonPressed )
            {
                auto mouse { event.mouseButton };
                // är det vänster musknapp?
                if ( mouse.button == Mouse::Button::Left )
                {
                    // flytta cirkeln
                    circle.setPosition (mouse.x, mouse.y);
                }
            }
        }

        /* hantera logiken */
        auto old_position { sprite.getPosition () };

        if ( Keyboard::isKeyPressed (Keyboard::Key::W) )
        {
            sprite.setRotation (0);
            sprite.move (0, -speed);
        }
        else if ( Keyboard::isKeyPressed (Keyboard::Key::S) )
        {
            sprite.setRotation (180);
            sprite.move (0, speed);
        }
        else if ( Keyboard::isKeyPressed (Keyboard::Key::A) )
        {
            sprite.setRotation (-90);
            sprite.move (-speed, 0);
        }
        else if ( Keyboard::isKeyPressed (Keyboard::Key::D) )
        {
            sprite.setRotation (90);
            sprite.move (speed, 0);
        }

        auto sprite_box { sprite.getGlobalBounds () };
        auto circle_box { circle.getGlobalBounds () };
        if ( sprite_box.intersects (circle_box) )
        {
            // om kollision, flytta tillbaks sprite
            sprite.setPosition (old_position);
        }

        /* rita ut */
        window.clear (); // rensa skärmen

        window.draw (text); // rita ut texten
        window.draw (circle); // rita ut cirkeln
        window.draw (sprite); // rita ut bilden

        window.display (); // visa ändringarna

        // räkna ut hur lång tid vi har kvar tills nästa
        // frame ska börja
        auto wait_time { target - clock.getElapsedTime () };

        // vänta tiden som blev över
        sleep (wait_time);
    }
}
