#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include "GAMECONSTANT.h"

typedef struct Character {
	int type;
	bool alive;
	int position_height;
	int position_width;
};

bool isFeasible(int* level, struct Character* character, int* act, int stage, int* key) {
	int tar_height;
	int tar_width;
	if (*act != 2 && *act != 4 && *act != 6 && *act != 8)
	{
		printf("�޷���ô��\n");
		system("pause");
		return false;
	}
	if (*act == 2 && (*character).position_height != STAGE_HEIGHT[stage - 1] - 1)
	{
		tar_height = (*character).position_height + 1;
		tar_width = (*character).position_width;
	}
	else if (*act == 8 && (*character).position_height != 0)
	{
		tar_height = (*character).position_height - 1;
		tar_width = (*character).position_width;
	}
	else if (*act == 4 && (*character).position_width != 0)
	{
		tar_height = (*character).position_height;
		tar_width = (*character).position_width - 1;
	}
	else if (*act == 6 && (*character).position_width != STAGE_WIDTH[stage - 1] - 1)
	{
		tar_height = (*character).position_height;
		tar_width = (*character).position_width + 1;
	}
	else {
		if((*character).type == 0)
			printf("������\n");
		return false;
	}
	if ((*character).type == 0) {
		if (*(level + tar_height * STAGE_WIDTH[stage - 1] + tar_width) == 1 || *(level + tar_height * STAGE_WIDTH[stage - 1] + tar_width) == 4)
		{
			printf("�޷���ô��\n");
			system("pause");
			return false;
		}
		else if (*(level + tar_height * STAGE_WIDTH[stage - 1] + tar_width) == 6 && *key != KEY_COUNT[stage - 1])
		{
			printf("Կ�ײ��㣬�޷�����\n");
			system("pause");
			return false;
		}
	}
	else if ((*character).type == 7) {
		if (*(level + tar_height * STAGE_WIDTH[stage - 1] + tar_width) > 4)
			return false;
	}
	else if ((*character).type == 8) {
		if (*(level + tar_height * STAGE_WIDTH[stage - 1] + tar_width) > 4 || *(level + tar_height * STAGE_WIDTH[stage - 1] + tar_width) == 1)
			return false;
	}
	return true;
}

void player_move(int* level, int* originLevel, struct Character* player, int* act, int stage, int* key, bool* stage_pass) {
	int tar_height = (*player).position_height;
	int tar_width = (*player).position_width;
	int tar_num;
	if (*(originLevel + tar_height * STAGE_WIDTH[stage - 1] + tar_width) == 2 || *(originLevel + tar_height * STAGE_WIDTH[stage - 1] + tar_width) > 4 || *(originLevel + tar_height * STAGE_WIDTH[stage - 1] + tar_width) == 0)
		*(level + tar_height * STAGE_WIDTH[stage - 1] + tar_width) = 2;
	if (*(originLevel + tar_height * STAGE_WIDTH[stage - 1] + tar_width) == 3 || *(originLevel + tar_height * STAGE_WIDTH[stage - 1] + tar_width) == 4)
		*(level + tar_height * STAGE_WIDTH[stage - 1] + tar_width) = 3;
	if (*act == 2) {
		tar_height++;
		(*player).position_height++;
	}
	else if (*act == 8)
	{
		tar_height--;
		(*player).position_height--;
	}
	else if (*act == 4)
	{
		tar_width--;
		(*player).position_width--;
	}
	else
	{
		tar_width++;
		(*player).position_width++;
	}
	tar_num = *(level + tar_height * STAGE_WIDTH[stage - 1] + tar_width);
	*(level + tar_height * STAGE_WIDTH[stage - 1] + tar_width) = 0;

	if (tar_num > 6)
	{
		printf("�������Ӵ��˹���\n");
		(*player).alive = false;
	}
	else if (tar_num == 5)
	{
		printf("���ռ���һ��Կ��\n");
		(*key)++;
		if (KEY_COUNT[stage - 1] != *key)
			printf("����Ҫ�ռ� %d ��Կ��\n", KEY_COUNT[stage - 1] - *key);
		else
			printf("Կ���ռ���ϣ�����ǰ����������\n");
		system("pause");
	}
	else if (tar_num == 6)
	{
		printf("���ѳɹ�\n");
		*stage_pass = true;
	}

}

