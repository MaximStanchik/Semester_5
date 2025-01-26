package by.Stanchik;

import java.net.HttpURLConnection;
import java.net.URL;

public class StripeCustomerTests {

    public static void main(String[] args) {

    }
}

    //private HttpURLConnection createConnection(String method, String endpoint) throws Exception {
        //URL url = new URL(endpoint); //создание обекта url, который представляет собой URL-адрес, который передается в качестве параметра endpoint
        //HttpURLConnection connection = (HttpURLConnection) url.openConnection(); // открытие соединения по указанному url. возвращаемый объект позволяет отправлять HTTP-запросы и получать HTTP-ответы
        //connection.setRequestMethod(method); //установка http-метода для соединения
        //connection.setRequestProperty("Authorization", "Bearer " + API_KEY); //установление заголовка Authorization для запроса, тут используется механизм аутентификации Bearer Token, API_KEY -- токен доступа
        //connection.setRequestProperty("Content-Type", "application/x-www-form-urlencoded"); //установление заголовка Content-Type
        //return connection; //возврат настроенного соединения HttpURLConnection
    //}

    // Метод для получения ответа от HTTP-соединения
    //private String getResponse(HttpURLConnection connection) throws Exception {
        // Создаем BufferedReader для чтения входного потока данных
        //BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
        //StringBuilder response = new StringBuilder(); // Строка для хранения ответа
        //String inputLine;

        // Читаем ответ построчно
        //while ((inputLine = in.readLine()) != null) {
            //response.append(inputLine); // Добавляем каждую строку к ответу
        //}
        //in.close(); // Закрываем поток
        //return response.toString(); // Возвращаем ответ как строку
    //}

    // Создание пользователя с минимально необходимыми данными
    //@Test
    //public void testCreateCustomerValid() throws Exception {
        // Устанавливаем соединение с указанием метода POST и базового URL
        //HttpURLConnection connection = createConnection("POST", BASE_URL);
        //connection.setDoOutput(true); // Разрешаем отправку данных в теле запроса

        // Данные для создания пользователя
        //String data = "email=test_user@example.com&description=Test user creation";

        // Используем DataOutputStream для записи данных в поток
        //try (DataOutputStream wr = new DataOutputStream(connection.getOutputStream())) {
            //wr.writeBytes(data); // Записываем данные
            //wr.flush(); // Сбрасываем поток
        //}

        // Проверяем, что код ответа 200 (Успех)
        //assertEquals(200, connection.getResponseCode());
    //}

    // Создание пользователя с корректно заполненными всеми полями
    //@Test
    //public void testCreateCustomerWithAllFields() throws Exception {
        //HttpURLConnection connection = createConnection("POST", BASE_URL);
        //connection.setDoOutput(true);
        //String data = "email=full_user@example.com&description=Full user creation&metadata[key]=value";
        //try (DataOutputStream wr = new DataOutputStream(connection.getOutputStream())) {
          //  wr.writeBytes(data);
            //wr.flush();
        //}
        // Проверяем, что код ответа 200 (Успех)
        //assertEquals(200, connection.getResponseCode());
    //}

    // Отправка запроса без обязательных полей
    //@Test
    //public void testCreateCustomerMissingRequiredFields() throws Exception {
        //HttpURLConnection connection = createConnection("POST", BASE_URL);
        //connection.setDoOutput(true);
        //String data = "emailll=test_user@example.com&descriptionnnn=Test user creation"; // Неверные поля
        //try (DataOutputStream wr = new DataOutputStream(connection.getOutputStream())) {
          //  wr.writeBytes(data);
            //wr.flush();
        //}
        // Проверяем, что код ответа 400 (Ошибка запроса)
        //assertEquals(400, connection.getResponseCode());
    //}

    // Использование невалидного email
   // @Test
    //public void testCreateCustomerInvalidEmail() throws Exception {
      //  HttpURLConnection connection = createConnection("POST", BASE_URL);
       // connection.setDoOutput(true);
        //String data = "email=invalid-email&description=Invalid email test"; // Неверный формат email
        //try (DataOutputStream wr = new DataOutputStream(connection.getOutputStream())) {
          //  wr.writeBytes(data);
            //wr.flush();
       // }
        // Проверяем, что код ответа 400 (Ошибка запроса)
        //assertEquals(400, connection.getResponseCode());
    //}

    // Интеграционное тестирование методов CRUD
  //  private String userId; // Переменная для хранения ID пользователя

    //// Подготовка теста: создание пользователя перед тестами
 //   @Before
  //  public void setUp() throws Exception {
  //      testCreateUsers(); // Создание нового пользователя
 //   }

    // Создание нового пользователя через POST /users
  //  @Test
   // public void testCreateUsers() throws Exception {
     //   HttpURLConnection connection = createConnection("POST", BASE_URL);
      //  connection.setDoOutput(true);
       // String userData = "email=new_user@example.com"; // Данные нового пользователя
        //try (DataOutputStream wr = new DataOutputStream(connection.getOutputStream())) {
         //   wr.writeBytes(userData);
           // wr.flush();
        //}

        //int responseCode = connection.getResponseCode(); // Получаем код ответа
        //assertEquals(200, responseCode); // Проверяем, что код ответа 200 (Успех)

        //String response = getResponse(connection); // Получаем ответ
        //System.out.println("Response: " + response); // Выводим ответ для отладки

        //JSONObject jsonResponse = new JSONObject(response); // Парсим ответ в JSON
        //if (jsonResponse.has("id")) { // Проверяем наличие ID пользователя
          //  userId = jsonResponse.getString("id"); // Сохраняем ID
            //System.out.println("Created User ID: " + userId); // Выводим ID для отладки
       // } else {
         //   fail("Response does not contain user ID: " + response); // Проверка на наличие ID
        //}
    //}

    // Получаем созданного пользователя через GET /users/{id}
    //@Test
    //public void testReadUsers() throws Exception {
      //  System.out.println("User ID: " + userId); // Выводим ID пользователя
       // assertNotNull("User ID should not be null", userId); // Проверяем, что ID не null

       // HttpURLConnection connection = createConnection("GET", BASE_URL + "/" + userId); // Создаем GET-запрос
      //  assertEquals(200, connection.getResponseCode()); // Проверяем код ответа

      //  String response = getResponse(connection); // Получаем ответ
     //   JSONObject jsonResponse = new JSONObject(response); // Парсим ответ в JSON

     //   assertEquals("new_user@example.com", jsonResponse.getString("email")); // Проверяем email
   // }

    // Обновляем данные пользователя через PUT /users/{id}
  //  @Test
  //  public void testUpdateUsers() throws Exception {
  //      HttpURLConnection connection = createConnection("POST", BASE_URL + "/" + userId); // Создаем POST-запрос
  //      connection.setDoOutput(true);
 //       String updatedData = "email=update_user@example.com"; // Данные для обновления
 //       try (DataOutputStream wr = new DataOutputStream(connection.getOutputStream())) {
  //          wr.writeBytes(updatedData);
  //          wr.flush();
 //       }
   //     assertEquals(200, connection.getResponseCode()); // Проверяем код ответа
   // }

    // Удаляем пользователя через DELETE /users/{id}
   // @Test
 //   public void testDeleteUsers() throws Exception {
 //       HttpURLConnection connection = createConnection("DELETE", BASE_URL + "/" + userId); // Создаем DELETE-запрос
 //       assertEquals(200, connection.getResponseCode()); // Проверяем код ответа
