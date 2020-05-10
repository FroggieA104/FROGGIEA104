#include <iostream> 
#include <deque>
#include <vector>
#include <conio.h>
#include <Windows.h> 
#include <stdio.h>

#define UP 72
#define DOWN 80
#define RIGHT 77
#define  LEFT 75
#define ENTER 13
#define N 10
#define RESET_COLOR "\x1b[0m"
#define ROJO_T "\x1b[31m"
#define VERDE_T "\x1b[32m"
#define AMARILLO_T "\x1b[33m"
#define AZUL_T "\x1b[34m"
#define MAGENTA_T "\x1b[35m"
#define CYAN_T "\x1b[36m"
#define BLANCO_F "\x1b[47m"

typedef struct {
	int score;
	char nombre[N];
}JUG;

void OculCurs();
void iraxy(int, int);
void Marco();
void pintar_limites();
void Ranking(char[], int);
void instrucciones();

using namespace std;

class Lane //pantalla
{
private:
	deque<bool>cars;//vector booleano que indica la posición de los coches
	bool right; //variable booleana
public:
	Lane(int width)
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
		return cars[pos];
	}

};

class Player //posición del jugador
{
public:
	int x, y;
	Player(int width) //posición inicial del jugador
	{
		x = (width / 2) + 1;
		y = 23;
	}
};

class Game
{
private:
	
	int numberofLanes, width, i, j;
	size_t a = 0;
	Player* player; //llama a la clase player (jugador)
	vector<Lane*> map; // vector que llama a la clase y le pone como variable referenciada el mapa
public:
	JUG P;
	Game(int w = 20, int h = 10)// condiciones inicales del tamaño del juego
	{
		numberofLanes = h;
		width = w;
		for (i = 0; i < numberofLanes; i++)
		{
			map.push_back(new Lane(width)); //agrega en el mapa lo que hay en la clase e indica el ancho maximo
		}
		player = new Player(width);
	}
	~Game()//destructor del juego
	{
		delete player;
		for (a = 0; a < map.size(); a++)
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

		for (i = 0; i < numberofLanes; i++) //largo
		{
			for (j = 0; j < width; j++)//ancho
			{
				if (i == 5 && (j == width / 3 + 3))
					printf(ROJO_T"FROGGIEA104" RESET_COLOR);
				if (i == 7 && (j == width - 8))
					printf(AZUL_T"SCORE: %d" RESET_COLOR, P.score);
				if (i == 9 && j == width / 2)
					printf("Meta" RESET_COLOR);
				if (i == 10 && j == 5)
					printf("###" RESET_COLOR);
				if (i == 10 && j == width - 6)
					printf("###" RESET_COLOR);
				if (map[i]->CheckPos(j) && j > 4 && i > 10 && i < numberofLanes - 1)
					printf(CYAN_T "." RESET_COLOR);
				else if (player->x == j && player->y == i)
					printf(VERDE_T "!0!" RESET_COLOR);
				else
					printf(" ");
			}
			cout << endl; //deja de imprimirlo cuando muere el codigo
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
		}
	}
	bool Logic()//indica la logica del movimiento, es decir, como se desarrolla el juego
	{
		for (i = 1; i < numberofLanes - 1; i++)
		{
			if (rand() % 5 == 1)//genera el mov del plano
				map[i]->Move();
			if (map[i]->CheckPos(player->x) && player->y == i)//choque del coche y del personaje
			{
				system("cls"); Marco();
				iraxy(12, 8); printf("GAME OVER");
				Sleep(1000);
				system("cls"); Marco();
				iraxy(7, 6); printf("Introduce tu nombre:\n");
				iraxy(7, 8); gets_s(P.nombre, sizeof(P.nombre));
				system("cls"); Marco();
				iraxy(13, 3); printf_s("Ranking");
				Ranking(P.nombre, P.score);//realiza e imprime el fichero Ranking
				Sleep(1000);
				return(0);
			}
		}
		if (player->y == 10)//aumenta la puntuacion
		{
			P.score++;
			player->y = numberofLanes - 1;
			printf("\x07");
		}
		return(1);
	}
};

