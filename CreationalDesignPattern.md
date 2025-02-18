Here's your **Creational Design Patterns** notes in **Markdown (.md) format**:  

# Creational Design Patterns

## Definition  
Creational design patterns **focus on object creation mechanisms** to improve flexibility and reuse of existing code.  
Instead of creating objects directly using the `new` keyword, creational patterns provide **controlled and optimized** ways to instantiate objects.

## Benefits of Creational Design Patterns  
✅ **Encapsulates object creation logic** → Reduces direct dependencies.  
✅ **Improves code maintainability** → Changes to object creation logic are centralized.  
✅ **Enhances flexibility** → Easily switch between different object implementations.  
✅ **Supports scalability** → Allows adding new object types without modifying existing code.  

---

## Types of Creational Design Patterns  

### 1️⃣ Singleton Pattern  
Ensures that a **class has only one instance** and provides a global access point to it.  

**🔹 Use Case:** Database connection, logging service, configuration management.  

```cpp
class Singleton {
private:
    static Singleton* instance;
    Singleton() {} // Private constructor

public:
    static Singleton* getInstance() {
        if (!instance)
            instance = new Singleton();
        return instance;
    }
};

// Initialize static member
Singleton* Singleton::instance = nullptr;
```

**✅ Pros:** Saves memory, avoids duplicate instances.  
**❌ Cons:** Can introduce **global state** issues if overused.  

---

### 2️⃣ Factory Method Pattern  
Defines an **interface for creating objects** but allows subclasses to **alter the type of objects created**.  

**🔹 Use Case:** GUI toolkits (creating buttons, dropdowns), database connections.  

```cpp
class Product {
public:
    virtual void use() = 0;
};

class ConcreteProductA : public Product {
public:
    void use() override { /* Logic for ProductA */ }
};

class ConcreteProductB : public Product {
public:
    void use() override { /* Logic for ProductB */ }
};

class Creator {
public:
    virtual Product* createProduct() = 0;
};

class ConcreteCreatorA : public Creator {
public:
    Product* createProduct() override { return new ConcreteProductA(); }
};

class ConcreteCreatorB : public Creator {
public:
    Product* createProduct() override { return new ConcreteProductB(); }
};
```

**✅ Pros:** Promotes loose coupling, enhances flexibility.  
**❌ Cons:** Adds complexity with extra classes.  

---

### 3️⃣ Abstract Factory Pattern  
Provides an **interface for creating families of related objects** without specifying their concrete classes.  

**🔹 Use Case:** UI frameworks supporting multiple themes, cross-platform software development.  

```cpp
class Button {
public:
    virtual void render() = 0;
};

class WindowsButton : public Button {
public:
    void render() override { /* Windows Button rendering */ }
};

class MacOSButton : public Button {
public:
    void render() override { /* macOS Button rendering */ }
};

class GUIFactory {
public:
    virtual Button* createButton() = 0;
};

class WindowsFactory : public GUIFactory {
public:
    Button* createButton() override { return new WindowsButton(); }
};

class MacOSFactory : public GUIFactory {
public:
    Button* createButton() override { return new MacOSButton(); }
};
```

**✅ Pros:** Ensures compatibility between related objects.  
**❌ Cons:** Can become **complicated** if too many product variations exist.  

---

### 4️⃣ Builder Pattern  
Separates **object construction from its representation**, allowing step-by-step object creation.  

**🔹 Use Case:** Creating complex objects like cars, reports, and UI components.  

```cpp
class Car {
public:
    std::string engine;
    std::string wheels;
    std::string seats;
};

class CarBuilder {
protected:
    Car* car;

public:
    CarBuilder() { car = new Car(); }
    virtual void buildEngine() = 0;
    virtual void buildWheels() = 0;
    virtual void buildSeats() = 0;
    Car* getCar() { return car; }
};

class SportsCarBuilder : public CarBuilder {
public:
    void buildEngine() override { car->engine = "V8 Engine"; }
    void buildWheels() override { car->wheels = "Racing Wheels"; }
    void buildSeats() override { car->seats = "Leather Seats"; }
};

class Director {
public:
    Car* construct(CarBuilder& builder) {
        builder.buildEngine();
        builder.buildWheels();
        builder.buildSeats();
        return builder.getCar();
    }
};
```

**✅ Pros:** Simplifies object creation, ensures consistency.  
**❌ Cons:** Adds complexity when the number of attributes is small.  

---

### 5️⃣ Prototype Pattern  
Creates new objects by **copying an existing object (cloning)** instead of creating a new instance from scratch.  

**🔹 Use Case:** Game object duplication, UI templates, document processing.  

```cpp
class Prototype {
public:
    virtual Prototype* clone() = 0;
};

class ConcretePrototype : public Prototype {
private:
    int value;

public:
    ConcretePrototype(int val) : value(val) {}
    Prototype* clone() override { return new ConcretePrototype(*this); }
};
```

**✅ Pros:** Efficient for complex object creation.  
**❌ Cons:** Deep copying can be expensive in memory and performance.  

---

## When to Use Creational Design Patterns?  
| Pattern            | Use Case |
|--------------------|---------|
| Singleton         | When only **one instance** should exist (logging, database connections). |
| Factory Method   | When object creation should be **delegated** to subclasses. |
| Abstract Factory | When you need to create **families of related objects** (UI components, OS-based widgets). |
| Builder          | When an object has **multiple configurations** (cars, reports, UIs). |
| Prototype        | When object **cloning** is needed (game objects, UI templates). |

---

