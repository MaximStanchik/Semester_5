ALTER PLUGGABLE DATABASE NEV_PDB OPEN;
SET SERVEROUTPUT ON;

alter session set NLS_DATE_FORMAT='YYYY-MM-DD';
set escape on

--Задачи среднего уровня:
-- 1.	Создайте процедуру, которая выводит список заказов и их итоговую стоимость для определенного покупателя. 
--		Параметр – наименование покупателя. Обработайте возможные ошибки.

-- первый вариант как можно решить задачу
CREATE OR REPLACE PROCEDURE getListOfOrders (P_COMPANY IN VARCHAR2) AS 
	totalAmount NUMBER := 0;
BEGIN
	dbms_output.put_line('Orders for ' || P_COMPANY || ':');
	FOR rec IN (SELECT * FROM ORDERS INNER JOIN CUSTOMERS ON ORDERS.CUST = CUSTOMERS.CUST_NUM WHERE COMPANY = P_COMPANY) LOOP
		totalAmount := totalAmount + rec.AMOUNT;
		dbms_output.put_line('Order number: ' || rec.ORDER_NUM || ', ' || 'amount: ' || rec.AMOUNT);
	END LOOP;
IF totalAmount = 0 THEN
	dbms_output.put_line('No orders found for the company ' || P_COMPANY);
ELSE
	dbms_output.put_line('Total amount: ' || totalAmount);
END IF;

EXCEPTION
	WHEN OTHERS THEN
		dbms_output.put_line('An error occured: ' || sqlerrm);
END;
		
SELECT * 
FROM user_errors 
WHERE name = 'getListOfOrders' AND TYPE = 'PROCEDURE';

BEGIN 
	getListOfOrders ('JCP Inc.');
END;

--третий вариант как можно решить задачу
CREATE OR REPLACE PROCEDURE getListOfOrdersCursor (P_COMPANY IN VARCHAR2) AS 
	totalAmount NUMBER := 0;
	CURSOR order_cursor IS SELECT * FROM ORDERS INNER JOIN CUSTOMERS ON ORDERS.CUST = CUSTOMERS.CUST_NUM WHERE COMPANY = P_COMPANY;
BEGIN
	dbms_output.put_line('Orders for ' || P_COMPANY || ':');
	

	FOR rec IN order_cursor LOOP
		totalAmount := totalAmount + rec.AMOUNT;
		dbms_output.put_line('Order number: ' || rec.ORDER_NUM || ', ' || 'amount: ' || rec.AMOUNT);
	END LOOP;
IF totalAmount = 0 THEN
	dbms_output.put_line('No orders found for the company ' || P_COMPANY);
ELSE
	dbms_output.put_line('Total amount: ' || totalAmount);
END IF;

EXCEPTION
	WHEN OTHERS THEN
		dbms_output.put_line('An error occured: ' || sqlerrm);
END;

BEGIN 
	getListOfOrdersCursor ('JCP Inc.');
END;
	
-- второй вариант как можно решить задачу
CREATE OR REPLACE PROCEDURE GET_ORDERS_LIST_FOR_CUSTOMER (
    P_CUST_NAME IN VARCHAR2
)
IS
    CURSOR ORDER_CUR IS
        SELECT o.ORDER_NUM, SUM(o.AMOUNT) AS TOTAL_AMOUNT
        FROM ORDERS o
        JOIN CUSTOMERS c ON o.CUST = c.CUST_NUM
        WHERE c.COMPANY = P_CUST_NAME
        GROUP BY o.ORDER_NUM;
BEGIN
    FOR LIST_RES IN ORDER_CUR LOOP
        DBMS_OUTPUT.PUT_LINE('Order Number: ' || LIST_RES.ORDER_NUM || ',     Total Amount: ' || LIST_RES.TOTAL_AMOUNT);
    END LOOP;

EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('No orders found for the customer: ' || P_CUST_NAME);
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('An error occurred: ' || SQLERRM);
END;