void enemy_move(int* level, int* originLevel, struct Character* enemy, struct Character* player, int* act, int stage, bool cannot_move)
{
	int tar_height = (*enemy).position_height;
	int tar_width = (*enemy).position_width;
	int tar_num;
	if (!cannot_move)
	{
		if (*(originLevel + tar_height * STAGE_WIDTH[stage - 1] + tar_width) == 2 || *(originLevel + tar_height * STAGE_WIDTH[stage - 1] + tar_width) == 1)
			*(level + tar_height * STAGE_WIDTH[stage - 1] + tar_width) = *(originLevel + tar_height * STAGE_WIDTH[stage - 1] + tar_width);
		if (*(originLevel + tar_height * STAGE_WIDTH[stage - 1] + tar_width) == 3 || *(originLevel + tar_height * STAGE_WIDTH[stage - 1] + tar_width) == 4)
			*(level + tar_height * STAGE_WIDTH[stage - 1] + tar_width) = 3;
		if (*(originLevel + tar_height * STAGE_WIDTH[stage - 1] + tar_width) > 4 || *(originLevel + tar_height * STAGE_WIDTH[stage - 1] + tar_width) == 0)
			*(level + tar_height * STAGE_WIDTH[stage - 1] + tar_width) = 2;
		if (*act == 2) {
			tar_height++;
			(*enemy).position_height++;
		}
		else if (*act == 8)
		{
			tar_height--;
			(*enemy).position_height--;
		}
		else if (*act == 4)
		{
			tar_width--;
			(*enemy).position_width--;
		}
		else
		{
			tar_width++;
			(*enemy).position_width++;
		}
		tar_num = *(level + tar_height * STAGE_WIDTH[stage - 1] + tar_width);
		*(level + tar_height * STAGE_WIDTH[stage - 1] + tar_width) = (*enemy).type;

		if (tar_num == 3)
		{
			printf("�й���ȵ��˻���...\n");
			system("pause");
			(*enemy).alive = false;
			*(level + tar_height * STAGE_WIDTH[stage - 1] + tar_width) = 3;
		}
		else if (tar_num == 0)
		{
			printf("�㱻����׽ס��\n");
			(*player).alive = false;
		}
	}
	else if (*(originLevel + tar_height * STAGE_WIDTH[stage - 1] + tar_width) == 3)
	{
		{
			printf("�й����޷��ƶ����ȵ��˻���...\n");
			system("pause");
			(*enemy).alive = false;
			*(level + tar_height * STAGE_WIDTH[stage - 1] + tar_width) = 3;
		}
	}

}

bool isPossible(int* level, struct Character* enemy, int stage) {
	int height = (*enemy).position_height;
	int width = (*enemy).position_width;
	if (height != 0)
	{
		if (*(level + (height - 1) * STAGE_WIDTH[stage - 1] + width) < 5)
		{
			if (*(level + (height - 1) * STAGE_WIDTH[stage - 1] + width) != 1 || (*enemy).type == 7)
				return true;
		}
	}
	if (height != STAGE_HEIGHT[stage - 1])
	{
		if (*(level + (height + 1) * STAGE_WIDTH[stage - 1] + width) < 5)
		{
			if (*(level + (height + 1) * STAGE_WIDTH[stage - 1] + width) != 1 || (*enemy).type == 7)
				return true;
		}
	}
	if (width != 0)
	{
		if (*(level + height * STAGE_WIDTH[stage - 1] + width - 1) < 5)
		{
			if (*(level + height * STAGE_WIDTH[stage - 1] + width - 1) != 1 || (*enemy).type == 7)
				return true;
		}
	}
	if (height != STAGE_WIDTH[stage - 1])
	{
		if (*(level + height * STAGE_WIDTH[stage - 1] + width + 1) < 5)
		{
			if (*(level + height * STAGE_WIDTH[stage - 1] + width + 1) != 1 || (*enemy).type == 7)
				return true;
		}
	}
	return false;
}

void playerAct(int* level, int* originLevel, struct Character* player, bool* stage_pass, int stage, int* key) {
	int act;
	int feasible = false;
	printf("�����ֵ����ж�\n");
	while (!feasible)
	{
		printf("���������2��4��6��8�����»س��������ƶ�����\n");
		scanf_s("%d", &act);
		feasible = isFeasible(level, player, &act, stage, key);
		if (feasible)
			player_move(level, originLevel, player, &act, stage, key, stage_pass);
	}
}

