ALTER PLUGGABLE DATABASE NEV_PDB OPEN;
SET SERVEROUTPUT ON;

alter session set NLS_DATE_FORMAT='YYYY-MM-DD';
set escape on


-- 1. Создайте процедуру, которая выводит список заказов и их итоговую стоимость
-- для определенного покупателя. Параметр – наименование покупателя. Обработайте
-- возможные ошибки.

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
/

EXECUTE GET_ORDERS_LIST_FOR_CUSTOMER('JCP Inc.');


-- 2. Создайте функцию, которая подсчитывает количество заказов покупателя
-- за определенный период. Параметры – покупатель, дата начала периода,
-- дата окончания периода.

CREATE OR REPLACE FUNCTION GET_COUNT_ORDERS_FOR_CUSTOMER (
    P_CUST_NAME IN VARCHAR2,
    P_START_DATE IN DATE,
    P_END_DATE IN DATE
) RETURN NUMBER
IS  
    V_ORDER_COUNT NUMBER;
BEGIN
    SELECT COUNT(*)
    INTO V_ORDER_COUNT
    FROM ORDERS o
    JOIN CUSTOMERS c ON o.CUST = c.CUST_NUM
    WHERE c.COMPANY = P_CUST_NAME
        AND o.ORDER_DATE BETWEEN P_START_DATE AND P_END_DATE;
    
    RETURN V_ORDER_COUNT;

EXCEPTION
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('An error occurred: ' || SQLERRM);
        RETURN -1;
END;
/

BEGIN
    DBMS_OUTPUT.PUT_LINE('Count Of Orders:   ' ||
        GET_COUNT_ORDERS_FOR_CUSTOMER(
            'JCP Inc.',
            TO_DATE('2007-09-17', 'YYYY-MM-DD'), 
            TO_DATE('2008-12-17', 'YYYY-MM-DD')
        )
    );
END;


-- 3. Создайте процедуру, которая выводит список всех товаров, приобретенных покупателем,
-- с указанием суммы продаж по возрастанию. Параметр – наименование покупателя.
-- Обработайте возможные ошибки.

CREATE OR REPLACE PROCEDURE GetOrders (p_customer_name IN VARCHAR2)
IS
    v_customer_id CUSTOMERS.CUST_NUM%TYPE;

    CURSOR orders_cursor IS
        SELECT o.ORDER_NUM, o.AMOUNT
        FROM ORDERS o
        WHERE o.CUST = v_customer_id
        ORDER BY o.AMOUNT;
BEGIN
    SELECT CUST_NUM
    INTO v_customer_id
    FROM CUSTOMERS
    WHERE COMPANY = p_customer_name;

    DBMS_OUTPUT.PUT_LINE('Customer: ' || p_customer_name);
    DBMS_OUTPUT.PUT_LINE('His orders: ');

    FOR order_rec IN orders_cursor LOOP
        DBMS_OUTPUT.PUT_LINE('Order Id: ' || order_rec.ORDER_NUM || '; Price: ' || order_rec.AMOUNT);
    END LOOP;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE(-20001, 'Customer ' || p_customer_name || ' not found.');
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('An error occurred: ' || SQLERRM);
END GetOrders;
/

drop procedure GetOrders;

BEGIN
    GetOrders('JCP Inc.');
end;


-- 4. Создайте функцию, которая добавляет покупателя в таблицу Customers,
-- и возвращает код добавленного покупателя или -1 в случае ошибки.
-- Параметры соответствуют столбцам таблицы, кроме кода покупателя,
-- который задается при помощи последовательности.

CREATE SEQUENCE CUST_SEQ
START WITH 2200
INCREMENT BY 10
NOMINVALUE
NOMAXVALUE
NOCYCLE;

CREATE OR REPLACE FUNCTION INSERT_CUSTOMER_BY_SEQ (
    P_COMPANY IN VARCHAR2,
    P_CUST_REP IN INTEGER,
    P_CREDIT_LIMIT IN DECIMAL
) RETURN NUMBER
IS  
    V_CUST_NUM NUMBER;
BEGIN
    SELECT CUST_SEQ.NEXTVAL INTO V_CUST_NUM FROM DUAL;

    INSERT INTO CUSTOMERS (CUST_NUM, COMPANY, CUST_REP, CREDIT_LIMIT)
    VALUES (V_CUST_NUM, P_COMPANY, P_CUST_REP, P_CREDIT_LIMIT);
    
    RETURN V_CUST_NUM;

