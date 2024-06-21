#include "../include/Page.h"

#include <iostream>

Page::Page() : capacity(0), namePath(""), pageID(-1) {
}

Page::Page(int size, string name) : capacity(size), namePath(name) {
}

int Page::getSize() {
  return capacity;
}

void Page::setSize(int size) {
  capacity = size;
}

int Page::getPageId() {
  return this->pageID;
}

void Page::setPageId(int pageId) {
  this->pageID = pageId;
}

string Page::getName() {
  return namePath;
}

void Page::setName(string name) {
  namePath = name;
}

/*
bool Page::addRecordInContent(string &record) {
  // Asumiendo que cada carácter cuenta como un byte
  int recordSize = record.size();
  if (recordSize <= capacity) {
    content.push_back(record);
    capacity -= recordSize; // Ajustar el tamaño restante
    return true;
  }
  return false;
}

bool Page::deleteRecordInContent(int index) {
  if (index >= 0 && index < content.size()) {
    capacity += content[index].size(); // Recuperar el tamaño del registro eliminado
    content.erase(content.begin() + index);
    return true;
  }
  return false;
}
*/

string &Page::getContent() {
  return contentRFL;
}

void Page::setContentRFL(string content) {
  this->contentRFL = content;
}