BEGIN
    GET_ORDERS_LIST_FOR_CUSTOMER('JCP Inc.'); 
END;

-- 2.	Создайте функцию, которая подсчитывает количество заказов покупателя за определенный период. 
--		Параметры – покупатель, дата начала периода, дата окончания периода.

CREATE OR REPLACE FUNCTION getCountOfOrdersForPeriod(P_COMPANY IN varchar2, startDate in date, endDate IN date) RETURN NUMBER IS 
v_count_of_orders NUMBER;
BEGIN
	IF startDate > endDate THEN
	dbms_output.put_line('Start date is higher then end date');
	RETURN 0;
	elsif startDate IS NULL OR endDate IS NULL THEN 
	dbms_output.put_line('Start date or end date is null');
	RETURN 0;
	ELSIF startDate < to_date('2000-01-01', 'YYYY-MM-DD') OR endDate < to_date('2000-01-01', 'YYYY-MM-DD') THEN 
	dbms_output.put_line('Date can not be earlier then "2000-01-01"');
	RETURN 0;
	ELSE 
	SELECT count(*) INTO v_count_of_orders FROM ORDERS INNER JOIN CUSTOMERS ON ORDERS.CUST = CUSTOMERS.CUST_NUM WHERE
	CUSTOMERS.COMPANY = P_COMPANY AND ORDER_DATE BETWEEN startDate AND endDate;
	RETURN v_count_of_orders;
	END IF;
	EXCEPTION 
	WHEN OTHERS THEN 
	dbms_output.put_line('An error occured ' || sqlerrm);
RETURN -1;
END;

DECLARE
	v_count_of_orders NUMBER;
BEGIN
	v_count_of_orders := getCountOfOrdersForPeriod('JCP Inc.', TO_DATE('1999-01-01', 'YYYY-MM-DD'), TO_DATE('2008-02-20', 'YYYY-MM-DD'));
	dbms_output.put_line('Количество заказов покупателя: ' || v_count_of_orders);
END;

-- 3.	Создайте процедуру, которая выводит список всех товаров, приобретенных покупателем, с указанием суммы продаж по возрастанию. 
--		Параметр – наименование покупателя. Обработайте возможные ошибки.

CREATE OR REPLACE PROCEDURE getAllCustomerProducts(P_COMPANY VARCHAR2) IS
v_count integer;
BEGIN 
	SELECT count(*) INTO v_count FROM CUSTOMERS WHERE COMPANY = P_COMPANY;
	IF v_count = 0 THEN 
	dbms_output.put_line('No products for company ' || P_COMPANY);
	ELSE 
	dbms_output.put_line('A list of orders for customer ' || P_COMPANY || ': ');
	FOR rec IN (SELECT * FROM ORDERS INNER JOIN CUSTOMERS ON ORDERS.CUST = CUSTOMERS.CUST_NUM WHERE COMPANY = P_COMPANY ORDER BY ORDERS.AMOUNT ASC) LOOP
		dbms_output.put_line('Order number: ' || rec.ORDER_NUM || ', ' || 'amount: ' || rec.AMOUNT || '.');
	END LOOP;
END IF;
	EXCEPTION 
	WHEN NO_DATA_FOUND THEN 
	dbms_output.put_line('No products found for customer ' || P_COMPANY);
	WHEN OTHERS THEN
	dbms_output.put_line('An error occured: ' || sqlerrm);
END;

BEGIN
	getAllCustomerProducts('JCP Inc.');
END;

-- 4.	Создайте функцию, которая добавляет покупателя в таблицу Customers, и возвращает код добавленного покупателя или -1 в случае ошибки. 
--		Параметры соответствуют столбцам таблицы, кроме кода покупателя, который задается при помощи последовательности.

CREATE OR SEQUENCE addCustomerSequence START WITH 2125 INCREMENT BY 1 nominvalue nomaxvalue nocycle;