EXCEPTION
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('An error occurred: ' || SQLERRM);
        RETURN -1;
END;
/

BEGIN
    DBMS_OUTPUT.PUT_LINE('New Costomer Id:   ' ||
        INSERT_CUSTOMER_BY_SEQ('TEST_COMP2', 109, 65000.00)
    );
END;


-- 5. Создайте процедуру, которая выводит список покупателей, в порядке убывания
-- общей стоимости заказов. Параметры – дата начала периода, дата окончания периода.
-- Обработайте возможные ошибки.

CREATE OR REPLACE PROCEDURE GetCustomer (p_start_date IN DATE, p_end_date IN DATE)
IS
    CURSOR order_cursor IS
        SELECT cu.COMPANY, o.AMOUNT, o.ORDER_DATE
        FROM ORDERS o
        INNER JOIN CUSTOMERS cu
        ON cu.CUST_NUM = o.CUST
        WHERE o.ORDER_DATE >= p_start_date 
        AND o.ORDER_DATE <= p_end_date
        ORDER BY o.AMOUNT DESC;
BEGIN
    IF p_end_date < p_start_date THEN
        RAISE_APPLICATION_ERROR(-20002, 'End date cannot be earlier than start date.');
    END IF;

    DBMS_OUTPUT.PUT_LINE('Customers with orders in the specified date range:');

    FOR order_rec IN order_cursor LOOP
        DBMS_OUTPUT.PUT_LINE(
            'Customer name: ' || order_rec.COMPANY || 
            '; Amount: ' || order_rec.AMOUNT || 
            '; Order date: ' || TO_CHAR(order_rec.ORDER_DATE, 'YYYY-YY-DD') || ';'
        );
    END LOOP;

EXCEPTION
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('An error occurred: ' || SQLERRM);
END GetCustomer;
/

BEGIN
    GetCustomer(
        TO_DATE('2007-01-01', 'YYYY-MM-DD'), 
        TO_DATE('2007-12-31', 'YYYY-MM-DD')
    );
END;
/


-- 6. Создайте функцию, которая подсчитывает количество заказанных товаров за
-- определенный период. Параметры – дата начала периода, дата окончания периода.

CREATE OR REPLACE FUNCTION GET_TOTAL_ORDERED_PROD (
    P_START_DATE IN DATE,
    P_END_DATE IN DATE
) RETURN NUMBER
IS
    V_SUM_PROD NUMBER;
BEGIN
    SELECT SUM(QTY)
    INTO V_SUM_PROD
    FROM ORDERS
    WHERE ORDER_DATE BETWEEN P_START_DATE AND P_END_DATE;

    RETURN NVL(V_SUM_PROD, 0);

EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('No data:' || V_SUM_PROD || SQLERRM);
        RETURN -1;
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('ERROR:' || V_SUM_PROD || SQLERRM);
        RETURN -1;
END;
/

DECLARE
    V_TOTAL NUMBER;
BEGIN
    V_TOTAL := GET_TOTAL_ORDERED_PROD(
        TO_DATE('2007-01-01', 'YYYY-MM-DD'),
        TO_DATE('2007-12-31', 'YYYY-MM-DD')
    );
    DBMS_OUTPUT.PUT_LINE('Total ordered products: ' || V_TOTAL);
END;
/


-- 7. Создайте процедуру, которая выводит список покупателей, у которых есть заказы
-- в этом временном периоде. Параметры – дата начала периода, дата окончания периода.
-- Обработайте возможные ошибки

CREATE OR REPLACE PROCEDURE GetCustomer (p_start_date IN DATE, p_end_date IN DATE)
IS
    CURSOR customer_cursor IS
        SELECT cu.COMPANY, o.ORDER_DATE
        FROM CUSTOMERS cu
        INNER JOIN ORDERS o
        ON o.CUST = cu.CUST_NUM
        WHERE o.ORDER_DATE >= p_start_date 
        AND o.ORDER_DATE <= p_end_date;
BEGIN
    DBMS_OUTPUT.PUT_LINE('All customer');

    FOR custom_rec IN customer_cursor LOOP
        DBMS_OUTPUT.PUT_LINE('Cusomer: ' || custom_rec.COMPANY || '; Order date: ' || custom_rec.ORDER_DATE || ';');
    END LOOP;
