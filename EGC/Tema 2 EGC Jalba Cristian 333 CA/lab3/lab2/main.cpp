#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Transform3D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include <iostream>
#include <windows.h>

#define PI 3.14159265358979323846
#define inf 1000000
#define w_grid	30
#define h_grid	30
#define dim_col_block 10
#define VERTEX_SIZE 2
#define PAS_SCROLL 0.5
#define ACOPERIRE_PIATA 10
#define ARIE_PAMANT_INITIALA 10	

using namespace std;

float cont = 0;
Visual2D *v2d1, *v2d2;
Object3D *cube11, *cube21, *cube31;
//matrice de patratzele din grid
Object3D ****patratzele_grid, *cursor , ***earth_water_grid;
Object3D **cuburi_casa;

int poz_mouse_x, poz_mouse_y, xcursor = 18, ycursor = 18, xinitial = 18, yinitial = 18;
int nr_patratzele = -1;
int blocks[h_grid][w_grid];	
int xbase_for_blocks[h_grid][w_grid];
int ybase_for_blocks[h_grid][w_grid];
int offset = 0, offset_y = -30;
int nr_total_obiecte = 0;
bool activate_mouse = false, change_color = false;
bool moveup = false, movedown = false, moveleft = false, moveright = false;
bool translateTocursor = false, createblock = false, scroll_up = false, scroll_down = false , scroll_left = false , scroll_right = false;
bool make_road = false, make_casa = false, make_piata = false, make_earth = false, make_water = false, make_grass = false;
int roads[h_grid][w_grid];
int zona_piete[h_grid][w_grid];
int pozitii_case[h_grid][w_grid];
int case_aprinse[h_grid][w_grid];
int case_albastre[h_grid][w_grid];
int earth_tiles[h_grid][w_grid];
int water_tiles[h_grid][w_grid];
int grass_tiles[h_grid][w_grid];
float xf1=-5, xf2=5, yf1=-5, yf2=5;
int rotate_casa_x, rotate_casa_y, rotire_casa=0;
bool rotate_house = false, enable_rotate = false, enter_house = false, conditii_piata = false, allow_construction = false, delete_road = false;

int numar_patratzele_construite_inainte_de_casa = 0;
int inaltime_casa = 1;	//reprezinta pozitia casei in vectorul de pe fiecare patratzel din grid
int nr_spam_buton_casa = 0;
int indice_unic_casa = 0;
//functia care permite adaugarea de obiecte

void DrawingWindow::init()
{
	yf1 -= 40;
	yf2 -= 40;
	v2d1 = new Visual2D(xf1, yf1, xf2, yf2, 0, 0, 1300, 600);
	v2d2 = new Visual2D(xf1, yf1, xf2, yf2, 0, 0, 1300, 600);
	v2d1->tipTran(true);
	v2d2->tipTran(true);
	addVisual2D(v2d1);
	addVisual2D(v2d2);
	//se deseneaza un cub
	int i, j, k;
	patratzele_grid = (Object3D ****)malloc(sizeof(Object3D) * h_grid);
	earth_water_grid = (Object3D ***)malloc(sizeof(Object3D) * h_grid);
	for (i = 0; i < h_grid; i++){
		patratzele_grid[i] = (Object3D ***)malloc(sizeof(Object3D)*w_grid);
		earth_water_grid[i] = (Object3D **)malloc(sizeof(Object3D)*w_grid);
		for (j = 0; j < w_grid; j++){
			//id-ul ultimului element din lista de patratzele din grid
			//fiecare patratzel va avea o "lista" de blocks
				pozitii_case[i][j] = 0;
			nr_patratzele++;
			//aici cream fiecare patratzel din grid
			//merge foarte frumos sa am un grid 2D dar din pacate eu vreau sa fie in spatiu
			//in consecinta trebuie sa fac cuburi cu inaltimea 0 sau 0.001 , ceva super mic
			//numai cuburi vad ca pot fi adaugate in framework , asa e el construit ...
			patratzele_grid[i][j] = (Object3D **)malloc(sizeof(Object3D)*dim_col_block);
			vector <Point3D*> vertices;
			vector <Face*> faces;
			offset++;
			vertices.push_back(new Point3D(VERTEX_SIZE + j, offset_y, VERTEX_SIZE + i));
			vertices.push_back(new Point3D(1 + j, offset_y, VERTEX_SIZE + i));
			vertices.push_back(new Point3D(1 + j, offset_y, 1 + i));
			vertices.push_back(new Point3D(VERTEX_SIZE + j, offset_y, 1 + i));

			vertices.push_back(new Point3D(VERTEX_SIZE + j, offset_y, VERTEX_SIZE + i));
			vertices.push_back(new Point3D(1 + j, offset_y, VERTEX_SIZE + i));
			vertices.push_back(new Point3D(1 + j, offset_y, 1 + i));
			vertices.push_back(new Point3D(VERTEX_SIZE + j, offset_y, 1 + i));

			//cele 6 fete
			vector <int> contour;
			//fata jos
			contour.clear();
			contour.push_back(0);
			contour.push_back(1);
			contour.push_back(2);
			contour.push_back(3);
			faces.push_back(new Face(contour));
			//fata sus
			contour.clear();
			contour.push_back(4);
			contour.push_back(5);
			contour.push_back(6);
			contour.push_back(7);
			faces.push_back(new Face(contour));
			//fata fata
			contour.clear();
			contour.push_back(0);
			contour.push_back(1);
			contour.push_back(5);
			contour.push_back(4);
			faces.push_back(new Face(contour));
			//fata dreapta
			contour.clear();
			contour.push_back(1);
			contour.push_back(2);
			contour.push_back(6);
			contour.push_back(5);
			faces.push_back(new Face(contour));
			//fata spate
			contour.clear();
			contour.push_back(2);
			contour.push_back(3);
			contour.push_back(7);
			contour.push_back(6);
			faces.push_back(new Face(contour));
			//fata stanga
			contour.clear();
			contour.push_back(3);
			contour.push_back(0);
			contour.push_back(4);
			contour.push_back(7);
			faces.push_back(new Face(contour));
			patratzele_grid[i][j][0] = new Object3D(vertices, faces, Color(0.4, 0.4, 0), false);
			earth_water_grid[i][j] = new Object3D(vertices, faces, Color(0.8,0.8,1), true);
			addObject3D_to_Visual2D(patratzele_grid[i][j][0], v2d1);
			addObject3D_to_Visual2D(earth_water_grid[i][j], v2d2);
			Transform3D::loadIdentityModelMatrix();
			Transform3D::rotateMatrixOy(PI / 4);
			Transform3D::rotateMatrixOx(0.61472907f);
			Transform3D::applyTransform(v2d1->visual2D_objects3D[nr_patratzele]);
			blocks[i][j] = 1;	
			xbase_for_blocks[i][j] = j;
			ybase_for_blocks[i][j] = i;
			roads[i][j] = 0;
			zona_piete[i][j] = 0;
			case_aprinse[i][j] = 0;
			earth_tiles[i][j] = 0;
			water_tiles[i][j] = 0;
			grass_tiles[i][j] = 0;
		}
	}
	//setez un pamant ceva mai mare
	for (int i = yinitial - ARIE_PAMANT_INITIALA; i <= yinitial + ARIE_PAMANT_INITIALA; i++)
		for (int j = xinitial - ARIE_PAMANT_INITIALA; j <= xinitial + ARIE_PAMANT_INITIALA; j++){
			earth_tiles[i][j] = 1;
			patratzele_grid[i][j][0]->color = Color(0.4, 0.2, 0);
			patratzele_grid[i][j][0]->fill = true;
		}
	//ma voi plimba cu acest cursor pe harta atunci cand apas pe w,a,s,d
	cursor = patratzele_grid[yinitial][xinitial][0];
	cursor->color = Color(1, 0, 0);
	cursor->fill = true;
	nr_total_obiecte = nr_patratzele;
}