CREATE OR REPLACE FUNCTION addCustomer (P_COMPANY IN varchar2, P_CUST_REP IN INTEGER, P_CREDIT_LIMIT IN DECIMAL) RETURN integer IS 
P_CUST_NUM INTEGER;
BEGIN 
	IF P_CREDIT_LIMIT <= 0 THEN 
	dbms_output.put_line('Credit limit must be a positive number');
	RETURN -1;
	ELSIF  P_CUST_REP <= 0 OR P_CUST_REP != TRUNC(P_CUST_REP) THEN
	dbms_output.put_line('Number of client must be a positive integer');
	RETURN -1;
	ELSE
	SELECT addCustomerSequence.nextval into P_CUST_NUM FROM dual;
	INSERT INTO CUSTOMERS(CUST_NUM, COMPANY, CUST_REP, CREDIT_LIMIT) VALUES (P_CUST_NUM, P_COMPANY, P_CUST_REP, P_CREDIT_LIMIT);
	RETURN P_CUST_NUM;
	END IF;
	EXCEPTION 
	WHEN OTHERS THEN 
	dbms_output.put_line('An error occured: ' || sqlerrm);
	RETURN -1;
END;

SELECT * FROM USER_SEQUENCES WHERE SEQUENCE_NAME = 'ADDCUSTOMERSEQUENCE';
SELECT * FROM user_errors WHERE name = 'ADDCUSTOMER' AND TYPE = 'FUNCTION';
SELECT * FROM customers;

DECLARE 
	v_count integer;
BEGIN
	v_count := addCustomer('test_company', 109.2, 9280.23);
	dbms_output.put_line(v_count);
END;

SELECT * FROM Customers ORDER BY CUST_NUM asc;

-- 5.	Создайте процедуру, которая выводит список покупателей, в порядке убывания общей стоимости заказов. 
--		Параметры – дата начала периода, дата окончания периода. Обработайте возможные ошибки.

CREATE OR replace PROCEDURE getListOfCustomers(startDate IN DATE, endDate IN date) as
BEGIN
	IF startDate > endDate THEN
	dbms_output.put_line('Start date is higher then end date');
	ELSIF startDate < to_date('1999-01-01', 'YYYY-MM-DD') OR endDate < to_date('1999-01-01', 'YYYY-MM-DD') THEN 
	dbms_output.put_line('Start date and end date must bu higher then 1999-01-01');
	ELSIF startDate IS NULL OR endDate IS NULL THEN 
	dbms_output.put_line('End date and start date must not be null');
	ELSE 
	dbms_output.put_line('Customers:');
	FOR rec IN (SELECT * FROM ORDERS INNER JOIN CUSTOMERS ON ORDERS.CUST = CUSTOMERS.CUST_NUM WHERE ORDER_DATE BETWEEN startDate AND endDate 
	ORDER BY amount DESC) LOOP 
		dbms_output.put_line('Customer: ' || rec.Company || '. Order date: ' || rec.ORDER_DATE || '. Amount: ' || rec.AMOUNT || '.');
	END LOOP;
	END IF;
	EXCEPTION
	WHEN no_data_found THEN
	dbms_output.put_line('No customers for specified period');
	WHEN OTHERS THEN
	dbms_output.put_line('An error occured: ' || sqlerrm);
END;

BEGIN
getListOfCustomers(TO_DATE('2007-12-17', 'YYYY-MM-DD'), TO_DATE('2008-01-11', 'YYYY-MM-DD'));
END;

SELECT * FROM user_errors WHERE name = 'getListOfCustomers' AND TYPE = 'PROCEDURE';

SELECT * FROM CUSTOMERS;
SELECT * FROM ORDERS

-- 6.	Создайте функцию, которая подсчитывает количество заказанных товаров за определенный период. 
--		Параметры – дата начала периода, дата окончания периода.

