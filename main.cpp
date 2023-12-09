/*
* ������ܿ�����־-------�Ǻ�һҶ.Ck[UV](Ѧ)
	1.������Ŀ
	2.�����ز�
	3.������Ϸ����
	4.��������
		���ڳ�ѧ�ߣ���õķ�ʽ��������û���������

		ѡ��ͼ�ο����������
		���β��õ��ǡ�easyx��ͼ�ο�
----------------------------�Ǻ�һҶ.CK(Ѧ)[UV]

		1�� ������Ϸ����
		2�� �����Ϸ����
			a.���ر�����ͬ�ٶ�ͬʱ�ƶ�
			b.ѭ������������ʵ�֣��ñ�������ѭ��������ô����
		3�� ʵ����Ϸ����
			a.���ر�����Դ
			b.��Ⱦ(����֪ʶ�����꣩
			�������⣺����ͼƬ��png��ʽͼƬ���ֺ�ɫ
		4�� ʵ����ұ���
			a.����ͼƬ��Դ
		5�� ʵ����ҵ���Ծ
		6)	ʵ���ϰ���-С�ڹ� �������
		7)	���ϰ�����з�װ �����Ż�
				a.�ȶ���ö�� �� �ṹ�� 
				b. ���ϰ�����г�ʼ��
				c.����ĸ��� ���ɷ�װ����
		8)	ʵ������¶�
		9)	ʵ�������ϰ���
		10��ʵ���ϰ����Ƶ���Ż�
		11)  ʵ����ײ���
		12�� ʵ����Ч
		13�� �޸���Чbug���Ż��¶�
		14�� ����Ѫ������
		15)	  �����Ϸ�������жϣ������жϣ�
		16�� ��ӱ��������Լ���Ϸ��ʼ������
*/

#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<vector>
#include"tools.h"

using namespace std;

// ������ú��Ԥ���� Ϊ���Ǹ��õ�ά��
#define WIN_SCORE 100

#define WIN_WIDTH 1012
#define	 WIN_HEIGHT 396 
#define OBSTACLE_COUNT 10

IMAGE imaBgs[3]; // ��Ϊ�������ط��϶�ҲҪ�õ���� ����ֱ�Ӷ���Ϊȫ�ֱ���					�洢����ͼƬ
int bgX[3];		// ��ű���ͼƬX����
int bgspeed[3] = { 1,2,4 }; // �����ƶ����ٶȽ��п��� ����ĵ�λ������

IMAGE bgHeros[12];
int HeroX;
int HeroY;
int HeroIndex;

bool heroJump;
bool herodown;

int jumpHeightMax;
int jumpHeightOff;

int update; // �����ж��Ƿ�Ҫˢ��

//IMAGE Tortoise[7]; // С�ڹ�
//int TortoiseX;	// С�ڹ��ˮƽ����
//int TortoiseY;	// С�ڹ�Ĵ�ֱ����
//bool torToiseExist;	// С�ڹ��Ƿ����
//int torToiseIndex;

typedef enum {
	// ö��
	TORTOISE,	// �ڹ� 0
	LION,			// ʨ�� 1
	HOOK1,
	HOOK2,
	HOOK3,
	HOOK4,
	OBSTACLE_TYPE_COUNT			// 6    �����Զ��� ö������  ���һ���Ϳ���ֱ�����ȫ���ĸ�����
}	obstacle_type; // �����ӾͿ���ֱ���������ʾ�ϰ���������

// ��Ÿ����ϰ����ͼƬ
vector<vector<IMAGE>> obstacleImags; // ��vectorһ���������г�Ա ÿ����Ա�ֶ������� ���˶�ά����

// ����typedef �����ڱ��� Ҳ���ǿ��Ա������Ҳ���Ե�������ṹ��
typedef struct obstacle
{
	int type;	// �ϰ�������
	int imaIndex;  //��ǰ��ʾͼƬ�����
	int x, y;	// �ϰ����ˮƽ����ʹ�ֱ����
	int speed;
	int power;  // ɱ����
	bool exist;
	bool hited;	// ��ʾ�Ƿ��Ѿ���������ײ
	bool passed; // ��ʾ�Ƿ��Լ���ͨ��
	// IMAGE img[12];
} obstacle_t;

