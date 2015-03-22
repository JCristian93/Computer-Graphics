//@author : Jalba Cristian 333 CA

#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include <iostream>
#include <windows.h>
#include <vector>
#include <math.h>

#define PI 3.14159265358979323846

using namespace std;

Visual2D *v2d1, *v_text;
Rectangle2D *rect, *player , *fata1, *fata2 ,*fata3, *ef1 , *ef2 , *ef3;
Rectangle2D *podea1, *podea2, *podea3, *podea4, *podea5, *podea6, *podea7,*tavan;
Rectangle2D *oponent, *oponent2;
Polygon2D *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9, *t10, *t11, *t12, *t13, *t14;
Polygon2D *t15, *t16, *t17, *t18, *t19, *t20, *t21, *t22, *t23, *t24, *t25, *t26, *t27, *t28;
Polygon2D *p1 , *p2, *p3 , *p4 , *p5, *p6, *p7, *p8, *p9, *p10, *p11, *p12, *p13, *p14;
Polygon2D *flag1, *flag2, *flag3, *flag4, *flag5;
Polygon2D *coin1, *coin2, *coin3, *coin4, *coin5, *coin6 , *coin7;
Circle2D *up1, *up2, *up3 ,*up4 ,*up5;
vector<Polygon2D*> vector_triunghi , vector_platforme, vector_flags, vector_coins;
vector<Rectangle2D*> vector_rect, vector_podea;
vector<Circle2D*> vector_cerc;
Text *mesaj , *mesaj_coins, *mesaj_win;
int i, k = 0, pas_efect = 0, nr_platforme = 14, nr_flags = 3, nr_circles = 5, nr_tzepe =28, nr_coins = 7 ;
float pas =0.0f, pas_space=0.0f, pas_rot=0.0f , platform_offset = 0.0f, checkpoint=0.0f, cerc_offset=0.0f, flag_offset=0.0f;
float bounce = 0.0f;
bool space = false, start = true , stay_on_platform = false, boost = false, flagged = false;
int vieti = 3 , respawn_time =0;	//numarul maxim de incercari , pana pierzi jocul
int contor_coins = 0 , last_coin = -1;
bool won = false;
char *buffer_text;	//in asta bag textul ce urmeaza sa fie afisat
//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{
	v2d1 = new Visual2D(0.0f,0.0f,1300,700,0,0,DrawingWindow::width,DrawingWindow::height);  
	v2d1->tipTran(true);
	v_text = new Visual2D(0.0f, 0.0f, 1300, 700, 0, 0, DrawingWindow::width, DrawingWindow::height);
	addVisual2D(v2d1);
	addVisual2D(v_text);
	buffer_text = (char*)malloc(100 * sizeof(char));
	sprintf(buffer_text, "numarul de vieti ramase este : %d", vieti);
	mesaj = new Text(buffer_text, Point2D(900, 600), Color(0, 0, 1), BITMAP_TIMES_ROMAN_24);	//containerul de text
	addText_to_Visual2D(mesaj , v_text);
	//adaug cercuri din care sari automat (nu stiu cum se numesc astea)
	up1 = new Circle2D(Point2D(4200, 240), 20, Color(1, 0, 1), false);
	up2 = new Circle2D(Point2D(6350, 200), 20, Color(1, 0, 1), false);
	up3 = new Circle2D(Point2D(6600, 200), 20, Color(1, 0, 1), false);
	up4 = new Circle2D(Point2D(6800, 200), 20, Color(1, 0, 1), false);
	up5 = new Circle2D(Point2D(6900, 200), 20, Color(1, 0, 1), false);
	vector_cerc.push_back(up1);
	vector_cerc.push_back(up1);
	vector_cerc.push_back(up1);
	vector_cerc.push_back(up1);
	vector_cerc.push_back(up2);

	//adaug triunghiurile in plan
	t1 = new Polygon2D(Color(0, 0, 1), true);	t4 = new Polygon2D(Color(0, 0, 1), true);
	t1->addPoint(Point2D(3090, 100));			t4->addPoint(Point2D(850, 50));
	t1->addPoint(Point2D(3060, 100));			t4->addPoint(Point2D(820, 50));
	t1->addPoint(Point2D(3075, 120));			t4->addPoint(Point2D(835, 70));
	
	t2 = new Polygon2D(Color(0, 0, 1), true);	t3 = new Polygon2D(Color(0, 0, 1), true);
	t2->addPoint(Point2D(3060, 100));			t3->addPoint(Point2D(3030, 100));
	t2->addPoint(Point2D(3030, 100));			t3->addPoint(Point2D(3000, 100));
	t2->addPoint(Point2D(3045, 120));			t3->addPoint(Point2D(3015, 120));

	t5 = new Polygon2D(Color(0, 0, 1), true);	t6 = new Polygon2D(Color(0, 0, 1), true);
	t5->addPoint(Point2D(880, 50));				t6->addPoint(Point2D(910, 50));
	t5->addPoint(Point2D(850, 50));				t6->addPoint(Point2D(880, 50));
	t5->addPoint(Point2D(865, 70));				t6->addPoint(Point2D(895, 70));

	t7 = new Polygon2D(Color(0, 0, 1), true);	t8 = new Polygon2D(Color(0, 0, 1), true);
	t7->addPoint(Point2D(940, 50));				t8->addPoint(Point2D(1830, 100));
	t7->addPoint(Point2D(910, 50));				t8->addPoint(Point2D(1800, 100));
	t7->addPoint(Point2D(925, 70));				t8->addPoint(Point2D(1815, 120));

	t9 = new Polygon2D(Color(0, 0, 1), true);	t10 = new Polygon2D(Color(0, 0, 1), true);
	t9->addPoint(Point2D(1860, 100));			t10->addPoint(Point2D(2130, 100));
	t9->addPoint(Point2D(1830, 100));			t10->addPoint(Point2D(2100, 100));
	t9->addPoint(Point2D(1845, 120));			t10->addPoint(Point2D(2115, 120));

	t11 = new Polygon2D(Color(0, 0, 1), true);	t12 = new Polygon2D(Color(0, 0, 1), true);
	t11->addPoint(Point2D(2160, 100));			t12->addPoint(Point2D(2430, 100));
	t11->addPoint(Point2D(2130, 100));			t12->addPoint(Point2D(2400, 100));
	t11->addPoint(Point2D(2145, 120));			t12->addPoint(Point2D(2415, 120));

	t13 = new Polygon2D(Color(0, 0, 1), true);	t14 = new Polygon2D(Color(0, 0, 1), true);
	t13->addPoint(Point2D(2460, 100));			t14->addPoint(Point2D(2730, 100));
	t13->addPoint(Point2D(2430, 100));			t14->addPoint(Point2D(2700, 100));
	t13->addPoint(Point2D(2445, 120));			t14->addPoint(Point2D(2715, 120));

	t15 = new Polygon2D(Color(0, 0, 1), true);	t16 = new Polygon2D(Color(0, 0, 1), true);
	t15->addPoint(Point2D(4800, 210));			t16->addPoint(Point2D(4770, 210));
	t15->addPoint(Point2D(4770, 210));			t16->addPoint(Point2D(4740, 210));
	t15->addPoint(Point2D(4785, 230));			t16->addPoint(Point2D(4755, 230));

	t17 = new Polygon2D(Color(0, 0, 1), true);	t18 = new Polygon2D(Color(0, 0, 1), true);
	t17->addPoint(Point2D(4740, 210));			t18->addPoint(Point2D(5030, 210));
	t17->addPoint(Point2D(4710, 210));			t18->addPoint(Point2D(5000, 210));
	t17->addPoint(Point2D(4725, 230));			t18->addPoint(Point2D(5015, 230));

	t19 = new Polygon2D(Color(0, 0, 1), true);	t20 = new Polygon2D(Color(0, 0, 1), true);
	t19->addPoint(Point2D(5060, 210));			t20->addPoint(Point2D(5090, 210));
	t19->addPoint(Point2D(5030, 210));			t20->addPoint(Point2D(5060, 210));
	t19->addPoint(Point2D(5045, 230));			t20->addPoint(Point2D(5075, 230));

	t21 = new Polygon2D(Color(0, 0, 1), true);	t22 = new Polygon2D(Color(0, 0, 1), true);
	t21->addPoint(Point2D(12100, 100));			t22->addPoint(Point2D(12180, 100));
	t21->addPoint(Point2D(12070, 100));			t22->addPoint(Point2D(12150, 100 ));
	t21->addPoint(Point2D(12085, 130));			t22->addPoint(Point2D(12165, 130));

	t23 = new Polygon2D(Color(0, 0, 1), true);	t24 = new Polygon2D(Color(0, 0, 1), true);
	t23->addPoint(Point2D(8100, 100));			t24->addPoint(Point2D(8180, 100));
	t23->addPoint(Point2D(8070, 100));			t24->addPoint(Point2D(8150, 100));
	t23->addPoint(Point2D(8085, 130));			t24->addPoint(Point2D(8165, 130));

	t25 = new Polygon2D(Color(0, 0, 1), true);	t26 = new Polygon2D(Color(0, 0, 1), true);
	t25->addPoint(Point2D(5630, 100));			t26->addPoint(Point2D(5660, 100));
	t25->addPoint(Point2D(5600, 100));			t26->addPoint(Point2D(5630, 100));
	t25->addPoint(Point2D(5615, 130));			t26->addPoint(Point2D(5645, 130));

	t27 = new Polygon2D(Color(0, 0, 1), true);	t28 = new Polygon2D(Color(0, 0, 1), true);
	t27->addPoint(Point2D(5690, 100));			t28->addPoint(Point2D(5720, 100));
	t27->addPoint(Point2D(5660, 100));			t28->addPoint(Point2D(5690, 100));
	t27->addPoint(Point2D(5675, 130));			t28->addPoint(Point2D(5705, 130));

	vector_triunghi.push_back(t1);		vector_triunghi.push_back(t8);
	vector_triunghi.push_back(t2);		vector_triunghi.push_back(t9);
	vector_triunghi.push_back(t3);		vector_triunghi.push_back(t10);
	vector_triunghi.push_back(t4);		vector_triunghi.push_back(t11);
	vector_triunghi.push_back(t5);		vector_triunghi.push_back(t12);
	vector_triunghi.push_back(t6);		vector_triunghi.push_back(t13);
	vector_triunghi.push_back(t7);		vector_triunghi.push_back(t14);
	vector_triunghi.push_back(t15);		vector_triunghi.push_back(t18);
	vector_triunghi.push_back(t16);		vector_triunghi.push_back(t19);
	vector_triunghi.push_back(t17);		vector_triunghi.push_back(t20);
	vector_triunghi.push_back(t21);		vector_triunghi.push_back(t22);
	vector_triunghi.push_back(t23);		vector_triunghi.push_back(t24);
	vector_triunghi.push_back(t25);		vector_triunghi.push_back(t26);
	vector_triunghi.push_back(t27);		vector_triunghi.push_back(t28);
	//adaug oponenti
	oponent = new Rectangle2D(Point2D(12100,100),50,50,Color(1,0,1),true);
	oponent2 = new Rectangle2D(Point2D(8100, 100), 50, 50, Color(1, 0, 1), true);
	//adaug rectangle-urile in plan
	podea1 = new Rectangle2D(Point2D(0, 0), 800, 100, Color(0, 0, 0), true);
	podea2 = new Rectangle2D(Point2D(800, 0), 150, 50, Color(0, 0, 0), true);
	podea3 = new Rectangle2D(Point2D(950, 0), 7000, 100, Color(0, 0, 0), true);
	podea4 = new Rectangle2D(Point2D(7000, 0), 150, 100, Color(0, 0, 0), true);
	podea5 = new Rectangle2D(Point2D(7150, 0), 1000, 100, Color(0, 0, 0), true);
	podea6 = new Rectangle2D(Point2D(8150, 0), 150, 100, Color(0, 0, 0), true);
	podea7 = new Rectangle2D(Point2D(8300, 0), 4000, 100, Color(0, 0, 0), true);
	tavan = new Rectangle2D(Point2D(0, 400), 15000, 90, Color(0, 0, 0), true);
	vector_podea.push_back(podea1);
	vector_podea.push_back(podea2);
	vector_podea.push_back(podea3);
	vector_podea.push_back(podea4);
	vector_podea.push_back(podea5);
	vector_podea.push_back(podea6);
	vector_podea.push_back(podea7);
	//creez playerul
	player = new Rectangle2D(Point2D(100, 100), 50, 50, Color(1, 0, 0), true);
	fata1 = new Rectangle2D(Point2D(110, 130), 10, 10, Color(0, 0, 1), true);
	fata2 = new Rectangle2D(Point2D(130, 130), 10, 10, Color(0, 0, 1), true);
	fata3 = new Rectangle2D(Point2D(110, 110), 30, 10, Color(0, 0, 1), true);
	ef1 = new Rectangle2D(Point2D(97, 97), 7, 7, Color(0, 1, 0), false);
	ef2 = new Rectangle2D(Point2D(96, 96), 7, 7, Color(0, 1, 0), false);
	ef3 = new Rectangle2D(Point2D(95, 95), 7, 7, Color(0, 1, 0), false);
	vector_rect.push_back(player);
	//adaug platforme in plan
	p1 = new Polygon2D(Color(0.5, 0.5, 0.5), true);		p6 = new Polygon2D(Color(0.5, 0.5, 0), true);
	p1->addPoint(Point2D(1600, 100));					p6->addPoint(Point2D(4300, 180));
	p1->addPoint(Point2D(1600, 130));					p6->addPoint(Point2D(4300, 210));
	p1->addPoint(Point2D(1800, 130));					p6->addPoint(Point2D(5400, 210));
	p1->addPoint(Point2D(1800, 100));					p6->addPoint(Point2D(5400, 180));
	
	p2 = new Polygon2D(Color(0.5, 0.5, 0), true);		p7 = new Polygon2D(Color(0.5, 0.5, 0), true);
	p2->addPoint(Point2D(1900, 120));					p7->addPoint(Point2D(4800, 210));
	p2->addPoint(Point2D(1900, 150));					p7->addPoint(Point2D(4800, 240));
	p2->addPoint(Point2D(2100, 150));					p7->addPoint(Point2D(5000, 240));
	p2->addPoint(Point2D(2100, 120));					p7->addPoint(Point2D(5000, 210));

	p3 = new Polygon2D(Color(0.5, 0.5, 0), true);		p8 = new Polygon2D(Color(0.5, 0.5, 0), true);
	p3->addPoint(Point2D(2200, 140));					p8->addPoint(Point2D(3100, 160));
	p3->addPoint(Point2D(2200, 170));					p8->addPoint(Point2D(3100, 190));
	p3->addPoint(Point2D(2400, 170));					p8->addPoint(Point2D(3500, 190));
	p3->addPoint(Point2D(2400, 140));					p8->addPoint(Point2D(3500, 160));

	p4 = new Polygon2D(Color(0.5, 0.5, 0), true);		p9 = new Polygon2D(Color(0.5, 0.5, 0), true);
	p4->addPoint(Point2D(2500, 160));					p9->addPoint(Point2D(3600, 170));
	p4->addPoint(Point2D(2500, 190));					p9->addPoint(Point2D(3600, 200));
	p4->addPoint(Point2D(2700, 190));					p9->addPoint(Point2D(3800, 200));
	p4->addPoint(Point2D(2700, 160));					p9->addPoint(Point2D(3800, 170));

	p5 = new Polygon2D(Color(0.5, 0.5, 0), true);		p10 = new Polygon2D(Color(0.5, 0.5, 0), true);
	p5->addPoint(Point2D(2800, 180));					p10->addPoint(Point2D(3900, 180));
	p5->addPoint(Point2D(2800, 210));					p10->addPoint(Point2D(3900, 210));
	p5->addPoint(Point2D(3000, 210));					p10->addPoint(Point2D(4100, 210));
	p5->addPoint(Point2D(3000, 180));					p10->addPoint(Point2D(4100, 180));

	p11 = new Polygon2D(Color(0.5, 0.5, 0), true);		p12 = new Polygon2D(Color(0.5, 0.5, 0), true);
	p11->addPoint(Point2D(6000, 130));					p12->addPoint(Point2D(7000, 130));
	p11->addPoint(Point2D(6000, 160));					p12->addPoint(Point2D(7000, 160));
	p11->addPoint(Point2D(6300, 160));					p12->addPoint(Point2D(8000, 160));
	p11->addPoint(Point2D(6300, 130));					p12->addPoint(Point2D(8000, 130));

	p13 = new Polygon2D(Color(0.5, 0.5, 0), true);		p14 = new Polygon2D(Color(0.5, 0.5, 0), true);
	p13->addPoint(Point2D(6500, 130));					p14->addPoint(Point2D(6600, 100));
	p13->addPoint(Point2D(6500, 160));					p14->addPoint(Point2D(6600, 130));
	p13->addPoint(Point2D(6670, 160));					p14->addPoint(Point2D(6900, 130));
	p13->addPoint(Point2D(6670, 130));					p14->addPoint(Point2D(6900, 100));

	vector_platforme.push_back(p1);
	vector_platforme.push_back(p2);
	vector_platforme.push_back(p3);
	vector_platforme.push_back(p4);
	vector_platforme.push_back(p5);
	vector_platforme.push_back(p6);
	vector_platforme.push_back(p7);
	vector_platforme.push_back(p8);
	vector_platforme.push_back(p9);
	vector_platforme.push_back(p10);
	vector_platforme.push_back(p11);
	vector_platforme.push_back(p12);
	vector_platforme.push_back(p13);
	vector_platforme.push_back(p14);
	//adaug flags in plan

	flag1 = new Polygon2D(Color(0.3, 0.3, 0.3), true);		flag2 = new Polygon2D(Color(0.3, 0.3, 0.3), true);
	flag1->addPoint(Point2D(1100, 100));					flag2->addPoint(Point2D(5900, 100));
	flag1->addPoint(Point2D(1100, 140));					flag2->addPoint(Point2D(5900, 140));
	flag1->addPoint(Point2D(1130, 130));					flag2->addPoint(Point2D(5930, 130));
	flag1->addPoint(Point2D(1105, 120));					flag2->addPoint(Point2D(5905, 120));
	flag1->addPoint(Point2D(1105, 100));					flag2->addPoint(Point2D(5905, 100));

	coin1 = new Polygon2D(Color(0, 0.8, 0), true);			coin2 = new Polygon2D(Color(0, 0.8, 0), true);
	coin1->addPoint(Point2D(1200, 100));					coin2->addPoint(Point2D(4900, 240));
	coin1->addPoint(Point2D(1200, 140));					coin2->addPoint(Point2D(4900, 280));
	coin1->addPoint(Point2D(1230, 130));					coin2->addPoint(Point2D(4930, 270));
	coin1->addPoint(Point2D(1205, 120));					coin2->addPoint(Point2D(4905, 260));
	coin1->addPoint(Point2D(1205, 100));					coin2->addPoint(Point2D(4905, 240));

	coin3 = new Polygon2D(Color(0, 0.8, 0), true);			coin4 = new Polygon2D(Color(0, 0.8, 0), true);
	coin3->addPoint(Point2D(2300, 170));					coin4->addPoint(Point2D(2900, 210));
	coin3->addPoint(Point2D(2300, 210));					coin4->addPoint(Point2D(2900, 250));
	coin3->addPoint(Point2D(2330, 200));					coin4->addPoint(Point2D(2930, 240));
	coin3->addPoint(Point2D(2305, 190));					coin4->addPoint(Point2D(2905, 230));
	coin3->addPoint(Point2D(2305, 170));					coin4->addPoint(Point2D(2905, 210));

	coin6 = new Polygon2D(Color(0, 0.8, 0), true);			coin7 = new Polygon2D(Color(0, 0.8, 0), true);
	coin6->addPoint(Point2D(6150, 160));					coin7->addPoint(Point2D(7500, 160));
	coin6->addPoint(Point2D(6150, 200));					coin7->addPoint(Point2D(7500, 200));
	coin6->addPoint(Point2D(6180, 190));					coin7->addPoint(Point2D(7530, 190));
	coin6->addPoint(Point2D(6155, 180));					coin7->addPoint(Point2D(7505, 180));
	coin6->addPoint(Point2D(6155, 160));					coin7->addPoint(Point2D(7505, 160));

	coin5 = new Polygon2D(Color(0, 0.8, 0), true);			flag3 = new Polygon2D(Color(0.3, 0.3, 0.3), true);
	coin5->addPoint(Point2D(3300, 190));					flag3->addPoint(Point2D(8200, 100));
	coin5->addPoint(Point2D(3300, 230));					flag3->addPoint(Point2D(8200, 140));
	coin5->addPoint(Point2D(3330, 220));					flag3->addPoint(Point2D(8230, 130));
	coin5->addPoint(Point2D(3305, 210));					flag3->addPoint(Point2D(8205, 120));
	coin5->addPoint(Point2D(3305, 190));					flag3->addPoint(Point2D(8205, 100));

	vector_flags.push_back(flag1);	vector_flags.push_back(flag2);	vector_flags.push_back(flag3);
	vector_coins.push_back(coin1);	vector_coins.push_back(coin2);	vector_coins.push_back(coin3);
	vector_coins.push_back(coin4);	vector_coins.push_back(coin5);
	vector_coins.push_back(coin6);	vector_coins.push_back(coin7);
	//lista de obiecte din plan
	
	addObject2D(t1);		//0
	addObject2D(t2);		//1
	addObject2D(t3);		//2
	addObject2D(fata1);		//3		//0
	addObject2D(fata2);		//4		//1
	addObject2D(fata3);		//5		//2
	addObject2D(player);	//6		//3
	addObject2D(t4);	addObject2D(t7);	addObject2D(t10);	addObject2D(t13);
	addObject2D(t5);	addObject2D(t8);	addObject2D(t11);	addObject2D(t14);
	addObject2D(t6);	addObject2D(t9);	addObject2D(t12);
	addObject2D(p1);		//18	//0
	addObject2D(p2);		//19	//1
	addObject2D(podea1);	//20	//0
	addObject2D(podea2);	//21	//1
	addObject2D(podea3);	//22	//2
	addObject2D(p3);		//23	//2
	addObject2D(p4);		//24	//3
	addObject2D(p5);		//25	//4
	addObject2D(p6);		//26
	addObject2D(p7);		//27
	addObject2D(p8);		//28
	addObject2D(p9);		//29
	addObject2D(p10);		//30
	addObject2D(ef1);		//31
	addObject2D(ef2);		//32
	addObject2D(ef3);		//33
	addObject2D(flag1);		//34	//0
	addObject2D(flag2);		//35
	addObject2D(up1);		//36	//0
	addObject2D(t15);	addObject2D(t16);	//37,38
	addObject2D(t17);	addObject2D(t18);	//39,40
	addObject2D(t19);	addObject2D(t20);	//41,42
	addObject2D(t21);	addObject2D(t22);	//43,44
	addObject2D(t23);	addObject2D(t24);	//45,46
	addObject2D(oponent);	addObject2D(oponent2);	//47,48
	addObject2D(flag3);								//49
	addObject2D(coin1);	addObject2D(coin2);	addObject2D(coin3);	//50,51,52
	addObject2D(coin4);	addObject2D(coin5);						//53,54
	addObject2D(coin6);	addObject2D(coin7);						//55,56
	addObject2D(podea4);		//57
	addObject2D(podea5);		//56
	addObject2D(podea6);		//57
	addObject2D(podea7);		//58
	addObject2D(t25);	addObject2D(t26);	//59,60	
	addObject2D(t27);	addObject2D(t28);	//61,62
	addObject2D(p11);	addObject2D(p12);	//63,64
	addObject2D(up2);		//65
