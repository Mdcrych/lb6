#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

template <class T> class Node {
public:
  T data;
  Node *next;
  Node *prev;

  Node(const T &data) : data(data), next(nullptr), prev(nullptr) {}
};

template <class T> class SinglyLinkedList {
private:
  Node<T> *head;
  Node<T> *tail;

public:
  SinglyLinkedList() : head(nullptr), tail(nullptr) {}

  void AppendTop(const T &data) {
    Node<T> *new_node = new Node<T>(data);
    if (head == nullptr) {
      head = new_node;
      tail = new_node;
      return;
    }

    new_node->next = head;
    head = new_node;
  }

  void AppendBack(const T &data) {
    Node<T> *new_node = new Node<T>(data);
    if (tail == nullptr) {
      head = new_node;
      tail = new_node;
      return;
    }
    tail->next = new_node;
    tail = new_node;
  }

  void AppendMiddle(const T &data, int index) {
    Node<T> *new_node = new Node<T>(data);
    Node<T> *temp = head;
    while (temp->next != nullptr && index > 0) {
      temp = temp->next;
      index--;
    }

    new_node->next = temp->next;
    temp->next = new_node;
  }

  T PopTop() {
    if (head == nullptr)
      return -1;
    Node<T> *temp = head;
    head = head->next;
    T temp_data = temp->data;
    delete temp;
    return temp_data;
  }

  T PopBack() {
    if (tail == nullptr)
      return nullptr;
    Node<T> *temp = head;
    while (temp->next != tail)
      temp = temp->next;
    temp->next = nullptr;
    T temp_data = tail->data;
    delete tail;
    tail = temp;
    return temp_data;
  }

  void inputAllList(T E) {
    Node<T> *temp = head;
    int count = 0;
    int ind = -1;
    bool flag = true;
    while (temp->next != nullptr){
      if (flag){
      if (temp->data == E)
        flag = false;
      ind ++;
      }
      count++;
      temp = temp->next;
    }
    
    if (!flag){
        
        T *arr = new T[++count];
        temp = head;
        count = 0; 
        while (temp->next != nullptr){
            arr[count] = temp->data;
            count++;
            temp = temp->next;
        }
        arr[count] = temp->data;
        for (int i = 0; i <= count; i++){
            AppendMiddle(arr[i], ind);
            ind++;
            }
        }
    
    
  }

  void PrintList() {
    Node<T> *temp = head;
    while (temp != nullptr) {
      std::cout << temp->data << " ";
      temp = temp->next;
    }
    std::cout << '\n';
  }
};

template <class T> class DoublyLinkedList {
private:
  Node<T> *head;
  Node<T> *tail;

public:
  DoublyLinkedList() : head(nullptr), tail(nullptr) {}

  void append(const T &data) {
    Node<T> *newNode = new Node<T>(data);
    if (tail == nullptr) {
      head = tail = newNode;
    } else {
      newNode->prev = tail;
      tail->next = newNode;
      tail = newNode;
    }
  }

  void prepend(const T &data) {
    Node<T> *newNode = new Node<T>(data);
    if (head == nullptr) {
      head = tail = newNode;
    } else {
      newNode->next = head;
      head->prev = newNode;
      head = newNode;
    }
  }

  bool remove(const T &deleteData) {
    Node<T> *current = head;
    while (current != nullptr) {
      if (current->data == deleteData) {
        if (current == head) {
          head = current->next;
          if (head != nullptr)
            head->prev = nullptr;
        } else if (current == tail) {
          tail = current->prev;
          tail->next = nullptr;
        } else {
          current->prev->next = current->next;
          current->next->prev = current->prev;
        }
        delete current;
        return true;
      }
      current = current->next;
    }
    return false;
  }

  Node<T> *findNode(const T &data) {
    Node<T> *current = head;
    while (current != nullptr) {
      if (current->data == data) {
        return current;
      }
      current = current->next;
    }
    return nullptr;
  }

  void swapNodes(const T &data1, const T &data2) {
    Node<T> *node1 = findNode(data1);
    Node<T> *node2 = findNode(data2);
    if (node1->next == node2 || node1->prev == node2) {
      Node<T> *next = node2->next;
      if (next != nullptr)
        next->prev = node1;
      node2->next = node1;
      node2->prev = node1->prev;
      if (node1->prev != nullptr)
        node1->prev->next = node2;
      node1->prev = node2;
      node1->next = next;
      if (node2->prev == nullptr)
        head = node2;
      if (node1->next == nullptr)
        tail = node1;
    }
  }
  void insert(const T &data) {
    prepend(data);
    append(data);
    }

  void printList() {
    Node<T> *current = head;
    while (current != nullptr) {
      std::cout << current->data << " ";
      current = current->next;
    }
    std::cout << std::endl;
  }
  
};

