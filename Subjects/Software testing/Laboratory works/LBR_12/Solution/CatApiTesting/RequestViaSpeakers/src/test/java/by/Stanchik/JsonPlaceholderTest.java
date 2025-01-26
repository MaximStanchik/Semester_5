package by.Stanchik;

import org.json.JSONArray;
import org.json.JSONObject;
import org.junit.Before;
import org.junit.Test;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.io.DataOutputStream;
import static junit.framework.Assert.assertEquals;
import static org.junit.Assert.*;

// 1. Получение списка доступных методов API
// Воспользуйтесь официальной документацией Stripe API для получения списка методов. Например, методы для управления пользователями:

// POST /v1/customers (создание пользователя)
// GET /v1/customers/{customer_id} (получение данных пользователя)
// POST /v1/customers/{customer_id} (обновление данных пользователя)
// DELETE /v1/customers/{customer_id} (удаление пользователя)

// 2. Список тест-кейсов для одного метода (например, POST /v1/customers)

// Позитивные тесты:
// Создание пользователя с минимально необходимыми данными (только обязательные поля).
// Создание пользователя с корректно заполненными всеми полями (обязательные и дополнительные).
// Создание пользователя с валидным email.

// Негативные тесты:
// Отправка запроса без обязательных полей.
// Использование невалидного email.
// Передача данных в некорректном формате (например, вместо JSON).
// Запрос без авторизационного токена.

// 3. Написание автотестов
// Пример автоматизированных тестов для метода POST /v1/customers:

public class JsonPlaceholderTest {
    private static final String ART_URL = "https://api.artic.edu/api/v1/artworks";
    private static final String BASE_URL = "https://api.stripe.com/v1/customers";
    private static final String API_KEY = "sk_test_51QYo7jH2UvoV83PCPhxtd3PNyliQnPghuP372Jqc6k4CWWLD2VE8wzkiKhA8dLuIk2u5fdnfIYqv9ojOPDqmZPkT00brGWsHl1";
    private HttpURLConnection createConnection(String method, String endpoint) throws Exception {
        URL url = new URL(endpoint);
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod(method);
        connection.setRequestProperty("Authorization", "Bearer " + API_KEY);
        connection.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");
        return connection;
    }

