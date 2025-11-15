#ifndef BSTIO_H
#define BSTIO_H

#include <string>
#include "bst.h"

class bstIO {
public:
    static void saveBinary(const std::string& filename, const bst& tree);

    static void loadBinary(const std::string& filename, bst& tree);

    static void loadFromTextFile(const std::string& filename, bst& tree, bool append = false);
};

#endif