//	addObject2D(up3);		//66
//	addObject2D(up4);		//67
//	addObject2D(up5);		//68
	addObject2D(p13);		//69
	addObject2D(p14);		//72
	addObject2D(tavan);		//73
}

static bool epsilon(float a, float b) {
	if (abs(a - b) < 12) return true;
	else return false;
}
static bool epsilon_cerc(float a, float b) {
	if (abs(a - b) < 50) return true;
	else return false;
}

//!!! ON IDLE IS HERE !!!
void DrawingWindow::onIdle()
{
	
	if (vieti == 0) {
		//afisam text ca e game over
		//trebuie sa apese r ca sa refaca jocul
		start = false;
		removeText_from_Visual2D(mesaj, v_text);
		removeText(mesaj);
		sprintf(buffer_text, "Ati murit , daca vreti sa mai incercat inca o data apasati r");
		mesaj = new Text(buffer_text, Point2D(300, 300), Color(1, 0, 0), BITMAP_TIMES_ROMAN_24);	//containerul de text
		addText_to_Visual2D(mesaj, v_text);
	}
	if (contor_coins == 5 && won == false) {
		removeText_from_Visual2D(mesaj_win, v_text);
		removeText(mesaj_win);
		buffer_text = (char*)malloc(100 * sizeof(char));
		sprintf(buffer_text, "Ai castigat! Daca vrei sa continui , poti apasa butonul de pauza(adica backspace)");
		mesaj_win = new Text(buffer_text, Point2D(300, 300), Color(1, 0, 1), BITMAP_TIMES_ROMAN_24);
		addText_to_Visual2D(mesaj_win, v_text);
		start = !start;
		won = true;
	}
	if (start == true) {
		pas += 5;
		bounce += 10 ;
		stay_on_platform = false;
		flagged = false;
		respawn_time += 20;
		removeText_from_Visual2D(mesaj_win, v_text);
		removeText(mesaj_win);
		buffer_text = (char*)malloc(100 * sizeof(char));
		//toate obiectele le translatez cu pas
		for (int i = 0; i < 3; i++){
			Transform2D::loadIdentityMatrix();
			Transform2D::translateMatrix(-pas, 0);
			Transform2D::applyTransform(objects2D[i]);
		}
		for (int i = 7; i < 43; i++){
			Transform2D::loadIdentityMatrix();
			Transform2D::translateMatrix(-pas, 0);
			Transform2D::applyTransform(objects2D[i]);
		}
		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(-pas, 0);
		Transform2D::applyTransform(objects2D[49]);
		for (int i = 57; i < 70; i++){
			Transform2D::loadIdentityMatrix();
			Transform2D::translateMatrix(-pas, 0);
			Transform2D::applyTransform(objects2D[i]);
		}
		//fac oponentul sa se miste
			if (bounce > 6000) bounce = 0.0f; 
			Transform2D::loadIdentityMatrix();
			Transform2D::translateMatrix(-bounce*2, 0);
			Transform2D::applyTransform(objects2D[43]);
			Transform2D::applyTransform(objects2D[44]);
			Transform2D::applyTransform(objects2D[45]);
			Transform2D::applyTransform(objects2D[46]);
			Transform2D::applyTransform(objects2D[47]);
			Transform2D::applyTransform(objects2D[48]);
		//numar cate coins am cules
		for (int i = 0; i < nr_coins; i++) {
			if (epsilon (vector_coins[i]->transf_points[0]->x , objects2D[6]->transf_points[0]->x)
				&& epsilon(vector_coins[i]->transf_points[0]->y, objects2D[6]->transf_points[0]->y)){
				contor_coins++;
				removeText_from_Visual2D(mesaj_coins, v_text);
				removeText(mesaj_coins);
				buffer_text = (char*)malloc(100 * sizeof(char));
				sprintf(buffer_text, "numarul de flags adunate este : %d", contor_coins);
				mesaj_coins = new Text(buffer_text, Point2D(800, 500), Color(0, 0, 1), BITMAP_TIMES_ROMAN_24);
				addText_to_Visual2D(mesaj_coins, v_text);
				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(0, -300);
				Transform2D::applyTransform(objects2D[i + 50]);
				last_coin = i;
			}
			else if (i <= last_coin) {
				//bubble lasat gol intentionat , nu vreau sa apara pe ecran steagul daca a fost cules deja
			}
			else {
				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(-pas, 0);
				Transform2D::applyTransform(objects2D[i + 50]);
			}
		}

		//fac verificari pt boost circles
		for (int i = 0; i < nr_circles; i++) {
			if (epsilon_cerc(vector_cerc[i]->transf_points[0]->x, objects2D[6]->transf_points[0]->x)
				&& epsilon_cerc(vector_cerc[i]->transf_points[0]->y, objects2D[6]->transf_points[0]->y)) {
				boost = true;
				space = true;
				cerc_offset = vector_cerc[i]->transf_points[0]->y - objects2D[6]->points[0]->y;
				k = 0;
				pas_space = 0;
				pas_rot = 0;
			//	platform_offset = 0.0f;
			}
		}

		//fac verificari pentru platforme
		for (int i = 0; i < nr_platforme; i++) {
			//if (epsilon(vector_platforme[i]->transf_points[0]->x, objects2D[6]->points[0]->x)
			//	&& epsilon(objects2D[6]->transf_points[0]->y, vector_platforme[i]->transf_points[0]->y)) pas = 0;
			if ((vector_platforme[i]->transf_points[0]->y <= objects2D[6]->transf_points[0]->y)
				&& objects2D[6]->transf_points[0]->y <= vector_platforme[i]->transf_points[1]->y
				&& epsilon(objects2D[6]->transf_points[0]->x + 40, vector_platforme[i]->transf_points[0]->x)) {
				pas = checkpoint;
				if (respawn_time > 200) {
					vieti--;
					respawn_time = 0;
					removeText_from_Visual2D(mesaj, v_text);
					removeText(mesaj);
					sprintf(buffer_text, "numarul de vieti ramase este : %d", vieti);
					mesaj = new Text(buffer_text, Point2D(900, 600), Color(0, 0, 1), BITMAP_TIMES_ROMAN_24);	//containerul de text
					addText_to_Visual2D(mesaj, v_text);
				}
				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(0, flag_offset);
				Transform2D::applyTransform(objects2D[6]);
				Transform2D::applyTransform(objects2D[5]);
				Transform2D::applyTransform(objects2D[4]);
				Transform2D::applyTransform(objects2D[3]);
				if (flag_offset != 0.0f) stay_on_platform = true;
			}
			else if (vector_platforme[i]->transf_points[0]->x <= objects2D[6]->transf_points[0]->x
				&& objects2D[6]->transf_points[0]->x <= vector_platforme[i]->transf_points[3]->x
				&& epsilon(vector_platforme[i]->transf_points[1]->y, objects2D[6]->transf_points[0]->y)) {
				stay_on_platform = true;
				//space = false;
				platform_offset = vector_platforme[i]->transf_points[1]->y - objects2D[6]->points[0]->y;
			}
			else if (epsilon(vector_platforme[i]->transf_points[2]->x, objects2D[6]->transf_points[0]->x)) {

				stay_on_platform = false;
				//	Transform2D::translateMatrix(0, -platform_offset);		//asta daca as putea corecta ar fi f frumos
				//	platform_offset = 0.0f;
			}
			else if (vector_platforme[i]->transf_points[0]->x <= objects2D[6]->transf_points[0]->x
				&& objects2D[6]->transf_points[0]->x <= vector_platforme[i]->transf_points[3]->x
				&& epsilon(vector_platforme[i]->transf_points[0]->y, objects2D[6]->transf_points[0]->y)
				&& flagged){
				pas = checkpoint;
				if (respawn_time > 200) {
					vieti--;
					respawn_time = 0;
					removeText_from_Visual2D(mesaj, v_text);
					removeText(mesaj);
					sprintf(buffer_text, "numarul de vieti ramase este : %d", vieti);
					mesaj = new Text(buffer_text, Point2D(900, 600), Color(0, 0, 1), BITMAP_TIMES_ROMAN_24);	//containerul de text
					addText_to_Visual2D(mesaj, v_text);
				}
				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(0, flag_offset);
				Transform2D::applyTransform(objects2D[6]);
				Transform2D::applyTransform(objects2D[5]);
				Transform2D::applyTransform(objects2D[4]);
				Transform2D::applyTransform(objects2D[3]);
				if (flag_offset != 0.0f) stay_on_platform = true;
			}
		}

		//fac verificari pentru flags
		for (int i = 0; i < nr_flags; i++) {
			if (epsilon(vector_flags[i]->transf_points[0]->x, objects2D[6]->transf_points[0]->x)
				&& epsilon(vector_flags[i]->transf_points[0]->y, objects2D[6]->transf_points[0]->y)){
				checkpoint = pas;
				flag_offset = vector_flags[i]->transf_points[0]->y - objects2D[6]->points[0]->y;
				flagged = true;
			}
		}
		//fac verificari pentru tzepe
		for (int i = 0; i < nr_tzepe; i++) {

			if (epsilon(vector_triunghi[i]->transf_points[1]->x, objects2D[6]->transf_points[0]->x)
				&& epsilon(objects2D[6]->transf_points[0]->y, vector_triunghi[i]->transf_points[1]->y)) 
			{
				pas = checkpoint;
				if (respawn_time > 200) {
					vieti--;
					respawn_time = 0;
					removeText_from_Visual2D(mesaj, v_text);
					removeText(mesaj);
					sprintf(buffer_text, "numarul de vieti ramase este : %d", vieti);
					mesaj = new Text(buffer_text, Point2D(900, 600), Color(0, 0, 1), BITMAP_TIMES_ROMAN_24);	//containerul de text
					addText_to_Visual2D(mesaj, v_text);
				}
				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(0, flag_offset);
				Transform2D::applyTransform(objects2D[6]);
				Transform2D::applyTransform(objects2D[5]);
				Transform2D::applyTransform(objects2D[4]);
				Transform2D::applyTransform(objects2D[3]);
				if (flag_offset != 0.0f) stay_on_platform = true;
			}
			else if (epsilon(vector_triunghi[i]->transf_points[1]->x, objects2D[6]->transf_points[0]->x + 50)
				&& epsilon(objects2D[6]->transf_points[0]->y, vector_triunghi[i]->transf_points[1]->y)) {
				pas = checkpoint;
				if (respawn_time > 200) {
					vieti--;
					respawn_time = 0;
					removeText_from_Visual2D(mesaj, v_text);
					removeText(mesaj);
					sprintf(buffer_text, "numarul de vieti ramase este : %d", vieti);
					mesaj = new Text(buffer_text, Point2D(900, 600), Color(0, 0, 1), BITMAP_TIMES_ROMAN_24);	//containerul de text
					addText_to_Visual2D(mesaj, v_text);
				}
				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(0, flag_offset);
				Transform2D::applyTransform(objects2D[6]);
				Transform2D::applyTransform(objects2D[5]);
				Transform2D::applyTransform(objects2D[4]);
				Transform2D::applyTransform(objects2D[3]);
				if (flag_offset != 0.0f) stay_on_platform = true;
			}
			else if (epsilon(vector_triunghi[i]->transf_points[2]->x, objects2D[6]->transf_points[0]->x+50)
				&& epsilon(objects2D[6]->transf_points[0]->y , vector_triunghi[i]->transf_points[2]->y)) {
				pas = checkpoint;
				if (respawn_time > 200) {
					vieti--;
					respawn_time = 0;
					removeText_from_Visual2D(mesaj, v_text);
					removeText(mesaj);
					sprintf(buffer_text, "numarul de vieti ramase este : %d", vieti);
					mesaj = new Text(buffer_text, Point2D(900, 600), Color(0, 0, 1), BITMAP_TIMES_ROMAN_24);	//containerul de text
					addText_to_Visual2D(mesaj, v_text);
				}
				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(0, flag_offset);
				Transform2D::applyTransform(objects2D[6]);
				Transform2D::applyTransform(objects2D[5]);
				Transform2D::applyTransform(objects2D[4]);
				Transform2D::applyTransform(objects2D[3]);
				if (flag_offset != 0.0f) stay_on_platform = true;
			}
			else if (epsilon(vector_triunghi[i]->transf_points[1]->x, objects2D[6]->transf_points[0]->x)
				&& epsilon(objects2D[6]->transf_points[0]->y, vector_triunghi[i]->transf_points[1]->y)) {
				pas = checkpoint;
				if (respawn_time > 200) {
					vieti--;
					respawn_time = 0;
					removeText_from_Visual2D(mesaj, v_text);
					removeText(mesaj);
					sprintf(buffer_text, "numarul de vieti ramase este : %d", vieti);
					mesaj = new Text(buffer_text, Point2D(900, 600), Color(0, 0, 1), BITMAP_TIMES_ROMAN_24);	//containerul de text
					addText_to_Visual2D(mesaj, v_text);
				}
				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(0, flag_offset);
				Transform2D::applyTransform(objects2D[6]);
				Transform2D::applyTransform(objects2D[5]);
				Transform2D::applyTransform(objects2D[4]);
				Transform2D::applyTransform(objects2D[3]);
				if (flag_offset != 0.0f) stay_on_platform = true;
			}
			else if (epsilon(vector_triunghi[i]->transf_points[2]->x, objects2D[6]->transf_points[0]->x)
				&& epsilon(objects2D[6]->transf_points[0]->y , vector_triunghi[i]->transf_points[2]->y)) {
				pas = checkpoint;
				if (respawn_time > 200) {
					vieti--;
					respawn_time = 0;
					removeText_from_Visual2D(mesaj,v_text);
					removeText(mesaj);
					sprintf(buffer_text, "numarul de vieti ramase este : %d", vieti);
					mesaj = new Text(buffer_text, Point2D(900, 600), Color(0, 0, 1), BITMAP_TIMES_ROMAN_24);	//containerul de text
					addText_to_Visual2D(mesaj, v_text);
				}
				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(0, flag_offset);
				Transform2D::applyTransform(objects2D[6]);
				Transform2D::applyTransform(objects2D[5]);
				Transform2D::applyTransform(objects2D[4]);
				Transform2D::applyTransform(objects2D[3]);
				if (flag_offset != 0.0f) stay_on_platform = true;
			}
		}

		if (stay_on_platform == true) {

			Transform2D::loadIdentityMatrix();
			Transform2D::translateMatrix(0, platform_offset);
			Transform2D::applyTransform(objects2D[6]);
			Transform2D::applyTransform(objects2D[5]);
			Transform2D::applyTransform(objects2D[4]);
			Transform2D::applyTransform(objects2D[3]);
		}
		else if (flagged == true) {
			cout << "e flagged";
			Transform2D::loadIdentityMatrix();
			Transform2D::translateMatrix(0, flag_offset);
			Transform2D::applyTransform(objects2D[6]);
			Transform2D::applyTransform(objects2D[5]);
			Transform2D::applyTransform(objects2D[4]);
			Transform2D::applyTransform(objects2D[3]);
		}
		//asta practic este caderea obiectului , poate ii dau rotatie aici
		else if (stay_on_platform == false) {
			if (space == false) platform_offset = 0.0f;
			//aici trebuie sa fac verificarea daca se afla o platforma sub player sau un cerc
			int ok = 0;
			for (int i = 0; i < nr_platforme; i++) 
				if (vector_platforme[i]->transf_points[1]->x <= objects2D[6]->transf_points[0]->x
					&&objects2D[6]->transf_points[0]->x <= vector_platforme[i]->transf_points[2]->x
					&&objects2D[6]->transf_points[0]->y >= vector_platforme[i]->transf_points[1]->y) {
					Transform2D::loadIdentityMatrix();
					Transform2D::translateMatrix(0,vector_platforme[i]->transf_points[1]->y - objects2D[6]->points[0]->y);
					Transform2D::applyTransform(objects2D[6]);
					Transform2D::applyTransform(objects2D[5]);
					Transform2D::applyTransform(objects2D[4]);
					Transform2D::applyTransform(objects2D[3]);
					ok = 1;
					break;
				}

			if (ok == 0) {
				Transform2D::loadIdentityMatrix();
				Transform2D::applyTransform(objects2D[6]);
				Transform2D::applyTransform(objects2D[5]);
				Transform2D::applyTransform(objects2D[4]);
				Transform2D::applyTransform(objects2D[3]);
			}
		}

		//fac playerul sa cada in groapa
		//fac o conventie : inaltimea groapei e de 100 si adancimea de 50
		for (int i = 2; i < 3; i++) {
			if (epsilon(vector_podea[i-1]->transf_points[0]->x, objects2D[6]->points[0]->x)
				&& epsilon(objects2D[6]->transf_points[0]->y, vector_podea[i-1]->transf_points[0]->y + 100 )) {
				//cade cand e la margine
			//	Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(0, -50);
				Transform2D::applyTransform(objects2D[6]);
				Transform2D::applyTransform(objects2D[5]);
				Transform2D::applyTransform(objects2D[4]);
				Transform2D::applyTransform(objects2D[3]);
			}

			if (vector_podea[i - 1]->transf_points[0]->x <= objects2D[6]->transf_points[0]->x
				&& objects2D[6]->transf_points[0]->x <= vector_podea[i]->transf_points[0]->x
				&& epsilon(objects2D[6]->transf_points[0]->y, vector_podea[i]->transf_points[0]->y + 100)){
				//cade cand sare in groapa
			//	Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(0, -50);
				Transform2D::applyTransform(objects2D[6]);
				Transform2D::applyTransform(objects2D[5]);
				Transform2D::applyTransform(objects2D[4]);
				Transform2D::applyTransform(objects2D[3]);
			}
			if (epsilon(vector_podea[i]->transf_points[0]->x, objects2D[6]->points[0]->x +50)
				&& epsilon(objects2D[6]->transf_points[0]->y, vector_podea[i]->transf_points[0]->y)) {
				pas = checkpoint;
				if (respawn_time > 200) {
					vieti--;
					respawn_time = 0;
					removeText_from_Visual2D(mesaj,v_text);
					removeText(mesaj);
					sprintf(buffer_text, "numarul de vieti ramase este : %d", vieti);
					mesaj = new Text(buffer_text, Point2D(900, 600), Color(0, 0, 1), BITMAP_TIMES_ROMAN_24);	//containerul de text
					addText_to_Visual2D(mesaj, v_text);
				}
				//moare cand loveste capatul gropii
				Transform2D::loadIdentityMatrix();
				Transform2D::applyTransform(objects2D[6]);
				Transform2D::applyTransform(objects2D[5]);
				Transform2D::applyTransform(objects2D[4]);
				Transform2D::applyTransform(objects2D[3]);
			}
		}
		
		//fac playerul sa sara

		if (space == true) {
			Transform2D::loadIdentityMatrix();
			pas_rot += 0.1495;
			if (k++ <= 20) {
				pas_space += 5;
				if (boost) {
					Transform2D::translateMatrix(0, pas_space + platform_offset + cerc_offset);
				}
				else if (flagged) {
					Transform2D::translateMatrix(0, pas_space + flag_offset);
				}
				else {
					Transform2D::translateMatrix(0, pas_space + platform_offset);
				}
			}
			else {

				pas_space -= 5;
				if (boost) {
					Transform2D::translateMatrix(0, pas_space + platform_offset + cerc_offset);
				}
				else if (flagged) {
					Transform2D::translateMatrix(0, pas_space + flag_offset);
				}
				else {
					Transform2D::translateMatrix(0, pas_space + platform_offset);
				}
				if (pas_space <= 0) {
					space = false;
					pas_space = 0;
				}
			}
			if (boost) {
				Transform2D::translateMatrix(-125, -125 - pas_space - platform_offset-cerc_offset);
				Transform2D::rotateMatrix(-pas_rot);
				Transform2D::translateMatrix(125, 125 + pas_space + platform_offset+cerc_offset);
			}
			else {
				Transform2D::translateMatrix(-125, -125 - pas_space - platform_offset);
				Transform2D::rotateMatrix(-pas_rot);
				Transform2D::translateMatrix(125, 125 + pas_space + platform_offset);
			}
			Transform2D::applyTransform(objects2D[6]);
			Transform2D::applyTransform(objects2D[5]);
			Transform2D::applyTransform(objects2D[4]);
			Transform2D::applyTransform(objects2D[3]);

		}
		else {
			k = 0;
			pas_space = 0;
			pas_rot = 0;
			platform_offset = 0.0f;
			boost = false;
			cerc_offset = 0.0f;
			//aplicam acum efectul de particule
		}
	}
}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{
	
	v2d1->poarta(0,0,width/4,height/4); 
	v_text->poarta(0, 0, width , height);
}

