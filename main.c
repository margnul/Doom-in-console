#include <windows.h>
#include <stdio.h>
#include <math.h>

#define PI  3.14159265358979
#define screen_height 80
#define screen_width 250
#define GUN_X 80-13
#define GUN_Y 250-18-100

void screen() {
	system("mode con cols=250 lines=81");
}

float map_height = 20;
float map_width = 20;
float view_distance = 30;
float player_x = 3;
float player_y = 3;
float player_sight = 15;
float radians;
float zoom = 25;
float wall_height = 10;
float fow = 60;
//float screen_height = 100;
//float screen_width = 250;
float distance;
float angle_help;
int alpha[4];

int map[20][20] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

float thow_ray(float angle) {
	radians = angle / 180 * PI;
	for (float i = 0; i < view_distance; i += 0.1) {
		//printf("%f ", 2 * i * sinf(fow / screen_width / 2));

		//printf("%f %f \n", player_x + i * cosf(angle), player_y + i * sinf(angle));

		/*
		if (player_x + i * cosf(radians) >= map_width) {
			//printf("%f %f %f \n", radians, player_x + i * cosf(radians), player_y + i * sinf(radians));
			return i;
		}
		if (player_x + i * cosf(radians) <= 0) {
			//printf("%f %f %f \n", radians, player_x + i * cosf(radians), player_y + i * sinf(radians));
			return i;
		}
		if (player_y + i * sinf(radians) >= map_height) {
			//printf("%f %f %f \n", radians, player_x + i * cosf(radians), player_y + i * sinf(radians));
			return i;
		}
		if (player_y + i * sinf(radians) <= 0) {
			//printf("%f %f %f \n", radians, player_x + i * cosf(radians), player_y + i * sinf(radians));
			return i;
		}
		*/

		// b = 2⋅a⋅sin β/2
		//float b = i * sinf(fow / screen_width / 180 * PI / 2);

		float ray_x = player_x + i * cosf(radians);
		float ray_y = player_y + i * sinf(radians);

		if (map[(int)(ray_y)][(int)(ray_x)]) {
			if (pow(ray_y - rint(ray_y), 2) + pow(ray_x - rint(ray_x), 2) < 0.01)
				return -i;
			return i;
		}

	}

	return view_distance;
}


