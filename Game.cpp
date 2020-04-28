#include<stdio.h>
#include<Windows.h>
#include<stdlib.h> //para usar el rand
#include<conio.h>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80 //Para usar cursores segun tabla ASCII
#define ENTER 13

void iraxy(int, int); // Función para movernos dentro de la pantalla, como un puntero
void OculCurs();//ocultar el cursor de la pantalla
void pintar_limites();
void Marco();//marco inicial del juego

class PERSONAJE { //Las clases especifica la forma de un objeto
	int x, y, corazones, vidas; //variables locales
public:       // lo que definamos aquí sera accesible a cualquier parte del programa
	PERSONAJE(int _x, int _y, int _corazones, int _vidas);
	int X() { return x; } //para sacar el valor de x (para el choque)
	int Y() { return y; }
	void COR() {
		corazones--;
	}
	void dibujar(); //dibujar el personaje
	void borrar(); //Para borrar el anterior cuando se mueva
	void mover();
	void pintar_corazones();
	void morir();
	void revivir();
};
PERSONAJE::PERSONAJE(int _x, int _y, int _corazones, int _vidas) {
	x = _x;
	y = _y;
	corazones = _corazones;
	vidas = _vidas;

}
void PERSONAJE::dibujar() { //Dibujamos el personaje con los elementos ascii
	iraxy(x, y);
	printf("%c%c", 207, 40);
	iraxy(x, y + 1);
	printf("%c%c", 40, 207);
}
void PERSONAJE::borrar() { //Para no dejar el rastro por donde se mueve el personaje
	iraxy(x, y);
	printf("  ");//Los espacios equivalen a borrar lo anterior
	iraxy(x, y + 1);
	printf("  ");
}
void PERSONAJE::mover() {
	if (_kbhit()) {  //kbhit -> función de la biblioteca conio.h que sabe si se ha pulsado una tecla.
		char tecla;
		tecla = _getch(); // con un scanf_s no funciona nose xk
		iraxy(x, y);
		borrar();
		if (tecla == IZQUIERDA && x > 3) //El personaje se mueve a la izquierda, con limite de pantalla
			x--;
		if (tecla == DERECHA && x + 2 < 37)//El personaje se mueve a la derecha, con límite, y el +6 por lo que ocupa el personaje
			x++;
		if (tecla == ARRIBA && y > 3)//El personaje se mueve hacia arriba (inversión del eje y), con limite
			y--;
		if (tecla == ABAJO && y + 1 < 23)//El personaje se mueve hacia abajo, con limite, y teniendo en cuenta al personaje
			y++;
		if (tecla == 'e') // Tecla de prueba para quitar corazones rapido
		{
			corazones--;
		}
		dibujar();
		pintar_corazones();
	}
}
void PERSONAJE::pintar_corazones() {

	int i;
	iraxy(14, 1);
	printf("VIDAS %d", vidas);
	iraxy(23, 1);
	printf("Salud"); //Letrero que nos dirá la salud
	iraxy(31, 1);
	printf("       ");
	for (i = 0; i < corazones; i++) {
		iraxy(31 + i, 1);
		printf("%c", 3); //Simbolo ASCII del corazón
	}
}
void PERSONAJE::morir() {
	if (corazones == 0) {
		borrar();
		Sleep(1000); //Para que haya tiempo entre que muere y revive (posible animación aqui)
		vidas--;
		corazones = 3;
		pintar_corazones();
		revivir();

	}
}
void PERSONAJE::revivir() {
	iraxy(18, 22);
	dibujar();
	mover();
}

class META {
	int x, y;
public:
	META(int _x, int _y);
	int X() { return x; } //para sacar el valor de x (para el choque)
	int Y() { return y; }
	void dibujar();
	void choque(class PERSONAJE& N);
};
META::META(int _x, int _y) {
	x = _x;
	y = _y;
}
void META::dibujar() {
	int i = 0;
	for (i = 3; i < 37; i++) //Limites del juego por arriba
	{
		iraxy(i, 3);
		printf("%c", 178);// Linea horizontal en ascii
	}
}
void META::choque(class PERSONAJE& N) { //FUNCION QUE LA ENTRA UNA ESTRUCTURA O CLASS
	if (x >= N.X() && x < N.X() + 2 && y >= N.Y() && y <= N.Y() + 2) //Cogiendo lo que ocupa la nave
	{
		N.dibujar(); //para que no se nos borre la nave
		//clrscr(); // POR QUÉ NO ME FUNCIONA ESTO SI ES DE LA LIBRERIA CONIO.H CONIO!
		iraxy(17, 10);
		printf("NIVEL COMPLETADO");
		y = 4;
	}
}