void AAct(int* level, int* originLevel, struct Character* A, struct Character* player, int stage, int key) {
	int act;
	bool feasible = false;
	bool cannot_move = !isPossible(level, A, stage);
	if (!cannot_move) {
		while (!feasible)
		{
			act = ((rand() % 4) + 1) * 2;
			feasible = isFeasible(level, A, &act, stage, key);
			if (feasible || cannot_move)
				enemy_move(level, originLevel, A, player, &act, stage, cannot_move);
		}
	}
	
}

void BAct(int* level, int* originLevel, struct Character* B, struct Character* player, int stage, int key) {
	int act;
	int times = 0;
	bool feasible = false;
	int ver_first = 0;
	bool go_left = false;
	bool go_right = false;
	bool go_down = false;
	bool go_up = false;
	bool cannot_move = !isPossible(level, B, stage);
	if ((*B).position_width > (*player).position_width)
		go_left = true;
	if ((*B).position_width < (*player).position_width)
		go_right = true;
	if ((*B).position_height > (*player).position_height)
		go_up = true;
	if ((*B).position_height < (*player).position_height)
		go_down = true;
	if (!cannot_move) {
		while (!feasible && times < 2)
		{
			ver_first = rand() % 2;
			if (ver_first == 1)
			{
				if (go_up)
					act = 8;
				else if (go_down)
					act = 2;
				else if (go_left)
					act = 4;
				else
					act = 6;
			}
			else
			{
				if (go_left)
					act = 4;
				else if (go_right)
					act = 6;
				else if (go_up)
					act = 8;
				else
					act = 2;
			}
			feasible = isFeasible(level, B, &act, stage, key);
			times += 1;
			if (feasible || cannot_move)
				enemy_move(level, originLevel, B, player, &act, stage, cannot_move);
		}
	}
}

void Swi_print(int* level, int stage, bool swi)
{
	system("cls");
	printf("��ǰΪ�� %d ��\n\n", stage);
	printf("��ǰ���̴�С %d x %d\n\n", STAGE_HEIGHT[stage - 1], STAGE_WIDTH[stage - 1]);
	for (int a = 0; a < STAGE_HEIGHT[stage - 1]; a++)
	{
		for (int b = 0; b < STAGE_WIDTH[stage - 1]; b++) {
			if (swi) {
				if (*(level + a * STAGE_WIDTH[stage - 1] + b) == 3)
					*(level + a * STAGE_WIDTH[stage - 1] + b) = 4;
				else if (*(level + a * STAGE_WIDTH[stage - 1] + b) == 4)
					*(level + a * STAGE_WIDTH[stage - 1] + b) = 3;
			}
			switch (*(level + a * STAGE_WIDTH[stage - 1] + b))
			{
			case 0:
				printf("x ");
				break;
			case 1:
				printf("# ");
				break;
			case 2:
				printf("  ");
				break;
			case 3:
				printf("0 ");
				break;
			case 4:
				printf("1 ");
				break;
			case 5:
				printf("K ");
				break;
			case 6:
				printf("D ");
				break;
			case 7:
				printf("A ");
				break;
			case 8:
				printf("B ");
				break;
			case 9:
				printf("C ");
				break;
			default:
				break;
			}
		}
		printf("\n");
	}
	printf("\n");
}

