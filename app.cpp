#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

int MAX_RECORDS = 100;

struct Product
{
    string name;
    float price;
    string category;
    int stock;
    string brand;
    string description;
    int purchases;
};

void displayMainMenu()
{
    cout << "------ Main Menu ------" << endl;
    cout << "1. Display all products" << endl;
    cout << "2. Search products" << endl;
    cout << "3. Display products detail by #" << endl;
    cout << "4. Add to cart" << endl;
    cout << "5. Display cart" << endl;
    cout << "6. Remove from cart" << endl;
    cout << "7. Checkout" << endl;
    cout << "8. Display My Orders" << endl;
    cout << "9. Display Order Detail by #" << endl;
    cout << "10. Exit" << endl;
    cout << "-----------------------" << endl;
}

void displayProducts(Product products[], int productCount)
{
    for (int i = 0; i < productCount; i++)
    {
        cout << "ID: " << i << endl;
        cout << "Name: " << products[i].name << endl;
        cout << "Price: " << products[i].price << endl;
        cout << "Category: " << products[i].category << endl;
        cout << "Brand: " << products[i].brand << endl;
        cout << endl;
    }
}

int main()
{
    // Read CSV with these attributes

    ifstream productFileIn("Products.csv");
    if (!productFileIn.is_open())
    {
        cout << "Error opening file" << endl;
        return 1;
    }

    Product products[MAX_RECORDS];
    int productCount = 0;

    // Loading the products from the file

    string line;
    istringstream ss;
    while (getline(productFileIn, line))
    {
        ss = istringstream(line);
        // read the attributes and store them in the struct array

        getline(ss, products[productCount].name, ',');
        ss >> products[productCount].price;
        ss.ignore();
        getline(ss, products[productCount].category, ',');
        ss >> products[productCount].stock;
        ss.ignore();
        getline(ss, products[productCount].brand, ',');
        getline(ss, products[productCount].description, ',');
        ss >> products[productCount].purchases;
        ss.ignore();
        productCount++;
    }

    productFileIn.close();

    bool exit = false;

    while (!exit)
    {
        displayMainMenu();
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            displayProducts(products, productCount);
            break;
        default:
            exit = true;
            break;
        }
    }
    return 0;
}