EXCEPTION
    WHEN others THEN
        DBMS_OUTPUT.PUT_LINE('error: ' || SQLERRM);
END GetCustomer;

BEGIN
    GetCustomer(
        TO_DATE('2007-01-01', 'YYYY-MM-DD'), 
        TO_DATE('2007-12-31', 'YYYY-MM-DD')
        );
END;


-- 8. Создайте функцию, которая подсчитывает количество покупателей определенного
-- товара. Параметры – наименование товара.

CREATE OR REPLACE FUNCTION GET_TOTAL_CUSTOMER_FOR_PROD (
    P_PROD_NAME IN VARCHAR2
) RETURN NUMBER
IS
    V_SUM_CUST NUMBER;
BEGIN
    SELECT COUNT(DISTINCT o.CUST)
    INTO V_SUM_CUST
    FROM ORDERS o
    JOIN PRODUCTS p ON o.MFR = p.MFR_ID AND o.PRODUCT = p.PRODUCT_ID
    WHERE p.DESCRIPTION = P_PROD_NAME;

    RETURN NVL(V_SUM_CUST, 0);

EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('No data:' || V_SUM_CUST || SQLERRM);
        RETURN -1;
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('ERROR:' || V_SUM_CUST || SQLERRM);
        RETURN -1;
END;
/

DECLARE
    V_TOTAL NUMBER;
BEGIN
    V_TOTAL := GET_TOTAL_CUSTOMER_FOR_PROD(
        'Ratchet Link'
    );
    DBMS_OUTPUT.PUT_LINE('Total ordered products: ' || V_TOTAL);
END;
/


-- 9. Создайте процедуру, которая увеличивает на 10% стоимость определенного товара.
-- Параметр – наименование товара. Обработайте возможные ошибки

CREATE OR REPLACE PROCEDURE AddPrice (p_description IN VARCHAR2)
IS
    v_result_price PRODUCTS.PRICE%TYPE; 
BEGIN
    SELECT p.PRICE
    INTO v_result_price
    from PRODUCTS p
    WHERE p.DESCRIPTION = p_description;

    v_result_price := v_result_price + (v_result_price / 10);

    UPDATE PRODUCTS p
    SET p.PRICE = v_result_price
    WHERE p.DESCRIPTION = p_description;

    DBMS_OUTPUT.PUT_LINE('All Correct');
EXCEPTION
    WHEN others THEN
        DBMS_OUTPUT.PUT_LINE('error: ' || SQLERRM);
END AddPrice;
/

CREATE OR REPLACE PROCEDURE ShowPrice (p_description IN VARCHAR2)
IS
    v_price orders.AMOUNT%TYPE;
BEGIN
    SELECT p.PRICE
    INTO v_price
    FROM PRODUCTS p
    WHERE p.DESCRIPTION = p_description;
    DBMS_OUTPUT.PUT_LINE('Now price: ' || v_price || ';');
EXCEPTION
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('Not fount');
END ShowPrice;
/

DECLARE
    v_description products.DESCRIPTION%TYPE := 'Widget Remover';
BEGIN
    ShowPrice(v_description);

    AddPrice(v_description);

    ShowPrice(v_description);
END;
/


-- 10. Создайте функцию, которая вычисляет количество заказов, выполненных в
-- определенном году для определенного покупателя. Параметры – покупатель, год. товара.

CREATE OR REPLACE FUNCTION GET_COUNT_OREDRS_YEAR (
    P_CUST_NAME IN VARCHAR2,
    P_YEAR IN NUMBER
) RETURN NUMBER
IS
    V_ORDER_COUNT NUMBER;
BEGIN
    SELECT COUNT(*)
    INTO V_ORDER_COUNT
    FROM ORDERS o
    JOIN CUSTOMERS c ON o.CUST = c.CUST_NUM
    WHERE c.COMPANY = P_CUST_NAME
        AND EXTRACT(YEAR FROM o.ORDER_DATE) = P_YEAR;
     
    RETURN NVL(V_ORDER_COUNT, 0);

EXCEPTION
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('ERROR' || SQLERRM);
        RETURN -1;
END;
/

DECLARE
    V_ORDER_COUNT NUMBER;
BEGIN
    V_ORDER_COUNT := GET_COUNT_OREDRS_YEAR('JCP Inc.', 2007);
    DBMS_OUTPUT.PUT_LINE('Orders in 2007 for customer: ' || V_ORDER_COUNT);
END;
/