int main()
{
	int y = 12, x = 10;
	char tecla, ini;
	bool start = TRUE, p1 = 1, p2 = 1;
	OculCurs();
	Marco();
	iraxy(10, 9); printf(ROJO_T "FroggieA104" RESET_COLOR);
	iraxy(17, 12); printf(AMARILLO_T "Instrucciones" RESET_COLOR);
	iraxy(17, 13); printf(VERDE_T "Start" RESET_COLOR);
	iraxy(17, 14); printf(AZUL_T"EXIT" RESET_COLOR);
	iraxy(13, y); printf(CYAN_T "==>" RESET_COLOR);
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
		iraxy(13, y); printf(CYAN_T"==>" RESET_COLOR);
		if (tecla == ENTER)//si pulso ENTER
		{
			switch (y)
			{
			case 12: //en la opcion INSTRUCCIONES
			{
				system("cls"); Marco(); instrucciones();
				iraxy(26, 15); printf(MAGENTA_T "Start" RESET_COLOR);
				iraxy(26, 16); printf("_____");
				ini = _getch();
				if (ini == ENTER)
				{
					system("cls");
					Game game(35, 24);
					while (p1 != 0)
					{
						game.Draw();
						game.Input();
						p1 = game.Logic();
					}
				}
				if (p1 == 0)
					start = 0;
				break;
			}
			case 13: //En la opcion START
			{
				system("cls");
				Game game(35, 24);
				while (p1 != 0)
				{
					game.Draw();
					game.Input();
					p1 = game.Logic();
				}
				if (p1 == 0)
					start = 0;
				break;
			}
			case 14://En ls opcion exit
			{
				system("cls"); Marco(); iraxy(5, 7);
				printf("Seguro que quiere salir?");
				iraxy(11, 14); printf(ROJO_T"Si" RESET_COLOR);
				iraxy(21, 14); printf(VERDE_T"No" RESET_COLOR);
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
						else
						{
							p2 = FALSE;
							system("cls"); Marco();
							iraxy(10, 9); printf(ROJO_T "FroggieA104" RESET_COLOR);
							iraxy(17, 12); printf(AMARILLO_T "Instrucciones" RESET_COLOR);
							iraxy(17, 13); printf(VERDE_T "Start" RESET_COLOR);
							iraxy(17, 14); printf(AZUL_T"EXIT" RESET_COLOR);
							iraxy(13, y); printf(CYAN_T "==>" RESET_COLOR);
						}
					}
				}
				break;
			}
			}
		}
	}
	return 0;
}

void OculCurs()
{
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO A; //estructura con las caracteristicas del cursor
	A.bVisible = FALSE;
	A.dwSize = 10;
	SetConsoleCursorInfo(hcon, &A);//aparicion del cursor
}

void iraxy(int x, int y)
{
	HANDLE coger;
	coger = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD posicion;
	posicion.X = x;
	posicion.Y = y;
	SetConsoleCursorPosition(coger, posicion);
}

void Marco()
{
	int x, y;
	iraxy(0, 0); printf("%c", 201);
	iraxy(0, 20); printf("%c", 200);
	iraxy(35, 0); printf("%c", 187);
	iraxy(35, 20); printf("%c", 188);
	for (x = 1; x < 35; x++)
	{
		iraxy(x, 0); printf("%c", 205);
		iraxy(x, 20); printf("%c", 205);
	}
	for (y = 1; y < 20; y++)
	{
		iraxy(0, y); printf("%c", 186);
		iraxy(35, y); printf("%c", 186);
	}
}

void pintar_limites()
{
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

void instrucciones()
{
	int i = 0;
	char texto[50];
	FILE* instruc;
	errno_t inst;
	inst = fopen_s(&instruc, "Instrucciones.txt", "r");
	if (inst != NULL) printf("ERROR");
	while (feof(instruc)==0)
	{
		fgets(texto, 50, instruc);
		i++;
		iraxy(4, 2 + i); printf("%s", texto);
	}
	fclose(instruc);
}

void Ranking(char cad[], int puntos)
{
	int i, j, line = 0;
	JUG* jug, jugaux;
	FILE* ranking, * listajug;
	errno_t R, R2;
	char aux[12];

	R = fopen_s(&ranking, "Ranking.txt", "w+");//abro el Ranking
	R2 = fopen_s(&listajug, "listajug.txt", "a+");

	if (R != NULL) printf("ERROR");//comprobar si abre el fichero
	if (R2 != NULL) printf("ERROR");//comprobar si abre el fichero

	fprintf_s(listajug, "\n%s %d", cad, puntos);//añado el nombre y la puntuación
	fseek(listajug, 0, SEEK_SET);//regreso el puntero del fichero al inicio
	jug = (JUG*)malloc(1 * sizeof(JUG));//reservo una estructura del tamaño de una "línea"
	
	while (feof(listajug)==0)
	{
		fgets(aux, _countof(aux), listajug);
		line++;
	}//Leo el archivo y anoto el numero de "lineas"
	fseek(listajug, 0, SEEK_SET);//regreso el puntero del fichero al inicio
	jug = (JUG*)malloc(line * sizeof(JUG));//Reservo la memoria que necesito
	
	//Empiezo a leer el Ranking NO ordenado
	line = 0;
	while (feof(listajug)==0)
	{
		fscanf_s(listajug, "%s", (jug + line)->nombre, _countof((jug + line)->nombre));
		fscanf_s(listajug, "%d", &(jug + line)->score);//guardo en el vector de estructuras los datos del fichero
		line++;//cuento cuántas líneas tiene
	}
	
	//Método de la burbuja(COMPARA UNA LINEA CON TODAS LAS DEMÁS)
	for (i = 0; i < (line - 1); i++)
	{
		for (j = i + 1; j < line; j++)
		{							 
			if ((jug + j)->score > (jug + i)->score)
			{
				jugaux = *(jug + j);
				*(jug + j) = *(jug + i);
				*(jug + i) = jugaux;
			}
		}
	}
	for (i = 0; i < line; i++)//imprimir en el fichero del ranking
	{
		fprintf_s(ranking, "%s %d", (jug + i)->nombre, (jug + i)->score);
		if (i >= 0 && i < 6)//solo imprimirá en pantalla los primeros 5
		{
			iraxy(5, 6 + i); printf("%d: %s %d", i + 1, (jug + i)->nombre, (jug + i)->score);
		}		
	}
	fclose(ranking);//cierro el fichero
	fclose(listajug);
	free(jug);//libero la memoria
}
