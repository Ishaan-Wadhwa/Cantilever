#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Product {
    int id;
    std::string name;
    double price;
    int quantity;
    
    void display() const {
        std::cout << "ID: " << id << ", Name: " << name << ", Price: $" << price << ", Quantity: " << quantity << std::endl;
    }
};

void addProduct(std::vector<Product>& products) {
    Product product;
    std::cout << "Enter Product ID: ";
    std::cin >> product.id;
    std::cout << "Enter Product Name: ";
    std::cin >> product.name;
    std::cout << "Enter Product Price: ";
    std::cin >> product.price;
    std::cout << "Enter Product Quantity: ";
    std::cin >> product.quantity;
    products.push_back(product);
    std::cout << "Product added successfully." << std::endl;
}

void updateProduct(std::vector<Product>& products) {
    int id;
    std::cout << "Enter Product ID to update: ";
    std::cin >> id;
    for (auto& product : products) {
        if (product.id == id) {
            std::cout << "Enter new Product Name: ";
            std::cin >> product.name;
            std::cout << "Enter new Product Price: ";
            std::cin >> product.price;
            std::cout << "Enter new Product Quantity: ";
            std::cin >> product.quantity;
            std::cout << "Product updated successfully." << std::endl;
            return;
        }
    }
    std::cout << "Product not found." << std::endl;
}

void deleteProduct(std::vector<Product>& products) {
    int id;
    std::cout << "Enter Product ID to delete: ";
    std::cin >> id;
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->id == id) {
            products.erase(it);
            std::cout << "Product deleted successfully." << std::endl;
            return;
        }
    }
    std::cout << "Product not found." << std::endl;
}

void saveToFile(const std::vector<Product>& products, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& product : products) {
        file << product.id << " " << product.name << " " << product.price << " " << product.quantity << std::endl;
    }
    file.close();
    std::cout << "Products saved to file." << std::endl;
}

void loadFromFile(std::vector<Product>& products, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File not found." << std::endl;
        return;
    }
    Product product;
    while (file >> product.id >> product.name >> product.price >> product.quantity) {
        products.push_back(product);
    }
    file.close();
    std::cout << "Products loaded from file." << std::endl;
}

void generateReport(const std::vector<Product>& products) {
    std::cout << "Inventory Report:" << std::endl;
    for (const auto& product : products) {
        product.display();
    }
}

void displayMenu() {
    std::cout << "Inventory Management System" << std::endl;
    std::cout << "1. Add Product" << std::endl;
    std::cout << "2. Update Product" << std::endl;
    std::cout << "3. Delete Product" << std::endl;
    std::cout << "4. Generate Report" << std::endl;
    std::cout << "5. Save to File" << std::endl;
    std::cout << "6. Load from File" << std::endl;
    std::cout << "7. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    std::vector<Product> products;
    std::string filename = "products.txt";
    int choice;
    
    while (true) {
        displayMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                addProduct(products);
                break;
            case 2:
                updateProduct(products);
                break;
            case 3:
                deleteProduct(products);
                break;
            case 4:
                generateReport(products);
                break;
            case 5:
                saveToFile(products, filename);
                break;
            case 6:
                loadFromFile(products, filename);
                break;
            case 7:
                std::cout << "Exiting the program." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    return 0;
}
