#pragma once
#include "esp_attr.h"

struct User {
  const char name[3];
  int meals;
};

extern RTC_DATA_ATTR User users[4];
extern RTC_DATA_ATTR int selectedUser;
extern RTC_DATA_ATTR int lastSelectedUser;



void incrementMeals(int userID);

void decrementMeals(int userID);

void drawMainMenu();

void drawEditUser();