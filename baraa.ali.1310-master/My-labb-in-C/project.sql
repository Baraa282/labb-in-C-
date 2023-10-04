CREATE DATABASE project;
USE project;

CREATE TABLE HomeDepartment
(
home_title VARCHAR(40) PRIMARY KEY,
welcome_text TEXT,
description TEXT 
);


CREATE TABLE BreadCrumbs
(
    parent VARCHAR(40) PRIMARY KEY ,
    parent_link VARCHAR(40),
    parent_title VARCHAR (40)
);



CREATE TABLE Departments
(
department_title VARCHAR(40) PRIMARY KEY,
description VARCHAR(40),
parent VARCHAR(40),
home_title VARCHAR(50),
FOREIGN KEY (parent) REFERENCES BreadCrumbs (parent),
FOREIGN KEY (home_title) REFERENCES HomeDepartment (home_title)
);

CREATE TABLE Product
(
product_id INT PRIMARY KEY NOT NULL ,
name VARCHAR(50),
stock INT ,
description TEXT ,
orginal_price int ,
tax INT ,
discount INT ,
department_title VARCHAR (60),
FOREIGN KEY (department_title) REFERENCES Departments (department_title)
);


CREATE TABLE Keyword
(
product_id INT ,
keyword VARCHAR (50),
PRIMARY KEY (product_id , keyword),
FOREIGN KEY (product_id) REFERENCES Product (product_id)
);

CREATE TABLE Address
(
postal_code VARCHAR(20) PRIMARY KEY,
street VARCHAR(30),
city VARCHAR (30)

);

CREATE TABLE Users
(
id_number INT PRIMARY KEY NOT NULL ,
first_name VARCHAR (50),
last_name VARCHAR(50),
email VARCHAR(30),
password VARCHAR(40),
phone_number VARCHAR (20),
checksbox_newsletter boolean,
postal_code VARCHAR (20),
FOREIGN KEY (postal_code) REFERENCES Address (postal_code)
);

CREATE TABLE OrderStatus
(
tracking_number VARCHAR(50) PRIMARY KEY,
status VARCHAR(20),
order_date DATETIME,
date_last_change TIME
);

CREATE TABLE Orders
(
order_id INT PRIMARY KEY NOT NULL,
payment_reference VARCHAR (50),
order_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
tracking_number VARCHAR (50),
id_number int,
FOREIGN KEY (tracking_number) REFERENCES OrderStatus (tracking_number),
FOREIGN KEY (id_number) REFERENCES Users(id_number)
);

CREATE TABLE Reviews 
(
review_id INT PRIMARY KEY NOT NULL,
text VARCHAR(40),
stars INT ,
id_number INT,
product_id INT,
order_id INT ,
FOREIGN KEY (id_number) REFERENCES Users (id_number),
FOREIGN KEY (product_id) REFERENCES Product (product_id),
FOREIGN KEY (order_id) REFERENCES Orders (order_id)
);
