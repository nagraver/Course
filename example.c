#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
    char name[16];
  float cost;
  float rating;
} data;

typedef struct roster {
  data info;
  struct roster *next;
} roster;

data enter_container();

void addFirst(roster **begin, data content);

void addLast(roster **begin, data content);

void add_many(roster **begin);

void print_roster(roster **begin);

void clearFirst(roster **begin);

void save_roster(roster **begin);

void load_roster(roster **begin);

void same_roster(roster **begin);

int main() {
  char value;
  roster *begin = NULL;

  while (1) {
    puts("1) Занести в начало списка");
    puts("2) Занести в конец списка");
    puts("3) Организовать список");
    puts("4) Вывести данные");
    puts("5) Удалить первый элемент");
    puts("6) Сохранить данные");
    puts("7) Загрузить данные");
    puts("8) Поиск повторяющихся элементов");
    puts("0) Завершить работу");

    scanf(" %c", &value);

    switch (value) {
    case '1':
      addFirst(&begin, enter_container());
      puts("Элемент добавлен в начало");
      print_roster(&begin);
      break;
    case '2':
      addLast(&begin, enter_container());
      puts("Элемент добавлен в конец");
      print_roster(&begin);
      break;
    case '3':
      add_many(&begin);
      print_roster(&begin);
      break;
    case '4':
      print_roster(&begin);
      break;
    case '5':
      clearFirst(&begin);
      puts("Первый элемент удален");
      print_roster(&begin);
      break;
    case '6':
      save_roster(&begin);
      puts("Данные успешно сохранены");
      break;
    case '7':
      load_roster(&begin);
      puts("Данные успешно загружены");
      print_roster(&begin);
      break;
    case '8':
      same_roster(&begin);
      break;
    case '0':
      while (begin)
        clearFirst(&begin);
      puts("Список отчищен");
      return 0;
    default:
      puts("Жииизнь за Нерзула");
      break;
    }
  }
}

data enter_container() {
  data container;
  puts("Введите наименование (не более 16 символов): ");
  scanf("%s", container.name);
  puts("Введите цену: ");
  scanf("%f", &container.cost);
  puts("Введите рейтинг: ");
  scanf("%f", &container.rating);
  return container;
}

void addFirst(roster **begin, data content) {
  roster *temp = (roster *)malloc(sizeof(roster));
  if (!temp) {
    perror("Ошибка выделения памяти");
    return;
  }
  temp->info = content;
  temp->next = *begin;
  *begin = temp;
}

void addLast(roster **begin, data content) {
  roster *temp = (roster *)malloc(sizeof(roster));
  if (!temp) {
    perror("Ошибка выделения памяти");
    return;
  }

  temp->info = content;
  temp->next = NULL;

  if (!*begin) {
    *begin = temp;
  } else {
    roster *current = *begin;
    while (current->next)
      current = current->next;
    current->next = temp;
  }
}

void add_many(roster **begin) {
  char value;
  while (1) {
    addLast(begin, enter_container());
    puts("Продолжить организацию списка: 1");
    puts("Закончить организацию списка: Любая кнопка");
    scanf(" %c", &value);
    if (value != '1')
      return;
  }
}

void print_roster(roster **begin) {
  puts("|   Наименование   |       Цена       |      Рейтинг     |");
  for (roster *current = *begin; current; current = current->next) {
    printf("| %16s | %16.2f | %16.2f |\n", current->info.name,
           current->info.cost, current->info.rating);
  }
}

void clearFirst(roster **begin) {
  if (!*begin)
    return;
  roster *temp = *begin;
  *begin = (*begin)->next;
  free(temp);
}

void save_roster(roster **begin) {
  FILE *file = fopen("fourth.txt", "wb");
  if (file == NULL) {
    perror("Не удалось открыть файл");
    return;
  }
  fseek(file, 0, SEEK_SET);

  for (roster *current = *begin; current; current = current->next) {
    data content = current->info;
    fwrite(&content, sizeof(data), 1, file);
  }

  fclose(file);
}

void load_roster(roster **begin) {
  FILE *file = fopen("fourth.txt", "rb");
  if (file == NULL) {
    perror("Не удалось открыть файл");
    return;
  }
  fseek(file, 0, SEEK_SET);

  data content;
  while (*begin)
    clearFirst(begin);
  while (fread(&content, sizeof(data), 1, file))
    addLast(begin, content);

  fclose(file);
}

void same_roster(roster **begin) {
  if (!*begin) {
    puts("Список пуст");
    return;
  }

  int flag = 0;
  for (roster *current = *begin; current; current = current->next) {
    for (roster *buffer = current->next; buffer; buffer = buffer->next) {
      if (current->info.cost == buffer->info.cost) {
        puts("|  Наименование  |      Цена      |     Рейтинг    |");
        printf("| %14s | %14.2f | %14.2f |\n", current->info.name,
               current->info.cost, current->info.rating);
        printf("| %14s | %14.2f | %14.2f |\n", buffer->info.name,
               buffer->info.cost, buffer->info.rating);
        flag = 1;
      }
    }
  }

  if (flag == 0)
    puts("Повторяющихся элементов нет");
}
