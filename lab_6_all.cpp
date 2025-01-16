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

  void HasDuplicates(T E) {
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
      std::cout<<"ABOBA"<<ind<<'\n';
    }
    
    if (!flag){
        
        T *arr = new T[++count];
        //std::cout<<"COUNT  "<<count<<"\n";
        temp = head;
        count = 0; 
        while (temp->next != nullptr){
            arr[count] = temp->data;
            std::cout<<"TEMP PLAYER   "<<temp->data<<"\n";
            count++;
            temp = temp->next;
        }
        arr[count] = temp->data;
        std::cout<<"TEMP PLAYER   "<<temp->data<<"\n";
        //std::cout<<"COUNTT   "<<count<<"\n";
        for (int i = 0; i <= count; i++){
            //std::cout<<"BEBEBE\n";
            AppendMiddle(arr[i], ind);
            std::cout<<"PIZDEZ  "<<arr[i]<<"   "<< i <<"\n";
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

/*
template <class T>
class Node {
public:
    T data;
    Node* prev;
    Node* next;
    Node(const T& data) : data(data), prev(nullptr), next(nullptr) {}
};
*/
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

#include <iostream>

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
  
  /*int E = 761; 
  std::cout << "Список целых чисел: ";
  intList.PrintList();
  intList.HasDuplicates(E);
  intList.PrintList();
  std::cout << "Есть ли дубликаты? " << std::endl;*/
  
  std::string E = "world";
  SinglyLinkedList<std::string> stringList;
  stringList.AppendTop("hello");
  stringList.AppendTop("world");
  stringList.AppendTop("hello");

  std::cout << "\nСписок строк: ";
  stringList.PrintList();
  stringList.HasDuplicates(E);
  stringList.PrintList();


  // второе задание

  DoublyLinkedList<int> list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(2);
  list.append(4);

  std::cout << "Список: ";
  list.printList();

  list.insert(2); // Удаляет первое вхождение 2

  std::cout << "Список после удаления первого 2: ";
  list.printList();

  DoublyLinkedList<std::string> StringList;
  StringList.append("hello");
  StringList.append("hello");
  StringList.append("chipi");
  StringList.append("chipi");
  StringList.append("chapa");
  StringList.append("chapa");
  std::cout << "Список: ";
  StringList.printList();
  StringList.insert("why are you gay? ");
  std::cout << "Список после удаления первого hello: ";
  StringList.printList();
  StringList.swapNodes("hello", "chipi");
  std::cout << "Список после перестановки hello and chipi: ";
  StringList.printList();

  //
  // третье задание

  UniqueCollection<std::string> compositions;
  compositions.add("Voina i pizdilka");
  compositions.add("Ya eby sobak");
  compositions.add("Vyzhivanie na sotky");
  compositions.add("Dozhyt do stypuhi");
  compositions.add("Na sotky menshe chem vchera");

  UniqueCollection<std::string> melomans[3];
  melomans[0].add("Voina i pizdilka");
  melomans[0].add("Vyzhivanie na sotky");
  melomans[0].add("Na sotky menshe chem vchera");
  melomans[0].add("Dozhyt do stypuhi");

  melomans[1].add("Voina i pizdilka");
  melomans[1].add("Ya eby sobak");
  melomans[1].add("Na sotky menshe chem vchera");

  melomans[2].add("Classica");
  melomans[2].add("Ya eby sobak");
  melomans[2].add("Vyzhivanie na sotkya");

  std::cout << "COLICHESTVO KNIGGEROV: " << compositions.GetSize() << '\n';
  int *count_compositions = new int[compositions.GetSize()];
  for (int i = 0; i < compositions.GetSize(); i++)
    count_compositions[i] = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < melomans[i].GetSize(); j++) {
      for (int l = 0; l < compositions.GetSize(); l++) {
        if (compositions.GetElement(l) == melomans[i].GetElement(j)) {
          count_compositions[l]++;
          break;
        }
      }
    }
  }

  for (int i = 0; i < compositions.GetSize(); i++) {
    std::cout << "KNIGGA NUMBER " << i+1 << "  " << count_compositions[i]
              << '\n';
  }
  // четвёртое задание
  //                 0123456789
  std::string rus = "ауоиэыяюеё";
  std::string big_rus = "АУОИЭЫЯЮЕЁ";

  UniqueCollection<std::string> letters[10];

  std::ifstream input("rus_text.txt");
  std::string line;
  while (std::getline(input, line)) {
    std::string temp;
    std::stringstream str_stream(line);
    while (str_stream >> temp) {
      std::cout << temp << '\n';
      for (int i = 0; i < temp.size() / 2; i++) {
        for (int j = 0; j < 10; j++) {
          if (int(temp[i]) == int(rus[j]) || int(temp[i]) == int(big_rus[j])) {
            letters[j].add(temp);
            std::cout << "Буквы " << int(temp[i]) << " " << int(rus[j]) << "  "
                      << int(big_rus[j]) << '\n';
          }
        }
      }
    }
  }
  input.close();

  for (int i = 0; i < 10; i++) {
    letters[i].print();
  }

  return 0;
}
