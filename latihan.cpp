#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "belajar SFML");
	sf::CircleShape bulat(65,360);
	// bulat(diameter,kehalusan) coba ubah kehalusan menjadi 3
	bulat.setRadius(65);
	bulat.setPointCount(360);
	bulat.setFillColor(sf::Color(255, 0, 0));
	// bulat.setOutlineColor(sf::Color(0, 255, 0));
	// bulat.setOutlineThickness(15); // coba ubah jadi -15
	
	sf::Texture texture;
	if (!texture.loadFromFile("sans.png")) // jika statment ini tidak berjalan
	{
		std::cout << "gagal menampilkan gambar";
	}
	bulat.setTexture(&texture);
	bulat.setTextureRect(sf::IntRect(0,0,200,200)); // IntRect(kiri,atas,kanan,bawah)
	bulat.setPosition(sf::Vector2f(50, 50)); // posisi titik di kiri atas pada kotak

	// sf::RectangleShape kotak(sf::Vector2f(100, 60)); // width,height
	// kotak.setSize(sf::Vector2f(500, 450)); // coba bandingkan jika tanpa ini
	// kotak.setPosition(sf::Vector2f(50, 50));

	// sf::ConvexShape convex(5); // convex(jumlah titik); <- optional. dapat ditulis menjadi convex;
	// convex = bidang yang tidak beraturan
	// convex.setPoint(0, sf::Vector2f(0, 0));
	// convex.setPoint(1, sf::Vector2f(100, 15));
	// convex.setPoint(2, sf::Vector2f(200, 75));
	// convex.setPoint(3, sf::Vector2f(45, 120));
	// convex.setPoint(4, sf::Vector2f(0, 70));
	/*
	sf::Vertex garis[] =
	{
		sf::Vertex(sf::Vector2f(45,100)), // vector2f(sumbu x, sumbu y)
		sf::Vertex(sf::Vector2f(200, 400))
	};
	garis[0].color = sf::Color::Cyan;
	garis[1].color = sf::Color::Cyan; // coba ganti warnanya

	// statement dibawah ini akan mengabaikan posisi garis di atas
	garis[0].position = sf::Vector2f(400, 400);
	garis[1].position = sf::Vector2f(100, 200);
	*/
	while (window.isOpen())
	{
		sf::Event event;
		// handle all events
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed :
					window.close();
					break;
			}
		}

	// update the game
	window.clear();

	// draw objects here
	window.draw(bulat);
	// window.draw(kotak);
	// window.draw(convex);
	// window.draw(garis, 2, sf::Lines);

	window.display();

	}
	return EXIT_SUCCESS;
}