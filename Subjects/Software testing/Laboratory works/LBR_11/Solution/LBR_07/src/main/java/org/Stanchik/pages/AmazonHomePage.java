package org.Stanchik.pages;

import org.openqa.selenium.*;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.time.Duration;
import java.util.Arrays;
import java.util.List;

public class AmazonHomePage {
    private WebDriver driver;
    private WebDriverWait webDriverWait;

    public AmazonHomePage (WebDriver webDriver) {
        this.driver = webDriver;
        this.webDriverWait = new WebDriverWait(webDriver, Duration.ofSeconds(10));
    }

    private List<String> keywords = Arrays.asList(
            "electronics",
            "smartphone",
            "phone",
            "android",
            "motorola",
            "samsung",
            "camera"
    );

    private By searchBox = By.id("twotabsearchtextbox");
    private By productSelector = By.cssSelector("span.a-size-medium");
    private By colorOption = By.id("color_name_0");
    private By addToCartButton = By.id("add-to-cart-button");
    private By categoryDropdown = By.id("nav-search-dropdown-card");
    private By electronicsOption = By.xpath("//option[text()='Electronics']");
    private By searchBut = By.id("nav-search-submit-button");
    private By searchResult = By.cssSelector(".s-main-slot .s-result-item");

    public void openHomePage() {
        driver.get("https://www.amazon.com");
    }

    public void printCookies() {
        for (Cookie cookie : driver.manage().getCookies()) {
            System.out.println("Cookie: " + cookie);
        }
    }

    public void searchProduct(String productName) {
        WebElement searchField = webDriverWait.until(ExpectedConditions.visibilityOfElementLocated(searchBox));
        searchField.sendKeys(productName);
        searchField.submit();
    }

    public void selectProduct() {
        WebElement product = webDriverWait.until(ExpectedConditions.elementToBeClickable(productSelector));
        product.click();
    }

    public void selectProductColorIfAvailable() {
        try {
            WebElement colorOptionElement = webDriverWait.until(ExpectedConditions.visibilityOfElementLocated(colorOption));
            colorOptionElement.click();
            System.out.println("Цвет продукта выбран.");
        } catch (TimeoutException e) {
            System.out.println("Опции цвета продукта не найдены, продолжаем...");
        }
    }

    public void addToCart() {
        try {
            WebElement addToCart = webDriverWait.until(ExpectedConditions.elementToBeClickable(addToCartButton));
            addToCart.click();
            System.out.println("Продукт добавлен в корзину.");
        } catch (TimeoutException e) {
            System.out.println("Кнопка 'Add to Cart' не найдена.");
        }
    }

    public void openCart() {
        driver.get("https://www.amazon.com/gp/cart/view.html?ref_=nav_cart"); //TODO: тут просто переход по ссылке, это не совсем соответствует заданию
    }

    public void checkProductsForCategory(String device) {
        WebElement category = webDriverWait.until(ExpectedConditions.visibilityOfElementLocated(categoryDropdown));
        category.click();

        WebElement electronics = driver.findElement(electronicsOption );
        electronics.click();

        WebElement search = driver.findElement(searchBox);
        search.sendKeys(device);

        WebElement searchButton = driver.findElement(searchBut);
        searchButton.click();

        List<WebElement> searchResults = webDriverWait.until(ExpectedConditions.visibilityOfAllElementsLocatedBy(searchResult));

        for (WebElement result : searchResults) {
            String categoryText = result.getText().toLowerCase();

            if (categoryText.contains("bought in past month") || categoryText.contains("$")) {
                boolean isElectronics = keywords.stream().anyMatch(categoryText::contains);
                if (isElectronics) {
                    System.out.println("Товар принадлежит категории 'Электроника': " + result.getText());
                }
                else {
                    System.out.println("Товар не принадлежит категории 'Электроника': " + result.getText());
                }
            }
        }
    }
}