//functia care defineste ce se intampla cand se apasa pe tastatura
void DrawingWindow::onKey(unsigned char key)
{
	switch(key)
	{
		case 27: {
			exit(0);
			break;
		}
		case 8: {
			start = !start;
			removeText_from_Visual2D(mesaj_win, v_text);
			removeText(mesaj_win);
			break;
		}
		case 32: {
			space = true;
			break;
		}
		case 114: {
			pas = 0;
			checkpoint = 0;
			vieti = 3;
			start = true;
			removeText_from_Visual2D(mesaj, v_text);
			removeText(mesaj);
			sprintf(buffer_text, "numarul de vieti ramase este : %d", vieti);
			mesaj = new Text(buffer_text, Point2D(900, 600), Color(0, 0, 1), BITMAP_TIMES_ROMAN_24);	//containerul de text
			addText_to_Visual2D(mesaj, v_text);
			contor_coins = 0;
			removeText_from_Visual2D(mesaj_coins, v_text);
			removeText(mesaj_coins);
			for (int i = 0; i <= last_coin; i++){
				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(0, 300);
				Transform2D::applyTransform(objects2D[i + 50]);
			}
			last_coin = -1;
			won = false;
			break;
		}
	}
}

//functia care defineste ce se intampla cand se da click pe mouse
void DrawingWindow::onMouse(int button,int state,int x, int y){}

int main(int argc, char** argv)
{
	//creare fereastra
	DrawingWindow dw(argc, argv, 1300, 700, 0, 0, "Tema1 EGC");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}