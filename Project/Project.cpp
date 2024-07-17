#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include <time.h>
#include <stdlib.h>

////map 
//
//7  
//
//8 *x=1000
//
//7
//
//8
//
//7
//
//8
//
//7
//
//
//  0   1   2   3   4   5   6
//7   8   9  10  11  12  13  14
// 15  16  17  18  19  20  21
//22  23  24  25  26  27  28  29
// 30  31  32  33  34  35  36
//37  38  39  40  41  42  43  44
// 45  46  47  48  49  50  51
//52  53  54  55  56  57  58  59








int position = 0;
int starting_point = 0;
int pengPos1[4];
int pengPos2[4];
int pengPos3[4];
int pengPos4[4];

int up_right[10];
int up_left[10];
int down_right[10];
int down_left[10];
int left[10];
int right[10];



int yellow_choosing_starting_point = 0;
int green_choosing_starting_point = 0;
int red_choosing_starting_point = 0;
int blue_choosing_starting_point = 0;

int yellow_choosing_ending_point = 0;
int green_choosing_ending_point = 0;
int red_choosing_ending_point = 0;
int blue_choosing_ending_point = 0;


int yellowSw = 0;
int greenSw = 0;
int redSw = 0;
int blueSw = 0;

int score_yellow = 0;
int score_green = 0;
int score_red = 0;
int score_blue = 0;

int Score[4] = { 0 };

int tile_yellow = 0;
int tile_green = 0;
int tile_red = 0;
int tile_blue = 0;

int Tile[4] = { 0 };


typedef struct ice {

	float bitmapx;
	float bitmapy;
	int mode; // 1fish=1 2fish=2 3fish=3 penguin=4 empty  ...
	int penguin_color;// 1=yellow 2=green 3=red 4=blue
	int penguin_number;  // 1-4 baste b tedad penguin haye har player 



};

struct ice ices[60];





int Row(int n) {

	int row = 0;

	if (0 <= n && n < 7) {
		row = 1;
	}

	else if (7 <= n && n < 15) {
		row = 2;
	}

	else if (15 <= n && n < 22) {
		row = 3;
	}

	else if (22 <= n && n < 30) {
		row = 4;
	}

	else if (30 <= n && n < 37) {
		row = 5;
	}

	else if (37 <= n && n < 45) {
		row = 6;
	}

	else if (45 <= n && n < 52) {
		row = 7;
	}

	else {
		row = 8;
	}


	return row;


}

int Column(int n) {

	int column = 0;

	if (Row(n) == 1) {
		column += (n - 0) + 1;
	}

	else if (Row(n) == 2) {
		column += (n - 7) + 1;
	}

	else if (Row(n) == 3) {
		column += (n - 15) + 1;
	}

	else if (Row(n) == 4) {
		column += (n - 22) + 1;
	}

	else if (Row(n) == 5) {
		column += (n - 30) + 1;
	}

	else if (Row(n) == 6) {
		column += (n - 37) + 1;
	}

	else if (Row(n) == 7) {
		column += (n - 45) + 1;
	}

	else {
		column += (n - 52) + 1;
	}

	return column;
}




void map_generation() {


	int temp;


	srand(time(NULL));

	for (int i = 0; i < 30; i++) {


		temp = rand() % 60;
		do {

			temp = rand() % 60;

		} while (ices[temp].mode >= 1 && ices[temp].mode <= 3);
		ices[temp].mode = 1;

	}

	for (int i = 0; i < 20; i++) {

		do {

			temp = rand() % 60;


		} while (ices[temp].mode >= 1 && ices[temp].mode <= 3);

		ices[temp].mode = 2;

	}


	for (int i = 0; i < 10; i++) {
		do {

			temp = rand() % 60;


		} while (ices[temp].mode >= 1 && ices[temp].mode <= 3);

		ices[temp].mode = 3;

	}

}



void map_loading(int loaded, ALLEGRO_BITMAP* pengy, ALLEGRO_BITMAP* pengg, ALLEGRO_BITMAP* pengr, ALLEGRO_BITMAP* pengb, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* empty, ALLEGRO_BITMAP* onefish, ALLEGRO_BITMAP* twofish, ALLEGRO_BITMAP* threefish, int monitor_width, int monitor_height) {

	if (loaded == 1) {

	}
	else {
		map_generation();
	}




	float x;
	float y;

	float icew = al_get_bitmap_width(twofish);
	float iceh = al_get_bitmap_height(twofish);

	float xras = 0.05 * monitor_width;
	float yras = 0.05 * monitor_height;

	float xfasele = 0.006 * monitor_width;
	float yfasele = 0.007 * monitor_height;

	float xchange = icew / 2;



	for (int i = 0; i < 60; i++) {


		int row = Row(i);
		int column = Column(i);



		if (row % 2 != 0) {

			x = xras + (column - 1) * icew + xfasele * (column - 1);

			y = yras + (row - 1) * 0.75 * iceh + yfasele * (row - 1);

			ices[i].bitmapx = x;
			ices[i].bitmapy = y;

			if (ices[i].mode == 1) {

				al_draw_bitmap(onefish, x, y, 0);

			}
			else if (ices[i].mode == 2) {

				al_draw_bitmap(twofish, x, y, 0);

			}
			else if (ices[i].mode == 3) {

				al_draw_bitmap(threefish, x, y, 0);

			}
			else if (ices[i].mode == 4) {


				if (ices[i].penguin_color == 1) {

					al_draw_bitmap(pengy, ices[i].bitmapx, ices[i].bitmapy, 0);
					al_flip_display(display);

				}
				if (ices[i].penguin_color == 2) {

					al_draw_bitmap(pengg, ices[i].bitmapx, ices[i].bitmapy, 0);
					al_flip_display(display);

				}

				if (ices[i].penguin_color == 3) {

					al_draw_bitmap(pengr, ices[i].bitmapx, ices[i].bitmapy, 0);
					al_flip_display(display);

				}
				if (ices[i].penguin_color == 4) {

					al_draw_bitmap(pengb, ices[i].bitmapx, ices[i].bitmapy, 0);
					al_flip_display(display);
				}
			}
			else if (ices[i].mode == 5) {
				al_draw_bitmap(empty, x, y, 0);
			}
		}
		else {

			x = xras + (column - 1) * icew + xfasele * (column - 1) - xchange;

			y = yras + (row - 1) * 0.75 * iceh + yfasele * (row - 1);


			ices[i].bitmapx = x;
			ices[i].bitmapy = y;

			if (ices[i].mode == 1) {

				al_draw_bitmap(onefish, x, y, 0);

			}
			else if (ices[i].mode == 2) {

				al_draw_bitmap(twofish, x, y, 0);

			}
			else if (ices[i].mode == 3) {

				al_draw_bitmap(threefish, x, y, 0);

			}
			else if (ices[i].mode == 4) {
				if (ices[i].penguin_color == 1) {

					al_draw_bitmap(pengy, ices[i].bitmapx, ices[i].bitmapy, 0);
					al_flip_display(display);

				}
				if (ices[i].penguin_color == 2) {

					al_draw_bitmap(pengg, ices[i].bitmapx, ices[i].bitmapy, 0);
					al_flip_display(display);

				}

				if (ices[i].penguin_color == 3) {

					al_draw_bitmap(pengr, ices[i].bitmapx, ices[i].bitmapy, 0);
					al_flip_display(display);

				}
				if (ices[i].penguin_color == 4) {

					al_draw_bitmap(pengb, ices[i].bitmapx, ices[i].bitmapy, 0);
					al_flip_display(display);
				}
			}
			else if (ices[i].mode == 5) {
				al_draw_bitmap(empty, x, y, 0);
			}
		}

	}
}


void bitmap_turn(ALLEGRO_BITMAP* turnr, ALLEGRO_BITMAP* turnb, ALLEGRO_BITMAP* turny, ALLEGRO_BITMAP* turng, int turn, ALLEGRO_DISPLAY* display) {

	ALLEGRO_MONITOR_INFO info;

	al_get_monitor_info(0, &info);

	int monitor_width = info.x2 - info.x1;
	int monitor_height = info.y2 - info.y1;


	if (turn == 1) {
		//yellow penguin
		al_draw_bitmap(turny, 0.6 * monitor_width, 0.02 * monitor_height, 0);
		al_flip_display(display);
	}

	else if (turn == 2) {
		//green penguin
		al_draw_bitmap(turng, 0.6 * monitor_width, 0.02 * monitor_height, 0);
		al_flip_display(display);
	}

	else if (turn == 3) {
		//red penguin
		al_draw_bitmap(turnr, 0.6 * monitor_width, 0.02 * monitor_height, 0);
		al_flip_display(display);
	}

	else {

		//blue penguin
		al_draw_bitmap(turnb, 0.6 * monitor_width, 0.02 * monitor_height, 0);
		al_flip_display(display);


	}

}

int row_check(int position) {//por shodan radif

	if (Row(position) % 2 != 0) {
		for (int i = 0; i < 7; i++) {
			if (ices[position + i].mode != 4) {
				return 0;
			}
		}
	}
	else {
		for (int i = 0; i < 8; i++) {
			if (ices[position + i].mode != 4) {
				return 0;
			}
		}

	}
	return 1;

}


int backward_forward_check(int position, int mode) {//aval akhar araye

	if (mode == -1) {

		for (int i = 0; i < position; i++) {
			if (ices[i].mode != 4) {
				return 0;
			}
		}
		return 1;


	}
	else {

		for (int i = position; i < 59; i++) {
			if (ices[i].mode != 4) {
				return 0;
			}
		}

		return 1;




	}






}


void choosing_ice_cap(int movement) {//entekhab vase entekhab jaye avalie panguina

	int temp = position;

	//rast
	if (movement == 1) {

		position += 1;

	}
	//chap
	else if (movement == -1) {
		position -= 1;
	}
	//bala                                                                              
	else if (movement == 2) {

		if (Row(position) % 2 == 0) {

			position -= (Column(position) + 6);

		}

		else {

			position -= (Column(position) + 7);

		}

	}
	//payin
	else {

		if (Row(position) % 2 == 0) {

			position += 8 - (Column(position) - 1);
		}

		else {

			position += 7 - (Column(position) - 1);

		}

	}

	if (position < 0 || position>59)
		position = temp;

	temp = position;
	if (ices[position].mode == 4) {






		if (movement == 1) {

			if (backward_forward_check(position, 1) == 1) {
				while (ices[position].mode == 4) {
					position -= 1;
				}
			}
			else {
				while (ices[position].mode == 4) {
					position += 1;
				}
			}





		}

		else if (movement == -1) {

			if (backward_forward_check(position, -1) == 1) {
				while (ices[position].mode == 4) {
					position += 1;
				}
			}
			else {
				while (ices[position].mode == 4) {
					position -= 1;
				}
			}







		}
		else if (movement == 2) {

			if (row_check(position) == 1 && position != 0) {

				while (ices[position].mode == 4) {
					position -= 1;
				}
			}
			else {
				while (ices[position].mode == 4) {
					position += 1;
				}
			}




		}
		else if (movement == -2) {





			if (row_check(position) == 1 && position == 52) {

				position = 45;


			}
			else {
				while (ices[position].mode == 4) {
					position += 1;
				}
			}

		}


		if (position < 0 || position>59) {
			position = temp;
		}


	}




}

void highlighter(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* onefish, ALLEGRO_BITMAP* twofish, ALLEGRO_BITMAP* threefish, ALLEGRO_BITMAP* onefishh, ALLEGRO_BITMAP* twofishh, ALLEGRO_BITMAP* threefishh, int mode) {


	if (mode == -1) {

		if (ices[position].mode == 1) {

			al_draw_bitmap(onefish, ices[position].bitmapx, ices[position].bitmapy, 0);

		}
		else if (ices[position].mode == 2) {

			al_draw_bitmap(twofish, ices[position].bitmapx, ices[position].bitmapy, 0);

		}

		else if (ices[position].mode == 3) {

			al_draw_bitmap(threefish, ices[position].bitmapx, ices[position].bitmapy, 0);

		}


	}

	else {

		if (ices[position].mode == 1) {

			al_draw_bitmap(onefishh, ices[position].bitmapx, ices[position].bitmapy, 0);

		}
		else if (ices[position].mode == 2) {

			al_draw_bitmap(twofishh, ices[position].bitmapx, ices[position].bitmapy, 0);

		}

		else if (ices[position].mode == 3) {

			al_draw_bitmap(threefishh, ices[position].bitmapx, ices[position].bitmapy, 0);

		}


	}


	al_flip_display(display);

}




