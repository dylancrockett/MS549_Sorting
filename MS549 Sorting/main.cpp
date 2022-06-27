#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "sorting_test.hpp"

using namespace std;
using namespace sorting_testing;

void main_menu();
void sorting_playground();
void testing_menu();

int main() {
	//enable unicode in wcout
	_setmode(_fileno(stdout), _O_U16TEXT);

	//run main menu
	main_menu();

    return 0;
}

//main menu
void main_menu() {
main_menu:

	wcout << "<> Main Menu <>\n\n";
	wcout << "[1] Sorting Playground\n";
	wcout << "[2] Testing Menu\n";
	wcout << "[3] Exit\n\n";
	wcout << "Please enter your selection: ";

	int choice;
	cin >> choice;

	switch (choice) {
	case 1:
		system("cls");
		sorting_playground();
		goto main_menu;
	case 2:
		system("cls");
		testing_menu();
		goto main_menu;
	case 3:
		return;
	default:
		system("cls");
		wcout << "INVALID OPTION: Please select one of the valid options below (1-3).\n\n";
		goto main_menu;
	}
}

void sorting_playground() {
	int* items = new int[100000000] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int itemCount = 10;
	int value;
	int index = -1;

sorting_menu:
	wcout << "List: [";
	for (int i = 0; i < itemCount; i++) {
		wcout << items[i] << ", ";
	}
	wcout << "\b\b]\n\n";

	wcout << "<> Sorting Playground Menu <>\n\n";
	wcout << "[1] Add item\n";
	wcout << "[2] Remove Item\n";
	wcout << "[3] Randomize List\n";
	wcout << "[4] Sort using Selection Sort\n";
	wcout << "[5] Sort using Quick Sort\n";
	wcout << "[6] Exit\n\n";
	wcout << "Please enter your choice: ";

	int choice;
	cin >> choice;

	system("cls");

	switch (choice) {
	case 1:
		wcout << "\n\nPlease enter the new value: ";
		wcin >> value;

		items[itemCount] = value;
		itemCount++;
		system("cls");
		goto sorting_menu;
	case 2:
		wcout << "\n\nPlease enter the value to remove: ";
		wcin >> value;
		index = -1;

		for (int i = 0; i < itemCount; i++) {
			if (items[i] == value) {
				index = i;
				break;
			}
		}

		if (index == -1) {
			wcout << "\n\nValue could not be found.";
			system("pause");
		}
		else {
			if (index + 1 != itemCount) copy(items + index + 1, items + itemCount, items + index);
			itemCount -= 1;
		}

		system("cls");
		goto sorting_menu;
	case 3:
		random_shuffle(&items[0], &items[itemCount]);
		system("cls");
		goto sorting_menu;
	case 4:
		selection_sort(items, itemCount);
		system("cls");
		goto sorting_menu;
	case 5:
		quick_sort(items, itemCount);
		system("cls");
		goto sorting_menu;
	case 6:
		system("cls");
		return;
	default:
		system("cls");
		wcout << "INVALID OPTION: Please select one of the valid options below.\n\n";
		goto sorting_menu;
	}
}

void testing_menu() {
testing_menu:
	wcout << "<> Testing Menu <>\n\n";
	wcout << "[1] Sort Algorithm Functionality Test\n";
	wcout << "[2] Sort Algorithm Performance Test\n";
	wcout << "[3] Exit\n\n";
	wcout << "Please enter which test you would like to run: ";

	int choice;
	cin >> choice;

	system("cls");

	switch (choice) {
	case 1:
		sorting_testing::test_functionality();
		system("pause");
		system("cls");
		goto testing_menu;
	case 2:
		sorting_testing::test_performance();
		system("pause");
		system("cls");
		goto testing_menu;
	case 3:
		return;
	default:
		wcout << "INVALID OPTION: Please select one of the valid options below (1-3).\n\n";
		goto testing_menu;
	}
}