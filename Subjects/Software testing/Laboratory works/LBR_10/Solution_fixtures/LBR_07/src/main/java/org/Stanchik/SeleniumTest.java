package org.Stanchik;

import com.aventstack.extentreports.ExtentReports;
import com.aventstack.extentreports.ExtentTest;
import com.aventstack.extentreports.reporter.ExtentHtmlReporter;
import org.junit.jupiter.api.*;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import org.openqa.selenium.*;
import org.openqa.selenium.opera.OperaDriver;
import org.openqa.selenium.opera.OperaOptions;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.time.Duration;
import java.util.List;
import java.util.stream.Stream;

public class SeleniumTest {

    private static WebDriver driver;
    private static WebDriverWait wait;
    private static ExtentReports extent;
    private ExtentTest test;

    @BeforeAll
    public static void setupClass() {
        System.setProperty("webdriver.opera.driver", "D:/OperaDriver/operadriver_win64/operadriver.exe");

        ExtentHtmlReporter htmlReporter = new ExtentHtmlReporter("reports/test-report.html");
        extent = new ExtentReports();
        extent.attachReporter(htmlReporter);
    }

    @BeforeEach
    public void setupTest() {
        OperaOptions options = new OperaOptions();
        options.setBinary("C:/Users/User/AppData/Local/Programs/Opera/opera.exe");
        options.addArguments("user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3");
        driver = new OperaDriver(options);
        wait = new WebDriverWait(driver, Duration.ofSeconds(10));
    }

    @AfterEach
    public void tearDown() {
        if (driver != null) {
            driver.quit();
        }
        extent.flush();
    }

    @Test
    @Tag("auth")
    public void testAmazonAuthorization() throws InterruptedException {
        test = extent.createTest("Тест авторизации на Amazon");
        try {
            driver.get("https://www.amazon.com/ap/signin?openid.pape.max_auth_age=0&openid.return_to=https%3A%2F%2Fwww.amazon.com%2F%3Fref_%3Dnav_signin&openid.identity=http%3A%2F%2Fspecs.openid.net%2Fauth%2F2.0%2Fidentifier_select&openid.assoc_handle=usflex&openid.mode=checkid_setup&openid.claimed_id=http%3A%2F%2Fspecs.openid.net%2Fauth%2F2.0%2Fidentifier_select&openid.ns=http%3A%2F%2Fspecs.openid.net%2Fauth%2F2.0");

            wait.until(ExpectedConditions.presenceOfElementLocated(By.id("ap_email")));
            WebElement emailField = wait.until(ExpectedConditions.visibilityOfElementLocated(By.id("ap_email")));
            emailField.sendKeys("your-email@example.com");

            WebElement continueButton = driver.findElement(By.id("continue"));
            continueButton.click();

            WebElement passwordField = wait.until(ExpectedConditions.visibilityOfElementLocated(By.id("ap_password")));
            passwordField.sendKeys("your-password");

            WebElement signInButton = driver.findElement(By.id("signInSubmit"));
            signInButton.click();

            Thread.sleep(10000);
            test.pass("Авторизация прошла успешно.");
        } catch (Exception e) {
            test.fail("Ошибка при авторизации: " + e.getMessage());
        }
    }

    static Stream<Arguments> provideSearchData() {
        return Stream.of(
                Arguments.of("smartphone"),
                Arguments.of("tablet"),
                Arguments.of("laptop")
        );
    }