void move_to_choose(int pengno, ALLEGRO_BITMAP* turnr, ALLEGRO_BITMAP* turnb, ALLEGRO_BITMAP* turny, ALLEGRO_BITMAP* turng, int turn, int show_turn, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* onefish, ALLEGRO_BITMAP* twofish, ALLEGRO_BITMAP* threefish, ALLEGRO_BITMAP* onefishh, ALLEGRO_BITMAP* twofishh, ALLEGRO_BITMAP* threefishh, ALLEGRO_BITMAP* ypenguin, ALLEGRO_BITMAP* gpenguin, ALLEGRO_BITMAP* rpenguin, ALLEGRO_BITMAP* bpenguin) {    //pengno=chandomin penguin baraye har rang

	//harekat vase entekhab jaye avalie panguina

	ALLEGRO_KEYBOARD_STATE keystate;
	al_get_keyboard_state(&keystate);
	do {


		if (al_key_down(&keystate, ALLEGRO_KEY_RIGHT)) {
			highlighter(display, onefish, twofish, threefish, onefishh, twofishh, threefishh, -1);
			choosing_ice_cap(1);
			highlighter(display, onefish, twofish, threefish, onefishh, twofishh, threefishh, 1);
		}

		else if (al_key_down(&keystate, ALLEGRO_KEY_LEFT)) {
			highlighter(display, onefish, twofish, threefish, onefishh, twofishh, threefishh, -1);
			choosing_ice_cap(-1);
			highlighter(display, onefish, twofish, threefish, onefishh, twofishh, threefishh, 1);
		}

		else if (al_key_down(&keystate, ALLEGRO_KEY_UP)) {
			highlighter(display, onefish, twofish, threefish, onefishh, twofishh, threefishh, -1);
			choosing_ice_cap(2);
			highlighter(display, onefish, twofish, threefish, onefishh, twofishh, threefishh, 1);
		}

		else if (al_key_down(&keystate, ALLEGRO_KEY_DOWN)) {
			highlighter(display, onefish, twofish, threefish, onefishh, twofishh, threefishh, -1);
			choosing_ice_cap(-2);
			highlighter(display, onefish, twofish, threefish, onefishh, twofishh, threefishh, 1);
		}
		al_rest(0.09);
		al_get_keyboard_state(&keystate);
	} while (!al_key_down(&keystate, ALLEGRO_KEY_ENTER));


	ices[position].penguin_color = turn; //save shomare khode player/penguin

	ices[position].penguin_number = pengno; //chandomin penguin

	if (ices[position].penguin_color == 1) {

		score_yellow += ices[position].mode;



		tile_yellow++;


	}

	else if (ices[position].penguin_color == 2) {

		score_green += ices[position].mode;
		tile_green++;

	}

	else if (ices[position].penguin_color == 3) {

		score_red += ices[position].mode;
		tile_red++;

	}

	else if (ices[position].penguin_color == 4) {

		score_blue += ices[position].mode;
		tile_blue++;

	}



	if (turn == 1) {


		al_draw_bitmap(ypenguin, ices[position].bitmapx, ices[position].bitmapy, 0);

	}

	else if (turn == 2) {

		al_draw_bitmap(gpenguin, ices[position].bitmapx, ices[position].bitmapy, 0);
	}

	else if (turn == 3) {

		al_draw_bitmap(rpenguin, ices[position].bitmapx, ices[position].bitmapy, 0);
	}

	else {

		al_draw_bitmap(bpenguin, ices[position].bitmapx, ices[position].bitmapy, 0);

	}

	if (position == starting_point) {
		starting_point++;
	}



	bitmap_turn(turnr, turnb, turny, turng, show_turn, display);


	ices[position].mode = 4;




	position = starting_point;

	al_rest(0.1);




}




void PengFinder() {



	int Yno = 0; //shomarande peng player e 1
	int Gno = 0;
	int Rno = 0;
	int Bno = 0;


	for (int i = 0; i < 4; i++) {
		pengPos1[i] = -2;
		pengPos2[i] = -2;
		pengPos3[i] = -2;
		pengPos4[i] = -2;
	}

	for (int i = 0; i < 60; i++) {

		if (ices[i].penguin_color == 1 && ices[i].mode == 4) {

			pengPos1[Yno] = i;


			Yno++;



		}

		else if (ices[i].penguin_color == 2 && ices[i].mode == 4) {

			pengPos2[Gno] = i;

			Gno++;
		}

		else if (ices[i].penguin_color == 3 && ices[i].mode == 4) {

			pengPos3[Rno] = i;

			Rno++;
		}

		else if (ices[i].penguin_color == 4 && ices[i].mode == 4) {

			pengPos4[Bno] = i;

			Bno++;

		}





	}





}





void penguin_highlighter(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pengy, ALLEGRO_BITMAP* pengg, ALLEGRO_BITMAP* pengr, ALLEGRO_BITMAP* pengb, ALLEGRO_BITMAP* pengyh, ALLEGRO_BITMAP* penggh, ALLEGRO_BITMAP* pengrh, ALLEGRO_BITMAP* pengbh, int mode) {

	//jabejayi panguina
	if (mode == -1) {


		if (ices[position].penguin_color == 1) {

			al_draw_bitmap(pengy, ices[position].bitmapx, ices[position].bitmapy, 0);
			al_flip_display(display);

		}
		if (ices[position].penguin_color == 2) {

			al_draw_bitmap(pengg, ices[position].bitmapx, ices[position].bitmapy, 0);
			al_flip_display(display);

		}

		if (ices[position].penguin_color == 3) {

			al_draw_bitmap(pengr, ices[position].bitmapx, ices[position].bitmapy, 0);
			al_flip_display(display);

		}
		if (ices[position].penguin_color == 4) {

			al_draw_bitmap(pengb, ices[position].bitmapx, ices[position].bitmapy, 0);
			al_flip_display(display);
		}



	}


	if (mode == 1) {



		if (ices[position].penguin_color == 1) {

			al_draw_bitmap(pengyh, ices[position].bitmapx, ices[position].bitmapy, 0);
			al_flip_display(display);

		}
		if (ices[position].penguin_color == 2) {

			al_draw_bitmap(penggh, ices[position].bitmapx, ices[position].bitmapy, 0);
			al_flip_display(display);

		}

		if (ices[position].penguin_color == 3) {

			al_draw_bitmap(pengrh, ices[position].bitmapx, ices[position].bitmapy, 0);
			al_flip_display(display);

		}
		if (ices[position].penguin_color == 4) {

			al_draw_bitmap(pengbh, ices[position].bitmapx, ices[position].bitmapy, 0);
			al_flip_display(display);
		}



	}




}




void checking_chooseable_ices(int peng, int position) {       // barresi e ja hayi k har peng mitavanad beravad

	//peida kardane makan haye momken baraye harket +


	int r = 0;       //shomarande baraye harekat be samte rast
	int l = 0;
	int ur = 0;
	int dr = 0;
	int ul = 0;
	int dl = 0;






	if (Row(position) % 2 != 0) {


		int maxFard = 6 + (8 * (Row(position) / 2)) + (7 * (Row(position) / 2)); //max shomareye har positioni ke dar radife farde
		int minFard = (8 * (Row(position) / 2)) + (7 * (Row(position) / 2));  //min shomareye har positioni ke dar radife farde

		for (int i = position + 1; i >= 0 && i <= maxFard && i <= 59; i++) {   //right movement for odd row

			if (ices[i].mode != 4 && ices[i].mode != 5) {
				right[r] = i;

				r++;
			}

			else break;

		}

		for (int i = position - 1; i >= 0 && i >= minFard && i <= 59; i--) {  //left movement for odd row

			if (ices[i].mode != 4 && ices[i].mode != 5) {
				left[l] = i;

				l++;
			}
			else break;

		}

	}

	else {

		int maxZoj = 6 + (8 * (Row(position) / 2)) + (7 * (Row(position) / 2 - 1));
		int minZoj = (8 * (Row(position) / 2 - 1)) + (7 * (Row(position) / 2));

		for (int i = position + 1; i >= 0 && i <= maxZoj && i <= 59; i++) {       //right movement for even row

			if (ices[i].mode != 4 && ices[i].mode != 5) {
				right[r] = i;

				r++;
			}
			else break;

		}

		for (int i = position - 1; i >= 0 && i >= minZoj && i <= 59; i--) {      //left movement for even row

			if (ices[i].mode != 4 && ices[i].mode != 5) {
				left[l] = i;

				l++;
			}
			else break;

		}

	}

	for (int i = position - 7; i >= 0 && i >= position - (7 * (Row(position) - 1)) && i <= 59 && i >= max_finder(position, 1); i = i - 7) {       //up-right movement


		if (ices[i].mode != 4 && ices[i].mode != 5) {
			up_right[ur] = i;

			ur++;
		}
		else break;

	}

	for (int i = position + 8; i <= position + (8 * (8 - Row(position))) && i >= 0 && i <= 59 && i <= max_finder(position, -1); i = i + 8) {       //down-right movement


		if (ices[i].mode != 4 && ices[i].mode != 5) {
			down_right[dr] = i;

			dr++;
		}
		else break;

	}

	for (int i = position - 8; i >= 0 && i >= position - (8 * (Row(position) - 1)) && i <= 59 && i >= min_finder(position, 1); i = i - 8) {       //up-left movement


		if (ices[i].mode != 4 && ices[i].mode != 5) {
			up_left[ul] = i;

			ul++;
		}
		else break;

	}

	for (int i = position + 7; i >= 0 && i <= position + (7 * (8 - Row(position))) && i <= 59 && i <= min_finder(position, -1); i = i + 7) {       //down-left movement


		if (ices[i].mode != 4 && ices[i].mode != 5) {
			down_left[dl] = i;

			dl++;
		}
		else break;

	}


	if (r == 0 && l == 0 && ur == 0 && ul == 0 && dr == 0 && dl == 0)
	{


		if (ices[position].penguin_color == 1) {
			int i = 0;
			for (i; i < peng; i++) {
				if (pengPos1[i] == position) {
					break;
				}
			}

			pengPos1[i] = -1;

		}


		else if (ices[position].penguin_color == 2) {

			int i = 0;
			for (i; i < peng; i++) {
				if (pengPos2[i] == position) {
					break;
				}
			}

			pengPos2[i] = -1;

		}

		else if (ices[position].penguin_color == 3) {
			int i = 0;
			for (i; i < peng; i++) {
				if (pengPos3[i] == position) {
					break;
				}
			}
			pengPos3[i] = -1;

		}

		else if (ices[position].penguin_color == 4) {
			int i = 0;
			for (i; i < peng; i++) {
				if (pengPos4[i] == position) {
					break;
				}
			}
			pengPos4[i] = -1;

		}


	}


}