template <class T> class UniqueCollection {
private:
  T *elements;  // Массив для хранения элементов
  int size;     // Текущий размер коллекции
  int capacity; // Вместимость коллекции

  // Увеличивает размер массива, если он заполнен
  void resize() {
    capacity *= 2;
    T *newElements = new T[capacity];
    for (int i = 0; i < size; ++i) {
      newElements[i] = elements[i];
    }
    delete[] elements;
    elements = newElements;
  }

public:
  // Проверяет, существует ли элемент в коллекции
  bool exists(T element) const {
    for (int i = 0; i < size; ++i) {
      if (elements[i] == element) {
        return true;
      }
    }
    return false;
  }

  T GetElement(int index = 0) {
    if (index >= 0 && index <= size)
      return elements[index];
    return elements[0];
  }

  int GetSize() { return size; }

  UniqueCollection() {
    capacity = 10;
    elements = new T[capacity];
    size = 0;
  }

  ~UniqueCollection() { delete[] elements; }

  // Метод для добавления элемента
  void add(T element) {
    if (!exists(element)) {
      if (size == capacity) {
        resize();
      }
      elements[size++] = element; // Добавляем элемент
    }
  }

  // Метод для удаления элемента
  void remove(T element) {
    for (int i = 0; i < size; ++i) {
      if (elements[i] == element) {
        elements[i] =
            elements[size - 1]; // Заменяем удаляемый элемент последним
        --size; // Уменьшаем размер
        return;
      }
    }
  }

  // Метод для объединения двух коллекций
  UniqueCollection unionWith(const UniqueCollection &other) const {
    UniqueCollection newCollection;
    for (int i = 0; i < size; ++i) {
      newCollection.add(elements[i]);
    }
    for (int i = 0; i < other.size; ++i) {
      newCollection.add(other.elements[i]);
    }
    return newCollection;
  }

  // Метод для исключения элементов другой коллекции
  UniqueCollection except(const UniqueCollection &other) const {
    UniqueCollection newCollection;
    for (int i = 0; i < size; ++i) {
      if (!other.exists(elements[i])) {
        newCollection.add(elements[i]);
      }
    }
    return newCollection;
  }

  // Метод для пересечения двух коллекций
  UniqueCollection intersect(const UniqueCollection &other) const {
    UniqueCollection newCollection;
    for (int i = 0; i < size; ++i) {
      if (other.exists(elements[i])) {
        newCollection.add(elements[i]);
      }
    }
    return newCollection;
  }

  // Метод для вывода коллекции
  void print() const {
    std::cout << "UniqueCollection: { ";
    for (int i = 0; i < size; ++i) {
      std::cout << elements[i] << " ";
    }
    std::cout << "}" << std::endl;
  }
};
int main() {
  setlocale(LC_ALL, "Russian");

  SinglyLinkedList<int> intList;
  intList.AppendTop(1);
  intList.AppendTop(1);
  intList.AppendTop(2);
  intList.AppendTop(3);
  
  int E = 1; 
  std::cout << "Список целых чисел: ";
  intList.PrintList();
  intList.inputAllList(E);
  std::cout << "Список после вставки всего массива после первого вхождения элемента E: " << std::endl;
  intList.PrintList();
  
  
  std::string G = "написан";
  SinglyLinkedList<std::string> stringList;
  stringList.AppendTop("текст");
  stringList.AppendTop("осознанный");
  stringList.AppendTop("написан");
  stringList.AppendTop("написан");
  stringList.AppendTop("здесь");

  std::cout << "\nСписок строк: ";
  stringList.PrintList();
  stringList.inputAllList(G);
  std::cout << "Список после вставки всего массива после первого вхождения элемента E: " << std::endl;
  stringList.PrintList();


  // второе задание

  DoublyLinkedList<int> list;//  здесь создаем лист с циферками
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(2);
  list.append(4);

  std::cout << "Список: ";
  list.printList();

  list.insert(2); // вызов метода вставляющего(хз, я б конечно просто две комманды втемняшил, но мб так веселее) 2 вперед и назад листа

  std::cout << "Список после вставки значений E: ";
  list.printList();

  DoublyLinkedList<std::string> StringList;// а здесь с буковами
  StringList.append("шнип");
  StringList.append("шнап");
  StringList.append("шнапи");
  StringList.append("шнапи");
  StringList.append("шнапи");
  StringList.append("шнуп");
  std::cout << "Список: ";
  StringList.printList();
  StringList.insert("И еще раз)"); // а здесь опять вместо двух команд используем одну, зато какую)))
  std::cout << "Список после вставки значений E: ";
  StringList.printList();

  // третье задание

  UniqueCollection<std::string> books;// здесь даем названия книгам, создавая коллекцию
  books.add("Черный обелиск");
  books.add("Собачье сердце");
  books.add("Заводной апельсин");
  books.add("Декамерон");
  books.add("Ночь в Лиссабоне");// да, я человек тонкой душевной организации

  UniqueCollection<std::string> readers[3];// а здесь книгочеи получают книги, которые они читают
  readers[0].add("Черный обелиск");
  readers[0].add("Заводной апельсин");
  readers[0].add("Декамерон");
  readers[0].add("Ночь в Лиссабоне");

  readers[1].add("Черный обелиск");
  readers[1].add("Собачье сердце");
  readers[1].add("Заводной апельсин");

  readers[2].add("Черный обелиск");
  readers[2].add("Собачье сердце");
  readers[2].add("Заводной апельсин");

  std::cout << "Количество книг: " << books.GetSize() << '\n';
  int *count_books = new int[books.GetSize()];
  for (int i = 0; i < books.GetSize(); i++)
    count_books[i] = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < readers[i].GetSize(); j++) {
      for (int l = 0; l < books.GetSize(); l++) {
        if (books.GetElement(l) == readers[i].GetElement(j)) {
          count_books[l]++;//здеся подсчитываем количество книг
          break;
        }
      }
    }
  }

  for (int i = 0; i < books.GetSize(); i++) {
    std::cout << "Название книги и количество читателей: " << books.GetElement(i) << ": " << count_books[i]// а здеся выводим этих самых книгов по номерам и количеству их прочитавших 
              << '\n';
  }
  std::string rus = "абвгддеёжзийклмнопрстуфхцчшщъыьэюя";
  std::string big_rus = "АБВГДЕЁЖЗИЁКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

  UniqueCollection<std::string> letters[33];

  std::ifstream input("rus_text.txt");
  if (!input.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return 1;
  }
  std::string line;
  std::string first_word;
  if (std::getline(input, line)) {
    std::string first_word;
    std::stringstream first_word_stream(line);
    first_word_stream >> first_word;
    for (int i = 0; i < first_word.size(); i++) {
      for (int j = 0; j < 10; j++) {
        if (first_word[i] == rus[j] || first_word[i] == big_rus[j]) {
          letters[j].add(first_word);
        }
      }
    }
  }

  while (std::getline(input, line)) {
    std::string temp;
    std::stringstream str_stream(line);
    while (str_stream >> temp) {
      for (int i = 0; i < temp.size(); i++) {
        bool skip = false;
        for (int j = 0; j < first_word.size(); j++) {
          if (temp[i] == first_word[j]) {
            skip = true;
            break;
          }
        }
        if (!skip) {
          bool all_present = true;
          for (int j = 0; j < 10; j++) {
            if (temp.find(rus[j]) == std::string::npos && temp.find(big_rus[j]) == std::string::npos) {
              all_present = false;
              break;
            }
          }
          if (all_present) {
            for (int j = 0; j < 5; j++) {
              letters[j].add(temp);
            }
          }
        }
      }
    }
  }

  input.close();

  for (int i = 0; i < 5; i++) {
    letters[i].print();
  }
  return 0;
}