obstacle_t obstacles[OBSTACLE_COUNT];
int lastObsIndex;

IMAGE imgHeroDown[2];

int heroBlood;
int score;  // ����

IMAGE imgSZ[10];

// ��Ϸ��ʼ�� 
void init()
{
	// ������Ϸ����
	initgraph(WIN_WIDTH, WIN_HEIGHT);// ��Ӧ�Ŀ�͸�

	// ���ر�����Դ 
	// ��Ϊ����ѭ������ȡ ������Ҫ���ʵ��ļ���
	char name[64];
	for (int i = 0; i < 3; i++) {
		// "res/bg001.png"   "res/bg002.png"  "res/bg003.png"
		sprintf(name, "res/bg%03d.png", i + 1); // ����3λ ������0
		// ��Ϊ������ ������forѭ������ȡ
		loadimage(&imaBgs[i],name);

		bgX[i] = 0;
	}

	for (int i = 0; i < 12; i++) {
		// "res/hero1.png"...... "res/hero12.png"
		sprintf(name, "res/hero%d.png", i + 1);
		loadimage(&bgHeros[i], name);
	}
	HeroX = WIN_WIDTH * 0.5 - bgHeros[0].getwidth() * 0.5;
	HeroY = 345 - bgHeros[0].getheight();
	HeroIndex = 0;

	heroJump = false;

	jumpHeightMax = 345 - bgHeros[0].getheight() -130;
	jumpHeightOff = -5; // �߶ȵ�ƫ����

	update = true;

	// ����С�ڹ��ز�
	//for (int i = 0; i < 7; i++) {
	//	// "res/t1.png" ... "res/t7.png"
	//	sprintf(name, "res/t%d.png", i + 1);
	//	loadimage(&Tortoise[i],name);
	//}
	//torToiseIndex = 0;
	//torToiseExist = false; 
	//TortoiseY = 345 - Tortoise[0].getheight() + 5;
	IMAGE imaTort;
	vector<IMAGE> imaTortArray;
	for (int i = 0; i < 7; i++) {
		sprintf(name, "res/t%d.png", i + 1);
		loadimage(&imaTort, name); 
		imaTortArray.push_back(imaTort);// һά����
	}
	obstacleImags.push_back(imaTortArray); // ���뵽�ոն���Ķ�ά������

	// ����Сʨ��
	IMAGE imaLion;
	vector<IMAGE> imaLionArray;
	for (int i = 0; i < 6; i++) {
		sprintf(name, "res/p%d.png", i + 1);
		loadimage(&imaLion, name);
		imaLionArray.push_back(imaLion); 
	}
	obstacleImags.push_back(imaLionArray);

	//  ��ʼ���ϰ����
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		obstacles[i].exist = false;
	}

	// �����¶��ز�
	loadimage(&imgHeroDown[0], "res/d1.png");
	loadimage(&imgHeroDown[1], "res/d2.png");
	herodown = false;

	// �������ӵ��ز�
	IMAGE imgH;

	for (int i = 0; i < 4; i++) {
		vector<IMAGE> imgHookArray;
		sprintf(name, "res/h%d.png", i + 1);
		loadimage(&imgH, name,75,267,true);
		imgHookArray.push_back(imgH);
		obstacleImags.push_back(imgHookArray);
	}

	// Ѫ������
	heroBlood = 100;

	// Ԥ������Ч
	preLoadSound("res/hit.mp3");

	// ��ӱ�������
	mciSendString("play res/bg.mp3 repeat", 0, 0, 0);

	lastObsIndex = -1;

	// ������ʼ��
	score = 0;

	// ��������ͼƬ
	for (int i = 0; i < 10; i++) {
		sprintf(name, "res/sz/%d.png", i);
		loadimage(&imgSZ[i], name);
	}
}

