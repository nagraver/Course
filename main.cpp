#include <iostream>
#include <string>

#include "./headers/files.h"
#include "./headers/refactoring.h"
#include "./headers/scrolling.h"
#include "./headers/service.h"
#include "./headers/structures.h"

using namespace std;

int main() {
    char choice;
    roster *begin = nullptr;
    NII content;

    while (true) {
        string text = "1 - Adding\n2 - Print data\n3 - Edit data\n4 - Save data\n5 - Load data\n";
        choice = getChoice(text, "12345");
        switch (choice) {
            case '1':
                while (true) {
                    choice = getChoice("1 - Add first\n2 - Add last\n3 - Organize\n", "123");
                    if (choice == '1') addFirst(&begin, enterContainer());
                    else if (choice == '2') addLast(&begin, enterContainer());
                    else if (choice == '3') addMany(&begin);
                    else if (choice == ESC) break;
                }
                break;
            case '2':
                while (true) {
                    choice = getChoice("1 - Srolling\n2 - Find\n3 - Analyze\n", "123");
                    if (choice == '1') scrolling(&begin);
                    else if (choice == '2') findByField(&begin);
                    else if (choice == '3') analyzeThemes(&begin);
                    else if (choice == ESC) break;
                }
                break;
            case '3':
                while (true) {
                    choice = getChoice("1 - Edit element\n2 - Sort\n3 - Delete selected\n4 - Delete list\n", "1234");
                    if (choice == ESC) break;
                    if (choice == '1') edit(&begin);
                    else if (choice == '2') {
                        while (true) {
                            char choice = getChoice("1 - Increasing sord\n2 - Decreasing sort\n", "12");
                            if (choice == '1') insertionSortIncrease(&begin);
                            else if (choice == '2') insertionSortDecrease(&begin);
                            else if (choice == ESC) break;
                        }
                    } else if (choice == '3') deleteSelected(&begin);
                    else if (choice == '4') {
                        while (true) {
                            choice = getChoice("1 - Delete without saving\n2 - Save and delete\n", "12");
                            if (choice == ESC) break;
                            else if (choice == '1') {
                                while (begin) deleteFirst(&begin);
                                break;
                            } else if (choice == '2') {
                                choice = getChoice("1 - Save to bin file\n2 - Save to txt file\n", "12");
                                if (choice == ESC) break;
                                else if (choice == '1') save_roster_bin(&begin);
                                else if (choice == '2') save_roster_txt(&begin);
                                while (begin) deleteFirst(&begin);
                                break;
                            }
                        }
                    }
                }
                break;
            case '4':
                while (true) {
                    choice = getChoice("1 - Save to bin file\n2 - Save to txt file\n", "12");
                    if (choice == '1') save_roster_bin(&begin);
                    else if (choice == '2') save_roster_txt(&begin);
                    else if (choice == ESC) break;
                }
                break;
            case '5':
                while (true) {
                    choice = getChoice("1 - Load from bin file\n2 - Load from txt file\n", "12");
                    if (choice == '1') load_roster_bin(&begin);
                    else if (choice == '2') load_roster_txt(&begin);
                    else if (choice == ESC) break;
                }
                break;
            case ESC:
                while (true) {
                    choice = getChoice("1 - Exit without saving\n2 - Exit and save\n", "12");
                    if (choice == ESC) break;
                    else if (choice == '1') {
                        while (begin) deleteFirst(&begin);
                        return 0;
                    } else if (choice == '2') {
                        while (true) {
                            choice = getChoice("1 - Save to bin file\n2 - Save to txt file\n", "12");
                            if (choice == ESC) break;
                            else if (choice == '1') save_roster_bin(&begin);
                            else if (choice == '2') save_roster_txt(&begin);
                            return 0;
                        }
                    }
                }
                break;
            default:
                cout << "Unknown command\n";
                break;
        }
    }
}
