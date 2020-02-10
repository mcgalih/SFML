#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>
#include <iostream>

class Heart
{
public:
	Heart(const sf::Vector2f& pos) : pos(pos)
	{
		texture.loadFromFile("heart.png");
		sprite = sf::Sprite(texture);
		sprite.setOrigin(17/2, 15/2);
	}
	void Draw(sf::RenderTarget& rt) const
	{
		rt.draw(sprite);
	}
	void setDirection(const sf::Vector2f& dir, float dt)
	{
		vel = dir * speed;
		pos += vel * dt;
		sprite.setPosition(pos);
	}
	void Update(float dt)
	{
		pos += vel * dt;
		sprite.setPosition(pos);
	}
	sf::Vector2f getPosition(){ return pos;};
	sf::FloatRect getGlobalBounds()
	{
		batas = sprite.getGlobalBounds();
		return batas;
	}
private:
	sf::FloatRect batas;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f pos;
	sf::Vector2f vel = { 0.0f,0.0f };
	const float speed = 300.0f;
};

class Health
{
public:
	Health(const sf::Vector2f& pos)
	{
		health.setPointCount(4);
		health.setPosition(pos);
		panjang = 150.0f;
	}
	void Bar()
	{
		health.setPoint(0, sf::Vector2f(0.0f, 0.0f));
		health.setPoint(1, sf::Vector2f(panjang, 0.0f));
		health.setPoint(2, sf::Vector2f(panjang, lebar));
		health.setPoint(3, sf::Vector2f(0.0f, lebar));
		if (panjang < 0.0f) panjang = 0.0f;
		else if (panjang > 150.0f) panjang = 150.0f;
	}
	void Damaged(float hit)
	{
		panjang += hit;
	}
	void Draw(sf::RenderTarget& rt) const
	{
		rt.draw(health);
	}
private:
	sf::ConvexShape health;
	float panjang, lebar = 30.0f;
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "ASLABLOVANIA");

	//===============================sans========================//
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
	//==============================================================//

	Heart hati({400.0f,350.0f});
	Health darah({ 500,230 });
	////////////////////////limit pergerakan////////////////////////////
	sf::RectangleShape kotak(sf::Vector2f(250.0f,150.0f));
	kotak.setOrigin(250.0f/2.0f, 150.0f/2.0f);
	kotak.setFillColor(sf::Color::Black);
	kotak.setOutlineThickness(4);
	kotak.setOutlineColor(sf::Color::White);
	kotak.setPosition(400, 350);

	sf::RectangleShape atas(sf::Vector2f(250.0f,1.0f));
	atas.setPosition(275.0f, 275.0f);

	sf::RectangleShape bawah(sf::Vector2f(250.0f, 1.0f));
	bawah.setPosition(275.0f, 425.0f);

	sf::RectangleShape kiri(sf::Vector2f(1.0f, 150.0f));
	kiri.setPosition(274.0f, 275.0f);

	sf::RectangleShape kanan(sf::Vector2f(1.0f, 150.0f));
	kanan.setPosition(526.0f, 275.0f);
	////////////////////////////////////////////////////////////////////
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
		}
		sf::Sprite sans;
		sans.setTexture(texture);
		sans.setTextureRect(frames[iFrame]);
		sans.setPosition(350, 100);
		//=======================================================//
		darah.Bar();

		sf::Vector2f dir = { 0.0f,0.0f };
		// batas pergerakan
		if (atas.getGlobalBounds().intersects(hati.getGlobalBounds())) dir.y += 1.0f;
		else if (bawah.getGlobalBounds().intersects(hati.getGlobalBounds())) dir.y -= 1.0f;
		else if (kiri.getGlobalBounds().intersects(hati.getGlobalBounds())) dir.x += 1.0f;
		else if (kanan.getGlobalBounds().intersects(hati.getGlobalBounds())) dir.x -= 1.0f;
		else
		{
			// input arah gerak
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
		}
		hati.setDirection(dir, dt);
		// membuat area dammage
		//sf::FloatRect hitbox = kotak.getGlobalBounds();
		//if (hitbox.contains(hati.getPosition())) darah.Damaged(-0.5f);


		// update the game
		window.clear();

		// draw objects here
		window.draw(sans);
		window.draw(kotak);
		hati.Draw(window);
		darah.Draw(window);

		//update the window
		window.display();
	}
}