void peng_pos_chooser(int penguin_num, ALLEGRO_BITMAP* turnr, ALLEGRO_BITMAP* turnb, ALLEGRO_BITMAP* turny, ALLEGRO_BITMAP* turng, int pengcolor, int penguin_number, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pengy, ALLEGRO_BITMAP* pengg, ALLEGRO_BITMAP* pengr, ALLEGRO_BITMAP* pengb, ALLEGRO_BITMAP* pengyh, ALLEGRO_BITMAP* penggh, ALLEGRO_BITMAP* pengrh, ALLEGRO_BITMAP* pengbh) {


	//entekhab inke kodam pangan ra harekat dahad

	int i = 1;


	ALLEGRO_KEYBOARD_STATE keystate;
	al_get_keyboard_state(&keystate);


	al_rest(0.09);




	for (int i = 0; i < penguin_num; i++) {
		checking_chooseable_ices(penguin_num, pengPos1[i]);

	}






	while (pengPos1[yellow_choosing_starting_point] == -1) {
		yellow_choosing_starting_point++;
		if (yellow_choosing_starting_point == penguin_num) {

			yellowSw = 1;
			return;
		}




	}
	if (pengcolor == 1) {
		position = pengPos1[yellow_choosing_starting_point];
	}





	for (int i = 0; i < penguin_num; i++) {
		checking_chooseable_ices(penguin_num, pengPos2[i]);

	}








	while (pengPos2[green_choosing_starting_point] == -1) {
		green_choosing_starting_point++;


		if (green_choosing_starting_point == penguin_num) {
			greenSw = 1;
			return;

		}


	}
	if (pengcolor == 2) {
		position = pengPos2[green_choosing_starting_point];
	}




	for (int i = 0; i < penguin_num; i++) {
		checking_chooseable_ices(penguin_num, pengPos3[i]);

	}


	while (pengPos3[red_choosing_starting_point] == -1) {

		red_choosing_starting_point++;

		if (red_choosing_starting_point == penguin_num) {
			redSw = 1;
			return;
		}



	}
	if (pengcolor == 3) {
		position = pengPos3[red_choosing_starting_point];

	}



	for (int i = 0; i < penguin_num; i++) {
		checking_chooseable_ices(penguin_num, pengPos4[i]);

	}



	while (pengPos4[blue_choosing_starting_point] == -1) {
		blue_choosing_starting_point++;

		if (blue_choosing_starting_point == penguin_num) {

			blueSw = 1;
			return;
		}



	}
	if (pengcolor == 4) {
		position = pengPos4[blue_choosing_starting_point];

	}




	for (int i = 3; i >= 0; i--) {
		if (pengPos1[i] != -1) {
			yellow_choosing_ending_point = i;
			break;
		}

	}
	for (int i = 3; i >= 0; i--) {
		if (pengPos2[i] != -1) {
			green_choosing_ending_point = i;
			break;
		}

	}
	for (int i = 3; i >= 0; i--) {
		if (pengPos3[i] != -1) {
			red_choosing_ending_point = i;
			break;
		}

	}
	for (int i = 3; i >= 0; i--) {

		if (pengPos4[i] != -1) {
			blue_choosing_ending_point = i;
			break;
		}

	}





	penguin_highlighter(display, pengy, pengg, pengr, pengb, pengyh, penggh, pengrh, pengbh, 1);


	do {


		if (al_key_down(&keystate, ALLEGRO_KEY_RIGHT)) {
			al_rest(0.01);

			if (pengcolor == 1 && i > yellow_choosing_ending_point) {
				i = yellow_choosing_starting_point;
			}
			else if (pengcolor == 2 && i > green_choosing_ending_point) {
				i = green_choosing_starting_point;
			}
			else if (pengcolor == 3 && i > red_choosing_ending_point) {
				i = red_choosing_starting_point;

			}
			else if (pengcolor == 4 && i > blue_choosing_ending_point) {
				i = blue_choosing_starting_point;
			}




			if (pengcolor == 1) {
				if (pengPos1[i] >= 0) {
					penguin_highlighter(display, pengy, pengg, pengr, pengb, pengyh, penggh, pengrh, pengbh, -1);
					position = pengPos1[i];

				}
				i++;

			}
			else if (pengcolor == 2) {

				if (pengPos2[i] >= 0) {
					penguin_highlighter(display, pengy, pengg, pengr, pengb, pengyh, penggh, pengrh, pengbh, -1);
					position = pengPos2[i];

				}
				i++;

			}
			else if (pengcolor == 3) {

				if (pengPos3[i] >= 0) {
					penguin_highlighter(display, pengy, pengg, pengr, pengb, pengyh, penggh, pengrh, pengbh, -1);
					position = pengPos3[i];

				}
				i++;

			}
			else if (pengcolor == 4) {

				if (pengPos4[i] >= 0) {
					penguin_highlighter(display, pengy, pengg, pengr, pengb, pengyh, penggh, pengrh, pengbh, -1);
					position = pengPos4[i];

				}
				i++;

			}



			penguin_highlighter(display, pengy, pengg, pengr, pengb, pengyh, penggh, pengrh, pengbh, 1);

		}

		else if (al_key_down(&keystate, ALLEGRO_KEY_LEFT)) {
			al_rest(0.01);
			if (pengcolor == 1 && i < yellow_choosing_starting_point) {
				i = yellow_choosing_ending_point;
			}
			else if (pengcolor == 2 && i < green_choosing_starting_point) {
				i = green_choosing_ending_point;
			}
			else if (pengcolor == 3 && i < red_choosing_starting_point) {
				i = red_choosing_ending_point;

			}
			else if (pengcolor == 4 && i < blue_choosing_starting_point) {
				i = blue_choosing_ending_point;
			}



			if (pengcolor == 1) {

				if (pengPos1[i] >= 0) {
					penguin_highlighter(display, pengy, pengg, pengr, pengb, pengyh, penggh, pengrh, pengbh, -1);
					position = pengPos1[i];

				}

				i--;

			}
			else if (pengcolor == 2) {


				if (pengPos2[i] >= 0) {
					penguin_highlighter(display, pengy, pengg, pengr, pengb, pengyh, penggh, pengrh, pengbh, -1);
					position = pengPos2[i];

				}

				i--;

			}
			else if (pengcolor == 3) {

				if (pengPos3[i] >= 0) {
					penguin_highlighter(display, pengy, pengg, pengr, pengb, pengyh, penggh, pengrh, pengbh, -1);
					position = pengPos3[i];

				}
				i--;

			}
			else  if (pengcolor == 4) {

				if (pengPos4[i] >= 0) {
					penguin_highlighter(display, pengy, pengg, pengr, pengb, pengyh, penggh, pengrh, pengbh, -1);
					position = pengPos4[i];

				}
				i--;

			}

			penguin_highlighter(display, pengy, pengg, pengr, pengb, pengyh, penggh, pengrh, pengbh, 1);

		}


		al_rest(0.15);

		al_get_keyboard_state(&keystate);



	} while (!al_key_down(&keystate, ALLEGRO_KEY_ENTER));




	al_rest(0.3);








}




int min_finder(int position, int mode) {

	//minimum jabejayi baraye harekat orib

	if (mode == 1) {//up left


		for (int i = position; i >= 0 && i <= 59; i = i - 8) {



			if (i == 37) {
				return 37;
			}
			if (i == 22) {
				return 22;
			}
			if (i == 7) {
				return 7;
			}



		}
		return position - (8 * (Row(position) - 1));


	}
	else {//down left

		for (int i = position; i >= 0 && i <= 59; i = i + 7) {

			if (i == 7) {
				return 7;
			}
			if (i == 22) {
				return 22;
			}
			if (i == 37) {
				return 37;
			}
			if (i == 52) {
				return 52;
			}
		}

		return position + (7 * (8 - Row(position)));


	}








}

int max_finder(int position, int mode) {

	//maximum jabejayi baraye harekat orib

	if (mode == 1) {// up right


		for (int i = position; i >= 0 && i <= 59; i = i - 7) {


			if (i == 44) {
				return 44;
			}
			if (i == 29) {
				return 29;
			}
			if (i == 14) {
				return 14;
			}

		}
		return position - (7 * (Row(position) - 1));


	}
	else {//down right 

		for (int i = position; i >= 0 && i <= 59; i = i + 8) {

			if (i == 14) {
				return 14;
			}
			if (i == 29) {
				return 29;
			}
			if (i == 44) {
				return 44;
			}
			if (i == 59) {
				return 59;
			}

		}
		return position + (8 * (8 - Row(position)));


	}

}










void move_highlighter(ALLEGRO_BITMAP* onefish, ALLEGRO_BITMAP* twofish, ALLEGRO_BITMAP* threefish, int redraw_draw, ALLEGRO_BITMAP* pengyh, ALLEGRO_BITMAP* penggh, ALLEGRO_BITMAP* pengrh, ALLEGRO_BITMAP* pengbh, int temp, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pengy, ALLEGRO_BITMAP* pengg, ALLEGRO_BITMAP* pengr, ALLEGRO_BITMAP* pengb, ALLEGRO_BITMAP* empty, int mode) {

	//harekate panguan baad az entekhab inke mikhahad kodam ra jabeja konad

	if (mode == 1) {



		if (ices[temp].penguin_color == 1) {

			al_draw_bitmap(pengy, ices[position].bitmapx, ices[position].bitmapy, 0);
			al_flip_display(display);

		}
		if (ices[temp].penguin_color == 2) {

			al_draw_bitmap(pengg, ices[position].bitmapx, ices[position].bitmapy, 0);
			al_flip_display(display);

		}

		if (ices[temp].penguin_color == 3) {

			al_draw_bitmap(pengr, ices[position].bitmapx, ices[position].bitmapy, 0);
			al_flip_display(display);

		}
		if (ices[temp].penguin_color == 4) {

			al_draw_bitmap(pengb, ices[position].bitmapx, ices[position].bitmapy, 0);
			al_flip_display(display);

		}



	}


	if (mode == 0) {


		if (redraw_draw == -1) {




			if (ices[position].mode == 1) {

				al_draw_bitmap(onefish, ices[position].bitmapx, ices[position].bitmapy, 0);

			}
			else if (ices[position].mode == 2) {

				al_draw_bitmap(twofish, ices[position].bitmapx, ices[position].bitmapy, 0);

			}

			else if (ices[position].mode == 3) {

				al_draw_bitmap(threefish, ices[position].bitmapx, ices[position].bitmapy, 0);

			}







		}



		else {





			if (ices[temp].penguin_color == 1) {

				al_draw_bitmap(pengyh, ices[position].bitmapx, ices[position].bitmapy, 0);
				al_flip_display(display);

			}
			if (ices[temp].penguin_color == 2) {

				al_draw_bitmap(penggh, ices[position].bitmapx, ices[position].bitmapy, 0);
				al_flip_display(display);

			}

			if (ices[temp].penguin_color == 3) {

				al_draw_bitmap(pengrh, ices[position].bitmapx, ices[position].bitmapy, 0);
				al_flip_display(display);

			}
			if (ices[temp].penguin_color == 4) {

				al_draw_bitmap(pengbh, ices[position].bitmapx, ices[position].bitmapy, 0);
				al_flip_display(display);




			}


		}










	}




}


void cleaning_the_map(int num_penguins, int color, ALLEGRO_BITMAP* empty, ALLEGRO_DISPLAY* display) {

	//vaghti yek rang nemitavanad harekat konad kashi haye zire an khali mishavand


	int p;
	PengFinder();
	for (int i = 0; i < num_penguins; i++) {
		if (color == 1) {
			p = pengPos1[i];

			al_draw_bitmap(empty, ices[p].bitmapx, ices[p].bitmapy, 0);
			al_flip_display(display);
		}

		else if (color == 2) {
			p = pengPos2[i];
			al_draw_bitmap(empty, ices[p].bitmapx, ices[p].bitmapy, 0);
			al_flip_display(display);
		}

		else if (color == 3) {
			p = pengPos3[i];
			al_draw_bitmap(empty, ices[p].bitmapx, ices[p].bitmapy, 0);
			al_flip_display(display);
		}

		else if (color == 4) {
			p = pengPos4[i];
			al_draw_bitmap(empty, ices[p].bitmapx, ices[p].bitmapy, 0);
			al_flip_display(display);
		}




	}




}