    @ParameterizedTest
    @Tag("category")
    @MethodSource("provideSearchData")
    public void testElectronicsCategory(String searchTerm) {
        test = extent.createTest("Тест поиска в категории электроника с термином: " + searchTerm);
        try {
            driver.get("https://www.amazon.com");
            WebElement categoryDropdown = wait.until(ExpectedConditions.visibilityOfElementLocated(By.id("nav-search-dropdown-card")));
            categoryDropdown.click();
            WebElement electronicsOption = driver.findElement(By.xpath("//option[text()='Electronics']"));
            electronicsOption.click();

            WebElement searchBox = driver.findElement(By.id("twotabsearchtextbox"));
            searchBox.sendKeys(searchTerm);
            WebElement searchButton = driver.findElement(By.id("nav-search-submit-button"));
            searchButton.click();

            List<WebElement> searchResults = wait.until(ExpectedConditions.visibilityOfAllElementsLocatedBy(By.cssSelector(".s-main-slot .s-result-item")));

            for (WebElement result : searchResults) {
                String categoryText = result.getText().toLowerCase();

                if (categoryText.contains("bought in past month") || categoryText.contains("$")) {
                    if (categoryText.contains("electronics") ||
                            categoryText.contains(searchTerm) ||
                            categoryText.contains("phone") ||
                            categoryText.contains("android") ||
                            categoryText.contains("motorola") ||
                            categoryText.contains("samsung") ||
                            categoryText.contains("camera")) {
                        test.info("Товар принадлежит категории 'Электроника': " + result.getText());
                    } else {
                        test.warning("Товар не принадлежит категории 'Электроника': " + result.getText());
                    }
                }
            }
            test.pass("Тест поиска в категории электроника завершен.");
        } catch (Exception e) {
            test.fail("Ошибка при поиске в категории электроника: " + e.getMessage());
        }
    }

    @Test
    @Tag("cart")
    @Disabled("Этот тест временно отключен")
    public void testAddToCart() {
        test = extent.createTest("Тест добавления в корзину");
        try {
            driver.get("https://www.amazon.com");

            WebElement searchBox = wait.until(ExpectedConditions.visibilityOfElementLocated(By.id("twotabsearchtextbox")));
            searchBox.sendKeys("Wireless Headphones");
            searchBox.submit();

            WebElement product = wait.until(ExpectedConditions.elementToBeClickable(By.cssSelector("span.a-size-medium")));
            product.click();

            try {
                WebElement colorOption = wait.until(ExpectedConditions.visibilityOfElementLocated(By.id("color_name_0")));
                colorOption.click();
            } catch (TimeoutException e) {
                test.warning("Опции продукта не найдены, продолжаем...");
            }

            try {
                WebElement addToCartButton = wait.until(ExpectedConditions.elementToBeClickable(By.id("add-to-cart-button")));
                addToCartButton.click();
            } catch (TimeoutException e) {
                test.warning("Кнопка 'Add to Cart' не найдена.");
            }

            driver.get("https://www.amazon.com/gp/cart/view.html?ref_=nav_cart");
            test.pass("Тест добавления в корзину завершен.");
        } catch (Exception e) {
            test.fail("Ошибка при добавлении в корзину: " + e.getMessage());
        }
    }

    @Test
    @Tag("checkbox")
    @Disabled("Этот тест временно отключен")
    public void testCheckbox() throws InterruptedException {
        test = extent.createTest("Тест чекбокса");
        try {
            driver.get("https://demoqa.com/checkbox");
            driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(10));
            WebElement homeCheckbox = driver.findElement(By.cssSelector("label[for='tree-node-home']"));

            if (!homeCheckbox.isSelected()) {
                homeCheckbox.click();
            }
            test.info("Checkbox был выбран: " + homeCheckbox.isSelected());
            test.pass("Тест чекбокса завершен.");
        } catch (Exception e) {
            test.fail("Ошибка при тестировании чекбокса: " + e.getMessage());
        }
    }

    @Test
    @Tag("cookies")
    public void testPrintCookies() {
        test = extent.createTest("Тест печати куки");
        try {
            driver.get("https://www.amazon.com");
            for (Cookie cookie : driver.manage().getCookies()) {
                test.info("Cookie: " + cookie);
            }
            test.pass("Тест печати куки завершен.");
        } catch (Exception e) {
            test.fail("Ошибка при печати куки: " + e.getMessage());
        }
    }
}
