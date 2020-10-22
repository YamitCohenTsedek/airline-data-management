
#include "MyCustomer.h"

/*
 * The format of CustomerFile:
 * string customerID;string customerFullName;int priority;
 */
string MyCustomer::getCustomerFileFormat () {
    string customerFileFormat;
    string customerID = id;
    string customerFullName = fullName;
    string customer_priority = to_string(customerPriority);
    customerFileFormat = customerID + ";" + customerFullName + ";" + customer_priority + ";\n";
    return customerFileFormat;
}