bool epsilon3D(float a, float b){
	if (abs(a - b) < 0.1) return true;
	return false;
}
//functie ce cunoaste matricea de roads si matricea de pozitii_casa si o vom apela
//la fiecare modificare de drum (in mod evident nu va fi apelata la cateva milisecunde ...)

//parcurgem cu functia asta tot "arborele" generat de subreteaua pietei
void cautare_recursiva(int poz_cur_y, int poz_cur_x, int **copie_roads){
	//if (verificam daca se afla o casa in vecinatatea pozitiei noastre curente)	ii schimbam culoarea
	//daca nu se afla , mergem pe una din acele directii daca putem , daca nu putem, ne intoarcem recursiv
	//pot merge foarte bn pe ideea cu stergerea din copia matricei , si un drum e sters doar daca s singurul drum
	//gen am 0 0 1 0 0					0 0 1 0 0 
	//		 0 1 1 2 2	care va deveni  0 0 2 2 2	iar acum se observa ca 1 din colt are 2 drumuri (sus si stanga) deci nu il va face 0
	//		 0 0 0 0 0					0 0 0 0 0 
	//fiecare veficicare va tine cont de aceasta copie
	//ca sa ma asigur ca nu ma duc si ma intorc la infinit pe un drum , o sa marchez cu 2 toate elementele de drum parcurse 
	//0 ramane pentru inchidere de drum , 1 pt neexplorat
	//e fix un DFS ...
	//1 va fi preferabil lui 2 
	//verificam daca se afla o casa in vecinatatea pozitiei noastre
	if (pozitii_case[poz_cur_y][poz_cur_x - 1] != 0) {
		for (int i = poz_cur_y - 2; i <= poz_cur_y + 2; i++){
			for (int j = poz_cur_x - 2; j <= poz_cur_x + 2; j++){
				if (pozitii_case[i][j] == pozitii_case[poz_cur_y][poz_cur_x - 1]) {
					patratzele_grid[i][j][inaltime_casa - 1]->color = Color(0.6, 0.8, 0);
					patratzele_grid[i][j][inaltime_casa - 1]->fill = true;
					case_aprinse[i][j] = 1;
					case_albastre[i][j] = 0;
				}
			}
		}
	}
	if (pozitii_case[poz_cur_y - 1][poz_cur_x] != 0) {
		for (int i = poz_cur_y - 2; i <= poz_cur_y + 2; i++){
			for (int j = poz_cur_x - 2; j <= poz_cur_x + 2; j++){
				if (pozitii_case[i][j] == pozitii_case[poz_cur_y - 1][poz_cur_x]) {
					patratzele_grid[i][j][inaltime_casa - 1]->color = Color(0.6, 0.8, 0);
					patratzele_grid[i][j][inaltime_casa - 1]->fill = true;
					case_aprinse[i][j] = 1;
					case_albastre[i][j] = 0;
				}
			}
		}
	}
	if (pozitii_case[poz_cur_y + 1][poz_cur_x] != 0) {
		for (int i = poz_cur_y - 2; i <= poz_cur_y + 2; i++ ){
			for (int j = poz_cur_x - 2; j <= poz_cur_x + 2; j++){
				if (pozitii_case[i][j] == pozitii_case[poz_cur_y + 1][poz_cur_x]) {
					patratzele_grid[i][j][inaltime_casa - 1]->color = Color(0.6, 0.8, 0);
					patratzele_grid[i][j][inaltime_casa - 1]->fill = true;
					case_aprinse[i][j] = 1;
					case_albastre[i][j] = 0;
				}
			}
		}
	}
	if (pozitii_case[poz_cur_y][poz_cur_x + 1] != 0) {
		for (int i = poz_cur_y - 2; i <= poz_cur_y + 2; i++){
			for (int j = poz_cur_x - 2; j <= poz_cur_x + 2; j++){
				if (pozitii_case[i][j] == pozitii_case[poz_cur_y][poz_cur_x + 1]) {
					patratzele_grid[i][j][inaltime_casa - 1]->color = Color(0.6, 0.8, 0);
					patratzele_grid[i][j][inaltime_casa - 1]->fill = true;
					case_aprinse[i][j] = 1;
					case_albastre[i][j] = 0;
				}
			}
		}
	}
	if (copie_roads[poz_cur_y][poz_cur_x - 1] == 1) {
		copie_roads[poz_cur_y][poz_cur_x - 1] = 2;
		cautare_recursiva(poz_cur_y, poz_cur_x - 1, copie_roads);
	}
	else if (copie_roads[poz_cur_y - 1][poz_cur_x] == 1) {
		copie_roads[poz_cur_y - 1][poz_cur_x] = 2;
		cautare_recursiva(poz_cur_y - 1, poz_cur_x, copie_roads);
	} 
	else if (copie_roads[poz_cur_y + 1][poz_cur_x] == 1) {
		copie_roads[poz_cur_y + 1][poz_cur_x] = 2;
		cautare_recursiva(poz_cur_y + 1, poz_cur_x, copie_roads);
	}
	else if (copie_roads[poz_cur_y][poz_cur_x + 1] == 1) {
		copie_roads[poz_cur_y][poz_cur_x + 1] = 2;
		cautare_recursiva(poz_cur_y , poz_cur_x + 1, copie_roads);	
	}
	//inseamna ca a explorat partial ramura , asa ca trebuie sa ne intoarcem
	//facem casutza curenta 0 si ne intoarcem
	copie_roads[poz_cur_y][poz_cur_x] = 0;
	if (copie_roads[poz_cur_y][poz_cur_x - 1] == 2) {
		cautare_recursiva(poz_cur_y, poz_cur_x - 1, copie_roads);
	}
	else if (copie_roads[poz_cur_y - 1][poz_cur_x] == 2) {
		cautare_recursiva(poz_cur_y - 1, poz_cur_x, copie_roads);
	}
	else if (copie_roads[poz_cur_y + 1][poz_cur_x] == 2) {
		cautare_recursiva(poz_cur_y + 1, poz_cur_x, copie_roads);
	}
	else if (copie_roads[poz_cur_y][poz_cur_x + 1] == 2) {
		cautare_recursiva(poz_cur_y, poz_cur_x + 1, copie_roads);
	}
	//conditia de oprire momentan e naturala , ar trebui sa se intoarca in piata
	return;
}

