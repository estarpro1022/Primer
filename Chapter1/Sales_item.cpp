/**
 * @file Sales_item.cpp
 * @author Kartone
 * @brief Count books' number with same ISBN 
 * Make sure same ISBN books are together
 * @version 0.1
 * @date 2022-07-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include "Sales_item.h"

int main() {
    Sales_item book, currBook;
    int count = 1;
    std::cin >> currBook;
    while (std::cin >> book) {
        if (book.isbn() == currBook.isbn()) {
            count++;
        } else {
            std::cout << "Books ISBN " << currBook.isbn() << " occur " << count
                      << "times";
            currBook = book;
            count = 1;
        }
    }
    std::cout << "Books ISBN " << currBook.isbn() << " occur " << count
              << "times";
    return 0;
}