class OBJETOS {
	int x, y;
public:
	OBJETOS(int _x, int _y);
	void dibujar(); // Es un dibujar y mover diferentes a los de la nave
	void mover();
	void choque(class PERSONAJE& N);
};
OBJETOS::OBJETOS(int _x, int _y) {
	x = _x;
	y = _y;

}
void OBJETOS::dibujar() {
	iraxy(x, y);
	printf("%c", 184);

}
void OBJETOS::mover() {
	iraxy(x, y);
	printf("       ");//Para borrar el anterior objeto
	x++; //Para que caigan (el eje y está invertido)
	if (x > 35) {
		y = rand() % 37 + 3; //Cogiendo el resto del número tendremos uno entre 0 y 71
						  // el +4 es para que entre dentro de la pantalla de juego y no en 0
		x = 10;
	}
	dibujar();
}
void OBJETOS::choque(class PERSONAJE& N) { //FUNCION QUE LA ENTRA UNA ESTRUCTURA O CLASS
	if (x >= N.X() && x < N.X() + 6 && y >= N.Y() && y <= N.Y() + 2) //Cogiendo lo que ocupa la nave
	{
		N.COR();//llAMAR A LA FUNCION DE ARRIBA RESTANDO CORAZONES
		N.dibujar(); //para que no se nos borre la nave
		N.pintar_corazones();
		x = rand() % 71 + 4;
		y = 4;
	}
}

int main()
{
	OculCurs();
	int y = 12, x = 10;
	char tecla, ini;
	bool start = TRUE, p1 = 1, p2 = 1, back = 1;
	iraxy(10, 9); printf("FroggieA104");
	iraxy(17, 12); printf("Instrucciones");
	iraxy(17, 13); printf("Start");
	iraxy(17, 14); printf("EXIT");
	iraxy(13, y); printf("==>");
	while (start != 0)//EMPIEZA EL JUEGO
	{
		tecla = _getch();
		iraxy(13, y); printf("   ");
		if (tecla == ABAJO) y++;
		if (tecla == ARRIBA) y--;
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
			{
				system("cls"); Marco();//deberia imprimirse el fichero de instrucciones
				iraxy(26, 15); printf("Start");
				iraxy(26, 16); printf("_____");
				ini = _getch();
				if (ini == ENTER)
				{
					//fclose(fi);//cerrar el fichero
					system("cls"); int fin_juego = 1; pintar_limites();
					PERSONAJE N(18, 22, 3, 3);//Estas funciones antes del while
					N.dibujar();//         se hacen para que se muestren en pantalla los elementos
					N.pintar_corazones();//antes de adentrarnos al bucle while.
					META M(1, 1);
					OBJETOS obj(3, 10); //

					while (fin_juego == 1)
					{
						obj.mover();
						obj.choque(N); //evalua si nos chocamos con el objeto obj
						M.dibujar();
						M.choque(N);
						N.mover();
						N.morir();
						Sleep(30);//Tarda 30ms entre ejecuciones del bucle para que no se sature
					}
				}
				break;
			}
				
			case 13://En la opcion START
			{
				system("cls"); bool fin_juego = 1; pintar_limites();
				PERSONAJE N(18, 22, 3, 3);//Estas funciones antes del while
				N.dibujar();//         se hacen para que se muestren en pantalla los elementos
				N.pintar_corazones();//antes de adentrarnos al bucle while.
				META M(1, 1);
				OBJETOS obj(3, 10); //

				while (fin_juego == 1)
				{
					obj.mover();
					obj.choque(N); //evalua si nos chocamos con el objeto obj
					M.dibujar();
					M.choque(N);
					N.mover();
					N.morir();
					Sleep(30);//Tarda 30ms entre ejecuciones del bucle para que no se sature
				}
				break;
			}
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
					if (tecla == 77) x += 10;
					if (tecla == 75) x -= 10;
					if (x < 10 || x > 20)
					{
						if (x < 10) x = 20;
						else x = 20;
					}
					iraxy(x, 15); printf("____");
					if (tecla == 13)
					{
						if (x == 10) { p2 = FALSE; start = 0; }
					}
				}
				break;
			}
		}
	}
	system("pause");
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
void pintar_limites() {
	int i; //Variable local de la función
	for (i = 2; i < 38; i++) //Limites del juego por arriba y abajo
	{
		iraxy(i, 2);
		printf("%c", 205);// Linea horizontal en ascii
		iraxy(i, 24);
		printf("%c", 205);
	}
	for (i = 3; i < 24; i++) //Limites del juego por la izquierda y la derecha
	{
		iraxy(2, i);
		printf("%c", 186);//186 linea vertical en ascii
		iraxy(37, i);
		printf("%c", 186);
	}
	iraxy(2, 2); //Ahora vamos a pintar las esquinas
	printf("%c", 201);
	iraxy(2, 24);
	printf("%c", 200);
	iraxy(37, 2);
	printf("%c", 187);
	iraxy(37, 24);
	printf("%c", 188);
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
//NOMBRE: FroggieA104