void verificare_conectivitate(int **copie_roads) {
	//mai intai luam pe rand pietele. Drumurile pornesc de la piete deci verificam de la ele
	//piata fiind cub , are doar 4 porturi pe care se poate conecta
	for (int i = 0; i < h_grid; i++){
		for (int j = 0; j < w_grid; j++){
			if (zona_piete[i][j] == 2){
				//apelez o functie recursiva de cautare a conexiunilor pornind de la o piata
				//caut toate casele din zona de acoperire a pietii , si verific daca fiecare casa e conectata la piata respectiva
				//caz in care colorez casa
				for (int k = 0; k < h_grid; k++){
					for (int l = 0; l < w_grid; l++){
						copie_roads[i][j] = roads[i][j];
					}
				}
				cautare_recursiva(i, j, copie_roads);
			}
		}
	}
}

//functia care permite animatia
void DrawingWindow::onIdle()
{
	allow_construction = false;
	
	if (water_tiles[ycursor][xcursor] == 1) {
		make_casa = false;
		make_earth = false;
		enable_rotate = false;
		rotate_house = false;
		make_piata = false;
		make_road = false;
		make_water = false;
		make_grass = false;
	}
	if (pozitii_case[ycursor][xcursor] == 1) {
		make_grass = false;
	}
	if (earth_tiles[ycursor][xcursor] == 0) {
		make_casa = false;
		enable_rotate = false;
		rotate_house = false;
		make_piata = false;
		make_road = false;
		make_water = false;
		make_grass = false;
	}

	if (roads[ycursor][xcursor] == 1 || pozitii_case[ycursor][xcursor] == 1){
		make_water = false;
	}
	if (zona_piete[ycursor][xcursor] == 1){
		if (roads[ycursor][xcursor] == 1 || roads[ycursor - 1][xcursor] == 1 || roads[ycursor][xcursor - 1] == 1
			|| roads[ycursor + 1][xcursor] == 1 || roads[ycursor][xcursor + 1] == 1){
			make_casa = false;
			enable_rotate = false;
			rotate_house = false;
		}
		if (water_tiles[ycursor][xcursor] == 1 || water_tiles[ycursor - 1][xcursor] == 1 || water_tiles[ycursor][xcursor - 1] == 1
			|| water_tiles[ycursor + 1][xcursor] == 1 || water_tiles[ycursor][xcursor + 1] == 1){
			make_casa = false;
			enable_rotate = false;
			rotate_house = false;
		}
			allow_construction = true;
			createblock = false;
	}
	else {
		make_casa = false;
		enable_rotate = false;
		rotate_house = false;
	}
	if (make_earth) {
		make_earth = false;
		if (roads[ycursor][xcursor] == 0
			&& pozitii_case[ycursor][xcursor] == 0
			&& water_tiles[ycursor][xcursor] == 0) earth_tiles[ycursor][xcursor] = 1;
		if (zona_piete[ycursor][xcursor] == 1){
			patratzele_grid[ycursor][xcursor][0]->color = Color(0.6, 0.2, 0.6);
			patratzele_grid[ycursor][xcursor][0]->fill = true;
		}
		else {
			patratzele_grid[ycursor][xcursor][0]->color = Color(0.4, 0.2, 0);
			patratzele_grid[ycursor][xcursor][0]->fill = true;
		}
	}
	if (make_grass) { //&& zona_piete[ycursor][xcursor] == 0) {
		make_grass = false;
		grass_tiles[ycursor][xcursor] = 1;
		patratzele_grid[ycursor][xcursor][0]->color = Color(0.6,0.6,0);
		patratzele_grid[ycursor][xcursor][0]->fill = true;
	}
	if (make_water) {
		make_water = false;
		water_tiles[ycursor][xcursor] = 1;
		patratzele_grid[ycursor][xcursor][0]->color = Color(0.4,0.6,1);
		patratzele_grid[ycursor][xcursor][0]->fill = true;
	}

	if (make_piata) {
		//piata va avea culoarea 0 , 0.8 , 0.2
		//aria pietei va avea culoarea 0.6 , 0.2 , 0.6
		//o casa nu se poate construi decat in aria pietei
		//o casa e recolorata daca e conectata la piata
		//aria pietei trebuie sa fie relativ mare ,  sa incapa multe case , sau sa avem mai multe piete pe harta
		make_piata = false;
		createblock = true; //practic construiesc un block ,dar pun niste conditii speciale in el
		conditii_piata = true;
	}
	if (enter_house && zona_piete[ycursor][xcursor - 1] == 1 && zona_piete[ycursor - 1][xcursor] == 1
		&& zona_piete[ycursor][xcursor + 1] == 1 && zona_piete[ycursor + 1][xcursor] == 1) {

		enter_house = false;
		//inseamna ca vrem sa salvam pozitia casei si adaugam casa in patratzele_grid
		enable_rotate = false;
		for (int i = 0; i < 3; i++){
			patratzele_grid[ycursor + rotate_casa_y][xcursor + rotate_casa_x][inaltime_casa] = cuburi_casa[i];
		}
		indice_unic_casa++;
		pozitii_case[ycursor][xcursor] = indice_unic_casa;
		if (rotire_casa % 4 == 0) {
			pozitii_case[ycursor][xcursor - 1] = indice_unic_casa;
			pozitii_case[ycursor + 1][xcursor] = indice_unic_casa;
		}
		else if (rotire_casa % 4 == 1){
			pozitii_case[ycursor - 1][xcursor] = indice_unic_casa;
			pozitii_case[ycursor][xcursor - 1] = indice_unic_casa;
		}
		else if (rotire_casa % 4 == 2){
			pozitii_case[ycursor][xcursor + 1] = indice_unic_casa;
			pozitii_case[ycursor - 1][xcursor] = indice_unic_casa;
		}
		else {
			pozitii_case[ycursor + 1][xcursor] = indice_unic_casa;
			pozitii_case[ycursor][xcursor + 1] = indice_unic_casa;
		}
		nr_spam_buton_casa = 0;
		rotate_house = false;
		make_casa = false;
	}
	if (enable_rotate && zona_piete[ycursor][xcursor - 1] == 1 && zona_piete[ycursor - 1][xcursor] == 1
		&& zona_piete[ycursor][xcursor + 1] == 1 && zona_piete[ycursor + 1][xcursor] == 1) {

		movedown = false;
		moveup = false;
		moveleft = false;
		moveright = false;
		make_road = false;
		createblock = false;
	}
	if (moveup) {
		moveup = false;
		if (ycursor == 0){
			//nu fac ceva
		}
		else {
			if (case_albastre[ycursor][xcursor] == 1) {
				cursor->color = Color(0, 0, 1);
				cursor->fill = true;
			}
			else if (case_aprinse[ycursor][xcursor] == 1){
				cursor->color = Color(0.6, 0.8, 0);
				cursor->fill = true;
			}
			else if (roads[ycursor][xcursor] == 1 && allow_construction) {
				cursor->color = Color(0.5, 0.5, 0.5);
				cursor->fill = true;
			}
			else if (water_tiles[ycursor][xcursor] == 1){
				cursor->color = Color(0.4, 0.6, 1);
				cursor->fill = true;
			}
			else if (grass_tiles[ycursor][xcursor] == 1) {
				cursor->color = Color(0.6, 0.6, 0);
				cursor->fill = true;
			}
			else if (earth_tiles[ycursor][xcursor] == 1 && zona_piete[ycursor][xcursor] == 1){
				cursor->color = Color(0.6, 0.2, 0.6);
				cursor->fill = true;
			}
			else if (earth_tiles[ycursor][xcursor] == 1){
				cursor->color = Color(0.4, 0.2, 0);
				cursor->fill = true;
			}
			else if (zona_piete[ycursor][xcursor] == 1) {
				cursor->color = Color(0.6, 0.2, 0.6);
				cursor->fill = false;
			}
			else {
				cursor->color = Color(0.4, 0.4, 0);
				cursor->fill = false;
			}
			ycursor--;
			cursor = patratzele_grid[ycursor][xcursor][0];
			cursor->color = Color(1, 0, 0);
			cursor->fill = true;
		}
	}
	if (movedown) {
		movedown = false;
		if (ycursor == h_grid - 1){

		}
		else {
			if (case_albastre[ycursor][xcursor] == 1) {
				cursor->color = Color(0, 0, 1);
				cursor->fill = true;
			}
			else if (case_aprinse[ycursor][xcursor] == 1){
				cursor->color = Color(0.6, 0.8, 0);
				cursor->fill = true;
			}
			else if (roads[ycursor][xcursor] == 1 && allow_construction) {
				cursor->color = Color(0.5, 0.5, 0.5);
				cursor->fill = true;
			}
			else if (water_tiles[ycursor][xcursor] == 1){
				cursor->color = Color(0.4, 0.6, 1);
				cursor->fill = true;
			}
			else if (grass_tiles[ycursor][xcursor] == 1) {
				cursor->color = Color(0.6, 0.6, 0);
				cursor->fill = true;
			}
			else if (earth_tiles[ycursor][xcursor] == 1 && zona_piete[ycursor][xcursor] == 1){
				cursor->color = Color(0.6, 0.2, 0.6);
				cursor->fill = true;
			}
			else if (earth_tiles[ycursor][xcursor] == 1){
				cursor->color = Color(0.4, 0.2, 0);
				cursor->fill = true;
			}
			else if (zona_piete[ycursor][xcursor] == 1) {
				cursor->color = Color(0.6, 0.2, 0.6);
				cursor->fill = false;
			}
			else {
				cursor->color = Color(0.4, 0.4, 0);
				cursor->fill = false;
			}
			ycursor++;
			cursor = patratzele_grid[ycursor][xcursor][0];
			cursor->color = Color(1, 0, 0);
			cursor->fill = true;
		}
	}
	if (moveleft) {
		moveleft = false;
		if (xcursor == 0){
			//nu fac ceva
		}
		else {
			if (case_albastre[ycursor][xcursor] == 1) {
				cursor->color = Color(0, 0, 1);
				cursor->fill = true;
			}
			else if (case_aprinse[ycursor][xcursor] == 1){
				cursor->color = Color(0.6, 0.8, 0);
				cursor->fill = true;
			}
			else if (roads[ycursor][xcursor] == 1 && allow_construction) {
				cursor->color = Color(0.5, 0.5, 0.5);
				cursor->fill = true;
			}
			else if (water_tiles[ycursor][xcursor] == 1){
				cursor->color = Color(0.4, 0.6, 1);
				cursor->fill = true;
			}
			else if (grass_tiles[ycursor][xcursor] == 1) {
				cursor->color = Color(0.6, 0.6, 0);
				cursor->fill = true;
			}
			else if (earth_tiles[ycursor][xcursor] == 1 && zona_piete[ycursor][xcursor] == 1){
				cursor->color = Color(0.6, 0.2, 0.6);
				cursor->fill = true;
			}
			else if (earth_tiles[ycursor][xcursor] == 1){
				cursor->color = Color(0.4, 0.2, 0);
				cursor->fill = true;
			}
			else if (zona_piete[ycursor][xcursor] == 1) {
				cursor->color = Color(0.6, 0.2, 0.6);
				cursor->fill = false;
			}
			else {
				cursor->color = Color(0.4, 0.4, 0);
				cursor->fill = false;
			}
			xcursor--;
			cursor = patratzele_grid[ycursor][xcursor][0];
			cursor->color = Color(1, 0, 0);
			cursor->fill = true;

		}
	}
	if (moveright) {
		moveright = false;
		if (xcursor == w_grid - 1) {

		}
		else {
			if (case_albastre[ycursor][xcursor] == 1) {
				cursor->color = Color(0, 0, 1);
				cursor->fill = true;
			}
			else if (case_aprinse[ycursor][xcursor] == 1){
				cursor->color = Color(0.6, 0.8, 0);
				cursor->fill = true;
			}
			else if (roads[ycursor][xcursor] == 1 && allow_construction) {
				cursor->color = Color(0.5, 0.5, 0.5);
				cursor->fill = true;
			}
			else if (water_tiles[ycursor][xcursor] == 1){
				cursor->color = Color(0.4, 0.6, 1);
				cursor->fill = true;
			}
			else if (grass_tiles[ycursor][xcursor] == 1) {
				cursor->color = Color(0.6, 0.6, 0);
				cursor->fill = true;
			}
			else if (earth_tiles[ycursor][xcursor] == 1 && zona_piete[ycursor][xcursor] == 1){
				cursor->color = Color(0.6, 0.2, 0.6);
				cursor->fill = true;
			}
			else if (earth_tiles[ycursor][xcursor] == 1){
				cursor->color = Color(0.4, 0.2, 0);
				cursor->fill = true;
			}
			else if (zona_piete[ycursor][xcursor] == 1) {
				cursor->color = Color(0.6, 0.2, 0.6);
				cursor->fill = false;
			}
			else {
				cursor->color = Color(0.4, 0.4, 0);
				cursor->fill = false;
			}
			xcursor++;
			cursor = patratzele_grid[ycursor][xcursor][0];
			cursor->color = Color(1, 0, 0);
			cursor->fill = true;
		}
	}
	if (createblock) {
		createblock = false;
		numar_patratzele_construite_inainte_de_casa++;
		roads[ycursor][xcursor] = 0;		//evident se va distruge drumul daca punem un cub pe el
		vector <Point3D*> vertices;
		vector <Face*> faces;

		//varfurile de jos
		vertices.push_back(new Point3D(VERTEX_SIZE + xbase_for_blocks[ycursor][xcursor],
			offset_y,
			VERTEX_SIZE + ybase_for_blocks[ycursor][xcursor]));
		vertices.push_back(new Point3D(1 + xbase_for_blocks[ycursor][xcursor],
			offset_y,
			VERTEX_SIZE + ybase_for_blocks[ycursor][xcursor]));
		vertices.push_back(new Point3D(1 + xbase_for_blocks[ycursor][xcursor],
			offset_y,
			1 + ybase_for_blocks[ycursor][xcursor]));
		vertices.push_back(new Point3D(VERTEX_SIZE + xbase_for_blocks[ycursor][xcursor],
			offset_y,
			1 + ybase_for_blocks[ycursor][xcursor]));
		//varfurile de sus
		vertices.push_back(new Point3D(VERTEX_SIZE + xbase_for_blocks[ycursor][xcursor],
			offset_y + 1,
			VERTEX_SIZE + ybase_for_blocks[ycursor][xcursor]));
		vertices.push_back(new Point3D(1 + xbase_for_blocks[ycursor][xcursor],
			offset_y + 1,
			VERTEX_SIZE + ybase_for_blocks[ycursor][xcursor]));
		vertices.push_back(new Point3D(1 + xbase_for_blocks[ycursor][xcursor],
			offset_y + 1,
			1 + ybase_for_blocks[ycursor][xcursor]));
		vertices.push_back(new Point3D(VERTEX_SIZE + xbase_for_blocks[ycursor][xcursor],
			offset_y + 1,
			1 + ybase_for_blocks[ycursor][xcursor]));

		//cele 6 fete
		vector <int> contour;
		//fata jos
		contour.clear();
		contour.push_back(0);
		contour.push_back(1);
		contour.push_back(2);
		contour.push_back(3);
		faces.push_back(new Face(contour));
		//fata sus
		contour.clear();
		contour.push_back(4);
		contour.push_back(5);
		contour.push_back(6);
		contour.push_back(7);
		faces.push_back(new Face(contour));
		//fata fata
		contour.clear();
		contour.push_back(0);
		contour.push_back(1);
		contour.push_back(5);
		contour.push_back(4);
		faces.push_back(new Face(contour));
		//fata dreapta
		contour.clear();
		contour.push_back(1);
		contour.push_back(2);
		contour.push_back(6);
		contour.push_back(5);
		faces.push_back(new Face(contour));
		//fata spate
		contour.clear();
		contour.push_back(2);
		contour.push_back(3);
		contour.push_back(7);
		contour.push_back(6);
		faces.push_back(new Face(contour));
		//fata stanga
		contour.clear();
		contour.push_back(3);
		contour.push_back(0);
		contour.push_back(4);
		contour.push_back(7);
		faces.push_back(new Face(contour));
		
		if (conditii_piata) {
			//in caz ca vreau sa construiesc un block piata , fac zona de acoperire si colorez special blockul
			conditii_piata = false;
			patratzele_grid[ycursor][xcursor][blocks[ycursor][xcursor]] = new Object3D(vertices, faces, Color(0, 0.8 , 0.2), true);
			for (int i = ycursor - ACOPERIRE_PIATA / 2; i <= ycursor + ACOPERIRE_PIATA / 2; i++)
				for (int j = xcursor - ACOPERIRE_PIATA / 2; j <= xcursor + ACOPERIRE_PIATA / 2; j++){
					if (i < h_grid && i >= 0 && j < w_grid && j >= 0){
						if (zona_piete[i][j] == 0) zona_piete[i][j] = 1;	//1 inseamna ca e zona de langa piata , iar 0 e restul
						if (roads[i][j] == 0 && pozitii_case[i][j] == 0) patratzele_grid[i][j][0]->color = Color(0.6, 0.2, 0.6);
						if (water_tiles[i][j] == 1) {
							patratzele_grid[i][j][0]->color = Color(0.4, 0.6, 1);
							patratzele_grid[i][j][0]->fill = true;
						}
						else if (grass_tiles[i][j] == 1){
							patratzele_grid[i][j][0]->color = Color(0.6, 0.6, 0);
							patratzele_grid[i][j][0]->fill = true;
						}
						else if (earth_tiles[i][j] == 1)  {
							patratzele_grid[i][j][0]->fill = true;
						}

					}
				}
			zona_piete[ycursor][xcursor] = 2;	//2 inseamna ca e piata insasi
			//fac drumul din jurul pietei
			for (int i = ycursor - 1; i <= ycursor + 1; i++){
				for (int j = xcursor - 1; j <= xcursor + 1; j++){
					roads[i][j] = 1;
					patratzele_grid[i][j][0]->color = Color(0.5,0.5,0.5);
					patratzele_grid[i][j][0]->fill = true;
				}
			}
		}
		else patratzele_grid[ycursor][xcursor][blocks[ycursor][xcursor]] = new Object3D(vertices, faces, Color(0, (float)xcursor / w_grid, (float)ycursor / h_grid), true);
		//stergerea si readaugarea elementelor pt a rezolva bugul vizual
		for (int i = 0; i < h_grid; i++)
			for (int j = 0; j < w_grid; j++){
				for (int k = 0; k < blocks[i][j]; k++)
			removeObject3D_from_Visual2D(patratzele_grid[i][j][k], v2d1);
		}
		nr_patratzele = -1;
		addObject3D_to_Visual2D(patratzele_grid[ycursor][xcursor][blocks[ycursor][xcursor]], v2d1);
		nr_total_obiecte++;
		Transform3D::loadIdentityModelMatrix();
		Transform3D::rotateMatrixOy(PI / 4);
		Transform3D::rotateMatrixOx(0.61472907f);
		Transform3D::applyTransform(v2d1->visual2D_objects3D[0]);
		xbase_for_blocks[ycursor][xcursor] = xcursor - blocks[ycursor][xcursor];
		ybase_for_blocks[ycursor][xcursor] = ycursor - blocks[ycursor][xcursor];
		blocks[ycursor][xcursor]++;
		nr_patratzele++;
		for (int i = w_grid - 1; i >= 0; i--){
			for (int j = h_grid - 1; j >= 0; j--){
					nr_patratzele++;
					addObject3D_to_Visual2D(patratzele_grid[j][i][0], v2d1);
					Transform3D::loadIdentityModelMatrix();
					Transform3D::rotateMatrixOy(PI / 4);
					Transform3D::rotateMatrixOx(0.61472907f);
					Transform3D::applyTransform(v2d1->visual2D_objects3D[nr_patratzele]);
			}
		}
		for (int i = w_grid - 1; i >= 0; i--){
			for (int j = h_grid - 1; j >= 0; j--){
				for (int k = 1; k <= blocks[j][i] - 1; k++){
						nr_patratzele++;
						addObject3D_to_Visual2D(patratzele_grid[j][i][k], v2d1);
						Transform3D::loadIdentityModelMatrix();
						Transform3D::rotateMatrixOy(PI / 4);
						Transform3D::rotateMatrixOx(0.61472907f);
						Transform3D::applyTransform(v2d1->visual2D_objects3D[nr_patratzele]);
				}
			}
		}
	}
	if (make_road && allow_construction) {
		make_road = false;
		//fac copia matricei de drumuri , pe care o voi folosi in DFS
		int **copie_roads;
		copie_roads = (int **)malloc(sizeof(int*) * h_grid);
		for (int i = 0; i < h_grid; i++)
			copie_roads[i] = (int *)malloc(sizeof(int) * w_grid);
		if (blocks[ycursor][xcursor] == 1)	{
			patratzele_grid[ycursor][xcursor][0]->fill = true;
			patratzele_grid[ycursor][xcursor][0]->color = Color(0.5,0.5,0.5);
			roads[ycursor][xcursor] = 1;
		}
		else {
			//ar fi frumos sa afisez ca nu pot construi drum , drumul il facem doar pe grid ... cica
		}
		//coloram aici toate casele in albastru
		for (int i = 0; i < h_grid; i++){
			for (int j = 0; j < w_grid; j++){
				copie_roads[i][j] = roads[i][j];
				if (pozitii_case[i][j] != 0){
					patratzele_grid[i][j][0]->color = Color(0, 0, 1);
					patratzele_grid[i][j][0]->fill = true;
					case_albastre[i][j] = 1;
				}
			}
		}
		verificare_conectivitate(copie_roads);
	}
	
	//inainte sa pun casa , cursorul va deveni casa si voi putea roti , apoi ca sa o asez , apas enter
	if (make_casa && nr_spam_buton_casa == 0
		&& zona_piete[ycursor][xcursor - 1] == 1 && zona_piete[ycursor - 1][xcursor] == 1
			&& zona_piete[ycursor][xcursor + 1] == 1 && zona_piete[ycursor + 1][xcursor] == 1) {
		nr_spam_buton_casa++;
		make_casa = false;	//casa default
		nr_total_obiecte = nr_total_obiecte + numar_patratzele_construite_inainte_de_casa;
		numar_patratzele_construite_inainte_de_casa = 0;
		cuburi_casa = (Object3D **)malloc(sizeof(Object3D)*3);
			for (int i = 0; i < 3; i++) {
				vector <Point3D*> vertices;
				vector <Face*> faces;
				//-1 0 ; 0 0 ; 0 1
				//o sa fac si rotirea
				//cazul default
				if (i == 0) {
					rotate_casa_x = -1;
					rotate_casa_y = 0;
				}
				else if (i == 1){
					rotate_casa_x = 0;
					rotate_casa_y = 0;
				}
				else {
					rotate_casa_x = 0;
					rotate_casa_y = 1;
				}
				//varfurile de jos
				vertices.push_back(new Point3D(VERTEX_SIZE + xbase_for_blocks[ycursor][xcursor] + rotate_casa_x,
					offset_y,
					VERTEX_SIZE + ybase_for_blocks[ycursor][xcursor] + rotate_casa_y));
				vertices.push_back(new Point3D(1 + xbase_for_blocks[ycursor][xcursor] + rotate_casa_x,
					offset_y,
					VERTEX_SIZE + ybase_for_blocks[ycursor][xcursor] + rotate_casa_y));
				vertices.push_back(new Point3D(1 + xbase_for_blocks[ycursor][xcursor] + rotate_casa_x,
					offset_y,
					1 + ybase_for_blocks[ycursor][xcursor] + rotate_casa_y));
				vertices.push_back(new Point3D(VERTEX_SIZE + xbase_for_blocks[ycursor][xcursor] + rotate_casa_x,
					offset_y,
					1 + ybase_for_blocks[ycursor][xcursor] + rotate_casa_y));
				//varfurile de sus
				vertices.push_back(new Point3D(VERTEX_SIZE + xbase_for_blocks[ycursor][xcursor] + rotate_casa_x,
					offset_y + 1,
					VERTEX_SIZE + ybase_for_blocks[ycursor][xcursor] + rotate_casa_y));
				vertices.push_back(new Point3D(1 + xbase_for_blocks[ycursor][xcursor] + rotate_casa_x,
					offset_y + 1,
					VERTEX_SIZE + ybase_for_blocks[ycursor][xcursor] + rotate_casa_y));
				vertices.push_back(new Point3D(1 + xbase_for_blocks[ycursor][xcursor] + rotate_casa_x,
					offset_y + 1,
					1 + ybase_for_blocks[ycursor][xcursor] + rotate_casa_y));
				vertices.push_back(new Point3D(VERTEX_SIZE + xbase_for_blocks[ycursor][xcursor] + rotate_casa_x,
					offset_y + 1,
					1 + ybase_for_blocks[ycursor][xcursor] + rotate_casa_y));

				//cele 6 fete
				vector <int> contour;
				//fata jos
				contour.clear();
				contour.push_back(0);
				contour.push_back(1);
				contour.push_back(2);
				contour.push_back(3);
				faces.push_back(new Face(contour));
				//fata sus
				contour.clear();
				contour.push_back(4);
				contour.push_back(5);
				contour.push_back(6);
				contour.push_back(7);
				faces.push_back(new Face(contour));
				//fata fata
				contour.clear();
				contour.push_back(0);
				contour.push_back(1);
				contour.push_back(5);
				contour.push_back(4);
				faces.push_back(new Face(contour));
				//fata dreapta
				contour.clear();
				contour.push_back(1);
				contour.push_back(2);
				contour.push_back(6);
				contour.push_back(5);
				faces.push_back(new Face(contour));
				//fata spate
				contour.clear();
				contour.push_back(2);
				contour.push_back(3);
				contour.push_back(7);
				contour.push_back(6);
				faces.push_back(new Face(contour));
				//fata stanga
				contour.clear();
				contour.push_back(3);
				contour.push_back(0);
				contour.push_back(4);
				contour.push_back(7);
				faces.push_back(new Face(contour));
				cuburi_casa[i] = new Object3D(vertices, faces, Color(0.2, 0.2, 0.2), false);
				addObject3D_to_Visual2D(cuburi_casa[i], v2d1);
				Transform3D::loadIdentityModelMatrix();
				Transform3D::rotateMatrixOy(PI / 4);
				Transform3D::rotateMatrixOx(0.61472907f);
				nr_total_obiecte++;
				Transform3D::applyTransform(v2d1->visual2D_objects3D[nr_total_obiecte]);
			}
			rotire_casa = 0;	
	}
	
	if (rotate_house && enable_rotate) {	//o putem roti doar daca e enabled rotirea
		//ramanem pe loc si rotim casa pana cand dam enter , apoi se elibereaza toate cheile non-scroll

		for (int i = 0; i < 3; i++)
		removeObject3D_from_Visual2D(cuburi_casa[i], v2d1);
		nr_total_obiecte -= 3;
		for (int i = 0; i < 3; i++) {
			vector <Point3D*> vertices;
			vector <Face*> faces;
			if (i == 0) {
				if (rotire_casa % 4 == 0) {
					rotate_casa_x = -1;
					rotate_casa_y = 0;
				}
				else if (rotire_casa % 4 == 1) {
					rotate_casa_x = 0;
					rotate_casa_y = -1;
				}
				else if (rotire_casa % 4 == 2) {
					rotate_casa_x = 1;
					rotate_casa_y = 0;
				}
				else if (rotire_casa % 4 == 3) {
					rotate_casa_x = 0;
					rotate_casa_y = 1;
				}
			}
			else if (i == 1){
				rotate_casa_x = 0;
				rotate_casa_y = 0;
			}
			else {
				if (rotire_casa % 4 == 0) {
					rotate_casa_x = 0;
					rotate_casa_y = 1;
				}
				else if (rotire_casa % 4 == 1) {
					rotate_casa_x = -1;
					rotate_casa_y = 0;
				}
				else if (rotire_casa % 4 == 2) {
					rotate_casa_x = 0;
					rotate_casa_y = -1;
				}
				else if (rotire_casa % 4 == 3) {
					rotate_casa_x = 1;
					rotate_casa_y = 0;
				}
			}
			
			//varfurile de jos
			vertices.push_back(new Point3D(VERTEX_SIZE + xbase_for_blocks[ycursor][xcursor] + rotate_casa_x,
				offset_y,
				VERTEX_SIZE + ybase_for_blocks[ycursor][xcursor] + rotate_casa_y));
			vertices.push_back(new Point3D(1 + xbase_for_blocks[ycursor][xcursor] + rotate_casa_x,
				offset_y,
				VERTEX_SIZE + ybase_for_blocks[ycursor][xcursor] + rotate_casa_y));
			vertices.push_back(new Point3D(1 + xbase_for_blocks[ycursor][xcursor] + rotate_casa_x,
				offset_y,
				1 + ybase_for_blocks[ycursor][xcursor] + rotate_casa_y));
			vertices.push_back(new Point3D(VERTEX_SIZE + xbase_for_blocks[ycursor][xcursor] + rotate_casa_x,
				offset_y,
				1 + ybase_for_blocks[ycursor][xcursor] + rotate_casa_y));
			//varfurile de sus
			vertices.push_back(new Point3D(VERTEX_SIZE + xbase_for_blocks[ycursor][xcursor] + rotate_casa_x,
				offset_y + 1,
				VERTEX_SIZE + ybase_for_blocks[ycursor][xcursor] + rotate_casa_y));
			vertices.push_back(new Point3D(1 + xbase_for_blocks[ycursor][xcursor] + rotate_casa_x,
				offset_y + 1,
				VERTEX_SIZE + ybase_for_blocks[ycursor][xcursor] + rotate_casa_y));
			vertices.push_back(new Point3D(1 + xbase_for_blocks[ycursor][xcursor] + rotate_casa_x,
				offset_y + 1,
				1 + ybase_for_blocks[ycursor][xcursor] + rotate_casa_y));
			vertices.push_back(new Point3D(VERTEX_SIZE + xbase_for_blocks[ycursor][xcursor] + rotate_casa_x,
				offset_y + 1,
				1 + ybase_for_blocks[ycursor][xcursor] + rotate_casa_y));

			//cele 6 fete
			vector <int> contour;
			//fata jos
			contour.clear();
			contour.push_back(0);
			contour.push_back(1);
			contour.push_back(2);
			contour.push_back(3);
			faces.push_back(new Face(contour));
			//fata sus
			contour.clear();
			contour.push_back(4);
			contour.push_back(5);
			contour.push_back(6);
			contour.push_back(7);
			faces.push_back(new Face(contour));
			//fata fata
			contour.clear();
			contour.push_back(0);
			contour.push_back(1);
			contour.push_back(5);
			contour.push_back(4);
			faces.push_back(new Face(contour));
			//fata dreapta
			contour.clear();
			contour.push_back(1);
			contour.push_back(2);
			contour.push_back(6);
			contour.push_back(5);
			faces.push_back(new Face(contour));
			//fata spate
			contour.clear();
			contour.push_back(2);
			contour.push_back(3);
			contour.push_back(7);
			contour.push_back(6);
			faces.push_back(new Face(contour));
			//fata stanga
			contour.clear();
			contour.push_back(3);
			contour.push_back(0);
			contour.push_back(4);
			contour.push_back(7);
			faces.push_back(new Face(contour));
			//foarte aiurea liniile astea , sunt doar pt debugging
			cuburi_casa[i] = new Object3D(vertices, faces, Color(0.2, 0.2, 0.2), false);
			addObject3D_to_Visual2D(cuburi_casa[i], v2d1);
			Transform3D::loadIdentityModelMatrix();
			Transform3D::rotateMatrixOy(PI / 4);
			Transform3D::rotateMatrixOx(0.61472907f);
			nr_total_obiecte++;
			Transform3D::applyTransform(v2d1->visual2D_objects3D[nr_total_obiecte]);
			}
	}

	if (translateTocursor) {
		translateTocursor = false;
		int xtranslate = xinitial - xcursor;
		int ytranslate = yinitial - ycursor;
		int nr = -1;
		for (int i = 0; i < h_grid; i++){
			for (int j = 0; j < w_grid; j++){
				nr++;
				Transform3D::loadIdentityModelMatrix();
				Transform3D::rotateMatrixOy(PI / 4);
				Transform3D::rotateMatrixOx(0.61472907f);
				Transform3D::translateMatrix(xtranslate, ytranslate, 0);
				Transform3D::applyTransform(v2d1->visual2D_objects3D[nr]);

			}
		}
		xinitial = xcursor;
		yinitial = ycursor;
	}
	if (activate_mouse) {
		for (int i = 0; i < h_grid; i++) {
			for (int j = 0; j < w_grid; j++){
				if (patratzele_grid[i][j][0]->transf_vertices[3]->x >= poz_mouse_x
					&& patratzele_grid[i][j][0]->transf_vertices[0]->x <= poz_mouse_x
					&& patratzele_grid[i][j][0]->transf_vertices[0]->z >= poz_mouse_y
					&& patratzele_grid[i][j][0]->transf_vertices[2]->z <= poz_mouse_y){
					patratzele_grid[i][j][0]->fill = true;
					activate_mouse = false;
				}
			}
			if (activate_mouse == false) break;
		}
		activate_mouse = false;
	}
	if (scroll_up) {

		scroll_up = false;
		yf2 = yf2 + PAS_SCROLL;
		yf1 = yf1 +  PAS_SCROLL;
		v2d1->fereastra(xf1, yf1, xf2, yf2);
	}
	if (scroll_down) {
		scroll_down = false;
		yf1 -= PAS_SCROLL;
		yf2 -= PAS_SCROLL;
		v2d1->fereastra(xf1, yf1, xf2, yf2);
	}
	if (scroll_right) {
		scroll_right = false;
		xf1 += PAS_SCROLL;
		xf2 += PAS_SCROLL;
		v2d1->fereastra(xf1, yf1, xf2, yf2);
	}
	if (scroll_left) {
		scroll_left = false;
		xf1 -= PAS_SCROLL;
		xf2 -= PAS_SCROLL;
		v2d1->fereastra(xf1, yf1, xf2, yf2);
	}
	if (delete_road) {
		//stergem din matricea de drumuri si facem clean pe ecran
		delete_road = false;
		roads[ycursor][xcursor] = 0;
		patratzele_grid[ycursor][xcursor][0]->fill = false;
		patratzele_grid[ycursor][xcursor][0]->color = Color(0.6,0.2,0.6);
	}
}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width, int height)
{

	v2d1->poarta(0, 0, width, height);
		

}