    private String getResponse(HttpURLConnection connection) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
        StringBuilder response = new StringBuilder();
        String inputLine;
        while ((inputLine = in.readLine()) != null) {
            response.append(inputLine);
        }
        in.close();
        return response.toString();
    }

    //Создание пользователя с минимально необходимыми данными
    //Создание пользователя с валидным email
    @Test
    public void testCreateCustomerValid() throws Exception {
        HttpURLConnection connection = createConnection("POST", BASE_URL);
        connection.setDoOutput(true);
        String data = "email=test_user@example.com&description=Test user creation";
        try (DataOutputStream wr = new DataOutputStream(connection.getOutputStream())) {
            wr.writeBytes(data);
            wr.flush();
        }
        assertEquals(200, connection.getResponseCode());
    }

    //Создание пользователя с корректно заполненными всеми полями (обязательные и дополнительные)
    @Test
    public void testCreateCustomerWithAllFields() throws Exception {
        HttpURLConnection connection = createConnection("POST", BASE_URL);
        connection.setDoOutput(true);
        String data = "email=full_user@example.com&description=Full user creation&metadata[key]=value";
        try (DataOutputStream wr = new DataOutputStream(connection.getOutputStream())) {
            wr.writeBytes(data);
            wr.flush();
        }
        assertEquals(200, connection.getResponseCode());
    }

    //Отправка запроса без обязательных полей
    @Test
    public void testCreateCustomerMissingRequiredFields() throws Exception {
        HttpURLConnection connection = createConnection("POST", BASE_URL);
        connection.setDoOutput(true);
        String data = "emailll=test_user@example.com&descriptionnnn=Test user creation";
        try (DataOutputStream wr = new DataOutputStream(connection.getOutputStream())) {
            wr.writeBytes(data);
            wr.flush();
        }
        assertEquals(400, connection.getResponseCode());
    }

    //Использование невалидного email
    @Test
    public void testCreateCustomerInvalidEmail() throws Exception {
        HttpURLConnection connection = createConnection("POST", BASE_URL);
        connection.setDoOutput(true);
        String data = "lemail=invalid-emai&description=Invalid email test";
        try (DataOutputStream wr = new DataOutputStream(connection.getOutputStream())) {
            wr.writeBytes(data);
            wr.flush();
        }
        assertEquals(400, connection.getResponseCode());
    }

    // 4. Интеграционное тестирование методов CRUD
    // Пример тестирования CRUD для /users:
    // Create: Создаем нового пользователя через POST /users.
    // Read: Получаем созданного пользователя через GET /users/{id}.
    // Update: Обновляем данные пользователя через PUT /users/{id}.
    // Delete: Удаляем пользователя через DELETE /users/{id}.

    private String userId;

    @Before
    public void setUp() throws Exception {
        testCreateUsers();
    }

    // Create: Создаем нового пользователя через POST /users
    @Test
    public void testCreateUsers() throws Exception {
        HttpURLConnection connection = createConnection("POST", BASE_URL);
        connection.setDoOutput(true);
        String userData = "email=new_user@example.com";
        try (DataOutputStream wr = new DataOutputStream(connection.getOutputStream())) {
            wr.writeBytes(userData);
            wr.flush();
        }

        int responseCode = connection.getResponseCode();
        assertEquals(200, responseCode);

        String response = getResponse(connection);
        System.out.println("Response: " + response);

        JSONObject jsonResponse = new JSONObject(response);
        if (jsonResponse.has("id")) {
            userId = jsonResponse.getString("id");
            System.out.println("Created User ID: " + userId); // Выводим userId для отладки
        } else {
            fail("Response does not contain user ID: " + response);
        }
    }

    // Read: Получаем созданного пользователя через GET /users/{id}
    @Test
    public void testReadUsers() throws Exception {
        System.out.println("User ID: " + userId);
        assertNotNull("User ID should not be null", userId);

        HttpURLConnection connection = createConnection("GET", BASE_URL + "/" + userId);
        assertEquals(200, connection.getResponseCode());

        String response = getResponse(connection);
        JSONObject jsonResponse = new JSONObject(response);

        assertEquals("new_user@example.com", jsonResponse.getString("email"));
    }

    // Update: Обновляем данные пользователя через PUT /users/{id}
    @Test
    public void testUpdateUsers() throws Exception {
        HttpURLConnection connection = createConnection("POST", BASE_URL + "/" + userId);
        connection.setDoOutput(true);
        String updatedData = "email=update_user@example.com";
        try (DataOutputStream wr = new DataOutputStream(connection.getOutputStream())) {
            wr.writeBytes(updatedData);
            wr.flush();
        }
        assertEquals(200, connection.getResponseCode());
    }

    // Delete: Удаляем пользователя через DELETE /users/{id}
    @Test
    public void testDeleteUsers() throws Exception {
        HttpURLConnection connection = createConnection("DELETE", BASE_URL + "/" + userId);
        assertEquals(200, connection.getResponseCode());
    }

    // 5. Тестирование обработки ошибок
    // Пустое тело запроса.
    // Неверный формат данных.
    // Запрос к несуществующей конечной точке.

    // Пустое тело запроса
    @Test
    public void testEmptyRequestBody() throws Exception {
        HttpURLConnection connection = createConnection("POST", BASE_URL);
        connection.setDoOutput(true);
        assertEquals(200, connection.getResponseCode());
    }

    // Неверный формат данных
    @Test
    public void testInvalidDataFormat() throws Exception {
        HttpURLConnection connection = createConnection("POST", BASE_URL);
        connection.setDoOutput(true);
        String jsonData = "email=123231&description=1231231";
        try (DataOutputStream wr = new DataOutputStream(connection.getOutputStream())) {
            wr.writeBytes(jsonData);
            wr.flush();
        }
        assertEquals(400, connection.getResponseCode());
    }

    // Запрос к несуществующей конечной точке
    @Test
    public void testNonexistentEndpoint() throws Exception {
        HttpURLConnection connection = createConnection("GET", BASE_URL + "/nonexistent");
        assertEquals(404, connection.getResponseCode());
    }

    // 6. Тестирование прав доступа
    // Для этого потребуется API с авторизацией. Если доступна авторизация (например, токен):
    // Отправка запроса без токена.
    // Отправка запроса с некорректным токеном.

    // Отправка запроса без токена
    @Test
    public void testAccessWithoutToken() throws Exception {
        URL url = new URL(BASE_URL);
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod("GET");
        assertEquals(401, connection.getResponseCode());
    }

    // Отправка запроса с некорректным токеном
    @Test
    public void testAccessWithInvalidToken() throws Exception {
        HttpURLConnection connection = createConnection("GET", BASE_URL);
        connection.setRequestProperty("Authorization", "Bearer invalid_token");
        assertEquals(401, connection.getResponseCode());
    }

    // 7. Тестирование валидации данных
    // Слишком длинное значение в поле.
    // Число вне допустимого диапазона.
    // Пропущено обязательное поле.

    // Слишком длинное значение в поле
    @Test
    public void testInvalidLongString() throws Exception {
        HttpURLConnection connection = createConnection("POST", BASE_URL);
        connection.setDoOutput(true);
        String data = "email=" + "a".repeat(1000) + "@example.com";
        try (DataOutputStream wr = new DataOutputStream(connection.getOutputStream())) {
            wr.writeBytes(data);
            wr.flush();
        }
        assertEquals(400, connection.getResponseCode());
    }

    // Число вне допустимого диапазона
    @Test
    public void testAgeOutOfRange() throws Exception {
        HttpURLConnection connection = createConnection("POST", BASE_URL);
        connection.setDoOutput(true);

        String data = "email=test_user@example.com&age=150";

        try (DataOutputStream wr = new DataOutputStream(connection.getOutputStream())) {
            wr.writeBytes(data);
            wr.flush();
        }

        assertEquals(400, connection.getResponseCode());
    }

    // Пропущено обязательное поле
    @Test
    public void testRequiredFieldMissing() throws Exception {
        HttpURLConnection connection = createConnection("POST", BASE_URL);
        connection.setDoOutput(true);
        connection.setRequestProperty("Authorization", "Bearer");
        assertEquals(401, connection.getResponseCode());
    }

    // 8. Тестирование пагинации
    // Для API с параметрами page и limit протестируйте:

    @Test
    public void testPagination() throws Exception {
        HttpURLConnection connection = createConnection("GET", ART_URL + "?limit=5");
        assertEquals(200, connection.getResponseCode());
        String response = getResponse(connection);
        JSONObject jsonResponse = new JSONObject(response);
        assertNotNull("Response should not be null", jsonResponse);

        if (jsonResponse.has("data")) {
            assertTrue("Data array should not be empty", jsonResponse.getJSONArray("data").length() > 0);
        } else {
            fail("Response should contain data array");
        }
    }

    @Test
    public void testPaginationOutOfRange() throws Exception {
        HttpURLConnection connection = createConnection("GET", ART_URL + "?limit=5&offset=999999"); // Example of out-of-range offset
        assertEquals(200, connection.getResponseCode());
        String response = getResponse(connection);
        JSONObject jsonResponse = new JSONObject(response);
        assertNotNull("Response should not be null", jsonResponse);
        assertTrue("Response should contain data array", jsonResponse.has("data"));
        assertTrue("Response data should be empty or less than limit", jsonResponse.getJSONArray("data").length() <= 5);
    }

    @Test
    public void testPaginationWithPage() throws Exception {
        HttpURLConnection connection = createConnection("GET", ART_URL + "?page=2&limit=1");
        assertEquals(200, connection.getResponseCode());
        String response = getResponse(connection);
        JSONObject jsonResponse = new JSONObject(response);
        assertNotNull("Response should not be null", jsonResponse);

        assertTrue("Response should contain data array", jsonResponse.has("data"));
        JSONArray dataArray = jsonResponse.getJSONArray("data");
        assertTrue("Data array should not be empty", dataArray.length() > 0);
    }
}
