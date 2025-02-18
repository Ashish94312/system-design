# Interface Segregation Principle (ISP)

## Definition  
The **Interface Segregation Principle (ISP)** states that a class should not be forced to implement interfaces it does not use. Instead, it should depend only on the methods it actually needs.

## Key Idea  
- Clients should **only depend on methods they actually use**.  
- Large, bloated interfaces should be **split into smaller, more focused interfaces**.  
- Helps **avoid unnecessary dependencies** and **reduces the impact of changes** in the system.  

## Why is ISP Important?  
- **Prevents bloated interfaces** (avoids implementing methods that are irrelevant).  
- **Enhances code maintainability** (changes affect only relevant parts).  
- **Improves flexibility** (easier to modify or extend without affecting unrelated functionality).  
- **Encourages modularity** (smaller interfaces are easier to understand and test).  

## Example of a Violation of ISP (Bad Design)  
```cpp
// A large interface forcing all implementations to define unrelated methods
class Worker {
public:
    virtual void work() = 0;
    virtual void eat() = 0;
};
 
class Robot : public Worker {
public:
    void work() override { /* Robot works */ }
    void eat() override { /* Robots don't eat! */ } // Unnecessary method for robots
};

The Robot class is forced to implement an eat() method it doesn’t need

// Segregating interfaces into smaller, more specific ones
class Workable {
public:
    virtual void work() = 0;
};

class Eatable {
public:
    virtual void eat() = 0;
};

class Robot : public Workable {
public:
    void work() override { /* Robot works */ }
    // No unnecessary 'eat()' method
};

class Human : public Workable, public Eatable {
public:
    void work() override { /* Human works */ }
    void eat() override { /* Human eats */ }
};
```


# Dependency Inversion Principle (DIP)

## Definition  
The **Dependency Inversion Principle (DIP)** states that:  
1. High-level modules should not depend on low-level modules. Both should depend on abstractions.  
2. Abstractions should not depend on details. Details should depend on abstractions.  

This principle helps **reduce coupling** and makes code more maintainable and flexible.

## Key Idea  
- Instead of directly depending on **concrete implementations**, depend on **abstract interfaces**.  
- Allows swapping out implementations without modifying high-level logic.  
- Promotes **loose coupling**, making the system easier to modify and extend.

## Why is DIP Important?  
- **Reduces code dependencies**, making it easier to change one part without affecting others.  
- **Improves testability** by allowing the use of mock dependencies.  
- **Enhances maintainability and flexibility**, as new implementations can be introduced without modifying existing code.  
- **Supports the Open/Closed Principle (OCP)** by making it easier to extend functionality.

## Example of a Violation of DIP (Bad Design)  
```cpp
// High-level module (Application) directly depends on a low-level module (MySQLDatabase)
class MySQLDatabase {
public:
    void connect() { /* Connect to MySQL */ }
    void query() { /* Execute query */ }
};

class Application {
private:
    MySQLDatabase db; // Direct dependency on a concrete class

public:
    void run() {
        db.connect();
        db.query();
    }
};
```