// Copyright 2020 Okmyanskiy Andrey

#include <gtest/gtest.h>

#include "include/stack.h"

TEST(Stack, wrongSizeInConstructor) {
    // Arrange
    int size;

    // Act
    size = -5;

    // Assert
    EXPECT_ANY_THROW(Stack stack(size));
}

TEST(Stack, getSizeWorks) {
    // Arrange
    int size = 10;

    // Act
    Stack stack(size);

    // Assert
}

TEST(Stack, getTopWorks) {
    // Arrange
    int size = 10;
    int top = 5;
    Stack stack(size);

    // Act
    for (int i = 0; i < top; i++) {
        stack.put(i);
    }

    // Assert
}

TEST(Stack, copyConstructorWorks) {
    // Arrange
    int size = 10;
    Stack stack(size);

    // Act
    for (int i = 0; i < stack.getSize(); i++) {
        stack.put(static_cast<double>(i));
    }
    Stack stack2(stack);

    // Assert
}

TEST(Stack, equalOperatorWorks) {
    // Arrange
    int size = 10;
    Stack stack(size);
    Stack stack2;

    // Act
    for (int i = 0; i < stack.getSize(); i++) {
        stack.put(static_cast<double>(i));
    }
    stack2 = stack;

    // Assert
}

TEST(Stack, comparisonOperatorWorks) {
    // Arrange
    int size = 10;
    Stack stack(size);

    // Act
    for (int i = 0; i < stack.getSize(); i++) {
        stack.put(static_cast<double>(i));
    }
    Stack stack2(stack);

    // Assert
}

TEST(Stack, notEqualComparisonOperatorWorks) {
    // Arrange
    int size = 10;
    Stack stack(size);
    Stack stack2(size);

    // Act
    for (int i = 0; i < stack.getSize(); i++) {
        stack.put(static_cast<double>(i));
    }
    for (int i = 0; i < stack2.getSize(); i++) {
        stack2.put(static_cast<double>(i+1));
    }

    // Assert
}

TEST(Stack, stackIsEmpty) {
    // Arrange
    int size = 10;

    // Act
    Stack stack(size);

    // Assert
}

TEST(Stack, stackIsNotEmpty) {
    // Arrange
    int size = 10;
    Stack stack(size);

    // Act
    for (int i = 0; i < stack.getSize()/2; i++) {
        stack.put(static_cast<double>(i));
    }

    // Assert
}

TEST(Stack, stackIsFull) {
    // Arrange
    int size = 10;
    Stack stack(size);

    // Act
    for (int i = 0; i < stack.getSize(); i++) {
        stack.put(static_cast<double>(i));
    }

    // Assert
}

TEST(Stack, stackIsNotFull) {
    // Arrange
    int size = 10;
    Stack stack(size);

    // Act
    for (int i = 0; i < stack.getSize()/2; i++) {
        stack.put(static_cast<double>(i));
    }

    // Assert
}

TEST(Stack, getAndPutWorks) {
    // Arrange
    int size = 1;
    double value = 14;
    Stack stack(size);

    // Act
    stack.put(value);

    // Assert
}
