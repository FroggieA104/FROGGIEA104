#include <iostream> //entrada y salida de datos genericos
#include <deque>//organiza los elementos de un tipo determinado en una organización lineal    
#include <vector> //organiza los elementos de un tipo determinado en una secuencia lineal VECTORES
#include <conio.h>//entrada y salida de datos para la pantalla
#include <time.h>//modifica el tiempo
#include <Windows.h> //programacion en windows
#include <stdio.h>

#define UP 72
#define DOWN 80
#define RIGHT 77
#define  LEFT 75
#define ENTER 13


#define RESET_COLOR "\x1b[0m"
#define ROJO_T "\x1b[31m"
#define VERDE_T "\x1b[32m"
#define AMARILLO_T "\x1b[33m"
#define AZUL_T "\x1b[34m"
#define MAGENTA_T "\x1b[35m"
#define CYAN_T "\x1b[36m"
#define BLANCO_F   "\x1b[47m"

using namespace std;

class Lane //pantalla
{
private:
	deque<bool>cars;//vector booleano que indica la posición de los coches
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
			if (rand() % 15 == 1)
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
	int i; //Variable local de la función
	for (i = 2; i < 37; i++) //Limites del juego por arriba y abajo
	{
		iraxy(i, 2);
		printf(AMARILLO_T "%c", 205);// Linea horizontal en ascii
		iraxy(i, 25);
		printf(AMARILLO_T"%c", 205);
	}
	for (i = 3; i < 25; i++) //Limites del juego por la izquierda y la derecha
	{
		iraxy(2, i);
		printf(AMARILLO_T"%c", 186);//186 linea vertical en ascii
		iraxy(37, i);
		printf(AMARILLO_T"%c", 186);
	}
	iraxy(2, 2); //Ahora vamos a pintar las esquinas
	printf(AMARILLO_T"%c", 201);
	iraxy(2, 25);
	printf(AMARILLO_T"%c", 200);
	iraxy(37, 2);
	printf(AMARILLO_T"%c", 187);
	iraxy(37, 25);
	printf(AMARILLO_T"%c", 188);
	
}
void Marco()
{
	int x, y;
	FijarCoord(0, 0); printf("%c", 201);
	FijarCoord(0, 20); printf("%c", 200);
	FijarCoord(35, 0); printf("%c", 187);
	FijarCoord(35, 20); printf("%c", 188);
	for (x = 1; x < 35; x++)
	{
		FijarCoord(x, 0); printf("%c", 205);
		FijarCoord(x, 20); printf("%c", 205);
	}
	for (y = 1; y < 20; y++)
	{
		FijarCoord(0, y); printf("%c", 186);
		FijarCoord(35, y); printf("%c", 186);
	}
}

class Player //posición del jugador
{
public:
	int x, y;
	Player(int width) //posición inicial del jugador
	{
		x = (width / 2) +1;
		y = 22;
	}
};

class Game
{
private:
	bool quit; //indica cuando se va a terminar el bucle
	int numberofLanes; //numero de lineas
	int width; //ancho del mapa
	int score;//puntuacion
	Player* player; //llama a la clase player (jugador)
	vector<Lane*> map; // vector que llama a la clase y le pone como variable referenciada el mapa
public:
	Game(int w = 20, int h = 10)// condiciones inicales del tamaño del juego
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
	~Game()//destructor del juego
	{
		delete player;
		for (int i = 0; i < map.size(); i++)
		{
			Lane* current = map.back(); //
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
				if (i == 5 && (j == width/3 +3))
					printf(ROJO_T"FROGGIEA104" RESET_COLOR );
				if (i == 7 && (j == width-8))
					printf(AZUL_T"SCORE: %d" RESET_COLOR, score); 
				if (i == 9 && j==width/2)
					printf("Meta" RESET_COLOR);
				if (i == 10 && j ==5)
					printf("###" RESET_COLOR);
				if (i == 10 && j== width-6 )
					printf("###" RESET_COLOR);
				if (map[i]->CheckPos(j) && i >10 && i < numberofLanes - 1)
					printf(CYAN_T "." RESET_COLOR);
				else if (player->x == j && player->y == i)
					printf(VERDE_T "!0!" RESET_COLOR);
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
			if (rand() % 5 == 1)//genera el mov del plano
				map[i]->Move();
			if (map[i]->CheckPos(player->x) && player->y == i)//choque del coche y del personaje
			{
				quit = false;
				score = 0;
				player->y = numberofLanes - 1;
				player->x = ( width  / 2) +1;
		                Sleep(20);
			}
		}
		if (player->y == 7)//aumenta la puntuacion
		{
			score++;
			player->y = numberofLanes -1;
			printf("\x07");
			
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
	Marco();
	int y = 12, x = 10;
	char tecla;
	bool start = TRUE, p1 = 1, p2 = 1, back=1;
	iraxy(10, 9); printf("FroggieA104");
	iraxy(17, 12); printf("Instrucciones");
	iraxy(17, 13); printf("Start");
	iraxy(17, 14); printf("EXIT");
	iraxy(13, y); printf("==>");
	while (start != 0)//EMPIEZA EL JUEGO
	{
		tecla = _getch();
		iraxy(13, y); printf("   ");
		if (tecla == DOWN) y++;
		if (tecla == UP) y--;
		if (y < 12 || y>14)
		{
			if (y < 12) y = 14;
			else y = 14;
		}
		iraxy(13, y); printf("==>");
		if (tecla == ENTER)//si pulso ENTER
		{
			switch (y)
			{
			case 12: //en la opcion INSTRUCCIONES
				system("cls"); Marco();//DEBE IMPRIMIRSE LE FICHERO INTRUCCIONES
				iraxy(26, 15); printf("Start");
				iraxy(26, 16); printf("_____");
				//Instrucciones(tecla);
				char ini; ini = _getch();
				if (ini == ENTER)
				{
					system("cls");
					cGame game(35, 24);
					game.Run();
				}
				break;
			case 13://En la opcion START
				system("cls");
				cGame game(34, 23);
				game.Run(); //void Contador(%score)
				cout << "Game Over" << endl;
				break;
			case 14://En ls opcion exit
				system("cls"); Marco(); iraxy(5, 7);
				printf("Seguro que quiere salir?");
				iraxy(11, 14); printf("Si");
				iraxy(21, 14); printf("No");
				iraxy(10, 15); printf("____");
				while (p2 != 0)
				{
					tecla = _getch();
					iraxy(x, 15); printf("    ");
					if (tecla == RIGHT) x += 10;
					if (tecla == LEFT) x -= 10;
					if (x < 10 || x > 20)
					{
						if (x < 10) x = 20;
						else x = 20;
					}
					iraxy(x, 15); printf("____");
					if (tecla == ENTER)
					{
						if (x == 10) { p2 = FALSE; start = 0; }
					}
				}
				break;
			}
		}
	}
	return 0;
}

