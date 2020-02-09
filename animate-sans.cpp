#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "ASLABLOVANIA");
	/*
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
	//sprite.setTextureRect(sf::IntRect(535, 0, 107, 136));*/
	sf::Texture texture;
	if (!texture.loadFromFile("heart.png")) // jika statment ini tidak berjalan
	{
		return EXIT_FAILURE;
	}

	sf::Sprite heart;
	heart.setTexture(texture);
	heart.setOrigin(59/2, 55/2);
	sf::Vector2f pos{ 50,50 };

	sf::ConvexShape health(4);
	sf::RectangleShape kotak(sf::Vector2f(300.0f,200.0f));
	kotak.setPosition(200, 200);

	health.setFillColor(sf::Color::Yellow);
	health.setPosition(100, 100);
	float lebar = 40.0f, panjang = 100.0f;

	sf::Vector2f vel = { 0.0f,0.0f };
	const float speed = 300.0f;

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
		/*
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
		sprite.setPosition(350, 100);*/
		//panjang -= dt;
		health.setPoint(0, sf::Vector2f(0.0f, 0.0f));
		health.setPoint(1, sf::Vector2f(panjang, 0.0f));
		health.setPoint(2, sf::Vector2f(panjang, lebar));
		health.setPoint(3, sf::Vector2f(0.0f, lebar));

		//if(panjang <= 0) panjang += dt;



		// handle input
		sf::Vector2f dir = { 0.0f,0.0f };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			dir.y -= 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			dir.y += 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			dir.x -= 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			dir.x += 1.0f;
		}

		
		
		vel = dir * speed;
		pos += vel * dt;
		heart.setPosition(pos);
		// membuat area dammage
		sf::FloatRect luasan = kotak.getGlobalBounds();
		if (luasan.contains(heart.getPosition())) panjang -= 0.05f;

		// update the game
		window.clear();

		// draw objects here
		//window.draw(sprite);
		window.draw(kotak);
		window.draw(heart);
		window.draw(health);

		//update the window
		window.display();

	}
}