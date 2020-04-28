#include <iostream> //entrada y salida de datos genericos
#include <deque>//organiza los elementos de un tipo determinado en una organizaci�n lineal    
#include <vector> //organiza los elementos de un tipo determinado en una secuencia lineal VECTORES
#include <conio.h>//entrada y salida de datos para la pantalla
#include <time.h>//modifica el tiempo
#include <Windows.h> //programacion en windows
#include <stdio.h>

#define UP 72
#define DOWN 80
#define RIGHT 77
#define  LEFT 75

using namespace std;

class cLane //pantalla
{
private:
	deque<bool>cars;//vector booleano que indica la posici�n de los coches
	bool right; //variable booleana
public:
	cLane(int width)
	{
		for (int i = 0; i < width; i++)
		{
			cars.push_front(true); //mete coches al principio de juego(las lineas estan llenas)  
		}
		right = rand() % 2;

	}
	void Move()
	{
		if (right)
		{
			if (rand() % 10 == 1)
				cars.push_front(true); //se generan coches      
			else cars.push_front(false);
			cars.pop_back(); //elimina el elemento que sobra del ancho    
		}
		else
		{
			if (rand() % 10 == 1)
			{
				cars.push_back(true);
			}
			else cars.push_back(false);
			cars.pop_front();
		}
	}
	bool CheckPos(int pos)// funcion que indica donde estan los coches
	{
		return cars[pos] ;
	}
	void Changedirection() //cambia la direccion de los coches
	{
		right != right;
	}
};

void iraxy(int x, int y)
{
	HANDLE coger;
	coger = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD posicion;
	posicion.X = x;
	posicion.Y = y;
	SetConsoleCursorPosition(coger, posicion);
}

void pintar_limites() {
	int i; //Variable local de la funci�n
	for (i = 2; i < 37; i++) //Limites del juego por arriba y abajo
	{
		iraxy(i, 2);
		printf("%c", 205);// Linea horizontal en ascii
		iraxy(i, 25);
		printf("%c", 205); 
	}
	for (i = 3; i < 25; i++) //Limites del juego por la izquierda y la derecha
	{
		iraxy(2, i);
		printf("%c", 186);//186 linea vertical en ascii
		iraxy(37, i);
		printf("%c", 186);
	}
	iraxy(2, 2); //Ahora vamos a pintar las esquinas
	printf("%c", 201);
	iraxy(2, 25);
	printf("%c", 200);
	iraxy(37, 2);
	printf("%c", 187);
	iraxy(37, 25);
	printf("%c", 188);
}

class cPlayer //posici�n del jugador
{
public:
	int x, y;
	cPlayer(int width) //posici�n inicial del jugador
	{
		x = width / 2 +2;
		y = 20;
	}
};

class cGame
{
private:
	bool quit; //indica cuando se va a terminar el bucle
	int numberofLanes; //numero de lineas
	int width; //ancho del mapa
	int score;//puntuacion
	cPlayer* player; //llama a la clase player (jugador)
	vector<cLane*> map; // vector que llama a la clase y le pone como variable referenciada el mapa
public:
	cGame(int w = 20, int h = 10)// condiciones inicales del tama�o del juego
	{
		numberofLanes = h;
		width = w;
		quit = false; //no se quita el juego accidentalmente
		for (int i = 0; i < numberofLanes; i++)
		{
			map.push_back(new cLane(width)); //agrega en el mapa lo que hay en la clase e indica el ancho maximo
		}
		player = new cPlayer(width);
	}
	~cGame()//destructor del juego
	{
		delete player;
		for (int i = 0; i < map.size(); i++)
		{
			cLane* current = map.back(); //
			map.pop_back();//elimina el mapa
			delete current;
		}
	}
	void Draw()//dibuja todo 
	{
		pintar_limites();
		system("cls");//limpia la pantalla cada vez que se mueven los coches(no se peta)
		
		for (int i = 0; i < numberofLanes; i++) //largo
		{
			for (int j =0; j < width; j++)//ancho
			{
				if (i == 0 && (j == 0 || j == width - 1))
					printf(" ");
				if (i == 4 && (j == 11))
					printf("Puntuacion: %d", score);
				if (i == 4 && (j == 5))
					printf("FROGGIEA104");
				if (i == 6 && j==width/2)
					printf("Meta");
				if (i == 7 && j ==5)
					printf("###");
				if (i == 7 && j== width-6 )
					printf("###");
				if (map[i]->CheckPos(j) && i >7 && i < numberofLanes - 1)
					printf(".");
				else if (player->x == j && player->y == i)
					printf("!!");
				else
					printf(" ");

			}
			cout << endl; //deja de imprimirlo cuando se muere
		}
		
	}
	void Input() //controles del jugador
	{
		if (_kbhit())//percibe cuando se pulsa una tecla
		{
			char current = _getch();
			if (current == LEFT)
				player->x--;
			if (current == RIGHT)
				player->x++;
			if (current == UP)
				player->y--;
			if (current == DOWN)
				player->y++;
			if (current == 'q')
				quit = true;
		}
	}
	void Logic()//indica la logica del movimiento, es decir, como se desarrolla el juego
	{
		for (int i = 1; i < numberofLanes - 1; i++)
		{
			if (rand() % 10 == 1)//genera el mov del plano
				map[i]->Move();
			if (map[i]->CheckPos(player->x) && player->y == i)//choque del coche y del personaje
			{
				quit = false;
				score = 0;
				player->y = numberofLanes - 1;
			}
		}
		if (player->y == 7)//aumenta la puntuacion
		{
			score++;
			player->y = numberofLanes -1;
			printf("\x07");
			map[rand() % numberofLanes]->Changedirection();
		}
	}
	void Run()
	{
		while (!quit)//continuara mientras no se quite el juego
		{
			Input();
			Draw();
			Logic();
		}
	}
};

void OculCurs()
{
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO A; //estructura con las caracteristicas del cursor
	A.bVisible = FALSE;
	A.dwSize = 10;
	SetConsoleCursorInfo(hcon, &A);//aparicion del cursor
}

int main()
{
	OculCurs();
	//srand(time(NULL));
	cGame game(35, 24);
	game.Run();
	cout << "Game Over" << endl;
	return 0;
}