#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

int MAX_RECORDS = 100;

int main()
{
    // Read CSV with these attributes
    // name,price,category,stock,brand,description,purchases
    ifstream productFileIn("Products.csv");
    if (!productFileIn.is_open())
    {
        cout << "Error opening file" << endl;
        return 1;
    }

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

    Product products[MAX_RECORDS];
    int productCount = 0;

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

    // Print the products

    for (int i = 0; i < productCount; i++)
    {
        cout << "Product " << i + 1 << endl;
        cout << "Name: " << products[i].name << endl;
        cout << "Price: " << products[i].price << endl;
        cout << "Category: " << products[i].category << endl;
        cout << "Stock: " << products[i].stock << endl;
        cout << "Brand: " << products[i].brand << endl;
        cout << "Description: " << products[i].description << endl;
        cout << "Purchases: " << products[i].purchases << endl;
        cout << endl;
    }

    return 0;
}