void creatObstacle()
{
	int i;
	for (i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacles[i].exist == false) {
			break;
		}
	}
	if (i >= OBSTACLE_COUNT) {
		return;
	}

	// ��������ϰ���
	// һЩ������Ϣ��ͳһ
	obstacles[i].exist = true;
	obstacles[i].hited = false;
	obstacles[i].imaIndex = 0; 
	/*obstacles[i].type = (obstacle_type)(rand() % OBSTACLE_TYPE_COUNT);*/ // ��Ϊ��2������ ���Զ�2ȡ�� 
	obstacles[i].type = (obstacle_type)(rand() % 3);

	// �ж���һ���ϰ��������Ƿ�Ϊ���� �����������ϰ����Ż�
	if(lastObsIndex >= 0 &&
			obstacles[lastObsIndex].type >= HOOK1 &&
			obstacles[lastObsIndex].type <= HOOK4 &&
			obstacles[i].type == LION &&
			obstacles[lastObsIndex].x > (WIN_WIDTH - 500)) {
		obstacles[i].type = TORTOISE;
	}
	lastObsIndex = i;

	if (obstacles[i].type == HOOK1)
	{
		obstacles[i].type +=  rand() % 4; //0-3
	}
	obstacles[i].x = WIN_WIDTH;  // ��������Ļ�ұ߳���
	obstacles[i].y = 350 - obstacleImags[obstacles[i].type][0].getheight();

	// �ڹ�
	if (obstacles[i].type == TORTOISE) {
		obstacles[i].speed = 0;
		obstacles[i].power = 5;		
	}

	// ʨ��
	else if (obstacles[i].type == LION) {
		obstacles[i].speed = 4;
		obstacles[i].power = 20;
	}

	// ���� ��Ϊ�������ͷ�Χ��ѡ ������1��4֮��������� ��ͳһ������һ������ֵ
	else if (obstacles[i].type >= HOOK1 && obstacles[i].type <= HOOK4) {
		obstacles[i].speed = 0;
		obstacles[i].power = 20;
		obstacles[i].y = 0; // �����ڶ���
	}

	obstacles[i].passed == false;
}

void checkHit()
{
	// ����򵥴ֱ�һ�� ����ѭ��
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacles[i].exist && obstacles[i].hited == false) {
			int a1x, a1y, a2x, a2y;
			int off = 30; // ƫ����
			// �򵥵��þ���������������ң�
			if (!herodown) {		// ���¶�״̬�����ܺ���Ծ��
				a1x = HeroX + off;
				a1y = HeroY + off;
				// ����������λ�ڼ���ͼƬ
				a2x = HeroX + bgHeros[HeroIndex].getwidth() - off;
				a2y = HeroY + bgHeros[HeroIndex].getheight();
			}
			else
			{
				a1x = HeroX + off;
				a1y = 345 - imgHeroDown[HeroIndex].getheight();
				a2x = HeroX + imgHeroDown[HeroIndex].getwidth() - off;
				a2y = 345;
			}

			// �ϰ��������
			IMAGE img = obstacleImags[obstacles[i].type][obstacles[i].imaIndex];
			int b1x = obstacles[i].x + off;
			int b1y = obstacles[i].y + off;
			int b2x = obstacles[i].x + img.getwidth() - off;
			int b2y = obstacles[i].y + img.getheight() - off;

			// ���ýӿ� �ж��Ƿ����ཻ
			if (rectIntersect(a1x,a1y,a2x,a2y,b1x,b1y,b2x,b2y)) {
				heroBlood -= obstacles[i].power;
				printf("Ѫ��ʣ��:%d\n", heroBlood);
				playSound("res/hit.mp3");
				obstacles[i].hited = true;
			}
		}
	}
}