int main() {
	screen();
	/*
	int height = 60;
	int width = 120;
	float x, y;
	float correction = 16 / 8;
	float correction2 = (float)height / (float)width;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			x = ((float)i / height * 2) - 1;
			y = ((float)j / width * 2) - 1;

			x *= correction * correction2;

			if (y < x*x+1 && y > x*x-1 && y-1 < x * x + 1 && y-1 > x * x - 1) {
				printf("%c", 219);
			}
			else {
				printf("%c", 255);
			}
		}
		printf("|\n");
	}
	for (int i = 0; i < width; i++) {
		printf("%c", 95);
	}

	while (0 == 0);
	return 0;
	*/


	alpha[3] = 176;
	alpha[2] = 177;
	alpha[1] = 178;
	alpha[0] = 219;

	unsigned char mas[screen_height][screen_width];
	//char str[10201]; //  50 * (200 + 1) + 1 == 10201
	char str[screen_height * (screen_width + 1) + 1]; //  100 * (250 + 1) + 1 == 25101

	while (1) {

		for (int i = 0; i < ((int)screen_height) / 2; i++) {
			for (int j = 0; j < ((int)screen_width); j++) {
				mas[i][j] = 255;
			}
		}
		for (int i = ((int)screen_height) / 2; i < screen_height; i++) {
			for (int j = 0; j < ((int)screen_width); j++) {
				mas[i][j] = 46;
			}
		}

		for (int i = 0; i <= screen_height * (screen_width + 1) / 2; i++) {
			if (i - ((i % ((int)screen_width))) - ((i % ((int)screen_width) + 1) * screen_width) == 0) {
				//printf("%d ", i);
				str[i] = '\n';
			}
			else {
				str[i] = 255;
			}
		}
		for (int i = screen_height * (screen_width + 1) / 2; i < screen_height * (screen_width + 1); i++) {
			if (i - ((i % ((int)screen_width))) - ((i % ((int)screen_width) + 1) * screen_width) == 0) {
				//printf("%d ", i);
				str[i] = '\n';
			}
			else {
				str[i] = '.';
			}
		}
		str[(int)screen_height * ((int)screen_width + 1)] = NULL;



		//going through all rays
		for (int i = -(screen_width / 2); i < screen_width / 2; i++) {
			//printf("_%d ", i);
			angle_help = (fow / screen_width);
			distance = thow_ray(angle_help * i + player_sight);


			//float wall_height = screen_height / 2 - ((int)distance / 2);

			float wall_on_screen = zoom * wall_height / abs(distance);
			if (wall_on_screen > screen_height)
				wall_on_screen = screen_height;

			//printf("%f %f %f %f \n", zoom , wall_height , distance, wall_on_screen);
			//printf("%d ", (int)((distance / view_distance)*4));

			for (int j = 0; j < wall_on_screen / 2; j++) {
				int mas_x = i + (int)screen_width / 2;
				int mas_y = (int)screen_height / 2;

				mas[mas_y - j][mas_x] = alpha[(int)((distance / view_distance) * 4)];
				mas[mas_y + j][mas_x] = alpha[(int)((distance / view_distance) * 4)];
				//if (((mas_y - j) * ((int)screen_width + 1) + mas_x) % ((int)screen_width) == 0) {
				//	printf("%d_%d ", mas_x, (mas_y - j));
				//}

				if (distance < 0) {
					str[(mas_y - j) * ((int)screen_width + 1) + mas_x] = '|';
					str[(mas_y + j) * ((int)screen_width + 1) + mas_x] = '|';
				}
				else {
					str[(mas_y - j) * ((int)screen_width + 1) + mas_x] = alpha[(int)((distance / view_distance) * 4)];
					str[(mas_y + j) * ((int)screen_width + 1) + mas_x] = alpha[(int)((distance / view_distance) * 4)];
				}

				//str[(mas_y - j) * ((int)screen_width + 1) + mas_x] = alpha[(int)((distance / view_distance) * 4)];
				//str[(mas_y + j) * ((int)screen_width + 1) + mas_x] = alpha[(int)((distance / view_distance) * 4)];



				//printf("%d %d | ", (int)((distance / view_distance) * 4), alpha[(int)((distance / view_distance) * 4)]);
				//printf(" %d %d _ %d %d\n", i+15, 14 - j,i+15, 14 + j);
			}

		}

		// drawing gun  18x13
		int gun_x = screen_width - 18 - 80;
		int gun_y = screen_height - 13;
		char gun[13][18] = {
			"   _______        ",
			"  /\\      \\       ",
			" /  \\      \\      ",
			"/    \\      \\     ",
			"\\     \\      \\    ",
			" \\     \\      \\   ",
			"  \\     \\      \\  ",
			"   \\     \\      \\ ",
			"    \\     \\______\\",
			"    |\\   /       /",
			"    | \\ /_______/ ",
			"    |   |      |  ",
			"    |   |      |  "
		};

		for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 18; j++) {
				if (gun[i][j] != ' ')
					str[(i + gun_y) * ((int)screen_width + 1) + (j + gun_x)] = gun[i][j];
			}
		}

		str[0] = '1';


		//clearing

		system("cls");






		// drawing

		/*

		for (int i = 0; i < screen_height; i++) {
			for (int j = 0; j < screen_width; j++) {
				printf("%c", mas[i][j]);
			}
			printf("\n");
		}


		for (int j = 0; j < screen_width; j++) {
			printf("_");
		}

		*/
		printf("%s", str);






		// moving

		float step = 0.1;
		if (GetAsyncKeyState(0x25)) {
			player_sight -= 1;
		}
		if (GetAsyncKeyState(0x27)) {
			player_sight += 1;
		}
		if (GetAsyncKeyState('W')) {
			radians = player_sight / 180 * PI;
			if (player_x + step * cosf(radians) > 1 && player_x + step * cosf(radians) < map_width - 1) {
				player_x += step * cosf(radians);
			}
			if (player_y + step * sinf(radians) > 1 && player_y + step * sinf(radians) < map_height - 1) {
				player_y += step * sinf(radians);
			}
		}
		if (GetAsyncKeyState('S')) {
			radians = player_sight / 180 * PI;
			if (player_x - step * cosf(radians) > 1 && player_x - step * cosf(radians) < map_width - 1) {
				player_x -= step * cosf(radians);
			}
			if (player_y - step * sinf(radians) > 1 && player_y - step * sinf(radians) < map_height - 1) {
				player_y -= step * sinf(radians);
			}

		}
		if (GetAsyncKeyState('A')) {
			radians = (player_sight - 90) / 180 * PI;
			if (player_x + step * cosf(radians) > 1 && player_x + step * cosf(radians) < map_width - 1) {
				player_x += step * cosf(radians);
			}
			if (player_y + step * sinf(radians) > 1 && player_y + step * sinf(radians) < map_height - 1) {
				player_y += step * sinf(radians);
			}
		}
		if (GetAsyncKeyState('D')) {
			radians = (player_sight + 90) / 180 * PI;
			if (player_x + step * cosf(radians) > 1 && player_x + step * cosf(radians) < map_width - 1) {
				player_x += step * cosf(radians);
			}
			if (player_y + step * sinf(radians) > 1 && player_y + step * sinf(radians) < map_height - 1) {
				player_y += step * sinf(radians);
			}

		}




		Sleep(3);

	}

	//		Sleep(100000 / 1);
	//	}


	return 0;

}