//    }

    // Тестирование обработки ошибок
// Пустое тело запроса
  //  @Test
  //  public void testEmptyRequestBody() throws Exception {
  //      HttpURLConnection connection = createConnection("POST", BASE_URL); // Создаем POST-запрос
  //      connection.setDoOutput(true);
  //      assertEquals(200, connection.getResponseCode()); // Проверяем код ответа (Ожидается 200)
 //   }

    // Неверный формат данных
  //  @Test
 //   public void testInvalidDataFormat() throws Exception {
  //      HttpURLConnection connection = createConnection("POST", BASE_URL);
  //      connection.setDoOutput(true);
 //       String jsonData = "email=123231&description=1231231"; // Неверный формат данных
  //      try (DataOutputStream wr = new DataOutputStream(connection.getOutputStream())) {
  //          wr.writeBytes(jsonData);
  //          wr.flush();
  //      }
   //     assertEquals(400, connection.getResponseCode()); // Проверяем код ответа (Ожидается 400)
   // }

    // Запрос к несуществующей конечной точке
//    @Test
//    public void testNonexistentEndpoint() throws Exception {
 //       HttpURLConnection connection = createConnection("GET", BASE_URL + "/nonexistent"); // Запрос к несуществующему URL
  //      assertEquals(404, connection.getResponseCode()); // Проверяем код ответа (Ожидается 404)
  ///  }

    // Тестирование прав доступа