void MainMovement(int penguin_num, ALLEGRO_BITMAP* onefish, ALLEGRO_BITMAP* twofish, ALLEGRO_BITMAP* threefish, ALLEGRO_BITMAP* pengyh, ALLEGRO_BITMAP* penggh, ALLEGRO_BITMAP* pengrh, ALLEGRO_BITMAP* pengbh, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pengy, ALLEGRO_BITMAP* pengg, ALLEGRO_BITMAP* pengr, ALLEGRO_BITMAP* pengb, ALLEGRO_BITMAP* empty) {

	//jabejayi asli panguan ha va daryaft score



	int up_clicked = 0;
	int down_clicked = 0;
	int right_clicked = 0;
	int left_clicked = 0;

	int temp = position;

	int uc = 0; //shomarande up click
	int dc = 0;
	int rc = 0;
	int lc = 0;

	for (int i = 0; i < 10; i++) {

		up_right[i] = -1;
		up_left[i] = -1;
		down_right[i] = -1;
		down_left[i] = -1;
		left[i] = -1;
		right[i] = -1;


	}

	int sw = 0;

	checking_chooseable_ices(penguin_num, position);

	ALLEGRO_KEYBOARD_STATE keystate;

	al_get_keyboard_state(&keystate);


	do {






		if (al_key_down(&keystate, ALLEGRO_KEY_RIGHT) && left_clicked == 0) {

			sw = 1;

			if (up_clicked == 0 && down_clicked == 0) {    //rast mamooli

				if (ices[position].mode == 5) {

				}
				else {
					move_highlighter(onefish, twofish, threefish, -1, pengyh, penggh, pengrh, pengbh, temp, display, pengy, pengg, pengr, pengb, empty, 0);//bardashtane highlight ghabli
				}

				if (right[rc] >= 0) {

					position = right[rc];

					rc++;


					move_highlighter(onefish, twofish, threefish, 1, pengyh, penggh, pengrh, pengbh, temp, display, pengy, pengg, pengr, pengb, empty, 0);//gozashtan highlight
					right_clicked = 1;
				}




			}

			else if (up_clicked == 1 && down_clicked == 0) {//bala zade shode va baad rast zade shode

				if (ices[position].mode == 5) {

				}
				else {
					move_highlighter(onefish, twofish, threefish, -1, pengyh, penggh, pengrh, pengbh, temp, display, pengy, pengg, pengr, pengb, empty, 0);
				}

				if (up_right[uc] >= 0) {

					position = up_right[uc];

					uc++;
					move_highlighter(onefish, twofish, threefish, 1, pengyh, penggh, pengrh, pengbh, temp, display, pengy, pengg, pengr, pengb, empty, 0);

				}
				else {
					up_clicked == 0;
				}


			}

			else if (down_clicked == 1 && up_clicked == 0) {//payin zade shode va baad rast zade shode

				if (ices[position].mode == 5) {

				}
				else {
					move_highlighter(onefish, twofish, threefish, -1, pengyh, penggh, pengrh, pengbh, temp, display, pengy, pengg, pengr, pengb, empty, 0);
				}

				if (down_right[dc] >= 0) {

					position = down_right[dc];
					dc++;
					move_highlighter(onefish, twofish, threefish, 1, pengyh, penggh, pengrh, pengbh, temp, display, pengy, pengg, pengr, pengb, empty, 0);

				}
				else {
					down_clicked == 0;
				}

			}


			al_rest(0.09);
		}

		else if (al_key_down(&keystate, ALLEGRO_KEY_LEFT) && right_clicked == 0) {
			sw = 1;
			if (ices[position].mode == 5) {

			}
			else {
				move_highlighter(onefish, twofish, threefish, -1, pengyh, penggh, pengrh, pengbh, temp, display, pengy, pengg, pengr, pengb, empty, 0);
			}

			if (up_clicked == 0 && down_clicked == 0) {//chap mamooli



				if (left[lc] >= 0) {

					position = left[lc];

					lc++;
					move_highlighter(onefish, twofish, threefish, 1, pengyh, penggh, pengrh, pengbh, temp, display, pengy, pengg, pengr, pengb, empty, 0);
					left_clicked = 1;
				}




			}
			else if (up_clicked == 1 && down_clicked == 0) {//bala zade shode va baad chap zade shode
				if (ices[position].mode == 5) {

				}
				else {
					move_highlighter(onefish, twofish, threefish, -1, pengyh, penggh, pengrh, pengbh, temp, display, pengy, pengg, pengr, pengb, empty, 0);
				}

				if (up_left[uc] >= 0) {

					position = up_left[uc];

					uc++;
					move_highlighter(onefish, twofish, threefish, 1, pengyh, penggh, pengrh, pengbh, temp, display, pengy, pengg, pengr, pengb, empty, 0);
				}
				else {
					down_clicked == 0;
				}


			}

			else if (down_clicked == 1 && up_clicked == 0) {//payin zade shode va baad chap zade shode

				if (ices[position].mode == 5) {

				}
				else {
					move_highlighter(onefish, twofish, threefish, -1, pengyh, penggh, pengrh, pengbh, temp, display, pengy, pengg, pengr, pengb, empty, 0);
				}

				if (down_left[dc] >= 0) {

					position = down_left[dc];

					dc++;
					move_highlighter(onefish, twofish, threefish, 1, pengyh, penggh, pengrh, pengbh, temp, display, pengy, pengg, pengr, pengb, empty, 0);
				}
				else {
					up_clicked == 0;
				}

			}

			al_rest(0.09);
		}



		else if (al_key_down(&keystate, ALLEGRO_KEY_UP) && right_clicked == 0 && left_clicked == 0 && down_clicked == 0) { // aval up click she



				// darsurati k bad az up click , left click she


			up_clicked = 1;

			al_rest(0.09);


		}






		else if (al_key_down(&keystate, ALLEGRO_KEY_DOWN) && right_clicked == 0 && left_clicked == 0 && up_clicked == 0) {  // ebteda down click she



			down_clicked = 1;
			al_rest(0.09);




		}

		al_rest(0.15);
		al_get_keyboard_state(&keystate);

	} while (!al_key_down(&keystate, ALLEGRO_KEY_ENTER) || sw == 0);


	move_highlighter(onefish, twofish, threefish, 1, pengyh, penggh, pengrh, pengbh, temp, display, pengy, pengg, pengr, pengb, empty, 1);

	ices[position].penguin_color = ices[temp].penguin_color;

	ices[position].penguin_number = ices[temp].penguin_number;

	if (ices[position].penguin_color == 1) {

		score_yellow += ices[position].mode;

	}

	else if (ices[position].penguin_color == 2) {

		score_green += ices[position].mode;

	}

	else if (ices[position].penguin_color == 3) {

		score_red += ices[position].mode;

	}

	else if (ices[position].penguin_color == 4) {

		score_blue += ices[position].mode;

	}

	ices[position].mode = 4;








	if (ices[temp].penguin_color == 1) {
		int i = 0;

		for (i; i < 4; i++) {
			if (pengPos1[i] == temp) {
				break;
			}
		}

		pengPos1[i] = position;


	}


	else if (ices[temp].penguin_color == 2) {

		int i = 0;
		for (i; i < 4; i++) {
			if (pengPos2[i] == temp) {
				break;
			}
		}
		pengPos2[i] = position;
	}

	else if (ices[temp].penguin_color == 3) {
		int i = 0;
		for (i; i < 4; i++) {
			if (pengPos3[i] == temp) {
				break;
			}
		}
		pengPos3[i] = position;

	}

	else if (ices[temp].penguin_color == 4) {
		int i = 0;
		for (i; i < 4; i++) {
			if (pengPos4[i] == temp) {
				break;
			}
		}
		pengPos4[i] = position;

	}




	al_rest(0.1);





}



void saving(FILE* Save, int num_players, int num_penguins, int i, int loaded) {



	if (!Save) {
		return 0;
	}



	struct ice ice1;

	for (int i = 0; i < 60; i++) {

		fwrite(&ices[i], sizeof(ice1), 1, Save);
	}

	fwrite(&num_players, sizeof(int), 1, Save);


	fwrite(&num_penguins, sizeof(int), 1, Save);

	fwrite(&position, sizeof(int), 1, Save);

	fwrite(&starting_point, sizeof(int), 1, Save);

	fwrite(pengPos1, sizeof(int), 4, Save);

	fwrite(pengPos2, sizeof(int), 4, Save);

	fwrite(pengPos3, sizeof(int), 4, Save);

	fwrite(pengPos4, sizeof(int), 4, Save);

	fwrite(up_right, sizeof(int), 10, Save);

	fwrite(up_left, sizeof(int), 10, Save);

	fwrite(down_right, sizeof(int), 10, Save);

	fwrite(down_left, sizeof(int), 10, Save);

	fwrite(left, sizeof(int), 10, Save);

	fwrite(right, sizeof(int), 10, Save);

	fwrite(&score_yellow, sizeof(int), 1, Save);

	fwrite(&score_green, sizeof(int), 1, Save);

	fwrite(&score_red, sizeof(int), 1, Save);

	fwrite(&score_blue, sizeof(int), 1, Save);

	fwrite(&tile_yellow, sizeof(int), 1, Save);

	fwrite(&tile_green, sizeof(int), 1, Save);

	fwrite(&tile_red, sizeof(int), 1, Save);

	fwrite(&tile_blue, sizeof(int), 1, Save);


	fwrite(&yellow_choosing_starting_point, sizeof(int), 1, Save);

	fwrite(&green_choosing_starting_point, sizeof(int), 1, Save);

	fwrite(&red_choosing_starting_point, sizeof(int), 1, Save);

	fwrite(&blue_choosing_starting_point, sizeof(int), 1, Save);

	fwrite(&yellow_choosing_ending_point, sizeof(int), 1, Save);

	fwrite(&green_choosing_ending_point, sizeof(int), 1, Save);

	fwrite(&red_choosing_ending_point, sizeof(int), 1, Save);

	fwrite(&blue_choosing_ending_point, sizeof(int), 1, Save);

	fwrite(&yellowSw, sizeof(int), 1, Save);

	fwrite(&greenSw, sizeof(int), 1, Save);

	fwrite(&redSw, sizeof(int), 1, Save);

	fwrite(&blueSw, sizeof(int), 1, Save);

	fwrite(&i, sizeof(int), 1, Save);





}









