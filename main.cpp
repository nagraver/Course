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
        string text = "1 - Add data\n2 - Print data\n3 - Edit data\n4 - Manage data\n";
        choice = getChoice("Main menu", text, "1234");
        switch (choice) {
            case '1':
                while (true) {
                    choice = getChoice("Add data", "1 - Add first\n2 - Add last\n3 - Organize\n", "123");
                    if (choice == ESC) break;
                    content = enterContainer();
                    printRosterHeader();
                    printRoster(content);
                    if (choice == '1') {
                        while (true) {
                            choice = getChoice("Add first confirm", "1 - Confirm\n", "1");
                            if (choice == ESC) cout << "Canceled\n";
                            else if (choice == '1') addFirst(&begin, content);
                            break;
                        }
                    } else if (choice == '2') {
                        while (true) {
                            choice = getChoice("Add last confirm", "1 - Confirm\n", "1");
                            if (choice == ESC) cout << "Canceled\n";
                            else if (choice == '1') addLast(&begin, content);
                            break;
                        }
                    } else if (choice == '3') addMany(&begin, content);
                }
                break;
            case '2':
                while (true) {
                    choice = getChoice("Print data", "1 - Srolling\n2 - Find\n3 - Analyze\n", "123");
                    if (choice == ESC) break;
                    else if (choice == '1') scrolling(&begin);
                    else if (choice == '2') findByField(&begin);
                    else if (choice == '3') analyzeThemes(&begin);
                }
                break;
            case '3':
                while (true) {
                    choice = getChoice("Edit data",
                                       "1 - Edit element\n2 - Sort\n3 - Delete selected\n4 - Delete list\n", "1234");
                    if (choice == ESC) break;
                    else if (choice == '1') edit(&begin);
                    else if (choice == '2') {
                        while (true) {
                            char choice = getChoice("Sort", "1 - Increasing sort\n2 - Decreasing sort\n", "12");
                            if (choice == ESC) break;
                            else if (choice == '1') insertionSortIncrease(&begin);
                            else if (choice == '2') insertionSortDecrease(&begin);
                        }
                    } else if (choice == '3') deleteSelected(&begin);
                    else if (choice == '4') {
                        while (true) {
                            choice = getChoice("Delete list", "1 - Delete without saving\n2 - Save and delete\n", "12");
                            if (choice == ESC) break;
                            else if (choice == '1') {
                                while (begin) deleteFirst(&begin);
                                break;
                            } else if (choice == '2') {
                                choice =
                                    getChoice("Save and delete", "1 - Save to bin file\n2 - Save to txt file\n", "12");
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
                    choice = getChoice("Manage data", "1 - Load\n2 - Save\n", "12");
                    if (choice == ESC) break;
                    else if (choice == '1') {
                        while (true) {
                            choice = getChoice("Load", "1 - Load from bin file\n2 - Load from txt file\n", "12");
                            if (choice == ESC) break;
                            else if (choice == '1') load_roster_bin(&begin);
                            else if (choice == '2') load_roster_txt(&begin);
                            break;
                        }
                    } else if (choice == '2') {
                        while (true) {
                            choice = getChoice("Save", "1 - Save to bin file\n2 - Save to txt file\n", "12");
                            if (choice == ESC) break;
                            else if (choice == '1') save_roster_bin(&begin);
                            else if (choice == '2') save_roster_txt(&begin);
                            break;
                        }
                    }
                }
                break;
            case ESC:
                while (true) {
                    choice = getChoice("Exit", "1 - Exit without saving\n2 - Exit and save\n", "12");
                    if (choice == ESC) break;
                    else if (choice == '1') {
                        while (begin) deleteFirst(&begin);
                        return 0;
                    } else if (choice == '2') {
                        while (true) {
                            choice = getChoice("Exit and save", "1 - Save to bin file\n2 - Save to txt file\n", "12");
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