void function()
{
	for (int i = 0; i < 3; i++) {
		bgX[i] -= bgspeed[i];
		// ����������� ��ΪͼƬ�Ŀ�������޵� ������������˴��ڿ�� ������һ������
		if (bgX[i] < -WIN_WIDTH) {
			bgX[i] = 0;
		}
	}

	// ʵ����Ծ
	if (heroJump) {
		if (HeroY < jumpHeightMax) {
			jumpHeightOff = 5; // ���������ĸ߶�С���������ˣ��Ǿ��Ѿ�������ô���� ����ƫ���� ����ҽ�����Ծ�½�
		}
		HeroY += jumpHeightOff;  // �������λ�õ�ƫ�����ƶ�

		if (HeroY > 345 - bgHeros[0].getheight()) {
			heroJump = false;  // ����ط����������Ծ�½���ԭ���ĸ߶� ��ر���Ծ�Ŀ�����
			jumpHeightOff = -5; // ��Ծƫ�����ĳ�ʼ�� �����´μ���ʹ��
		}
	}

	// ʵ���¶�
	else if (herodown) {
		static int count = 0;
		count++;
		int delays[2] = { 8,30 };
		if (count >= delays[HeroIndex]) {
			count = 0;
			HeroIndex++;
			if (HeroIndex == 2) {
				HeroIndex = 0;
				herodown = false;
			}
		}
		
	}
	else {
		// ����Ծ ��ִ�б���
		HeroIndex = (HeroIndex + 1) % 12; // ��Ϊֻ��12��ͼƬ ����ȡֵ��12��ȡ����ʹ�ã�����ط�������������ŵ�
	}

	// ����С�ڹ�
	static int frameCount = 0; // ���ﾲ̬����Ϊ ����ÿ�ε�����ͻ����� �����ӾͲ�������
	static int enemyFre = 50;
	frameCount++;
	if (frameCount > enemyFre) {
		frameCount = 0; // ����������
		//if (!torToiseExist) {	// ���ȷ��ֻ��һ��С�ڹ�����
		//	torToiseExist = true;
		//	TortoiseX = WIN_WIDTH;
		enemyFre = 50 + rand() % 51; // 50-100 ֡�����
		creatObstacle();
	}
	/*torToiseIndex = (torToiseIndex + 1) % 7;*/ // ��Ϊ������ͼƬ

	// ����С�ڹ��λ��
	// TortoiseX -= bgspeed[2];
	// Ϊ����С�ڹ������뿪���ں����ʧ ��Ϊ��ʡ��Դ �ж�С�ڹ����ʱ���ִ��
		// if (torToiseExist) {
		// if (TortoiseX < -Tortoise[0].getwidth())
		// {
		//	torToiseExist = false;
		//	}
 //}

	// �����ϰ��������
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacles[i].exist) {
			obstacles[i].x -= obstacles[i].speed + bgspeed[2];
			if (obstacles[i].x < -obstacleImags[obstacles[i].type][0].getwidth() * 2) {
				obstacles[i].exist = false;
			}

			int len = obstacleImags[obstacles[i].type].size(); // �����size�÷����Լ�����ж��ٸ�Ԫ��
			obstacles[i].imaIndex = (obstacles[i].imaIndex + 1) % len;
		}
	}

	// ��Һ��ϰ����ײ��⡱����
	checkHit();
}
	

// ��Ⱦ����Ϸ������
void updateBg()
{
	// ����λ�ø���ʵ������Լ����� ΢��ʲô��
	putimagePNG2(bgX[0], 0, &imaBgs[0]);
	putimagePNG2(bgX[1], 119, &imaBgs[1]);
	putimagePNG2(bgX[2], 330, &imaBgs[2]);
}

void jump()
{
	heroJump = true;  // �����������������������Ծ�����ť��
	update = true; // ��������Ծ���� ������ˢ�� ��������
}

void down()
{
	herodown = true;
	update = true;
	HeroIndex = 0;
}

void keyEvent()
{
	char ch;
	if (_kbhit()) {  // ����а������� kbhit���� true
		ch = _getch(); //  getch() ����Ҫ���ո�Ϳ���ֱ�Ӷ�ȡ�û����������
		if (ch == ' ') {
			jump();  // ��Ϊ��Ծ��һ������ ������Զ������Ƿ�װ��һ������
		}
		else if (ch == 's' || ch == 'S') {
			down();
		}
	}
}

