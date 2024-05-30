#include <stdexcept>

#include "List.h"

using namespace std;

List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

List::List() {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
}

List::List(const List& L) { 
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
    Node *N = L.frontDummy->next;
    while (N != L.backDummy) {
        this->insertAfter(N->data);
        moveNext();
        N = N->next;
    }
    moveFront();
}

List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}

int List::length() const {
   return num_elements;
}

ListElement List::front() const {
   if (length() <= 0) {
      throw length_error("List: front(): empty list");
   }
   return frontDummy->next->data;
}

ListElement List::back() const {
   if (length() <= 0) {
      throw length_error("List: back(): empty list");
   }
   return backDummy->prev->data;
}

int List::position() const {
   if (pos_cursor < 0 || pos_cursor > length()) {
      throw range_error("List: position(): empty list");
   }
   return pos_cursor;
}

ListElement List::peekNext() const {
   if (pos_cursor >= length()) {
      throw range_error("List: peekNext(): cursor at back");
   }
   return afterCursor->data;
}

ListElement List::peekPrev() const {
   if (pos_cursor <= 0) {
      throw range_error("List: peekPrev(): cursor at front");
   }
   return beforeCursor->data;
}

void List::clear() {
    moveFront();
    while (length() > 0) {
        eraseAfter();
    }
}

void List::moveFront(){
   beforeCursor = frontDummy;
   afterCursor = frontDummy->next;
   pos_cursor = 0;
}

void List::moveBack(){
   afterCursor = backDummy;
   beforeCursor = backDummy->prev;
   pos_cursor = num_elements;
}

ListElement List::moveNext() {
   if (position() > length()) {
      throw range_error("List: moveNext(): cursor at front");
   }
   beforeCursor = beforeCursor->next;
   afterCursor = afterCursor->next;
   pos_cursor++;
   return beforeCursor->data;
}

ListElement List::movePrev() {
    if (position() < 0) {
      throw range_error("List: movePrev(): cursor at front");
    }
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}

void List::insertAfter(ListElement x) {
    if (pos_cursor < 0) {
      throw range_error("List: insertAfter(): cursor at front");
    }
    if (afterCursor == nullptr || beforeCursor == nullptr) {
      throw range_error("List: insertAfter(): cursor at NULL");
    }    
    Node *temp = new Node(x);
    temp->prev = beforeCursor;
    beforeCursor->next = temp;
    temp->next = afterCursor;
    afterCursor->prev = temp;
    afterCursor = temp;
    num_elements++;
}

void List::insertBefore(ListElement x) {
    if (pos_cursor < 0) {
        exit(EXIT_FAILURE);
    }
    if (afterCursor == nullptr || beforeCursor == nullptr) {
        exit(EXIT_FAILURE);
    }
    Node *temp = new Node(x);

    temp->prev = beforeCursor;
    beforeCursor->next = temp;
    temp->next = afterCursor;
    afterCursor->prev = temp;
    beforeCursor = temp;

    pos_cursor++;
    num_elements++;
}

void List::setAfter(ListElement x) {
    if (pos_cursor > length()) {
      throw range_error("List: setAfter(): cursor at back");
   }
   afterCursor->next->data = x;
}

void List::setBefore(ListElement x) {
   if (pos_cursor < 0) {
      throw range_error("List: setBefore(): cursor at front");
   }
   beforeCursor->prev->data = x;
}

void List::eraseAfter() {
    if (pos_cursor > length()) {
        throw range_error("List: eraseAfter(): cursor at back");
    }
    Node *N = afterCursor;
    beforeCursor->next = afterCursor->next;
    N->next->prev = beforeCursor;
    afterCursor = N->next;
    delete N;
    num_elements--;
}

void List::eraseBefore() {
   if (pos_cursor > 0 && beforeCursor != nullptr) {
      Node* temp = beforeCursor;
      beforeCursor = temp->prev;
      beforeCursor->next = afterCursor;
      afterCursor->prev = beforeCursor;
      delete temp;
      num_elements--;
      pos_cursor--;
   } else {
      throw range_error("List: eraseBefore(): cursor at front");
   }
}

int List::findNext(ListElement x) {
   Node *N = afterCursor;
   for (int i = pos_cursor; N != backDummy; i++) {
      if (N->data == x) {
         afterCursor = N->next;
         beforeCursor = N;
         pos_cursor = i + 1;
         return pos_cursor;
      }
      N = N->next;
   }
   afterCursor = backDummy;
   beforeCursor = backDummy->prev;
   pos_cursor = num_elements;
   return -1;
}

int List::findPrev(ListElement x) {
    Node* temp = afterCursor->prev;
    int prevPos = pos_cursor - 1;
    while (temp != frontDummy) {
        if (temp->data == x) {
            beforeCursor = temp->prev;
            afterCursor = temp;
            pos_cursor = prevPos;
            return prevPos;
        }
        temp = temp->prev;
        prevPos--;
    }
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
    return -1;
}

void List::cleanup() {
   int position = 0;
   Node *cursor = frontDummy->next;
   do {
      Node *current = cursor;
      Node *n = cursor->next;
      int inner_position = position + 1;
      while (n != backDummy) {
         if (cursor->data == n->data) {
               current->next = n->next;
               n->next->prev = current;
               delete n;
               n = current->next;
               num_elements--;
               if (inner_position <= pos_cursor) {
                  pos_cursor--;
               }
         }
         else {
               current = n;
               n = current->next;                
         }
         inner_position++;
      }
      position++;
      cursor = cursor->next;
   } while (cursor != backDummy);
}

List List::concat(const List& L) const {
   List newList;
   Node *N = this->frontDummy->next;
   Node *M = L.frontDummy->next;

   do {
      newList.insertAfter(N->data);
      N = N->next;
   } while (N != this->backDummy);

   do {
      newList.insertAfter(M->data);
      M = M->next;
   } while (M != L.backDummy);

   return newList;
}

std::string List::to_string() const {
   Node *N = nullptr;
   string s = "";
   for (N = frontDummy; N!= nullptr; N = N->next) {
      s += std::to_string(N->data) + " ";
   }
   return s;
}

bool List::equals(const List& R) const {
   if (this->num_elements != R.num_elements) {
      return false;
   }
   Node* N = this->frontDummy;
   Node* M = R.frontDummy;
   for (int i = 0; i < this->num_elements; i++) {
      if (N->data != M->data) {
         return false;
      }
      N = N->next;
      M = M->next;
   }
   return true;
}

std::ostream& operator<<(std::ostream& stream, const List& L) {
    List::Node* current = L.frontDummy->next;
    while (current != L.backDummy) {
        stream << current->data << " ";
        current = current->next;
    }
    return stream;
}


bool operator==( const List& A, const List& B ) {
   return A.List::equals(B);
} 

List& List::operator=(const List& L) {
    if (this != &L) {
      List temp = L;
      swap(frontDummy, temp.frontDummy);
      swap(backDummy, temp.backDummy);
      swap(num_elements, temp.num_elements);
      swap(beforeCursor, temp.beforeCursor);
      swap(afterCursor, temp.afterCursor);
      swap(pos_cursor, temp.pos_cursor);
    }
    return *this;
}