bool stage1() {
	struct Character player = { 0, true, 9, 4 };
	struct Character A1 = { 7, true, 4, 0 };
	struct Character A2 = { 7, true, 4, 9 };
	struct Character A3 = { 7, true, 3, 1 };
	struct Character A4 = { 7, true, 5, 1 };
	struct Character A5 = { 7, true, 2, 2 };
	struct Character A6 = { 7, true, 4, 2 };
	struct Character A7 = { 7, true, 6, 2 };
	struct Character A8 = { 7, true, 3, 8 };
	struct Character A9 = { 7, true, 5, 8 };
	struct Character A10 = { 7, true, 2, 7 };
	struct Character A11 = { 7, true, 4, 7 };
	struct Character A12 = { 7, true, 6, 7 };
	bool stage_pass = false;
	int stage = 1;
	int key = 0;
	bool round = true;
	srand((unsigned)time(NULL));
	int level[10][10] = {
	{1,1,1,1,2,6,1,1,1,1},
	{1,1,1,1,2,2,1,1,1,1},
	{1,1,7,1,2,2,1,7,1,1},
	{1,7,1,1,2,2,1,1,7,1},
	{7,1,7,1,5,2,1,7,1,7},
	{1,7,1,1,2,2,1,1,7,1},
	{1,1,7,1,2,2,1,7,1,1},
	{1,1,1,1,2,2,1,1,1,1},
	{1,1,1,1,2,2,1,1,1,1},
	{1,1,1,1,0,2,1,1,1,1}
	};
	int originLevel[10][10];
	for (int a = 0; a < 10; a++)
	{
		for (int b = 0; b < 10; b++)
			originLevel[a][b] = level[a][b];
	}

	Swi_print(&level, stage, false);
	while (player.alive && !stage_pass)
	{
		if (round)
			playerAct(&level, &originLevel, &player, &stage_pass, stage, &key);
		else {
			if (A1.alive)
				AAct(&level, &originLevel, &A1, &player, stage, &key);
			if (A2.alive)
				AAct(&level, &originLevel, &A2, &player, stage, &key);
			if (A3.alive)
				AAct(&level, &originLevel, &A3, &player, stage, &key);
			if (A4.alive)
				AAct(&level, &originLevel, &A4, &player, stage, &key);
			if (A5.alive)
				AAct(&level, &originLevel, &A5, &player, stage, &key);
			if (A6.alive)
				AAct(&level, &originLevel, &A6, &player, stage, &key);
			if (A7.alive)
				AAct(&level, &originLevel, &A7, &player, stage, &key);
			if (A8.alive)
				AAct(&level, &originLevel, &A8, &player, stage, &key);
			if (A9.alive)
				AAct(&level, &originLevel, &A9, &player, stage, &key);
			if (A10.alive)
				AAct(&level, &originLevel, &A10, &player, stage, &key);
			if (A11.alive)
				AAct(&level, &originLevel, &A11, &player, stage, &key);
			if (A12.alive)
				AAct(&level, &originLevel, &A12, &player, stage, &key);
			printf("\n");
			Swi_print(&level, stage, true);
			printf("\n");
		}
		round = !round;
	}
	if (stage_pass) {
		printf("��һ��ͨ��\n");
		printf("�Ժ���Ϸ��ʼʱ��������Ϊ167942258��ֱ�ӽ���ڶ���\n");
		system("pause");
		return true;
	}
	printf("����ʧ�ܣ�����������\n");
	system("pause");
	return false;
}

bool stage2() {
	struct Character player = { 0, true, 10, 1 };
	struct Character A1 = { 7, true, 0, 0 };
	struct Character A2 = { 7, true, 0, 11 };
	struct Character A3 = { 7, true, 11, 0 };
	struct Character A4 = { 7, true, 11, 11 };
	struct Character B1 = { 8, true, 4, 4 };
	struct Character B2 = { 8, true, 6, 6 };

	bool stage_pass = false;
	int stage = 2;
	int key = 0;
	bool round = true;
	srand((unsigned)time(NULL));
	int level[12][12] = {
	{7,1,1,1,1,1,1,1,1,1,1,7},
	{1,5,2,2,2,2,2,2,2,2,6,1},
	{1,2,1,1,2,1,2,1,1,1,2,1},
	{1,2,1,1,2,2,2,1,1,1,2,1},	
	{1,2,2,2,8,2,2,2,2,2,2,1},
	{1,2,1,1,2,5,2,1,1,1,2,1},
	{1,2,1,1,2,2,8,1,1,1,2,1},
	{1,2,2,2,2,2,2,2,2,2,2,1},
	{1,2,1,1,2,1,2,1,1,1,2,1},
	{1,2,1,1,2,1,2,1,1,1,2,1},
	{1,0,2,2,2,2,2,2,2,2,5,1},
	{7,1,1,1,1,1,1,1,1,1,1,7}
	};
	int originLevel[12][12];
	for (int a = 0; a < 12; a++)
	{
		for (int b = 0; b < 12; b++)
			originLevel[a][b] = level[a][b];
	}

	Swi_print(level, stage, false);
	while (player.alive && !stage_pass)
	{
		if (round)
			playerAct(&level, &originLevel, &player, &stage_pass, stage, &key);
		else {
			if (A1.alive)
				AAct(&level, &originLevel, &A1, &player, stage, &key);
			if (A2.alive)
				AAct(&level, &originLevel, &A2, &player, stage, &key);
			if (A3.alive)
				AAct(&level, &originLevel, &A3, &player, stage, &key);
			if (A4.alive)
				AAct(&level, &originLevel, &A4, &player, stage, &key);
			if (B1.alive)
				BAct(&level, &originLevel, &B1, &player, stage, &key);
			if (B2.alive)
				BAct(&level, &originLevel, &B2, &player, stage, &key);
			printf("\n");
			Swi_print(&level, stage, true);
			printf("\n");
		}
		round = !round;
	}
	if (stage_pass) {
		printf("�ڶ���ͨ��\n");
		printf("�Ժ���Ϸ��ʼʱ��������Ϊ732184005��ֱ�ӽ��������\n");
		system("pause");
		return true;
	}
	printf("����ʧ�ܣ�����������\n");
	system("pause");
	return false;
}

