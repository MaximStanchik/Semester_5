package org.Stanchik;

import org.openqa.selenium.*;
import org.openqa.selenium.opera.OperaDriver;
import org.openqa.selenium.opera.OperaOptions;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.time.Duration;
import java.util.List;

public class SeleniumTest
{

    public static void main( String[] args )
    {
        System.setProperty("webdriver.opera.driver", "D:/OperaDriver/operadriver_win64/operadriver.exe");
        OperaOptions options = new OperaOptions();
        options.setBinary("C:/Users/User/AppData/Local/Programs/Opera/opera.exe");
        WebDriver driver = new OperaDriver(options);

        try {
            driver.get("https://habr.com/ru/articles/152653/");

            findElementsByCss(driver, "div.tm-comment-thread__comment:nth-child(2) div.tm-comment__body-content"); //не получается
            findElementsByCss(driver, "p");
            findElementsByCss(driver, "body");
            findElementsByCss(driver, "article.tm-comment-thread__comment"); //не получается

            findElementsByXPath(driver, "//input[@type='text']");
            findElementsByXPath(driver, "//ul/li");
            findElementsByXPath(driver, "(//p)[1]");

            findElementsByTag(driver, "h3");

            findElementsByPartialLinkText(driver, "Все вакансии");

            checkSecondComment(driver);

        }
        catch(Exception e) {
            e.printStackTrace();
        }
        finally {
            driver.quit();
        }
    };

    private static void findElementsByCss(WebDriver driver, String css) {
        try {
            List<WebElement> elements = driver.findElements(By.cssSelector(css));
            System.out.println("Найдено элементов с CSS-селектором " + css + ": " + elements.size());
        }
        catch (NoSuchElementException e) {
            System.out.println("Элемент не найден по CSS-селектору " + css);
        }
    };

    private static void findElementsByXPath(WebDriver driver, String xpath) {
        try {
            List<WebElement> elements = driver.findElements(By.xpath(xpath));
            System.out.println("Найдено элементов с указанным XPath " + xpath + ": " + elements.size());
        }
        catch (NoSuchElementException e) {
            System.out.println("Элемент не найден по XPath " + xpath);
        }
    };

    private static void findElementsByTag(WebDriver driver, String tag) {
        try {
            List<WebElement> elements = driver.findElements(By.tagName(tag));
            System.out.println("Найдено элементов с указанным тегом " + tag + ": " + elements.size());
        }
        catch (NoSuchElementException e) {
            System.out.println("Элемент не найден по тегу " + tag);
        }
    };

    private static void findElementsByPartialLinkText(WebDriver driver, String partialLinkText) {
        try {
            List<WebElement> elements = driver.findElements(By.partialLinkText(partialLinkText));
            System.out.println("Найдено элементов по частичному тексту ссылки " + partialLinkText + ":" + elements.size());
        }
        catch (NoSuchElementException e) {
            System.out.println("Элемент не найден по частичному тексту ссылки " + partialLinkText);
        }
    };

    private static void checkSecondComment(WebDriver driver) { // не получается
        WebDriverWait wait = new WebDriverWait(driver, Duration.ofSeconds(10));
        try {
            List<WebElement> comments = wait.until(ExpectedConditions.presenceOfAllElementsLocatedBy(By.xpath("//div[contains(@class, 'tm-comment')]")));

            if (comments.size() < 2) {
                System.out.println("Недостаточно комментариев.");
                return;
            }

            WebElement secondComment = comments.get(1);
            System.out.println("Второй комментарий: " + secondComment.getText());

        } catch (TimeoutException e) {
            System.out.println("Комментарии не найдены или время ожидания истекло.");
        }
    }
}