int main() {

	for (int i = 0; i < 60; i++) {
		ices[i].penguin_color = -1;
		ices[i].penguin_number = -1;
	}

	int mulitple_winner = 0;
	int winners[4] = { -1 };
	int winner;
	int sw4 = 0;
	int sw_game = 1;
	int sw2 = 0;
	int sw3 = 0;
	int num_players;
	int num_penguins;
	int loaded = 0;
	int loaded_turn = 1;


	float x = 0, y = 0;


	FILE* Save2;



	Save2 = fopen("save.dat", "wb");

	//ijad khode allegro va addon ha
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_init_primitives_addon();

	//gereftane tool va arz monitor

	ALLEGRO_MONITOR_INFO info;

	al_get_monitor_info(0, &info);

	int monitor_width = info.x2 - info.x1;
	int monitor_height = info.y2 - info.y1;





	//ijad display,font,yek saf baraye event ha
	ALLEGRO_DISPLAY* display = al_create_display(700, 400);

	ALLEGRO_FONT* fontGill48 = al_load_ttf_font("GILLUBCD.TTF", 48, 0);

	ALLEGRO_FONT* fontGill36 = al_load_ttf_font("GILLUBCD.TTF", 36, 0);

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);

	ALLEGRO_BITMAP* load_screen = NULL;

	ALLEGRO_BITMAP* play_button = NULL;

	ALLEGRO_BITMAP* LOGO = NULL;

	ALLEGRO_BITMAP* players = NULL;

	ALLEGRO_BITMAP* two_players = NULL;

	ALLEGRO_BITMAP* three_players = NULL;

	ALLEGRO_BITMAP* four_players = NULL;

	ALLEGRO_BITMAP* load_button = NULL;

	ALLEGRO_BITMAP* OneFish = NULL;

	ALLEGRO_BITMAP* TwoFish = NULL;

	ALLEGRO_BITMAP* ThreeFish = NULL;

	ALLEGRO_BITMAP* OneFishh = NULL;

	ALLEGRO_BITMAP* TwoFishh = NULL;

	ALLEGRO_BITMAP* ThreeFishh = NULL;

	ALLEGRO_BITMAP* YellowTurn = NULL;

	ALLEGRO_BITMAP* GreenTurn = NULL;

	ALLEGRO_BITMAP* RedTurn = NULL;

	ALLEGRO_BITMAP* BlueTurn = NULL;

	ALLEGRO_BITMAP* YellowPenguin = NULL;

	ALLEGRO_BITMAP* GreenPenguin = NULL;

	ALLEGRO_BITMAP* RedPenguin = NULL;

	ALLEGRO_BITMAP* BluePenguin = NULL;

	ALLEGRO_BITMAP* YellowPenguinh = NULL;

	ALLEGRO_BITMAP* GreenPenguinh = NULL;

	ALLEGRO_BITMAP* RedPenguinh = NULL;

	ALLEGRO_BITMAP* BluePenguinh = NULL;

	ALLEGRO_BITMAP* Empty = NULL;

	ALLEGRO_BITMAP* Blank = NULL;

	ALLEGRO_BITMAP* YellowWin = NULL;

	ALLEGRO_BITMAP* GreenWin = NULL;

	ALLEGRO_BITMAP* RedWin = NULL;

	ALLEGRO_BITMAP* BlueWin = NULL;

	ALLEGRO_BITMAP* Save = NULL;

	//gereftane input az keyboard va mouse va display
	al_install_keyboard();

	al_install_mouse();

	al_register_event_source(queue, al_get_keyboard_event_source());

	al_register_event_source(queue, al_get_display_event_source(display));

	al_register_event_source(queue, al_get_timer_event_source(timer));

	al_register_event_source(queue, al_get_mouse_event_source());


	//bitmap loading

	load_screen = al_load_bitmap("hey-that-is-my-fish.jpg");
	al_draw_bitmap(load_screen, 0, 0, 0);

	al_flip_display(display);
	al_rest(5.00);


	play_button = al_load_bitmap("playB.png");

	LOGO = al_load_bitmap("Hey-Thats-My-Fish-title.jpg");

	players = al_load_bitmap("number_of_players.png");

	two_players = al_load_bitmap("2player.png");

	three_players = al_load_bitmap("3player.png");

	four_players = al_load_bitmap("4player.png");

	load_button = al_load_bitmap("loadBbb.png");

	OneFish = al_load_bitmap("1fish.png");

	TwoFish = al_load_bitmap("2fish.png");

	ThreeFish = al_load_bitmap("3fish.png");

	OneFishh = al_load_bitmap("1fishh.png");

	TwoFishh = al_load_bitmap("2fishh.png");

	ThreeFishh = al_load_bitmap("3fishh.png");

	YellowTurn = al_load_bitmap("Yturn.png");

	GreenTurn = al_load_bitmap("Gturn.png");

	RedTurn = al_load_bitmap("Rturn.png");

	BlueTurn = al_load_bitmap("Bturn.png");

	YellowPenguin = al_load_bitmap("penguiny.png");

	GreenPenguin = al_load_bitmap("penguing.png");

	RedPenguin = al_load_bitmap("penguinr.png");

	BluePenguin = al_load_bitmap("penguinb.png");

	YellowPenguinh = al_load_bitmap("penguinyh.png");

	GreenPenguinh = al_load_bitmap("penguingh.png");

	RedPenguinh = al_load_bitmap("penguinrh.png");

	BluePenguinh = al_load_bitmap("penguinbh.png");

	Empty = al_load_bitmap("empty.png");

	Blank = al_load_bitmap("blank.png");

	YellowWin = al_load_bitmap("Ywin.png");

	GreenWin = al_load_bitmap("Gwin.png");

	RedWin = al_load_bitmap("Rwin.png");

	BlueWin = al_load_bitmap("Bwin.png");

	Save = al_load_bitmap("save.png");


	if (load_screen == NULL)return 0;
	if (play_button == NULL)return 0;
	if (players == NULL)return 0;
	if (two_players == NULL)return 0;
	if (three_players == NULL)return 0;
	if (four_players == NULL)return 0;
	if (load_button == NULL)return 0;
	if (OneFish == NULL)return 0;
	if (TwoFish == NULL)return 0;
	if (ThreeFish == NULL)return 0;
	if (OneFishh == NULL)return 0;
	if (TwoFishh == NULL)return 0;
	if (ThreeFishh == NULL)return 0;
	if (YellowTurn == NULL)return 0;
	if (GreenTurn == NULL)return 0;
	if (RedTurn == NULL)return 0;
	if (BlueTurn == NULL)return 0;
	if (YellowPenguin == NULL)return 0;
	if (GreenPenguin == NULL)return 0;
	if (RedPenguin == NULL)return 0;
	if (BluePenguin == NULL)return 0;
	if (YellowPenguinh == NULL)return 0;
	if (GreenPenguinh == NULL)return 0;
	if (RedPenguinh == NULL)return 0;
	if (BluePenguinh == NULL)return 0;
	if (Empty == NULL)return 0;
	if (Blank == NULL)return 0;
	if (YellowWin == NULL)return 0;
	if (GreenWin == NULL)return 0;
	if (RedWin == NULL)return 0;
	if (BlueWin == NULL)return 0;
	if (Save == NULL)return 0;

	//menu loading


	al_resize_display(display, monitor_width / 1.5, monitor_height / 1.4);

	al_set_window_position(display, monitor_width / 5, monitor_height / 5);

	al_clear_to_color(al_map_rgb(144, 197, 229));

	al_draw_bitmap(play_button, 0.5 * monitor_width, monitor_height / 7, 0);

	al_draw_bitmap(LOGO, monitor_width / 5, 0, 0);

	al_draw_bitmap(load_button, 0.5 * monitor_width, monitor_height * 0.2 + 100, 0);

	al_flip_display(display);

	int sw = 1;

	al_start_timer(timer);

	while (sw == 1) {//game loop

		ALLEGRO_EVENT event;

		al_wait_for_event(queue, &event);


		//menu


		//mouse movement
		if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {

			x = event.mouse.x;
			y = event.mouse.y;

		}

		//closing the window
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {

			sw = 0;
			continue;

		}



		if (sw3 == 0) {
			//play button
			if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button & 1
				&& x > 0.5 * monitor_width && x < 0.5 * monitor_width + al_get_bitmap_width(play_button)
				&& y>monitor_height / 7 && y < monitor_height / 7 + al_get_bitmap_height(play_button)
				&& sw2 == 0)
			{

				al_draw_bitmap(players, monitor_width / 50, monitor_height / 6, 0);
				al_draw_bitmap(two_players, monitor_width / 50, monitor_height / 6 + 100, 0);
				al_draw_bitmap(three_players, monitor_width / 50, monitor_height / 6 + 150 + al_get_bitmap_height(two_players), 0);
				al_draw_bitmap(four_players, monitor_width / 50, al_get_bitmap_height(two_players) + al_get_bitmap_height(three_players) + monitor_height / 6 + 200, 0);
				al_flip_display(display);
				sw2 = 1;

			}

			//2players
			if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button & 1
				&& x > monitor_width / 50 && x <monitor_width / 50 + al_get_bitmap_width(two_players)
				&& y>monitor_height / 6 + 100 && y < monitor_height / 6 + 100 + al_get_bitmap_height(two_players)
				&& sw2 == 1)
			{

				num_players = 2;
				num_penguins = 4;
				sw3 = 1;
				al_set_window_position(display, 0, 0);

				al_resize_display(display, monitor_width, monitor_height);
				al_clear_to_color(al_map_rgb(0, 105, 148));
				al_flip_display(display);
			}

			//3players
			if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button & 1
				&& x > monitor_width / 50 && x <monitor_width / 50 + al_get_bitmap_width(two_players)
				&& y>monitor_height / 6 + 150 + al_get_bitmap_height(two_players) && y < monitor_height / 6 + al_get_bitmap_height(two_players) + al_get_bitmap_height(three_players) + 150
				&& sw2 == 1)
			{

				num_players = 3;
				num_penguins = 3;
				sw3 = 1;
				al_set_window_position(display, 0, 0);

				al_resize_display(display, monitor_width, monitor_height);
				al_clear_to_color(al_map_rgb(0, 105, 148));
				al_flip_display(display);

			}

			//4players
			if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button & 1
				&& x > monitor_width / 50 && x < monitor_width / 50 + al_get_bitmap_width(four_players)
				&& y>monitor_height / 6 + 200 + al_get_bitmap_height(two_players) + al_get_bitmap_height(three_players) && y < monitor_height / 6 + 200 + al_get_bitmap_height(two_players) + al_get_bitmap_height(three_players) + al_get_bitmap_height(four_players)
				&& sw2 == 1)

			{

				num_players = 4;
				num_penguins = 2;
				sw3 = 1;
				al_set_window_position(display, 0, 0);
				al_resize_display(display, monitor_width, monitor_height);
				al_clear_to_color(al_map_rgb(0, 105, 148));

				al_flip_display(display);

			}

			//load_button
			if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button & 1
				&& x > 0.5 * monitor_width && x <0.5 * monitor_width + al_get_bitmap_width(load_button)
				&& y> monitor_height * 0.2 + 100 && y < monitor_height * 0.2 + 100 + al_get_bitmap_height(load_button)
				)
			{

				sw3 = 1;
				sw4 = 0;
				loaded = 1;

			}

		}
		else {
			//closing the window
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {

				sw = 0;
				return 0;


			}

			//The game




			if (sw4 == 0) {
				if (loaded == 1) {
					//load
					FILE* load;
					load = fopen("save.dat", "rb");

					if (!load) {
						return 0;
					}

					al_set_window_position(display, 0, 0);

					al_resize_display(display, monitor_width, monitor_height);
					al_clear_to_color(al_map_rgb(0, 105, 148));
					al_flip_display(display);

					while (!feof(load)) {
						struct ice ice1;

						for (int i = 0; i < 60; i++) {

							fread(&ices[i], sizeof(ice1), 1, load);
						}

						fread(&num_players, sizeof(int), 1, load);

						fread(&num_penguins, sizeof(int), 1, load);
						//

						fread(&position, sizeof(int), 1, load);

						fread(&starting_point, sizeof(int), 1, load);

						fread(pengPos1, sizeof(int), 4, load);

						fread(pengPos2, sizeof(int), 4, load);

						fread(pengPos3, sizeof(int), 4, load);

						fread(pengPos4, sizeof(int), 4, load);

						fread(up_right, sizeof(int), 10, load);

						fread(up_left, sizeof(int), 10, load);

						fread(down_right, sizeof(int), 10, load);

						fread(down_left, sizeof(int), 10, load);

						fread(left, sizeof(int), 10, load);

						fread(right, sizeof(int), 10, load);

						fread(&score_yellow, sizeof(int), 1, load);

						fread(&score_green, sizeof(int), 1, load);

						fread(&score_red, sizeof(int), 1, load);

						fread(&score_blue, sizeof(int), 1, load);

						fread(&tile_yellow, sizeof(int), 1, load);

						fread(&tile_green, sizeof(int), 1, load);

						fread(&tile_red, sizeof(int), 1, load);

						fread(&tile_blue, sizeof(int), 1, load);


						fread(&yellow_choosing_starting_point, sizeof(int), 1, load);

						fread(&green_choosing_starting_point, sizeof(int), 1, load);

						fread(&red_choosing_starting_point, sizeof(int), 1, load);

						fread(&blue_choosing_starting_point, sizeof(int), 1, load);

						fread(&yellow_choosing_ending_point, sizeof(int), 1, load);

						fread(&green_choosing_ending_point, sizeof(int), 1, load);

						fread(&red_choosing_ending_point, sizeof(int), 1, load);

						fread(&blue_choosing_ending_point, sizeof(int), 1, load);

						fread(&yellowSw, sizeof(int), 1, load);

						fread(&greenSw, sizeof(int), 1, load);

						fread(&redSw, sizeof(int), 1, load);

						fread(&blueSw, sizeof(int), 1, load);

						fread(&loaded_turn, sizeof(int), 1, load);

					}

					map_loading(loaded, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin, display, Empty, OneFish, TwoFish, ThreeFish, monitor_width, monitor_height);
					al_flip_display(display);

					al_draw_textf(fontGill48, al_map_rgb(255, 255, 255), 0.6 * monitor_width, 0.1 * monitor_height, 0, "Score Board:");

					al_draw_textf(fontGill36, al_map_rgb(255, 255, 0), 0.6 * monitor_width, 0.2 * monitor_height, 0, "Yellow: %d", score_yellow);

					al_draw_textf(fontGill36, al_map_rgb(0, 255, 0), 0.6 * monitor_width, 0.3 * monitor_height, 0, "Green: %d", score_green);

					if (num_players == 3) {

						al_draw_textf(fontGill36, al_map_rgb(255, 60, 60), 0.6 * monitor_width, 0.4 * monitor_height, 0, "Red: %d", score_red);

					}

					if (num_players == 4) {

						al_draw_textf(fontGill36, al_map_rgb(255, 60, 60), 0.6 * monitor_width, 0.4 * monitor_height, 0, "Red: %d", score_red);

						al_draw_textf(fontGill36, al_map_rgb(144, 197, 229), 0.6 * monitor_width, 0.5 * monitor_height, 0, "Blue: %d", score_blue);

					}



					al_draw_bitmap(Save, 0.8 * monitor_width, monitor_height * 0.1, 0);

					al_flip_display(display);


					sw4 = 1;

				}

				else {







					//generate kardan game

					map_loading(loaded, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin, display, Empty, OneFish, TwoFish, ThreeFish, monitor_width, monitor_height);

					al_flip_display(display);

					al_draw_textf(fontGill48, al_map_rgb(255, 255, 255), 0.6 * monitor_width, 0.1 * monitor_height, 0, "Score Board:");

					al_draw_textf(fontGill36, al_map_rgb(255, 255, 0), 0.6 * monitor_width, 0.2 * monitor_height, 0, "Yellow: %d", score_yellow);

					al_draw_textf(fontGill36, al_map_rgb(0, 255, 0), 0.6 * monitor_width, 0.3 * monitor_height, 0, "Green: %d", score_green);

					if (num_players == 3) {

						al_draw_textf(fontGill36, al_map_rgb(255, 60, 60), 0.6 * monitor_width, 0.4 * monitor_height, 0, "Red: %d", score_red);
					}

					if (num_players == 4) {

						al_draw_textf(fontGill36, al_map_rgb(255, 60, 60), 0.6 * monitor_width, 0.4 * monitor_height, 0, "Red: %d", score_red);

						al_draw_textf(fontGill36, al_map_rgb(144, 197, 229), 0.6 * monitor_width, 0.5 * monitor_height, 0, "Blue: %d", score_blue);

					}

					al_draw_bitmap(YellowTurn, 0.6 * monitor_width, 0.02 * monitor_height, 0);
					al_flip_display(display);

					for (int i = 1; i <= num_players * num_penguins; i++) {


						al_flip_display(display);
						position = starting_point;
						if (ices[position].mode == 1) {

							al_draw_bitmap(OneFishh, ices[position].bitmapx, ices[position].bitmapy, 0);

							al_flip_display(display);

						}
						else if (ices[position].mode == 2) {

							al_draw_bitmap(TwoFishh, ices[position].bitmapx, ices[position].bitmapy, 0);

							al_flip_display(display);


						}

						else if (ices[position].mode == 3) {

							al_draw_bitmap(ThreeFishh, ices[position].bitmapx, ices[position].bitmapy, 0);

							al_flip_display(display);


						}


						switch (num_players) {

							int j;

						case(2):

							if (i % 2 == 1) {

								j = (i / 2) + 1;

								move_to_choose(j, RedTurn, BlueTurn, YellowTurn, GreenTurn, 1, 2, display, OneFish, TwoFish, ThreeFish, OneFishh, TwoFishh, ThreeFishh, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin);
								continue;
							}
							else if (i % 2 == 0) {

								j = i / 2;

								move_to_choose(j, RedTurn, BlueTurn, YellowTurn, GreenTurn, 2, 1, display, OneFish, TwoFish, ThreeFish, OneFishh, TwoFishh, ThreeFishh, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin);
								continue;
							}


						case(3):

							if (i % 3 == 1) {

								j = (i / 3) + 1;

								move_to_choose(j, RedTurn, BlueTurn, YellowTurn, GreenTurn, 1, 2, display, OneFish, TwoFish, ThreeFish, OneFishh, TwoFishh, ThreeFishh, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin);
								continue;
							}
							else if (i % 3 == 2) {

								j = (i / 3) + 2;

								move_to_choose(j, RedTurn, BlueTurn, YellowTurn, GreenTurn, 2, 3, display, OneFish, TwoFish, ThreeFish, OneFishh, TwoFishh, ThreeFishh, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin);
								continue;
							}
							else if (i % 3 == 0) {

								j = (i / 3);

								move_to_choose(j, RedTurn, BlueTurn, YellowTurn, GreenTurn, 3, 1, display, OneFish, TwoFish, ThreeFish, OneFishh, TwoFishh, ThreeFishh, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin);
								continue;
							}


						case(4):

							if (i % 4 == 1) {

								j = (i / 4) + 1;

								move_to_choose(j, RedTurn, BlueTurn, YellowTurn, GreenTurn, 1, 2, display, OneFish, TwoFish, ThreeFish, OneFishh, TwoFishh, ThreeFishh, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin);
								continue;
							}
							else if (i % 4 == 2) {

								j = (i / 4) + 2;

								move_to_choose(j, RedTurn, BlueTurn, YellowTurn, GreenTurn, 2, 3, display, OneFish, TwoFish, ThreeFish, OneFishh, TwoFishh, ThreeFishh, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin);
								continue;
							}
							else if (i % 4 == 3) {

								j = (i / 4) + 3;

								move_to_choose(j, RedTurn, BlueTurn, YellowTurn, GreenTurn, 3, 4, display, OneFish, TwoFish, ThreeFish, OneFishh, TwoFishh, ThreeFishh, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin);
								continue;
							}
							else if (i % 4 == 0) {

								j = (i / 4);

								move_to_choose(j, RedTurn, BlueTurn, YellowTurn, GreenTurn, 4, 1, display, OneFish, TwoFish, ThreeFish, OneFishh, TwoFishh, ThreeFishh, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin);
								continue;
							}



						}


					}

				}
				sw4 = 1;

			}

			else {


				PengFinder();
				al_rest(0.1);

				int yellowswdone = 0;
				int greenswdone = 0;
				int redswdone = 0;
				int blueswdone = 0;

				int i = loaded_turn;

				while (sw_game == 1) {


					//halghi asli bazi 

					
					
					if (i == 8) {
						saving(Save2, num_players, num_penguins, i, loaded);

					}
				








					if (num_players == 2) {

						if (yellowSw == 1) {
							i++;
						}

						if (i % 2 != 0 && yellowSw == 0) {





							peng_pos_chooser(4, RedTurn, BlueTurn, YellowTurn, GreenTurn, 1, 4, display, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin, YellowPenguinh, GreenPenguinh, RedPenguinh, BluePenguinh);




							tile_yellow++;





							if (yellowSw == 1 && yellowswdone == 0) {
								cleaning_the_map(num_penguins, 1, Empty, display);
								i++;
								bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 2, display);


								al_draw_bitmap(Blank, 0.6 * monitor_width, 0.2 * monitor_height, 0);

								al_flip_display(display);

								al_draw_textf(fontGill36, al_map_rgb(255, 255, 0), 0.6 * monitor_width, 0.2 * monitor_height, 0, "Yellow: %d", score_yellow);

								al_flip_display(display);
								yellowswdone = 1;
							}



							else {


								al_draw_bitmap(Empty, ices[position].bitmapx, ices[position].bitmapy, 0);

								al_flip_display(display);



								//save score

								ices[position].mode = 5;


								al_draw_bitmap(Blank, 0.6 * monitor_width, 0.2 * monitor_height, 0);

								al_flip_display(display);



								al_draw_textf(fontGill36, al_map_rgb(255, 255, 0), 0.6 * monitor_width, 0.2 * monitor_height, 0, "Yellow: %d", score_yellow);

								al_flip_display(display);


								MainMovement(num_penguins, OneFish, TwoFish, ThreeFish, YellowPenguinh, GreenPenguinh, RedPenguinh, BluePenguinh, display, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin, Empty);



								if (greenSw == 0) {
									bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 2, display);
								}
								i++;

								if (greenSw == 1 && greenswdone == 0) {
									cleaning_the_map(num_penguins, 2, Empty, display);


									bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 1, display);

									al_draw_bitmap(Blank, 0.6 * monitor_width, 0.3 * monitor_height, 0);

									al_flip_display(display);

									al_draw_textf(fontGill36, al_map_rgb(0, 255, 0), 0.6 * monitor_width, 0.3 * monitor_height, 0, "Green: %d", score_green);

									al_flip_display(display);
									greenswdone = 1;
								}


							}
						}
						if (greenSw == 1) {
							i++;
						}
						else  if (i % 2 == 0 && greenSw == 0) {





							peng_pos_chooser(4, RedTurn, BlueTurn, YellowTurn, GreenTurn, 2, 4, display, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin, YellowPenguinh, GreenPenguinh, RedPenguinh, BluePenguinh);



							tile_green++;



							if (greenSw == 1 && greenswdone == 0) {
								cleaning_the_map(num_penguins, 2, Empty, display);
								i++;
								bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 1, display);


								al_draw_bitmap(Blank, 0.6 * monitor_width, 0.3 * monitor_height, 0);

								al_flip_display(display);

								al_draw_textf(fontGill36, al_map_rgb(0, 255, 0), 0.6 * monitor_width, 0.3 * monitor_height, 0, "Green: %d", score_green);

								al_flip_display(display);
							}







							else {
								al_draw_bitmap(Empty, ices[position].bitmapx, ices[position].bitmapy, 0);

								al_flip_display(display);



								ices[position].mode = 5;



								al_draw_bitmap(Blank, 0.6 * monitor_width, 0.3 * monitor_height, 0);

								al_flip_display(display);

								al_draw_textf(fontGill36, al_map_rgb(0, 255, 0), 0.6 * monitor_width, 0.3 * monitor_height, 0, "Green: %d", score_green);

								al_flip_display(display);

								MainMovement(num_penguins, OneFish, TwoFish, ThreeFish, YellowPenguinh, GreenPenguinh, RedPenguinh, BluePenguinh, display, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin, Empty);
								if (yellowSw == 0) {
									bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 1, display);
								}

								i++;
								if (yellowSw == 1 && yellowswdone == 0) {
									cleaning_the_map(num_penguins, 1, Empty, display);
									i++;
									bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 2, display);

									al_draw_bitmap(Blank, 0.6 * monitor_width, 0.2 * monitor_height, 0);

									al_flip_display(display);

									al_draw_textf(fontGill36, al_map_rgb(255, 255, 0), 0.6 * monitor_width, 0.2 * monitor_height, 0, "Yellow: %d", score_yellow);

									al_flip_display(display);
									yellowswdone = 1;
								}
							}



						}


						Score[0] = score_yellow;
						Score[1] = score_green;

						Tile[0] = tile_yellow;
						Tile[1] = tile_green;

						if (greenSw == 1 && yellowSw == 1) {
							int max = 0;
							for (int i = 0; i < num_players; i++)
							{

								if (Score[i] > max)
								{
									max = Score[i];
									winner = i;
								}
								else if (Score[i] == max)
								{
									if (Tile[i] > Tile[winner])
									{
										winner = i;
										max = Score[i];
									}
									else if (Tile[i] == Tile[winner]) {
										winners[i] = 1;

										mulitple_winner = 1;
									}
								}
							}



							if (mulitple_winner == 1) {

								if (winner == 0) {
									al_clear_to_color(al_map_rgb(0, 105, 148));
									al_draw_bitmap(YellowWin, monitor_width / 4, monitor_height / 2, 0);
									al_flip_display(display);
									al_rest(4);
									sw3 = 0;
									sw_game = 0;
								}
								else {
									al_clear_to_color(al_map_rgb(0, 105, 148));
									al_draw_bitmap(GreenWin, monitor_width / 4, monitor_height / 2, 0);
									al_flip_display(display);
									al_rest(4);
									sw3 = 0;
									sw_game = 0;
								}
							}
							else {
								al_clear_to_color(al_map_rgb(0, 105, 148));
								al_draw_bitmap(YellowWin, monitor_width / 4, monitor_height / 2, 0);
								al_draw_bitmap(GreenWin, monitor_width / 4, monitor_height / 1.5, 0);
								al_flip_display(display);
								al_rest(4);
								sw3 = 0;
								sw_game = 0;

							}
						}


						else if (num_players == 3) {

							if (yellowSw == 1) {
								i++;
							}

							if (i % 3 == 1 && yellowSw == 0) {





								peng_pos_chooser(3, RedTurn, BlueTurn, YellowTurn, GreenTurn, 1, 3, display, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin, YellowPenguinh, GreenPenguinh, RedPenguinh, BluePenguinh);



								tile_yellow++;





								if (yellowSw == 1) {
									cleaning_the_map(num_penguins, 1, Empty, display);
									i++;
									bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 2, display);


									al_draw_bitmap(Blank, 0.6 * monitor_width, 0.2 * monitor_height, 0);

									al_flip_display(display);

									al_draw_textf(fontGill36, al_map_rgb(255, 255, 0), 0.6 * monitor_width, 0.2 * monitor_height, 0, "Yellow: %d", score_yellow);

									al_flip_display(display);

								}





								else {
									al_draw_bitmap(Empty, ices[position].bitmapx, ices[position].bitmapy, 0);

									al_flip_display(display);






									ices[position].mode = 5;




									al_draw_bitmap(Blank, 0.6 * monitor_width, 0.2 * monitor_height, 0);

									al_flip_display(display);

									al_draw_textf(fontGill36, al_map_rgb(255, 255, 0), 0.6 * monitor_width, 0.2 * monitor_height, 0, "Yellow: %d", score_yellow);

									al_flip_display(display);

									//}
									MainMovement(num_penguins, OneFish, TwoFish, ThreeFish, YellowPenguinh, GreenPenguinh, RedPenguinh, BluePenguinh, display, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin, Empty);

									if (greenSw == 0) {
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 2, display);
									}

									i++;
									if (greenSw == 1 && yellowSw == 0) {
										cleaning_the_map(num_penguins, 2, Empty, display);
										i++;
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 3, display);


										al_draw_bitmap(Blank, 0.6 * monitor_width, 0.3 * monitor_height, 0);

										al_flip_display(display);

										al_draw_textf(fontGill36, al_map_rgb(0, 255, 0), 0.6 * monitor_width, 0.3 * monitor_height, 0, "Green: %d", score_green);

										al_flip_display(display);
									}
									if (redSw == 1) {
										cleaning_the_map(num_penguins, 3, Empty, display);
										i++;
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 1, display);


										al_draw_bitmap(Blank, 0.6 * monitor_width, 0.4 * monitor_height, 0);

										al_flip_display(display);

										al_draw_textf(fontGill36, al_map_rgb(255, 60, 60), 0.6 * monitor_width, 0.4 * monitor_height, 0, "Red: %d", score_red);

										al_flip_display(display);
									}
								}
							}

							if (greenSw == 1) {
								i++;
							}
							else if (i % 3 == 2 && greenSw == 0) {





								peng_pos_chooser(3, RedTurn, BlueTurn, YellowTurn, GreenTurn, 2, 3, display, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin, YellowPenguinh, GreenPenguinh, RedPenguinh, BluePenguinh);



								tile_green++;



								if (greenSw == 1) {
									cleaning_the_map(num_penguins, 2, Empty, display);
									i++;
									bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 3, display);

									al_draw_bitmap(Blank, 0.6 * monitor_width, 0.3 * monitor_height, 0);

									al_flip_display(display);

									al_draw_textf(fontGill36, al_map_rgb(0, 255, 0), 0.6 * monitor_width, 0.3 * monitor_height, 0, "Green: %d", score_green);

									al_flip_display(display);
								}






								else {

									al_draw_bitmap(Empty, ices[position].bitmapx, ices[position].bitmapy, 0);

									al_flip_display(display);



									ices[position].mode = 5;


									al_draw_bitmap(Blank, 0.6 * monitor_width, 0.3 * monitor_height, 0);

									al_flip_display(display);

									al_draw_textf(fontGill36, al_map_rgb(0, 255, 0), 0.6 * monitor_width, 0.3 * monitor_height, 0, "Green: %d", score_green);

									al_flip_display(display);



									MainMovement(num_penguins, OneFish, TwoFish, ThreeFish, YellowPenguinh, GreenPenguinh, RedPenguinh, BluePenguinh, display, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin, Empty);

									if (redSw == 0) {
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 3, display);
									}
									i++;
									if (yellowSw == 1) {
										cleaning_the_map(num_penguins, 1, Empty, display);
										i++;
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 2, display);

										al_draw_bitmap(Blank, 0.6 * monitor_width, 0.2 * monitor_height, 0);

										al_flip_display(display);

										al_draw_textf(fontGill36, al_map_rgb(255, 255, 0), 0.6 * monitor_width, 0.2 * monitor_height, 0, "Yellow: %d", score_yellow);

										al_flip_display(display);
									}
									if (redSw == 1) {
										cleaning_the_map(num_penguins, 3, Empty, display);
										i++;
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 1, display);

										al_draw_bitmap(Blank, 0.6 * monitor_width, 0.4 * monitor_height, 0);

										al_flip_display(display);

										al_draw_textf(fontGill36, al_map_rgb(255, 60, 60), 0.6 * monitor_width, 0.4 * monitor_height, 0, "Red: %d", score_red);

										al_flip_display(display);
									}

								}


							}


							if (redSw == 1) {
								i++;
							}


							else if (i % 3 == 0 && redSw == 0) {





								peng_pos_chooser(3, RedTurn, BlueTurn, YellowTurn, GreenTurn, 3, 3, display, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin, YellowPenguinh, GreenPenguinh, RedPenguinh, BluePenguinh);



								tile_red++;




								if (redSw == 1) {
									cleaning_the_map(num_penguins, 3, Empty, display);
									i++;
									bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 1, display);

									al_draw_bitmap(Blank, 0.6 * monitor_width, 0.4 * monitor_height, 0);

									al_flip_display(display);

									al_draw_textf(fontGill36, al_map_rgb(255, 60, 60), 0.6 * monitor_width, 0.4 * monitor_height, 0, "Red: %d", score_red);

									al_flip_display(display);
								}






								else {

									al_draw_bitmap(Empty, ices[position].bitmapx, ices[position].bitmapy, 0);

									al_flip_display(display);

									ices[position].mode = 5;



									al_draw_bitmap(Blank, 0.6 * monitor_width, 0.4 * monitor_height, 0);

									al_flip_display(display);

									al_draw_textf(fontGill36, al_map_rgb(255, 60, 60), 0.6 * monitor_width, 0.4 * monitor_height, 0, "Red: %d", score_red);

									al_flip_display(display);



									MainMovement(num_penguins, OneFish, TwoFish, ThreeFish, YellowPenguinh, GreenPenguinh, RedPenguinh, BluePenguinh, display, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin, Empty);

									if (yellowSw == 0) {
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 1, display);
									}
									i++;
									if (greenSw == 1 && greenswdone == 0) {
										cleaning_the_map(num_penguins, 2, Empty, display);
										i++;
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 3, display);

										al_draw_bitmap(Blank, 0.6 * monitor_width, 0.3 * monitor_height, 0);

										al_flip_display(display);

										al_draw_textf(fontGill36, al_map_rgb(0, 255, 0), 0.6 * monitor_width, 0.3 * monitor_height, 0, "Green: %d", score_green);

										al_flip_display(display);
									}

									if (yellowSw == 1) {
										cleaning_the_map(num_penguins, 1, Empty, display);
										i++;
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 2, display);

										al_draw_bitmap(Blank, 0.6 * monitor_width, 0.2 * monitor_height, 0);

										al_flip_display(display);

										al_draw_textf(fontGill36, al_map_rgb(255, 255, 0), 0.6 * monitor_width, 0.2 * monitor_height, 0, "Yellow: %d", score_yellow);

										al_flip_display(display);
									}
								}

							}




							Score[0] = score_yellow;
							Score[1] = score_green;
							Score[2] = score_red;

							Tile[0] = tile_yellow;
							Tile[1] = tile_green;
							Tile[2] = tile_red;

							if (greenSw == 1 && yellowSw == 1 && redSw == 1) {

								for (int i = 0; i < num_players; i++)
								{
									static int max = 0;
									if (Score[i] > max)
									{
										max = Score[i];
										winner = i;
									}
									else if (Score[i] == max)
									{
										if (Tile[i] > Tile[winner])
										{
											winner = i;
											max = Score[i];
										}
										else if (Tile[i] == Tile[winner]) {
											winners[i] = i;

											mulitple_winner = 1;
										}
									}
								}
								if (mulitple_winner == 0) {
									if (winner == 0) {
										al_clear_to_color(al_map_rgb(0, 105, 148));
										al_draw_bitmap(YellowWin, monitor_width / 4, monitor_height / 2, 0);
										al_flip_display(display);
										sw3 = 0;
										sw_game = 0;
									}
									else if (winner == 1) {
										al_clear_to_color(al_map_rgb(0, 105, 148));
										al_draw_bitmap(GreenWin, monitor_width / 4, monitor_height / 2, 0);
										al_flip_display(display);
										sw3 = 0;
										sw_game = 0;
									}
									else if (winner == 2) {
										al_clear_to_color(al_map_rgb(0, 105, 148));
										al_draw_bitmap(RedWin, monitor_width / 2, monitor_height / 2, 0);
										al_flip_display(display);
										sw3 = 0;
										sw_game = 0;
									}
								}
								else {

									for (int i = 0; i < 3; i++) {

										if (winners[i] == 0) {
											al_clear_to_color(al_map_rgb(0, 105, 148));
											al_draw_bitmap(YellowWin, monitor_width / 4, monitor_height / 2, 0);
											al_flip_display(display);


										}
										else if (winners[i] == 1) {
											al_clear_to_color(al_map_rgb(0, 105, 148));
											al_draw_bitmap(GreenWin, monitor_width / 4, monitor_height / 1.9, 0);
											al_flip_display(display);

										}
										else if (winners[i] == 2) {
											al_clear_to_color(al_map_rgb(0, 105, 148));
											al_draw_bitmap(RedWin, monitor_width / 2, monitor_height / 1.8, 0);
											al_flip_display(display);
										}

									}

									sw3 = 0;
									sw_game = 0;

								}
							}
						}





						else if (num_players == 4) {
							if (yellowSw == 1) {
								i++;
							}

							if (i % 4 == 1 && yellowSw == 0) {




								peng_pos_chooser(2, RedTurn, BlueTurn, YellowTurn, GreenTurn, 1, 2, display, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin, YellowPenguinh, GreenPenguinh, RedPenguinh, BluePenguinh);



								tile_yellow++;




								if (yellowSw == 1) {
									cleaning_the_map(num_penguins, 1, Empty, display);
									i++;
									bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 2, display);

									al_draw_bitmap(Blank, 0.6 * monitor_width, 0.2 * monitor_height, 0);

									al_flip_display(display);

									al_draw_textf(fontGill36, al_map_rgb(255, 255, 0), 0.6 * monitor_width, 0.2 * monitor_height, 0, "Yellow: %d", score_yellow);

									al_flip_display(display);
								}





								else {

									al_draw_bitmap(Empty, ices[position].bitmapx, ices[position].bitmapy, 0);

									al_flip_display(display);

									ices[position].mode = 5;


									al_draw_bitmap(Blank, 0.6 * monitor_width, 0.2 * monitor_height, 0);

									al_flip_display(display);

									al_draw_textf(fontGill36, al_map_rgb(255, 255, 0), 0.6 * monitor_width, 0.2 * monitor_height, 0, "Yellow: %d", score_yellow);

									al_flip_display(display);

									MainMovement(num_penguins, OneFish, TwoFish, ThreeFish, YellowPenguinh, GreenPenguinh, RedPenguinh, BluePenguinh, display, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin, Empty);

									if (greenSw == 0) {
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 2, display);
									}
									i++;
									if (greenSw == 1) {
										cleaning_the_map(num_penguins, 2, Empty, display);
										i++;
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 3, display);

										al_draw_bitmap(Blank, 0.6 * monitor_width, 0.3 * monitor_height, 0);

										al_flip_display(display);

										al_draw_textf(fontGill36, al_map_rgb(0, 255, 0), 0.6 * monitor_width, 0.3 * monitor_height, 0, "Green: %d", score_green);

										al_flip_display(display);
									}

									if (redSw == 1) {
										cleaning_the_map(num_penguins, 3, Empty, display);
										i++;
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 4, display);


										al_draw_bitmap(Blank, 0.6 * monitor_width, 0.4 * monitor_height, 0);

										al_flip_display(display);

										al_draw_textf(fontGill36, al_map_rgb(255, 60, 60), 0.6 * monitor_width, 0.4 * monitor_height, 0, "Red: %d", score_red);

										al_flip_display(display);

									}
									if (blueSw == 1) {
										cleaning_the_map(num_penguins, 4, Empty, display);
										i++;
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 1, display);

										al_draw_bitmap(Blank, 0.6 * monitor_width, 0.5 * monitor_height, 0);

										al_flip_display(display);


										al_draw_textf(fontGill36, al_map_rgb(144, 197, 229), 0.6 * monitor_width, 0.5 * monitor_height, 0, "Blue: %d", score_blue);

										al_flip_display(display);
									}
								}


							}

							if (greenSw == 1) {
								i++;
							}
							else if (i % 4 == 2 && greenSw == 0) {




								peng_pos_chooser(2, RedTurn, BlueTurn, YellowTurn, GreenTurn, 2, 2, display, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin, YellowPenguinh, GreenPenguinh, RedPenguinh, BluePenguinh);




								tile_green++;



								if (greenSw == 1) {
									cleaning_the_map(num_penguins, 2, Empty, display);
									i++;
									bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 3, display);

									al_draw_bitmap(Blank, 0.6 * monitor_width, 0.3 * monitor_height, 0);

									al_flip_display(display);

									al_draw_textf(fontGill36, al_map_rgb(0, 255, 0), 0.6 * monitor_width, 0.3 * monitor_height, 0, "Green: %d", score_green);

									al_flip_display(display);
								}







								else {

									al_draw_bitmap(Empty, ices[position].bitmapx, ices[position].bitmapy, 0);

									al_flip_display(display);

									ices[position].mode = 5;


									al_draw_bitmap(Blank, 0.6 * monitor_width, 0.3 * monitor_height, 0);

									al_flip_display(display);

									al_draw_textf(fontGill36, al_map_rgb(0, 255, 0), 0.6 * monitor_width, 0.3 * monitor_height, 0, "Green: %d", score_green);

									al_flip_display(display);




									MainMovement(num_penguins, OneFish, TwoFish, ThreeFish, YellowPenguinh, GreenPenguinh, RedPenguinh, BluePenguinh, display, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin, Empty);

									if (redSw == 0) {
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 3, display);

									}

									i++;
									if (yellowSw == 1) {
										cleaning_the_map(num_penguins, 1, Empty, display);
										i++;
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 2, display);

										al_draw_bitmap(Blank, 0.6 * monitor_width, 0.2 * monitor_height, 0);

										al_flip_display(display);

										al_draw_textf(fontGill36, al_map_rgb(255, 255, 0), 0.6 * monitor_width, 0.2 * monitor_height, 0, "Yellow: %d", score_yellow);

										al_flip_display(display);
									}
									if (redSw == 1) {
										cleaning_the_map(num_penguins, 3, Empty, display);
										i++;
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 4, display);

										al_draw_bitmap(Blank, 0.6 * monitor_width, 0.4 * monitor_height, 0);

										al_flip_display(display);

										al_draw_textf(fontGill36, al_map_rgb(255, 60, 60), 0.6 * monitor_width, 0.4 * monitor_height, 0, "Red: %d", score_red);

										al_flip_display(display);
									}
									if (blueSw == 1) {
										cleaning_the_map(num_penguins, 4, Empty, display);
										i++;
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 1, display);

										al_draw_bitmap(Blank, 0.6 * monitor_width, 0.5 * monitor_height, 0);

										al_flip_display(display);


										al_draw_textf(fontGill36, al_map_rgb(144, 197, 229), 0.6 * monitor_width, 0.5 * monitor_height, 0, "Blue: %d", score_blue);

										al_flip_display(display);
									}

								}

							}


							if (redSw == 1) {
								i++;
							}
							else if (i % 4 == 3 && redSw == 0) {




								peng_pos_chooser(2, RedTurn, BlueTurn, YellowTurn, GreenTurn, 3, 2, display, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin, YellowPenguinh, GreenPenguinh, RedPenguinh, BluePenguinh);




								tile_red++;




								if (redSw == 1) {
									cleaning_the_map(num_penguins, 3, Empty, display);
									i++;
									bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 4, display);

									al_draw_bitmap(Blank, 0.6 * monitor_width, 0.4 * monitor_height, 0);

									al_flip_display(display);

									al_draw_textf(fontGill36, al_map_rgb(255, 60, 60), 0.6 * monitor_width, 0.4 * monitor_height, 0, "Red: %d", score_red);

									al_flip_display(display);
								}







								else {

									al_draw_bitmap(Empty, ices[position].bitmapx, ices[position].bitmapy, 0);
									al_flip_display(display);
									ices[position].mode = 5;
									//save score

									//if (returned== 1) {


									//	score_red += ices[position].score;


									//}

									//else {//harekati nist




									//}

									al_draw_bitmap(Blank, 0.6 * monitor_width, 0.4 * monitor_height, 0);

									al_flip_display(display);

									al_draw_textf(fontGill36, al_map_rgb(255, 60, 60), 0.6 * monitor_width, 0.4 * monitor_height, 0, "Red: %d", score_red);

									al_flip_display(display);

									MainMovement(num_penguins, OneFish, TwoFish, ThreeFish, YellowPenguinh, GreenPenguinh, RedPenguinh, BluePenguinh, display, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin, Empty);

									if (blueSw == 0) {

										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 4, display);

									}
									i++;
									if (greenSw == 1) {
										cleaning_the_map(num_penguins, 2, Empty, display);
										i++;
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 3, display);

										al_draw_bitmap(Blank, 0.6 * monitor_width, 0.3 * monitor_height, 0);

										al_flip_display(display);

										al_draw_textf(fontGill36, al_map_rgb(0, 255, 0), 0.6 * monitor_width, 0.3 * monitor_height, 0, "Green: %d", score_green);

										al_flip_display(display);
									}

									if (yellowSw == 1) {
										cleaning_the_map(num_penguins, 1, Empty, display);
										i++;
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 2, display);

										al_draw_bitmap(Blank, 0.6 * monitor_width, 0.2 * monitor_height, 0);

										al_flip_display(display);

										al_draw_textf(fontGill36, al_map_rgb(255, 255, 0), 0.6 * monitor_width, 0.2 * monitor_height, 0, "Yellow: %d", score_yellow);

										al_flip_display(display);
									}
									if (blueSw == 1) {
										cleaning_the_map(num_penguins, 4, Empty, display);
										i++;
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 1, display);

										al_draw_bitmap(Blank, 0.6 * monitor_width, 0.5 * monitor_height, 0);

										al_flip_display(display);


										al_draw_textf(fontGill36, al_map_rgb(144, 197, 229), 0.6 * monitor_width, 0.5 * monitor_height, 0, "Blue: %d", score_blue);

										al_flip_display(display);
									}

								}

							}
							if (blueSw == 1) {
								i++;
							}
							else if (i % 4 == 0 && blueSw == 0) {




								peng_pos_chooser(2, RedTurn, BlueTurn, YellowTurn, GreenTurn, 4, 2, display, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin, YellowPenguinh, GreenPenguinh, RedPenguinh, BluePenguinh);




								tile_blue++;




								if (blueSw == 1) {
									cleaning_the_map(num_penguins, 4, Empty, display);
									i++;
									bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 1, display);

									al_draw_bitmap(Blank, 0.6 * monitor_width, 0.5 * monitor_height, 0);

									al_flip_display(display);


									al_draw_textf(fontGill36, al_map_rgb(144, 197, 229), 0.6 * monitor_width, 0.5 * monitor_height, 0, "Blue: %d", score_blue);

									al_flip_display(display);
								}





								else {

									al_draw_bitmap(Empty, ices[position].bitmapx, ices[position].bitmapy, 0);

									al_flip_display(display);

									ices[position].mode = 5;
									//save score

									//if (returned== 1) {


									//	score_blue += ices[position].score;


									//}

									//else {//harekati nist




									//}

									al_draw_bitmap(Blank, 0.6 * monitor_width, 0.5 * monitor_height, 0);

									al_flip_display(display);


									al_draw_textf(fontGill36, al_map_rgb(144, 197, 229), 0.6 * monitor_width, 0.5 * monitor_height, 0, "Blue: %d", score_blue);

									al_flip_display(display);

									MainMovement(num_penguins, OneFish, TwoFish, ThreeFish, YellowPenguinh, GreenPenguinh, RedPenguinh, BluePenguinh, display, YellowPenguin, GreenPenguin, RedPenguin, BluePenguin, Empty);

									if (yellowSw == 0) {
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 1, display);

									}
									i++;
									if (greenSw == 1) {
										cleaning_the_map(num_penguins, 2, Empty, display);
										i++;
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 3, display);


										al_draw_bitmap(Blank, 0.6 * monitor_width, 0.3 * monitor_height, 0);

										al_flip_display(display);

										al_draw_textf(fontGill36, al_map_rgb(0, 255, 0), 0.6 * monitor_width, 0.3 * monitor_height, 0, "Green: %d", score_green);

										al_flip_display(display);
									}

									if (yellowSw == 1) {
										cleaning_the_map(num_penguins, 1, Empty, display);
										i++;
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 2, display);

										al_draw_bitmap(Blank, 0.6 * monitor_width, 0.2 * monitor_height, 0);

										al_flip_display(display);

										al_draw_textf(fontGill36, al_map_rgb(255, 255, 0), 0.6 * monitor_width, 0.2 * monitor_height, 0, "Yellow: %d", score_yellow);

										al_flip_display(display);
									}
									if (redSw == 1) {
										cleaning_the_map(num_penguins, 3, Empty, display);
										i++;
										bitmap_turn(RedTurn, BlueTurn, YellowTurn, GreenTurn, 4, display);

										al_draw_bitmap(Blank, 0.6 * monitor_width, 0.4 * monitor_height, 0);

										al_flip_display(display);

										al_draw_textf(fontGill36, al_map_rgb(255, 60, 60), 0.6 * monitor_width, 0.4 * monitor_height, 0, "Red: %d", score_red);

										al_flip_display(display);
									}

								}

							}


							Score[0] = score_yellow;
							Score[1] = score_green;
							Score[2] = score_red;
							Score[3] = score_blue;

							Tile[0] = tile_yellow;
							Tile[1] = tile_green;
							Tile[2] = tile_red;
							Tile[3] = tile_blue;

							if (greenSw == 1 && yellowSw == 1 && redSw == 1 && blueSw == 1) {
								for (int i = 0; i < num_players; i++)
								{
									static int max = 0;

									if (Score[i] > max)
									{
										max = Score[i];
										winner = i;
									}
									else if (Score[i] == max)
									{
										if (Tile[i] > Tile[winner])
										{
											winner = i;
											max = Score[i];
										}
										else if (Tile[i] == Tile[winner]) {

											winners[i] = 1;

											mulitple_winner = 1;
										}
									}
								}
							}

							if (mulitple_winner == 0) {
								if (winner == 0) {
									al_clear_to_color(al_map_rgb(0, 105, 148));
									al_draw_bitmap(YellowWin, monitor_width / 4, monitor_height / 2, 0);
									al_flip_display(display);
									sw3 = 0;
									sw_game = 0;
								}

								else if (winner == 1) {
									al_clear_to_color(al_map_rgb(0, 105, 148));
									al_draw_bitmap(GreenWin, monitor_width / 4, monitor_height / 2, 0);
									al_flip_display(display);
									sw3 = 0;
									sw_game = 0;
								}

								else if (winner == 2) {
									al_clear_to_color(al_map_rgb(0, 105, 148));
									al_draw_bitmap(RedWin, monitor_width / 4, monitor_height / 2, 0);
									al_flip_display(display);
									sw3 = 0;
									sw_game = 0;
								}

								else if (winner == 3) {
									al_clear_to_color(al_map_rgb(0, 105, 148));
									al_draw_bitmap(BlueWin, monitor_width / 4, monitor_height / 2, 0);
									al_flip_display(display);
									sw3 = 0;
									sw_game = 0;
								}
							}
							else {

								for (int i = 0; i < 3; i++) {

									if (winners[i] == 0) {
										al_clear_to_color(al_map_rgb(0, 105, 148));
										al_draw_bitmap(YellowWin, monitor_width / 4, monitor_height / 2, 0);
										al_flip_display(display);


									}
									else if (winners[i] == 1) {
										al_clear_to_color(al_map_rgb(0, 105, 148));
										al_draw_bitmap(GreenWin, monitor_width / 4, monitor_height / 1.9, 0);
										al_flip_display(display);

									}
									else if (winners[i] == 2) {
										al_clear_to_color(al_map_rgb(0, 105, 148));
										al_draw_bitmap(RedWin, monitor_width / 2, monitor_height / 1.8, 0);
										al_flip_display(display);
									}
									else if (winners[i] == 3) {
										al_clear_to_color(al_map_rgb(0, 105, 148));
										al_draw_bitmap(BlueWin, monitor_width / 2, monitor_height / 1.7, 0);
										al_flip_display(display);
									}

								}

								sw3 = 0;
								sw_game = 0;



							}

						}

					}
				}
			}

		}



	}


	fclose(Save2);

	//cleaning up
	al_destroy_display(display);
	al_destroy_font(fontGill48);
	al_destroy_font(fontGill36);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_timer(timer);
	al_destroy_bitmap(load_screen);
	al_destroy_bitmap(LOGO);
	al_destroy_bitmap(players);
	al_destroy_bitmap(two_players);
	al_destroy_bitmap(three_players);
	al_destroy_bitmap(four_players);
	al_destroy_bitmap(load_button);
	al_destroy_bitmap(OneFish);
	al_destroy_bitmap(TwoFish);
	al_destroy_bitmap(ThreeFish);
	al_destroy_bitmap(YellowTurn);
	al_destroy_bitmap(GreenTurn);
	al_destroy_bitmap(RedTurn);
	al_destroy_bitmap(BlueTurn);
	al_destroy_bitmap(YellowPenguin);
	al_destroy_bitmap(GreenPenguin);
	al_destroy_bitmap(RedPenguin);
	al_destroy_bitmap(BluePenguin);
	al_destroy_bitmap(YellowPenguinh);
	al_destroy_bitmap(GreenPenguinh);
	al_destroy_bitmap(RedPenguinh);
	al_destroy_bitmap(BluePenguinh);
	al_destroy_bitmap(Empty);
}