# airline-data-management

An airline data management software. The data are objects of the following types:<br />
* Employees - an employee can be a manager, a navigator, a flight attendant, a pilot, or other. Each employee has seniority, a birth year, and a direct employer.
* Planes - a plane has a model number, a list of the number of crew members of any job type required to fly the plane, and the maximal number of passengers in each class.
* Flights - a flight has a plane model, a date, a source, a destination, a list of reservations, and a list of the assigned crew. 
* Customers - a customer has a full name, a priority rating (a number between 1 and 5), and a list of all orders he has placed.
* Reservations - a reservation has a customer, a flight ID, a class in which the customer is interested, and the max baggage of the customer.


Each object has a unique ID which is stored as a string, and there is no duplication of data.<br />

The data is stored in tables in files so that it is saved after the program closes and is reloads in the next running.
