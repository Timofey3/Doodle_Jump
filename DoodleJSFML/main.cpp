#include <SFML\Graphics.hpp>
#include <time.h>
#include <iostream>

struct Point
{
    int x, y;
};



int main()
{  
    sf::Texture t1, t2, t3;
    t1.loadFromFile("background.png");
    t2.loadFromFile("doodle.png");
    t3.loadFromFile("platform.png");

    sf::Vector2u textureSize1 = t1.getSize(); // t1 background texture size
    sf::Vector2u textureSize2 = t2.getSize(); // t2 doodle texture size
    sf::Vector2u textureSize3 = t3.getSize(); // t3 platform texture size

    int widthBack = textureSize1.x; //  t1 background width
    int heightBack = textureSize1.y; // t1 background  height
    
    int widthDoodle = textureSize2.x; // t2 doodle width
    int heightDoodle = textureSize2.y; // t2 doodle height

    int widthPlatform = textureSize3.x; // t3 platform width
    int heightPlatform = textureSize3.y; // t3 platform height

    sf::RenderWindow window(sf::VideoMode(widthBack, heightBack), "Doddle Jump");

    srand(time(0));

    window.setFramerateLimit(60);

    sf::Sprite sBackground(t1), sPers(t2), sPlat(t3);

    int const K=5; //K is cuantity of platforms
    int Jump = -10; //J is jump speed

    Point plat[K]; 

    for (int i = 0; i < K;i++)   //generating platform coordinates
    {
        plat[i].x = rand() % widthBack; 
        plat[i].y = rand() % heightBack;
    }

    int x = 100, y = 100, h = (heightBack)/2;
    float dx = 0, dy = 0;


    while (window.isOpen())
    {
        sf::Event event;
    
        while (window.pollEvent(event))// windows events
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) x += 3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) x -= 3;


        dy += 0.2; //Y velocity
        y += dy;
       
        ////////////////////////////////////////
        if (y > (heightBack-heightDoodle)) dy = Jump;// jump up if sPers is poul of window size by Y coordinates
        /////////////////////////////////////////
        
        if (x > (widthBack- widthDoodle)) x = widthBack - widthDoodle;
        if (x < 0) x = 0;

        if (y<h) // time to roll the screen and generate new platforms
            for (int i = 0; i < K; i++)
            {
                y = h;
                plat[i].y -= dy; // move platforms down by Y coordinates
                if (plat[i].y > heightBack) { plat[i].y = 0; plat[i].x = rand() % widthBack; } //in case of platform is generated out of the game window borders
            }
                    
       
        for (int i = 0; i < K; i++) 
            if ((((x > plat[i].x) && (x + widthDoodle < plat[i].x + widthPlatform))\
                ||((x<plat[i].x+widthPlatform)&&(x+widthDoodle>plat[i].x+widthPlatform))\
                || ((x < plat[i].x) && (x + widthDoodle > plat[i].x))\
                || ((x > plat[i].x) && (x < plat[i].x))\
                || ((x < plat[i].x) && (x + widthDoodle > plat[i].x)))\
                && ((y+heightDoodle == plat[i].y)||((y + heightDoodle > plat[i].y) && (y + heightDoodle <= plat[i].y+heightPlatform)))) std::cout << "intersection" << std::endl, dy = Jump; //jump from platform in case intersection with it //std::cout <<"intersection"<<std::endl,
       
        sPers.setPosition(x, y);

        window.draw(sBackground);

        window.draw(sPers);
            
        
        for (int i = 0; i < K; i++)
        {
            sPlat.setPosition(plat[i].x, plat[i].y);

            window.draw(sPlat);
        }
      
        //window.clear();
        //window.draw(shape);
        window.display();
        }

	return 0;

}