#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "ASLABLOVANIA");
	
	sf::Texture texture;
	if (!texture.loadFromFile("animate-sans.png")) // jika statment ini tidak berjalan
	{
		return EXIT_FAILURE;
	}

	sf::SoundBuffer buffer;

	if (!buffer.loadFromFile("audio/Undertale Sound Effect - Notice.wav"))
	{
		return EXIT_FAILURE;
	}

	sf::Sound sound;
	sound.setBuffer(buffer);

	const int nFrames = 6;
	float holdtime = 0.1f;
	sf::IntRect frames[nFrames];
	int iFrame = 0;
	float time = 0.0f;
	for (int i = 0; i < nFrames; i++)
	{
		frames[i] = { 0 + i * 640/6 , 0, 640/6, 136 };
	}
	sf::Clock clock;
	auto tp = std::chrono::steady_clock::now();

	//sf::Sprite sprite;
	//sprite.setTexture(texture);

	//sprite.setTextureRect(sf::IntRect(0, 0, 107, 136));
	//sprite.setTextureRect(sf::IntRect(107, 0, 107, 136));
	//sprite.setTextureRect(sf::IntRect(214, 0, 107, 136));
	//sprite.setTextureRect(sf::IntRect(321, 0, 107, 136));
	//sprite.setTextureRect(sf::IntRect(428, 0, 107, 136));
	//sprite.setTextureRect(sf::IntRect(535, 0, 107, 136));
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
		
		time += dt;
		
		if (time >= holdtime)
		{
			time -= holdtime;
			++iFrame;
			if (iFrame == 1) holdtime = 0.1f;
			else if (iFrame == 2) holdtime = 0.1f;
			else if (iFrame == 3)
			{
				sound.play();
				holdtime = 0.5f;
			}
			else if (iFrame == 4) holdtime = 0.1f;
			else if (iFrame == 5)
			{
				sound.play();
				holdtime = 0.5f;
			}
			else if (iFrame >= nFrames)
			{
				holdtime = 0.1f;
				iFrame = 1;
			}
			// advance();
		}
		sf::Sprite sprite;
		sprite.setTexture(texture);
		sprite.setTextureRect(frames[iFrame]);
		sprite.setPosition(350, 100);

		// update the game
		window.clear();

		// draw objects here
		window.draw(sprite);

		//update the window
		window.display();

	}
}