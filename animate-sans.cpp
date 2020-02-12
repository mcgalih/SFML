#include "animate-sans.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "ASLABLOVANIA");

	//===============================sans========================//
	sf::Texture texture;
	if (!texture.loadFromFile("image/animate-sans-normal.png")) // jika statment ini tidak berjalan
	{
		return EXIT_FAILURE;
	}

	sf::Sprite sans;
	sans.setTexture(texture);
	sf::SoundBuffer buffer;
	buffer.loadFromFile("audio/GIOVANIA.ogg");
	sf::Sound bgm;
	bgm.setBuffer(buffer);
	bgm.play();

	const int nFrames = 9;
	float holdtime = 0.1f;
	sf::IntRect frames[nFrames];
	int iFrame = 0;
	float time = 0.0f;
	for (int i = 0; i < nFrames; i++)
	{
		frames[i] = { 0 + i * 828/9 , 0, 828/9, 134 };
	}
	//==============================================================//

	Heart hati({400.0f,350.0f});
	Health darah({ 500,230 });

	// tes menampilkan kotak pada rentang waktu tertentu
	sf::Clock clock;
	sf::RectangleShape bro(sf::Vector2f(20,20));

	auto tp = std::chrono::steady_clock::now();
	//start the game loop
	while (window.isOpen())
	{
		// process event
		sf::Event event;
		while (window.pollEvent(event))
		{
			// close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		const auto new_tp = std::chrono::steady_clock::now();
		float dt = std::chrono::duration<float>(new_tp - tp).count();
		tp = new_tp;
		//===============================sans========================//
		time += dt;
		
		if (time >= holdtime)
		{
			time -= holdtime;
			++iFrame;
			/*if (iFrame == 1) holdtime = 0.1f;
			else if (iFrame == 2) holdtime = 0.1f;
			else if (iFrame == 3)
			{
				//sound.play();
				holdtime = 0.5f;
			}
			else if (iFrame == 4) holdtime = 0.1f;
			else if (iFrame == 5)
			{
				//sound.play();
				holdtime = 0.5f;
			}*/
			if (iFrame >= nFrames) iFrame = 1;
		}
		sans.setTextureRect(frames[iFrame]);
		sans.setOrigin(92 / 2, 134 / 2);
		sans.setPosition(window.getSize().x/2,(window.getSize().y/2)-120);
		//=======================================================//
		darah.Bar();
		hati.Movement(dt);
		// membuat area dammage
		//sf::FloatRect hitbox = kotak.getGlobalBounds();
		//if (hitbox.contains(hati.getPosition())) darah.Damaged(-0.5f);

		// update the game
		sf::Time elapsed = clock.getElapsedTime();
		window.clear();

		// draw objects here
		window.draw(sans);
		hati.Draw(window);
		darah.Draw(window);
		/*if (elapsed.asSeconds() >= 5)
		{
			if (elapsed.asSeconds() > 10) clock.restart();
			else window.draw(bro);
		}*/

		//update the window
		window.display();
	}
}