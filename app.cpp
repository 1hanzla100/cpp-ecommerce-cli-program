#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

int const MAX_RECORDS = 100;

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

struct Cart
{
    Product product;
    int quantity;
};

struct OrderItem
{
    Product product;
    int quantity;
    float subTotal;
};

struct Order
{
    OrderItem orderItems[MAX_RECORDS];
    int orderItemCount;
    float total;
    string name;
    string address;
    string phone;
    string city;
    string state;
    string paymentTransactionId;
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
    for (int i = 1; i < productCount; i++)
    {
        cout << "ID: " << i << endl;
        cout << "Name: " << products[i].name << endl;
        cout << "Price: " << products[i].price << endl;
        cout << "Category: " << products[i].category << endl;
        cout << "Brand: " << products[i].brand << endl;
        cout << endl;
    }
}

void searchProducts(Product products[], int productCount, string input)
{
    for (int i = 0; i < productCount; i++)
    {
        if (input == products[i].category || input == products[i].name)
        {
            cout << i << " \t " << products[i].name << " \t " << products[i].price << " \t " << products[i].brand << endl;
        }
    }
}

void displayDetails(Product products[], int productCount, int index)
{
    for (int i = 0; i < productCount; i++)
    {
        if (index == i)
        {
            cout << "Name:  " << products[i].name << endl;
            cout << "Price:  " << products[i].price << endl;
            cout << "Brand:  " << products[i].brand << endl;
            cout << "Description: " << products[i].description << endl;
            cout << "Purchases: " << products[i].purchases << endl;
            cout << "Stock: " << products[i].stock << endl;
        }
    }
}
Cart addToCart(Product products[], int productCount)
{
    int productId;
    int quantity;

    while (true)
    {
        cout << "Enter the product ID: ";
        cin >> productId;
        if (productId < 0 || productId >= productCount)
        {
            cout << "Invalid product ID. Please enter a valid product ID: ";
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        cout << "Enter the quantity: ";
        cin >> quantity;
        if (quantity < 0 || quantity > products[productId].stock)
        {
            cout << "Invalid quantity. Please enter a valid quantity: ";
        }
        else
        {
            break;
        }
    }

    Cart cart;
    cart.product = products[productId];
    cart.quantity = quantity;
    return cart;
}

void displayCart(Cart cart[], int cartCount)
{
    for (int i = 0; i < cartCount; i++)
    {
        cout << "Item #" << i + 1 << endl;
        cout << "Product: " << cart[i].product.name << endl;
        cout << "Price: " << cart[i].product.price << endl;
        cout << "Quantity: " << cart[i].quantity << endl;
        cout << "Subtotal: " << cart[i].product.price * cart[i].quantity << endl;
        cout << endl;
    }
}

void removeItemFromCart(Cart *cart, int *cartCount)
{
    int index;
    cout << "Enter the item number to remove: ";
    cin >> index;
    if (index == 0 || index >= *cartCount)
    {
        cout << "Invalid item number. Please enter a valid item number." << endl;
    }
    else
    {
        if (index - 1 == *cartCount - 1 || index - 1 == 0)
        {
            (*cartCount)--;
            return;
        }
        for (int i = index; i < *cartCount - 1; i++)
        {
            *(cart + i) = *(cart + i + 1);
        }
        (*cartCount)--;
    }
}

int main()
{
    // Read CSV with these attributes

    ifstream productFileIn("Products.csv");

    Product products[MAX_RECORDS];
    int productCount = 0;

    Cart cart[MAX_RECORDS];
    int cartCount = 0;

    string line;
    istringstream ss;
    while (getline(productFileIn, line))
    {
        ss = istringstream(line);
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
        case 2:
        {
            string input;
            cout << "Enter which category you want to buy:";
            cin >> input;
            searchProducts(products, productCount, input);
        }
        break;
        case 3:
        {
            int index;
            cout << "Enter the product for Details:";
            cin >> index;
            displayDetails(products, productCount, index);
        }
        break;
        case 4:
        {
            cart[cartCount] = addToCart(products, productCount);
            cartCount++;
        }
        break;
        case 5:
            displayCart(cart, cartCount);
            break;
        case 6:
            removeItemFromCart(cart, &cartCount);
            break;
        default:
            exit = true;
            break;
        }
    }
    return 0;
}