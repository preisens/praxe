#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include <stdbool.h>




void Welcome();

void Menu();

char* getRandomMonster(const char* folderPath);

void StartPlayer();

void Combat();

int compare_scores(const void *a, const void *b);

void levelUp();

void CreateScore();

void End();

void Generate_map();

void Print_map();

void MoveControl();

void MoveUpdate();

void SetCursorPosition(int x, int y);

void PrintItems();

void UsePotion(int *invalid);

void ResetItems();

void UpdateItemNumber(const char* itemName);

void shop();

int DecreaseItemCount(char input, int *mpotion, int *hpotion);

void UpdateEquipment(int input);
void readSkills();

void printRandomSkills();

void ResetSkills();