// Отправка запроса без токена
  //  @Test
  //  public void testAccessWithoutToken() throws Exception {
 //       URL url = new URL(BASE_URL); // Создаем URL
 //       HttpURLConnection connection = (HttpURLConnection) url.openConnection(); // Открываем соединение
 //       connection.setRequestMethod("GET"); // Устанавливаем метод GET
   //     assertEquals(401, connection.getResponseCode()); // Проверяем код ответа (Ожидается 401)
  //  }

    // Отправка запроса с некорректным токеном
  //  @Test
  //  public void testAccessWithInvalidToken() throws Exception {
  //      HttpURLConnection connection = createConnection("GET", BASE_URL); // Создаем GET-запрос
   //     connection.setRequestProperty("Authorization", "Bearer invalid_token"); // Устанавливаем некорректный токен
   //     assertEquals(401, connection.getResponseCode()); // Проверяем код ответа (Ожидается 401)
  //  }

    // Тестирование валидации данных
// Слишком длинное значение в поле
 //   @Test
  //  public void testInvalidLongString() throws Exception {
  //      HttpURLConnection connection = createConnection("POST", BASE_URL);
  //      connection.setDoOutput(true);
   ///     String data = "email=" + "a".repeat(1000) + "@example.com"; // Слишком длинный email
   //     try (DataOutputStream wr = new DataOutputStream(connection.getOutputStream())) {
   //         wr.writeBytes(data);
   ///         wr.flush();
   //     }
  //     assertEquals(400, connection.getResponseCode()); // Проверяем код ответа (Ожидается 400)
  //  }

    // Число вне допустимого диапазона
  //  @Test
   // public void testAgeOutOfRange() throws Exception {
     //   HttpURLConnection connection = createConnection("POST", BASE_URL);
       // connection.setDoOutput(true);
        //String data = "email=test_user@example.com&age=150"; // Неверное значение возраста
        //try (DataOutputStream wr = new DataOutputStream(connection.getOutputStream())) {
         //   wr.writeBytes(data);
          //  wr.flush();
        //}
        //assertEquals(400, connection.getResponseCode()); // Проверяем код ответа (Ожидается 400)
   // }

    // Пропущено обязательное поле
    //@Test
    //public void testRequiredFieldMissing() throws Exception {
     //   HttpURLConnection connection = createConnection("POST", BASE_URL);
       // connection.setDoOutput(true);
        //connection.setRequestProperty("Authorization", "Bearer"); // Отсутствует токен
        //assertEquals(401, connection.getResponseCode()); // Проверяем код ответа (Ожидается 401)
   // }

    // Тестирование пагинации
    //@Test
    //public void testPagination() throws Exception {
      //  HttpURLConnection connection = createConnection("GET", ART_URL + "?limit=5"); // Запрос с параметром limit
        //assertEquals(200, connection.getResponseCode()); // Проверяем код ответа (Ожидается 200)
        //String response = getResponse(connection); // Получаем ответ
        //JSONObject jsonResponse = new JSONObject(response); // Парсим ответ в JSON
        //assertNotNull("Response should not be null", jsonResponse); // Проверяем, что ответ не null

        //if (jsonResponse.has("data")) {
          //  assertTrue("Data array should not be empty", json
