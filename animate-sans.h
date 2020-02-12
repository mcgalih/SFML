#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>
#include <iostream>

class Heart
{
public:
	Heart(const sf::Vector2f& pos) : pos(pos)
	{
		texture.loadFromFile("image/heart.png");
		sprite = sf::Sprite(texture);
		sprite.setOrigin(17 / 2, 15 / 2);
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
	sf::Vector2f getPosition() { return pos; };
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
		health.setFillColor(sf::Color::Yellow);
		panjang = 100.0f;
	}
	void Bar()
	{
		health.setPoint(0, sf::Vector2f(0.0f, 0.0f));
		health.setPoint(1, sf::Vector2f(panjang, 0.0f));
		health.setPoint(2, sf::Vector2f(panjang, lebar));
		health.setPoint(3, sf::Vector2f(0.0f, lebar));
		if (panjang < 0.0f) panjang = 0.0f;
		else if (panjang > 100.0f) panjang = 100.0f;
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

class Movement
{
public:
	Movement()
	{
		kotak.setSize(sf::Vector2f(250.0f, 150.0f));
		kotak.setOrigin(250.0f / 2.0f, 150.0f / 2.0f);
		kotak.setFillColor(sf::Color::Black);
		kotak.setOutlineThickness(4);
		kotak.setOutlineColor(sf::Color::White);
		kotak.setPosition(400, 350);

		atas.setSize(sf::Vector2f(250.0f, 1.0f));
		atas.setPosition(275.0f, 275.0f);

		bawah.setSize(sf::Vector2f(250.0f, 1.0f));
		bawah.setPosition(275.0f, 425.0f);

		kiri.setSize(sf::Vector2f(1.0f, 150.0f));
		kiri.setPosition(274.0f, 275.0f);

		kanan.setSize(sf::Vector2f(1.0f, 150.0f));
		kanan.setPosition(526.0f, 275.0f);
	}
	void limit(Heart& hati, sf::Vector2f& dir)
	{
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
	}
	void Draw(sf::RenderTarget& rt) const
	{
		rt.draw(kotak);
	}
private:
	sf::RectangleShape kotak, atas, bawah, kiri, kanan;
};