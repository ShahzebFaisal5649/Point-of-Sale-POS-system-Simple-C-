# Sales Management System

## Overview

This project is a simple Sales Management System implemented in C++. It allows the management of items and customers, as well as handling sales and payments. The system supports adding, updating, finding, and removing items and customers. Additionally, it manages sales transactions by associating items with customers and calculating totals.

## Features

- **Item Management**: Add, update, find, and remove items.
- **Customer Management**: Add, update, find, and remove customers.
- **Sales Management**: Create new sales, add items to sales, remove items from sales, and make payments.

## File Structure

- `main.cpp`: Main implementation file containing the classes and main program logic.

## Classes

### `SalesManager`
- Base class for managing items and customers.

### `Item` (Inherits `SalesManager`)
- Manages individual item details.
- Methods: `read_item`, `addItem`, `updateItem`, `removeItem`, `printItem`, `same_sku`, `get_item`, etc.

### `Customer` (Inherits `SalesManager`)
- Manages customer details.
- Methods: `readCustomer`, `addCustomer`, `updateCustomer`, `removeCustomer`, `printCustomer`, `same_cnic`, `get_customer`, etc.

### `Sale`
- Manages sales transactions.
- Methods: `add_item`, `remove_item`, `set_total`, `print_sale`, `print_items`, `make_payment`, etc.

## Usage

### Compiling the Program

To compile the program, use the following command:

```bash
g++ -o sales_management mai.cpp
```

### Running the Program

To run the compiled program:

```bash
./sales_management
```

### Main Menu Options

1. **Manage Items**
    - Add new Item
    - Update Item details
    - Find Items
    - Remove Existing Item
    - Back to Main Menu

2. **Manage Customers**
    - Add new Customer
    - Update Customer details
    - Find Customers
    - Remove Existing Customer
    - Back to Main Menu

3. **Make New Sale**
    - Add new Item to Sale
    - End Sale
    - Remove Existing Item from Sale
    - Cancel Sale

4. **Make Payment**
    - Make a payment for a sale.

5. **Exit**
    - Exit the program.

## Example

### Adding an Item

1. Select "Manage Items" from the main menu.
2. Select "Add new Item".
3. Enter the details for the item (SKU, description, price, quantity).

### Adding a Customer

1. Select "Manage Customers" from the main menu.
2. Select "Add new Customer".
3. Enter the details for the customer (CNIC, name, email, number, status).

### Creating a Sale

1. Select "Make New Sale" from the main menu.
2. Enter the CNIC of the customer.
3. Add items to the sale by entering their SKU and quantity.
4. End the sale to finalize it.

### Making a Payment

1. Select "Make Payment" from the main menu.
2. Enter the sale ID.
3. Enter the payment amount.

## Files

- `items.txt`: Stores item details.
- `customer.txt`: Stores customer details.

## Notes

- The system uses simple text files (`items.txt` and `customer.txt`) to store item and customer details.
- Ensure these files exist in the same directory as the executable.

## Future Improvements

- Implement error handling and data validation.
- Use a more robust storage solution (e.g., a database) for better scalability and reliability.
- Enhance the user interface for better usability.

