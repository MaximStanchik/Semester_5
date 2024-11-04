create or replace PROCEDURE system.REGISTER_USER(
    p_login IN VARCHAR2,
    p_password IN VARCHAR2,
    p_user_id OUT NUMBER,
    p_user_login OUT VARCHAR2
) AS
    v_user_count NUMBER;
begin

    SELECT COUNT(*)
    INTO v_user_count
    FROM App_User
    WHERE LOGIN = p_login;

    IF v_user_count > 0 THEN
        RAISE_APPLICATION_ERROR(-20001, 'User already exists');
    END IF;

    IF LENGTH(p_login) < 3 OR LENGTH(p_password) < 6 THEN
        RAISE_APPLICATION_ERROR(-20002, 'Login or password are not valid');
    END IF;

    INSERT INTO App_User (LOGIN, PASSWORD)
    VALUES (p_login, p_password)
    RETURNING ID, LOGIN INTO p_user_id, p_user_login;
END;
/