//functia care defineste ce se intampla cand se apasa pe tastatura
void DrawingWindow::onKey(unsigned char key)
{
	switch (key)
	{
	case 27: {
		exit(0);
		break;
	}
	case 102: {
		make_grass = true;
		break;
	}
	case 70: {
		make_grass = true;
		break;
	}
	case 113: {
		make_water = true;
		break;
	}
	case 81: {
		make_water = true;
		break;
	}
	case 101: {
		make_earth = true;
		break;
	}
	case 69: {
		make_earth = true;
		break;
	}
	case 127: {
		delete_road = true;
		break;
	}
	case 97 : {
		//translatie la dreapta
		moveleft = true;
		break;
	}
	case 65: {
		//translatie la dreapta
		moveleft = true;
		break;
	}
	case 119: {
		//translatie in jos
		moveup = true;
		break;
	}
	case 87: {
		//translatie in jos
		moveup = true;
		break;
	}
	case 115: {
		//translatie in sus
		movedown = true;
		break;
	}
	case 83: {
		//translatie in sus
		movedown = true;
		break;
	}
	case 100:{
		//translatie la stanga
		moveright = true;
		break;
	}
	case 68: {
		//translatie la stanga
		moveright = true;
		break;
	}
	case 116: { //t
		rotate_house = true;
		rotire_casa++;
		break;
	}
	case 84: {	//T
		rotate_house = true;
		rotire_casa++;
		break;
	}
	case 98: {	//B
		//cream un nou block la pozitia cursorului
		createblock = true;
		make_casa = false;
		break;
	}
	case 105: {	//b
		scroll_up = true;
		break;
	}
	case 73: {
		scroll_up = true;
		break;
	}
	case 106: {
		scroll_left = true;
		break;
	}
	case 74: {
		scroll_left = true;
		break;
	}
	case 107: {
		scroll_down = true;
		break;
	}
	case 75: {
		scroll_down = true;
		break;
	}
	case 108: {
		scroll_right = true;
		break;
	}
	case 76: {
		scroll_right = true;
		break;
	}
	case 114: {
		make_road = true;
		break;
	}
	case 82: {
		make_road = true;
		break;
	}
	case 99: {
		make_casa = true;
		enable_rotate = true;
		break;
	}
	case 67: {
		make_casa = true;
		enable_rotate = true;
		break;
	}
	case 112: {
		make_piata = true;
		break;
	}
	case 80: {
		make_piata = true;
		break;
	}
	case 13: {
		enter_house = true;
		enable_rotate = false;
		break;
	}
	}
}

//functia care defineste ce se intampla cand se da click pe mouse
void DrawingWindow::onMouse(int button, int state, int x, int y)
{
	
}


int main(int argc, char** argv)
{
	//creare fereastra
	DrawingWindow dw(argc, argv, 600, 600, 300, 100, "Laborator EGC");	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}