void updateEnemy()
{
	// ��ȾС�ڹ�
	/*if (torToiseExist) {
		putimagePNG2(TortoiseX, TortoiseY,WIN_WIDTH,&Tortoise[torToiseIndex]);
	}*/

	// ��Ⱦ�ϰ���
	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{
		if (obstacles[i].exist) {
			putimagePNG2(obstacles[i].x, obstacles[i].y,WIN_WIDTH, &obstacleImags[obstacles[i].type][obstacles[i].imaIndex]);
			// ����Ϳ�����Ⱦ��ֹ��С�ڹ� ��������Ǽ�������Ⱦ�� ��Ϊ����ǳ��ӣ�Ȼ����ž��Ƕ�Ӧ������ ����1����ʨ�������� Ȼ�������Ⱦ�ڼ��� �ڼ���ͼƬ������ ͼƬ��������һ����
		}
	}
}

void updateHero()
{
	if (!herodown) {
		putimagePNG2(HeroX, HeroY, &bgHeros[HeroIndex]);
	}
	else {
		int y = 345 - imgHeroDown[HeroIndex].getheight();
		putimagePNG2(HeroX,y,&imgHeroDown[HeroIndex]);
	}
}

void updateBloodBar()
{
	drawBloodBar(10,10,200,10,2,BLUE,DARKGRAY,RED,heroBlood/100.0);
}

void checkOver()
{
	if (heroBlood <= 0)
	{
		loadimage(0, "res/over.png");
		FlushBatchDraw(); // ˢ�»���
		mciSendString("stop res/bg.mp3", 0, 0, 0);
		system("pause");
			
		// ��֮ͣ�� ��ѡ��ֱ�ӿ�ʼ��һ��
		heroBlood = 100;
		score = 0;
		mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
	}
}

void gameBeginScreen()
{
	// ��ʼʱ����ʾ��Ϸ����
	loadimage(0, "res/over.png");
	system("pause");
}

void checkScore()
{
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		if (obstacles[i].exist &&
			obstacles[i].passed == false &&
			obstacles[i].hited == false &&
			obstacles[i].x + obstacleImags[obstacles[i].type][0].getwidth() < HeroX) {
			/*score++;
			obstacles[i].passed = true;
			printf("score:%d\n", score);*/
			if (obstacles[i].type == TORTOISE) {
				score++;
				obstacles[i].passed = true;
				printf("����:%d\n", score);
			}

			else if (obstacles[i].type == LION) {
				score += 4;
				obstacles[i].passed = true;
				printf("����:%d\n", score);
			}

			// ����else ����Ϊ���Ժ�������µ��ϰ������
			else if (obstacles[i].type >= HOOK1 && obstacles[i].type <= HOOK4) {
				score += 3;
				obstacles[i].passed = true;
				printf("����:%d\n", score);
			}
		}
	}
}

void updateScore()
{
	// 50 => "50"  '5'     '5' - '0' = 5;
	char str[8];
	sprintf(str, "%d", score);

	int x = 20;
	int y = 25;

	for (int i = 0; str[i]; i++) {
		int sz = str[i] - '0';
		putimagePNG(x, y, &imgSZ[sz]);
		x += imgSZ[sz].getwidth() + 5;
	}
}

void checkWin()
{
	if (score >= WIN_SCORE)
	{
		FlushBatchDraw();
		mciSendString("play res/win.mp3", 0, 0, 0);
		Sleep(2000);
		loadimage(0, "res/win.png");
		FlushBatchDraw(); // ˢ�»���
		mciSendString("stop res/bg.mp3", 0, 0, 0);
		system("pause");

		heroBlood = 100;
		score = 0;
		mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
	}
}

int main(void)
{
	init(); // �������һ����ʼ�� Ϊ���Ǹ�����ά��

	gameBeginScreen(); // ��������

	int timer = 0;

	while (1) {
		keyEvent();
		timer += getDelay();
		if (timer > 30) {
			timer = 0;
			update = true;	// 30��ˢ��һ��
		}

		if (update) {
			update = false; // ʹ���� Ȼ��رտ���
			BeginBatchDraw();
			updateBg(); // ͼƬ����
			// putimagePNG2(HeroX, HeroY, &bgHeros[HeroIndex]);
			updateHero();
			updateEnemy();
			updateBloodBar();
			updateScore();
			checkWin(); 
			EndBatchDraw();

			checkOver();
			checkScore();

			function();
		}
	}

	system("pause");

	return 0;
}