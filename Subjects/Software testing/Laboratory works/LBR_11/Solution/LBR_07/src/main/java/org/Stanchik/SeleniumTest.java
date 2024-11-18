package org.Stanchik;

import org.openqa.selenium.*;
import org.openqa.selenium.opera.OperaDriver;
import org.openqa.selenium.opera.OperaOptions;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;

import org.Stanchik.pages.AmazonHomePage;
import org.Stanchik.pages.AmazonSignIn;
import org.Stanchik.pages.DemoqaCheckbox;

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
            System.out.println("5 -- вывести в консоль все куки");

            Scanner scanner = new Scanner(System.in);
            int chooseTest = scanner.nextInt();

            switch (chooseTest) {
                case 1: {
                    AmazonSignIn amazonSignIn = new AmazonSignIn (driver);
                    amazonSignIn.OpenPage();
                    amazonSignIn.AmazonAuthorization("your-email@example.com", "your-password");
                    Thread.sleep(10000);
                    break;
                }
                case 2: {
                    AmazonHomePage productCategoryTest = new AmazonHomePage(driver);
                    productCategoryTest.openHomePage();
                    productCategoryTest.checkProductsForCategory("smartphone");
                    Thread.sleep(10000);

                    break;
                }
                case 3: {
                    AmazonHomePage cartTestPage = new AmazonHomePage(driver);
                    cartTestPage.openHomePage();
                    cartTestPage.searchProduct("Wireless Headphones");
                    cartTestPage.selectProduct();
                    cartTestPage.selectProductColorIfAvailable();
                    cartTestPage.addToCart();
                    cartTestPage.openCart();
                    break;
                }
                case 4: {
                    DemoqaCheckbox checkboxPage = new DemoqaCheckbox(driver);
                    checkboxPage.openPage();
                    checkboxPage.selectHomeCheckBox();
                    Thread.sleep(10000);
                    break;
                }
                case 5: {
                    AmazonHomePage homePage = new AmazonHomePage(driver);
                    homePage.openHomePage();
                    homePage.printCookies();
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
