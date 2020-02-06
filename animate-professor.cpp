#include <SFML/Graphics.hpp>
#include <chrono>

class Animation
{
public:
	Animation(int x, int y, int width, int height)
	{
		texture.loadFromFile("professor_walk_cycle_no_hat.png");
		for (int i = 0; i < nFrames; i++)
		{
			frames[i] = { x + i * width , y, width, height };
		}
	}
	void ApllytoSprite(sf::Sprite& s) const
	{
		s.setTexture(texture);
		s.setTextureRect(frames[iFrame]);
	}
	void Update(float dt)
	{
		time += dt;
		while (time >= holdtime)
		{
			time -= holdtime;
			if (++iFrame >= nFrames)
			{
				iFrame = 0;
			}
			// advance();
		}
	}
private:
	void advance()
	{
		if (++iFrame >= nFrames)
		{
			iFrame = 0;
		}
	}
private:
	static constexpr int nFrames = 8;
	static constexpr float holdtime = 0.1f;
	sf::Texture texture;
	sf::IntRect frames[nFrames];
	int iFrame = 0;
	float time = 0.0f;
};

class Character
{
public:
	Character(const sf::Vector2f& pos) : pos(pos), RightWalk(64,64*3,64,50)
	{ // bukan 50 , seharusnya 64
		sprite.setTextureRect({ 0,0,64,64 });
	}
	void setDirection(const sf::Vector2f& dir)
	{
		vel = dir * speed;
	}
	void Update(float dt)
	{
		pos += vel * dt;
		RightWalk.Update(dt);
		RightWalk.ApllytoSprite(sprite);
		sprite.setPosition(pos);
	}
	void Draw(sf::RenderTarget& rt) const
	{
		rt.draw(sprite);
	}

private:
	static constexpr float speed = 100.0f;
	sf::Vector2f pos;
	sf::Vector2f vel = { 0.0f,0.0f };
	sf::Sprite sprite;
	Animation RightWalk;
};

int main()
{
	// create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	sf::Vector2f tes = { 0,0 };
	Character mydude({ 100.0f,100.0f });

	// timepoint for delta time measurement (inisialisasi titik waktu pertama)
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
		//get dt
		float dt;
		{
			// inisialisasi titik waktu kedua
			const auto new_tp = std::chrono::steady_clock::now();
			// mengambil lama durasi dari titik pertama ke kedua, dimasukkan ke dt
			dt = std::chrono::duration<float>(new_tp - tp).count();
			// menjadikan titik waktu kedua kembali menjadi titik waktu pertama
			tp = new_tp;
		}
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
		mydude.setDirection(dir);

		// update the model
		// mydude.Update(1.0f / 60.0f);
		mydude.Update(dt);

		// update the game
		window.clear();

		// draw objects here
		mydude.Draw(window);

		//update the window
		window.display();

	}
	return EXIT_SUCCESS;
}