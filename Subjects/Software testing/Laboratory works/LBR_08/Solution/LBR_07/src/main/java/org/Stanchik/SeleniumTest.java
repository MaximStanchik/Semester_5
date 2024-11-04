package org.Stanchik;

import org.openqa.selenium.*;
import org.openqa.selenium.opera.OperaDriver;
import org.openqa.selenium.opera.OperaOptions;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.time.Duration;
import java.util.List;
import java.util.Scanner;

public class SeleniumTest
{
    public static void main( String[] args )
    {
        System.setProperty("webdriver.opera.driver", "D:/OperaDriver/operadriver_win64/operadriver.exe");
        OperaOptions options = new OperaOptions();
        options.setBinary("C:/Users/User/AppData/Local/Programs/Opera/opera.exe");
        options.addArguments("user-agent=Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3");
        WebDriver driver = new OperaDriver(options);

        try {
            WebDriverWait wait = new WebDriverWait(driver, Duration.ofSeconds(10));

            System.out.println("Выберите тест:");
            System.out.println("1 -- тестировние авторизации на сайте Amazon");
            System.out.println("2 -- тестировние тест-кейса, где проверяется, что все найденные товары принадлежат категории 'Электроника'");
            System.out.println("3 -- тестировние тест-кейса, где проверяется функциональность добавления в корзину");
            System.out.println("4 -- тестировние чекбокса на сайте 'https://demoqa.com/checkbox'");

            Scanner scanner = new Scanner(System.in);
            int chooseTest = scanner.nextInt();

            switch (chooseTest) {
                case 1: {
                    driver.get("https://www.amazon.com/ap/signin?openid.pape.max_auth_age=0&openid.return_to=https%3A%2F%2Fwww.amazon.com%2F%3Fref_%3Dnav_signin&openid.identity=http%3A%2F%2Fspecs.openid.net%2Fauth%2F2.0%2Fidentifier_select&openid.assoc_handle=usflex&openid.mode=checkid_setup&openid.claimed_id=http%3A%2F%2Fspecs.openid.net%2Fauth%2F2.0%2Fidentifier_select&openid.ns=http%3A%2F%2Fspecs.openid.net%2Fauth%2F2.0");

                    WebElement emailField = wait.until(ExpectedConditions.visibilityOfElementLocated(By.id("ap_email")));
                    emailField.sendKeys("your-email@example.com");

                    WebElement continueButton = driver.findElement(By.id("continue"));
                    continueButton.click();

                    WebElement passwordField = wait.until(ExpectedConditions.visibilityOfElementLocated(By.id("ap_password")));
                    passwordField.sendKeys("your-password");

                    WebElement signInButton = driver.findElement(By.id("signInSubmit"));
                    signInButton.click();

                    Thread.sleep(10000);

                    break;
                }
                case 2: {
                    driver.get("https://www.amazon.com");

                    WebElement categoryDropdown = wait.until(ExpectedConditions.visibilityOfElementLocated(By.id("nav-search-dropdown-card")));
                    categoryDropdown.click();
                    WebElement electronicsOption = driver.findElement(By.xpath("//option[text()='Electronics']"));
                    electronicsOption.click();

                    WebElement searchBox = driver.findElement(By.id("twotabsearchtextbox"));
                    searchBox.sendKeys("smartphone");

                    WebElement searchButton = driver.findElement(By.id("nav-search-submit-button"));
                    searchButton.click();

                    List<WebElement> searchResults = wait.until(ExpectedConditions.visibilityOfAllElementsLocatedBy(By.cssSelector(".s-main-slot .s-result-item")));
                    for (WebElement result : searchResults) {
                        String categoryText = result.getText();
                        if (!categoryText.contains("Electronics")) {
                            System.out.println("Товар не принадлежит категории 'Электроника': " + result.getText());
                        }
                        else {
                            System.out.println("Товар принадлежит категории 'Электроника'");
                        }
                    }

                    break;
                }
                case 3: {
                    driver.get("https://www.amazon.com");

                    WebElement searchBox = wait.until(ExpectedConditions.visibilityOfElementLocated(By.id("twotabsearchtextbox")));
                    searchBox.sendKeys("Wireless Headphones");
                    searchBox.submit();

                    WebElement product = wait.until(ExpectedConditions.elementToBeClickable(By.cssSelector("span.a-size-medium")));
                    product.click();

                    try {
                        WebElement colorOption = wait.until(ExpectedConditions.visibilityOfElementLocated(By.id("color_name_0")));
                        colorOption.click();
                    }
                    catch (TimeoutException e) {
                        System.out.println("Опции продукта не найдены, продолжаем...");
                    }

                    try {
                        WebElement addToCartButton = wait.until(ExpectedConditions.elementToBeClickable(By.id("add-to-cart-button")));
                        addToCartButton.click();
                    }
                    catch (TimeoutException e) {
                        System.out.println("Кнопка 'Add to Cart' не найдена.");
                    }

                    driver.get("https://www.amazon.com/gp/cart/view.html?ref_=nav_cart");
                    break;
                }
                case 4: {
                    driver.get("https://demoqa.com/checkbox");
                    driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(10));
                    WebElement homeCheckbox = driver.findElement(By.cssSelector("label[for='tree-node-home']"));

                    if (!homeCheckbox.isSelected()) {
                        homeCheckbox.click();
                    }
                    System.out.println("Checkbox был выбран: " + homeCheckbox.isSelected());
                    System.out.println("Checkbox теперь выбран");

                    Thread.sleep(20000);
                    break;
                }
                default: {
                    System.out.println("Неправильно введены данные");
                    break;
                }
            }
        }
        catch(Exception e) {
            e.printStackTrace();
        }
        finally {
            driver.quit();
        }
    };
}
