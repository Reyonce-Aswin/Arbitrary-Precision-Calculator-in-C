# 🔢 Arbitrary Precision Calculator in C

## 📌 Overview

Arbitrary-precision arithmetic (also known as **big-number arithmetic** or **multiple-precision arithmetic**) allows computations on numbers whose size is limited only by the available system memory. This project implements an **Arbitrary Precision Calculator in C**, overcoming the fixed-size limitations of standard data types such as `int`, `long`, or `long long`.

The calculator is built **from scratch**, without using any external big-number libraries, and supports arithmetic operations on very large integers—commonly required in areas like **cryptography**, **scientific computing**, and **systems programming**.

---

## 🎯 Project Objectives

* Implement arithmetic operations on very large numbers
* Understand and apply **Abstract Data Types (ADT)**
* Use **linked lists** to represent and manipulate big numbers
* Analyze and optimize **time and space complexity**
* Gain hands-on experience with **low-level memory management in C**

---

## ✨ Features

* Supports integers with **hundreds to thousands of digits**
* Operations implemented:

  * Addition
  * Subtraction
  * Multiplication
  * Division
  * Modulus
  * Power
* Handles:

  * Positive and negative numbers
  * Large carry and borrow propagation
* Modular and extensible code structure

---

## 🛠️ Technologies Used

* **Language:** C
* **Concepts:**

  * Data Structures & Algorithms
  * Abstract Data Types (ADT)
  * Linked Lists (Self-referential structures)
  * Order of Complexity (Big-O Analysis)

---

## 📚 Pre-requisites

* Basic knowledge of C programming
* Understanding of:

  * Linked lists
  * Abstract Data Types (ADT)
  * Time and space complexity

---

## 🧠 Implementation Details

* Each digit of a number is stored in a **node of a linked list**
* Numbers are processed digit-by-digit to simulate manual arithmetic
* Separate modules are used for:

  * Number parsing
  * Arithmetic operations
  * Memory management
* Careful handling of edge cases such as:

  * Negative operands
  * Zero values
  * Large exponent calculations

---

## 📈 Project Outcomes / Results

* Successfully performed arithmetic operations on **very large integers**
* Built a scalable and memory-efficient big-number representation
* Improved understanding of **algorithmic trade-offs**
* Strengthened debugging skills related to **segmentation faults and memory leaks**
* Developed a strong foundation in **systems-level programming**

---

## 🚀 How to Build & Run

```bash
gcc *.c -o apc
./apc <operand 1> <operator> <operand 2>
```
---

## 🔮 Future Enhancements

* Support for floating-point big numbers
* Optimization of power and division algorithms
* Improved CLI interface
* File-based input/output support

---

## 🤝 Contributing

Contributions, suggestions, and improvements are welcome!
Feel free to fork the repository and submit a pull request.

---

## 🔗 Author

**Reyonce Aswin**
**Emertxe Information Technologies**
📫 Feel free to connect on LinkedIn and explore more projects on GitHub.

---