int main() {
	int pwd;
	bool pass = false;
	int stage = 1;
	printf("������Ϸ����");
	printf("x������ҵ�ǰλ�ã�����ͨ������2��4��6��8����������ƶ������ڵ�ͨ·\n");
	printf("#����ǽ�ڣ�ÿ��ǽ�ڵ�λ��Ϊ�̶�������޷�ͨ��\n");
	printf("�ո����ͨ·����ҿ����ƶ�����,Կ�׺͹������ɵĵط�֮�����ͨ·\n");
	printf("0����ر�״̬�µĻ��أ�1������״̬�µģ�����ÿ�غϻ���0��1֮���л�\n");
	printf("��˵������1���ڵ�ʱ���������ȥ������0����\n");
	printf("K����Կ�ף�����Կ�׵Ĺؿ���Ҫ���ռ�������Կ�ײſ���ͨ������\n");
	printf("D������ţ�ͨ�����ż���ͨ���ùؿ�\n");
	printf("A�������A���˹����˶��������������һ��һ�񣬿ɴ�ǽ\n");
	printf("B�������B���˹����˶���������ң��������ң���һ��һ�񣬲��ɴ�ǽ\n");
	printf("C�������C����ʼΪ��ֹ������ռ���Կ�׺�ʼ������ƶ�������б���ƶ�����һ��һ�񣬲��ɴ�ǽ\n");
	printf("��Һ͸��ֽ����ж�����������Ӵ������������ͱ�������Ϊʧ�ܣ����ﲻ���ص�\n");
	printf("������Ա�����Ļ���ɱ����Կ�׺ʹ��ű�������Ϊǽ��\n\n");
	printf("��Ϸ��ʼ\n");
	printf("����һ�������Կ�ʼ��Ϸ\n");
	scanf_s("%d", &pwd);
	switch (pwd) {
	case 167942258:
		stage = 2;
		break;
	case 732184005:
		stage = 3;
		break;
	case 686229654:
		stage = 4;
		break;
	case 404756992:
		stage = 5;
		break;
	case 480705311:
		stage = 6;
		break;
	case 119106563:
		stage = 7;
		break;
	case 521621872:
		stage = 8;
		break;
	case 315152842:
		stage = 9;
		break;
	default:
		break;
	}
	if (stage < 2) {
		while (!pass) {
			pass = stage1();
		}
		stage++;
		pass = !pass;
	}
	if (stage < 3) {
		while (!pass) {
			pass = stage2();
		}
		stage++;
		pass = !pass;
	}
	/*
	if (stage < 4) {
		while (!pass) {
			pass = stage3();
		}
		stage++;
		pass = !pass;
	}
	if (stage < 5) {
		while (!pass) {
			pass = stage4();
		}
		stage++;
		pass = !pass;
	}
	if (stage < 6) {
		while (!pass) {
			pass = stage5();
		}
		stage++;
		pass = !pass;
	}
	if (stage < 7) {
		while (!pass) {
			pass = stage6();
		}
		stage++;
		pass = !pass;
	}
	if (stage < 8) {
		while (!pass) {
			pass = stage7();
		}
		stage++;
		pass = !pass;
	}
	if (stage < 9) {
		while (!pass) {
			pass = stage8();
		}
		stage++;
		pass = !pass;
	}
	if (stage < 10) {
		while (!pass)
			pass = stage9();
	}*/
	printf("\n��ϲͨ�أ�\n");
	system("pause");
	return 0;
}