CREATE OR REPLACE FUNCTION getCountOfOrdersForPeriod (startDate IN DATE, endDate IN date) RETURN NUMBER IS
v_count_of_orders NUMBER;
BEGIN
	IF startDate > endDate THEN
	dbms_output.put_line('Start date is higher then end date');
	RETURN -1;
	ELSE 
	SELECT count(*) INTO v_count_of_orders FROM ORDERS WHERE ORDER_DATE BETWEEN startDate AND endDate;
	RETURN v_count_of_orders;
	END IF;
EXCEPTION
WHEN OTHERS THEN 
dbms_output.put_line('An error occured ' || sqlerrm);
END;

DECLARE
v_count_of_orders NUMBER;
BEGIN 
	v_count_of_orders := getCountOfOrdersForPeriod(TO_DATE('2007-12-17', 'YYYY-MM-DD'), TO_DATE('2008-01-11', 'YYYY-MM-DD'));
	dbms_output.put_line('Count of orders: ' || v_count_of_orders);
END;

SELECT * FROM ORDERS;

-- 7.	Создайте процедуру, которая выводит список покупателей, у которых есть заказы в этом временном периоде. 
--		Параметры – дата начала периода, дата окончания периода. Обработайте возможные ошибки

CREATE OR REPLACE PROCEDURE getAListOfCustomers (startDate IN DATE, endDate IN DATE) IS 
BEGIN 
	IF startDate > endDate THEN 
	dbms_output.put_line('Start date is higher then end date.');
	ELSE 
	dbms_output.put_line('Customers:');
	FOR rec IN (SELECT DISTINCT (COMPANY) FROM ORDERS INNER JOIN CUSTOMERS ON ORDERS.CUST = CUSTOMERS.CUST_NUM WHERE ORDER_DATE BETWEEN 
	startDate AND endDate) LOOP
		dbms_output.put_line(rec.COMPANY);
	END LOOP;
	END IF;
EXCEPTION
WHEN no_data_found THEN 
dbms_output.put_line('No customers found for period');
WHEN others THEN 
dbms_output.put_line('An error occured: ' || sqlerrm || '.');
END;

SELECT * FROM user_errors WHERE name = 'getAListOfCustomers' AND TYPE = 'PROCEDURE';

BEGIN
	getAListOfCustomers(TO_DATE('2007-12-17', 'YYYY-MM-DD'), TO_DATE('2008-02-02', 'YYYY-MM-DD'));
END;


SELECT * FROM CUSTOMERS;
SELECT * FROM ORDERS;


-- 8.	Создайте функцию, которая подсчитывает количество покупателей определенного товара. 
--		Параметры – наименование товара.

	CREATE OR REPLACE FUNCTION getCountOfCustomersOfOrder (P_DESCRIPTION IN VARCHAR2) RETURN number IS 
	v_count_of_customers NUMBER;
	BEGIN
		SELECT count(DISTINCT orders.CUST) INTO v_count_of_customers FROM orders INNER JOIN products ON orders.PRODUCT = products.PRODUCT_ID 
	WHERE DESCRIPTION = P_DESCRIPTION;
		RETURN v_count_of_customers;
	EXCEPTION
	WHEN OTHERS THEN
	dbms_output.put_line('An error occured ' || sqlerrm);
	END;

	CREATE OR REPLACE FUNCTION getCountOfCustomersOfOrder (P_DESCRIPTION IN VARCHAR2) RETURN number IS 
	v_count_of_customers NUMBER;
	v_product_number NUMBER; 
	BEGIN 
		SELECT count(*) INTO v_product_number FROM PRODUCTS WHERE DESCRIPTION = P_DESCRIPTION;
		IF v_product_number = 0 then
		RETURN -1;
		ELSE 
		SELECT count(DISTINCT orders.CUST) INTO v_count_of_customers FROM orders INNER JOIN products ON orders.PRODUCT = products.PRODUCT_ID
	WHERE DESCRIPTION = P_DESCRIPTION;
		RETURN v_count_of_customers;
	END IF;
	EXCEPTION
	WHEN OTHERS THEN
	dbms_output.put_line('An error occured ' || sqlerrm);
	END;
	
	DECLARE
	v_count_of_customers NUMBER;
	BEGIN
		v_count_of_customers := getCountOfCustomersOfOrder ('Reducer');
		dbms_output.put_line(v_count_of_customers);
	END;

SELECT * FROM ORDERS;
SELECT * FROM PRODUCTS;

SELECT * FROM orders;
SELECT * FROM products;

SELECT count(DISTINCT orders.CUST) FROM orders INNER JOIN products ON orders.PRODUCT = products.PRODUCT_ID WHERE DESCRIPTION = 'Reducer';
SELECT * FROM orders INNER JOIN products ON orders.PRODUCT = products.PRODUCT_ID WHERE DESCRIPTION = 'Reducer'; 

-- 9.	Создайте процедуру, которая увеличивает на 10% стоимость определенного товара. 
--		Параметр – наименование товара. Обработайте возможные ошибки

CREATE OR REPLACE PROCEDURE increaseCost (P_DESCRIPTION IN VARCHAR2) AS 
	p_price PRODUCTS.PRICE%TYPE;
    v_products_count integer;
BEGIN 
	SELECT COUNT(*) INTO v_products_count FROM PRODUCTS WHERE DESCRIPTION = P_DESCRIPTION;
	IF v_products_count = 0 THEN
	dbms_output.put_line('No products with description ' || P_DESCRIPTION);
	ELSE 
	SELECT PRICE INTO p_price FROM PRODUCTS WHERE DESCRIPTION = P_DESCRIPTION;
	dbms_output.put_line('Old price: ' || p_price);
	p_price := p_price * 1.1;
	dbms_output.put_line('New price: ' || p_price);
	UPDATE PRODUCTS SET PRICE = p_price WHERE DESCRIPTION = P_DESCRIPTION;
	END IF;
EXCEPTION 
	WHEN no_data_found THEN
		dbms_output.put_line('No products found with description "' || P_DESCRIPTION || '"');
	WHEN OTHERS THEN 
	dbms_output.put_line('An error occured: ' || sqlerrm);
END increaseCost;

SELECT * FROM user_errors WHERE name = 'increaseCost' AND TYPE = 'PROCEDURE';

BEGIN
	increaseCost('Widget Remover');
END;

SELECT PRICE FROM PRODUCTS WHERE DESCRIPTION = 'Widget Remover';

-- 10.	Создайте функцию, которая вычисляет количество заказов, выполненных в определенном году для определенного покупателя. 
--		Параметры – покупатель, год. товара.

SELECT * FROM ORDERS;
SELECT * FROM CUSTOMERS;

CREATE OR REPLACE FUNCTION getCountOfOrders(P_COMPANY IN varchar2, p_year IN number) RETURN NUMBER
IS 
	v_order_count NUMBER;
BEGIN
	IF p_year != trunc(p_year) OR p_year < 1999 OR p_year > EXTRACT (YEAR FROM sysdate) THEN
	dbms_output.put_line('Incorrect format of year');
	RETURN 0;
	ELSE 
	SELECT count(*) INTO v_order_count FROM ORDERS INNER JOIN CUSTOMERS ON ORDERS.CUST = CUSTOMERS.CUST_NUM WHERE 
	COMPANY = P_COMPANY AND EXTRACT(YEAR FROM ORDER_DATE) = p_year; 
	RETURN v_order_count;
	END IF;
EXCEPTION
	WHEN OTHERS THEN 
	dbms_output.put_line('An error occured ' || sqlerrm);
RETURN -1;
END;

DECLARE
v_order_count NUMBER;
BEGIN
	v_order_count := getCountOfOrders('JCP Inc.', 2008);
	dbms_output.put_line(v_order_count);
END;

SELECT * FROM user_errors WHERE name = 'getCountOfOrders' AND TYPE = 'FUNCTION';



